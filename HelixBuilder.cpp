#include"HelixBuilder.h"

HelixInWire::~HelixInWire(){
	this->Destroy();
}


//Метод задает все параметры спирали
int HelixInWire::SetHelixInWire(
	Point* originPoint,
	Line* helpLine,
	Line* normalLine,
	double startAngle,
	CartesianCoordinateSystem *coordsys)

{
	
	try{
 
	 Session *theSession = Session::GetSession();
    Part *workPart(theSession->Parts()->Work());
    Part *displayPart(theSession->Parts()->Display());
	
    
    this->SetOrientationOption(Features::HelixBuilder::OrientationOptionsSpecified);
    
    this->Spine()->SetDistanceTolerance(0.001);
    
    this->Spine()->SetChainingTolerance(0.001);
    
    this->SizeLaw()->AlongSpineData()->Spine()->SetDistanceTolerance(0.001);
    
    this->SizeLaw()->AlongSpineData()->Spine()->SetChainingTolerance(0.001);
    
    this->SizeLaw()->LawCurve()->SetDistanceTolerance(0.001);
    
    this->SizeLaw()->LawCurve()->SetChainingTolerance(0.001);
    
    this->PitchLaw()->AlongSpineData()->Spine()->SetDistanceTolerance(0.001);
    
    this->PitchLaw()->AlongSpineData()->Spine()->SetChainingTolerance(0.001);
    
    this->PitchLaw()->LawCurve()->SetDistanceTolerance(0.001);
    
    this->PitchLaw()->LawCurve()->SetChainingTolerance(0.001);
    
    this->Spine()->SetAngleTolerance(0.01);
    
    this->SizeLaw()->AlongSpineData()->Spine()->SetAngleTolerance(0.01);
    
    this->SizeLaw()->LawCurve()->SetAngleTolerance(0.01);
    
    this->PitchLaw()->AlongSpineData()->Spine()->SetAngleTolerance(0.01);
    
    this->PitchLaw()->LawCurve()->SetAngleTolerance(0.01);
    
    this->StartLimit()->SetPercentUsed(false);

	this->SetSizeOption(Features::HelixBuilder::SizeOptionsDiameter);
    
    this->StartLimit()->Expression()->SetRightHandSide("0");
    
    this->EndLimit()->SetPercentUsed(false);
    
    this->EndLimit()->Expression()->SetRightHandSide("10");
    
	 std::ostringstream RHS;
	
	 RHS<<startAngle;
   
    this->StartAngle()->SetRightHandSide(RHS.str());
    
   
    Direction *Zdirection;
   Zdirection = workPart->Directions()->CreateDirection(normalLine, SenseForward, SmartObject::UpdateOptionWithinModeling);
 
     Direction *Ydirection;
    Ydirection = workPart->Directions()->CreateDirection(helpLine, SenseForward, SmartObject::UpdateOptionWithinModeling);

  
    Xform *xform5;
    xform5 = workPart->Xforms()->CreateXformByPointYDirZDir(originPoint, Ydirection, Zdirection, SmartObject::UpdateOptionWithinModeling, 1.0);
    if(xform5==NULL)
		throw NXException::Create("Lol xform5 is NULL");

    if(coordsys==NULL)
    cartesianCoordinateSystem = workPart->CoordinateSystems()->CreateCoordinateSystem(xform5, SmartObject::UpdateOptionWithinModeling);
	else
	 cartesianCoordinateSystem = coordsys;

	   
    Features::Feature *nullFeatures_Feature(NULL);

    
    Features::DatumCsysBuilder *datumCsysBuilder1;
    datumCsysBuilder1 = workPart->Features()->CreateDatumCsysBuilder(nullFeatures_Feature);

	datumCsysBuilder1->SetCsys(cartesianCoordinateSystem);
    
    datumCsysBuilder1->SetDisplayScaleFactor(1.25);
    
    NXObject *nXObject;
    nXObject = datumCsysBuilder1->Commit();

    this->SetCoordinateSystem(cartesianCoordinateSystem);
	//this->SetCoordinateSystem(dynamic_cast<CartesianCoordinateSystem*>(nXObject));

    dynamic_cast<CartesianCoordinateSystem*>(nXObject);


    
    this->SizeLaw()->Value()->SetRightHandSide("1.2");
    
    this->PitchLaw()->Value()->SetRightHandSide("4");
    
    this->Evaluate();
  
    NXObject *nXObject1;
    nXObject1 = this->Commit();

   if(nXObject1==NULL)
	   throw NXException::Create("Helix is NULL");

	}
	catch(std::exception &ex){

		 UI *theUI = UI::GetUI();
		 theUI->NXMessageBox()->Show("Error handler in helix builder", NXOpen::NXMessageBox::DialogTypeError, ex.what());
		 return 1;
	}
    
   return 0;
}


