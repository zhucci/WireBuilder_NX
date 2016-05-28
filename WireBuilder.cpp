
#include "WireBuilder.h"
// Главный класс управляющий созданием проволоки, и получающий указания от GUI

WireBuilder::WireBuilder()
{

		theSession = Session::GetSession();
		workPart= theSession->Parts()->Work();
		displayPart= theSession->Parts()->Display();
//Значения переменных для трубы по умолчанию, если вдруг в UI не будет задано никакого числа
		DiameterOfTube=0.8; 
		DiameterAsString="0.8";
		NXObject *nullNXObject(NULL);
		this->SolideTube=nullNXObject;
		cartesianCoordinateSystem=NULL;
		isSpline3=false;
		tangent=1.2;
		LengthOut="30";
		WidthOut="7";
		PitchHelix="1.4";
		DiameterHelix="1.2";
		LengthHelix="10";

		

}

int WireBuilder::AddPlaceForWire(Face * choiceCylinder){

	Hole* newHole = new Hole(workPart, choiceCylinder);
	holes.push_back(newHole);
	int size = holes.size();
	if(size>1)
	AddTraceBetweenHoles(size-1,size);
		return 0;
}
int WireBuilder::AddTraceBetweenHoles(int FS, int LS){
		 try{

			NXObject *nullNXObject(NULL);
			//Создание встроенной сущность сплайна и передача его конструктору производного класса
			StudioSplineBuild *newSpline = new StudioSplineBuild(
																	*(workPart->Features()->CreateStudioSplineBuilderEx(nullNXObject))
																);
			bool RevFS=holes[FS-1]->isRevDir();
			
			if(FS>1)
				RevFS=!RevFS;

					AllSplineInWire.insert(
												AllSplineInWire.begin()+FS-1, //указатель куда записываем

												newSpline->SetStudioSplineBuild  //ссылка на что записываем
												(
												holes[FS-1]->GetVirtualLine(),
												RevFS,
												holes[LS-1]->GetVirtualLine(),
												holes[LS-1]->isRevDir(),
												this->tangent,
												this->isSpline3)			
										);

				delete newSpline;
	}

	catch(NXException &ex){

		UI *theUI = UI::GetUI();
		theUI->NXMessageBox()->Show("Error handler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
return 0;
}

 int WireBuilder::AddStudioSplineToWire(bool isfirst,size_t inPlace) 
 {
 }

 int WireBuilder::DeleteSpline(int number)
 {
	try{
		
		theSession->UpdateManager()->AddToDeleteList(AllSplineInWire[number-1]->GetEntities());
		std::vector<Features::Feature*>::iterator pointer;
		pointer=AllSplineInWire.begin()+number-1;

		AllSplineInWire.erase(pointer);

		
	}

catch(NXException &ex)
	{
		UI *theUI = UI::GetUI();
		theUI->NXMessageBox()->Show("Error handler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}

	 return 0;
}

 int WireBuilder::ReverseWire(int NumberOfHole){
	 	 try{
		 
			 holes[NumberOfHole-1]->ReverseDirection();

			 if(NumberOfHole-1>0)
					ReverseSplineWithNumber(NumberOfHole-1);
			
			 if(holes.size()>NumberOfHole)
					ReverseSplineWithNumber(NumberOfHole);
		
	}
	catch(NXException &ex){

			UI *theUI = UI::GetUI();
			theUI->NXMessageBox()->Show("ReverseWire", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	 return 0;
 }

 int WireBuilder::ReverseSplineWithNumber(int number){
	 try{
		
		 DeleteSpline(number);
		 AddTraceBetweenHoles(number, number+1);

	}
	catch(NXException &ex){

			UI *theUI = UI::GetUI();
			theUI->NXMessageBox()->Show("Delete spline with number", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}
	 return 0;

 }

Point *WireBuilder::GetOriginalPoint(){
	try{
		
			Scalar *scalar;
			scalar = workPart->Scalars()->CreateScalar(0.5, Scalar::DimensionalityTypeNone, SmartObject::UpdateOptionWithinModeling);
			Point *point1, *point2;
			size_t size=holes.size()-1;
			std::vector<NXObject *> obj1=this->holes[0]->GetVirtualLine()->GetEntities();
			std::vector<NXObject *> obj2=this->holes[size]->GetVirtualLine()->GetEntities();


			if(!holes[0]->isRevDir())
			point1=workPart->Points()->CreatePoint((dynamic_cast<Line*>(obj1[0]))->StartPoint());
		else
			point1=workPart->Points()->CreatePoint((dynamic_cast<Line*>(obj1[0]))->EndPoint());

			if(!holes[size]->isRevDir())
			point2=workPart->Points()->CreatePoint((dynamic_cast<Line*>(obj2[0]))->StartPoint());
		else
			point2=workPart->Points()->CreatePoint((dynamic_cast<Line*>(obj2[0]))->EndPoint());

		
	return workPart->Points()->CreatePoint( point1, point2, scalar, SmartObject::UpdateOptionWithinModeling);	
		}
			catch(NXException &ex){
				UI *theUI = UI::GetUI();
				theUI->NXMessageBox()->Show("Error handler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
			}
}


 int WireBuilder::SetCartesianCoordinateSystem(CartesianCoordinateSystem *coord){

	cartesianCoordinateSystem=coord;

	return 0;
 }

int  WireBuilder::CreateCartesianCoordinateSystem(CartesianCoordinateSystem *coord){
    
	std::vector<NXObject *> objects1(1);
    
	this->cartesianCoordinateSystem->SetVisibility(SmartObject::VisibilityOptionInvisible); 
	
	objects1[0] = cartesianCoordinateSystem;
	
	theSession->UpdateManager()->AddToDeleteList(objects1); // Удаление предылущей версии траектории поволоки
	
	cartesianCoordinateSystem=coord;

    Features::Feature *nullFeatures_Feature(NULL);
    
    Features::DatumCsysBuilder *datumCsysBuilder1;
    datumCsysBuilder1 = workPart->Features()->CreateDatumCsysBuilder(nullFeatures_Feature);

    
    datumCsysBuilder1->SetCsys(coord);
    
    datumCsysBuilder1->SetDisplayScaleFactor(1.0);
	
    NXObject *nXObject;
    nXObject = datumCsysBuilder1->Commit();
	

	return 0;

}

CartesianCoordinateSystem * WireBuilder::CreateCartesianCoordinateSystem(Point* originPoint, Line* helpLine, Line* normalLine){

    Features::Feature *nullFeatures_Feature(NULL);

    
    Features::DatumCsysBuilder *datumCsysBuilder1;
    datumCsysBuilder1 = workPart->Features()->CreateDatumCsysBuilder(nullFeatures_Feature);
    
	 
    Direction *Zdirection;
   Zdirection = workPart->Directions()->CreateDirection(normalLine, SenseForward, SmartObject::UpdateOptionWithinModeling);
 
     Direction *Ydirection;
    Ydirection = workPart->Directions()->CreateDirection(helpLine, SenseForward, SmartObject::UpdateOptionWithinModeling);

  
    Xform *xform;
    xform = workPart->Xforms()->CreateXformByPointYDirZDir(originPoint, Ydirection, Zdirection, SmartObject::UpdateOptionWithinModeling, 1.0);
	    if(!xform)
		throw NXException::Create("Lol xform5 is NULL");

    cartesianCoordinateSystem = workPart->CoordinateSystems()->CreateCoordinateSystem(xform, SmartObject::UpdateOptionWithinModeling);

    
    datumCsysBuilder1->SetCsys(cartesianCoordinateSystem);
    
    datumCsysBuilder1->SetDisplayScaleFactor(1.25);

	this->cartesianCoordinateSystemTag=datumCsysBuilder1->Tag();
    
    NXObject *nXObject;
    nXObject = datumCsysBuilder1->Commit();
	NXString string = nXObject->JournalIdentifier();

	return cartesianCoordinateSystem;

}

Line *WireBuilder::CreateLine(Features::Feature* feature1,Features::Feature* feature2)
{
	
  try
{
		std::vector<NXObject *> obj1=feature1->GetEntities();
		std::vector<NXObject *> obj2=feature2->GetEntities();
	Point *point1, *point2;
	size_t size=holes.size()-1;

		if(!holes[0]->isRevDir())
			point1=workPart->Points()->CreatePoint((dynamic_cast<Line*>(obj1[0]))->StartPoint());
		else
			point1=workPart->Points()->CreatePoint((dynamic_cast<Line*>(obj1[0]))->EndPoint());

		if(!holes[size]->isRevDir())
			point2=workPart->Points()->CreatePoint((dynamic_cast<Line*>(obj2[0]))->StartPoint());
		else
			point2=workPart->Points()->CreatePoint((dynamic_cast<Line*>(obj2[0]))->EndPoint());



	return workPart->Curves()->CreateLine(point1,point2);
		}
		catch(NXException &ex)
		{
			UI *theUI = UI::GetUI();
			theUI->NXMessageBox()->Show("Error handler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
		}

}

int WireBuilder::AddHelixToWire()
{

      Features::Helix *nullFeatures_Helix(NULL);

	Point *originPoint=GetOriginalPoint();
	size_t size=holes.size()-1;

	std::vector<NXObject *> obj2=holes[size]->GetVirtualLine()->GetEntities();

		Line *helpLine=this->CreateLine(holes[0]->GetVirtualLine(),holes[size]->GetVirtualLine());

		if(!cartesianCoordinateSystem)
		cartesianCoordinateSystem = CreateCartesianCoordinateSystem(originPoint, helpLine, dynamic_cast<Line*>(obj2[0]));
		
		 HelixInWire helixBuilder1(
			 0.0,
			cartesianCoordinateSystem,
			 *(workPart->Features()->CreateHelixBuilder(nullFeatures_Helix)),
			 LengthHelix,
			 DiameterHelix,
			 PitchHelix
			 );

		  HelixInWire helixBuilder2(
			 180.0,
			 cartesianCoordinateSystem,
			 *(workPart->Features()->CreateHelixBuilder(nullFeatures_Helix)),
			 LengthHelix,
			 DiameterHelix,
			 PitchHelix
			 );

	  this->AllHelixInWire.push_back(helixBuilder1.GetFeature());
	  this->AllHelixInWire.push_back(helixBuilder2.GetFeature());

	   NXObject *nullNXObject(NULL);

					StudioSplineBuild *newSpline1 = new StudioSplineBuild(*(workPart->Features()->CreateStudioSplineBuilderEx(nullNXObject)));

					AllBridgeInWire.push_back(
							newSpline1->SetStudioSplineBuild(
									holes[0]->GetVirtualLine(),
									!holes[0]->isRevDir(),
									helixBuilder1.GetFeature(),
									false,
									tangent,
									isSpline3
							)
			
					);
					delete newSpline1;
					newSpline1=NULL;


			StudioSplineBuild *newSpline2 = new StudioSplineBuild(*(workPart->Features()->CreateStudioSplineBuilderEx(nullNXObject)));

					AllBridgeInWire.push_back(
							newSpline2->SetStudioSplineBuild(
									holes[size]->GetVirtualLine(),
									!holes[size]->isRevDir(),
									helixBuilder2.GetFeature(),
									false,
									tangent,
									isSpline3
							)
			
					);
					delete newSpline2;
					newSpline2=NULL;


	return 0;
}

int WireBuilder::DeleteHelixFromWire(){

	
				size_t valueHelix=this->AllHelixInWire.size();
				std::vector<NXObject*> objectForDelete;
			
					for(int i=0;i<valueHelix;i++){

					//	AllHelixInWire[i]->HideBody();
						objectForDelete.push_back(dynamic_cast<NXObject*>(AllHelixInWire[i]));
					}

					size_t valueOfBridges=this->AllBridgeInWire.size();

					for(int i=0;i<valueOfBridges;i++)
						objectForDelete.push_back(dynamic_cast<NXObject*>(AllBridgeInWire[i]));
				
					AllHelixInWire.clear();
					AllBridgeInWire.clear();

					theSession->UpdateManager()->AddToDeleteList(objectForDelete);
				
					return 0;
		}

int WireBuilder::DeleteHoleFromWire(int number)
{
	try{
		
		bool isEndOfWire=false;
	if(number==1){
		if(this->AllSplineInWire.size()>0)
		DeleteSpline(number);
		isEndOfWire=true;
	}
	else if(number==holes.size()){
		DeleteSpline(number-1);
		isEndOfWire=true;
	}
	else{
		DeleteSpline(number);
		DeleteSpline(number-1);
	}

		holes[number-1]->UnHighLightFace();
		theSession->UpdateManager()->AddToDeleteList(holes[number-1]->GetVirtualLine()->GetEntities());
		
			std::vector<Hole *>::iterator pointer;
			pointer=holes.begin()+number-1;
			holes.erase(pointer);

		if(holes.size()>1 && !isEndOfWire )
			AddTraceBetweenHoles(number-1,number);
		//theSession->UpdateManager()->DoUpdate(Session::UndoMarkId::UndoMarkIdDummyMember);
		return 0;
	}
	catch(NXException &ex)
		{
			UI *theUI = UI::GetUI();
			theUI->NXMessageBox()->Show("Error handler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
			return 1;
		}
}

int WireBuilder::HighLightHole(int number)
{
	int size=holes.size();
	if(number<size+1){
		for(int i=0;i<size;i++)
			holes[i]->UnHighLightFace();

	holes[number-1]->HighLightFace();
	}
	return 0;
}

int WireBuilder::AddNewHoleBelow(Face *choiceCylinder,int number)
{

	DeleteSpline(number);

	Hole* newHole = new Hole(workPart, choiceCylinder);
	holes.insert(holes.begin()+number,newHole);
	
	
	AddTraceBetweenHoles(number, number+1);
	AddTraceBetweenHoles(number+1,number+2);
	
	return 0;
}

int WireBuilder::CreateSweepOnSpline(){

	try{
	
	Features::Feature *nullFeatures_Feature(NULL);
    Features::TubeBuilder *tubeBuilder1;

    tubeBuilder1 = workPart->Features()->CreateTubeBuilder(nullFeatures_Feature);
    tubeBuilder1->SetTolerance(0.1);
	
   
	tubeBuilder1->OuterDiameter()->SetRightHandSide(DiameterAsString);
    
    tubeBuilder1->InnerDiameter()->SetRightHandSide("0");
    
    tubeBuilder1->BooleanOption()->SetType(GeometricUtilities::BooleanOperation::BooleanTypeCreate);

    
    tubeBuilder1->SetOutputOption(Features::TubeBuilder::OutputSingleSegment);
    
    tubeBuilder1->PathSection()->SetDistanceTolerance(0.1);
    
    tubeBuilder1->PathSection()->SetChainingTolerance(0.1);
    
    tubeBuilder1->PathSection()->SetAllowedEntityTypes(Section::AllowTypesOnlyCurves);
	
	std::vector<SelectionIntentRule *> rules;
 
	  if(!AllSplineInWire.empty())
      rules.push_back(workPart->ScRuleFactory()->CreateRuleCurveFeature(AllSplineInWire));
	 
	  if(!AllHelixInWire.empty())
	  rules.push_back(workPart->ScRuleFactory()->CreateRuleCurveFeature(AllHelixInWire));
	  
	  std::vector<Features::Feature *> allvirtualcurve;
	  if(!holes.empty()){
		
		  for(int i=0;i<holes.size();i++){
			  allvirtualcurve.push_back(holes[i]->GetVirtualLine());
		  }
		  rules.push_back(workPart->ScRuleFactory()->CreateRuleCurveFeature(allvirtualcurve));
		  }
	  if(!AllBridgeInWire.empty()){
		  rules.push_back(workPart->ScRuleFactory()->CreateRuleCurveFeature(AllBridgeInWire));
	  }
	

    tubeBuilder1->PathSection()->AllowSelfIntersection(true);

    NXObject *nullNXObject(NULL);

	Point* helpPoint1 = workPart->Points()->CreatePoint(dynamic_cast<Line *>((holes[0]->GetVirtualLine()->GetEntities())[0])->StartPoint());
	
	tubeBuilder1->PathSection()->AddToSection(rules, nullNXObject, nullNXObject, nullNXObject, helpPoint1->Coordinates(), Section::ModeCreate, false);
    
	if(tubeBuilder1->Validate())
	SolideTube=tubeBuilder1->Commit();

	}
	catch(NXException &ex){
			UI *theUI = UI::GetUI();
			theUI->NXMessageBox()->Show("Error handler in WireBuilder", NXOpen::NXMessageBox::DialogTypeError, ex.what());		
	}
	return 0;
}

int WireBuilder::DeleteTube(){
try{
	
		
	    theSession->UpdateManager()->AddToDeleteList(SolideTube);
		theSession->UpdateManager()->DoUpdate(Session::UndoMarkId::UndoMarkIdDummyMember);
		NXObject *nullNXObject(NULL);
		SolideTube=nullNXObject;
		
		return 0;
	}

catch(NXException &ex)
	{
		UI *theUI = UI::GetUI();
		theUI->NXMessageBox()->Show("Error handler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
		return 1;
	}


	
}
WireBuilder::~WireBuilder(){

}