//--//--
int	HelixInWire::SetHelixInWire(
	CartesianCoordinateSystem *coordsys,
	double rotation,
	NXString LengthHelix,
	NXString DiameterHelix, 
	NXString PitchHelix){

	try{
 

	Session *theSession = Session::GetSession();
    Part *workPart(theSession->Parts()->Work());
    Part *displayPart(theSession->Parts()->Display());

    this->SetOrientationOption(Features::HelixBuilder::OrientationOptionsSpecified);
    
    this->Spine()->SetDistanceTolerance(0.0254);
    
    this->Spine()->SetChainingTolerance(0.02413);
	
    
    this->SizeLaw()->AlongSpineData()->Spine()->SetDistanceTolerance(0.001);
    
    this->SizeLaw()->AlongSpineData()->Spine()->SetChainingTolerance(0.001);
    
    this->SizeLaw()->LawCurve()->SetDistanceTolerance(0.001);
    
    this->SizeLaw()->LawCurve()->SetChainingTolerance(0.001);
    
    this->PitchLaw()->AlongSpineData()->Spine()->SetDistanceTolerance(0.001);
    
    this->PitchLaw()->AlongSpineData()->Spine()->SetChainingTolerance(0.001);
    
    this->PitchLaw()->LawCurve()->SetDistanceTolerance(0.001);
    
    this->PitchLaw()->LawCurve()->SetChainingTolerance(0.001);
    
    this->Spine()->SetAngleTolerance(0.01);
    
    this->SizeLaw()->AlongSpineData()->Spine()->SetAngleTolerance(0.01);
    
    this->SizeLaw()->LawCurve()->SetAngleTolerance(0.01);
    
    this->PitchLaw()->AlongSpineData()->Spine()->SetAngleTolerance(0.01);
    
    this->PitchLaw()->LawCurve()->SetAngleTolerance(0.01);
    
    this->StartLimit()->SetPercentUsed(false);
    
    this->StartLimit()->Expression()->SetRightHandSide("0");
    
    this->EndLimit()->SetPercentUsed(false);

    this->EndLimit()->Expression()->SetRightHandSide(LengthHelix);

	this->SetSizeOption(Features::HelixBuilder::SizeOptionsDiameter);

	std::ostringstream RHS;
	RHS<<rotation;
   
    this->StartAngle()->SetRightHandSide(RHS.str());

    this->SetCoordinateSystem(coordsys);

    this->SizeLaw()->Value()->SetRightHandSide(DiameterHelix);

    this->PitchLaw()->Value()->SetRightHandSide(PitchHelix);
    
    this->Evaluate();
  
    NXObject *nXObject1;
    nXObject1 = this->Commit();

   if(nXObject1==NULL)
	   throw NXException::Create("Helix is NULL");

	}
	catch(std::exception &ex){

		 UI *theUI = UI::GetUI();
		 theUI->NXMessageBox()->Show("Error handler in helix builder", NXOpen::NXMessageBox::DialogTypeError, ex.what());
		 return 1;
	}
    
	return 0;

}

