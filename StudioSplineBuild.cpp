#include"StudioSplineBuilder.h"

Features::Feature * StudioSplineBuild::SetStudioSplineBuild(
	Features::Feature *firstSection,
	bool ReverseStart,
	Features::Feature *lastSection,
	bool ReverseEnd,
	double tangent,
	bool isSpline3)
{
	try{
		
		Features::Helix *nullFeatures_Helix(NULL);
		Features::VirtualCurve *nullFeature_VirtualCurve(NULL);

		bool isHelix=false;
		if(typeid(*lastSection)==typeid(*firstSection))
			isHelix=false;
		else
			isHelix=true;
			
	Session *theSession = Session::GetSession();
    Part *workPart(theSession->Parts()->Work());
    Part *displayPart(theSession->Parts()->Display());

    
    Point3d origin1(0.0, 0.0, 0.0);
    Vector3d normal1(0.0, 0.0, 1.0);
    Plane *plane1;
    plane1 = workPart->Planes()->CreatePlane(origin1, normal1, SmartObject::UpdateOptionWithinModeling);
    
     this->SetDrawingPlane(plane1);
	 this->SetMovementPlane(plane1);

	
    this->OrientExpress()->SetReferenceOption(GeometricUtilities::OrientXpressBuilder::ReferenceWcsDisplayPart); //
    
    this->SetMovementMethod(Features::StudioSplineBuilderEx::MovementMethodTypeView); // 
    
    this->SetType(Features::StudioSplineBuilderEx::TypesByPoles);
    if(isSpline3)
    this ->SetDegree(3);  
	else
    this ->SetDegree(2); 

    this->OrientExpress()->SetAxisOption(GeometricUtilities::OrientXpressBuilder::AxisPassive);
    
    this->OrientExpress()->SetPlaneOption(GeometricUtilities::OrientXpressBuilder::PlanePassive);
    
    this->Extender()->EndValue()->SetRightHandSide("0");
    
    this->SetInputCurveOption(Features::StudioSplineBuilderEx::InputCurveOptionsHide);
    
    this ->SetMatchKnotsType(Features::StudioSplineBuilderEx::MatchKnotsTypesNone); //
    
    Scalar *scalarFirstSection, *scalarEndSection, *helixSection;
	helixSection = workPart->Scalars()->CreateScalar(0.0, Scalar::DimensionalityTypeNone, SmartObject::UpdateOptionWithinModeling);

		if(ReverseStart)
			scalarFirstSection = workPart->Scalars()->CreateScalar(0.0, Scalar::DimensionalityTypeNone, SmartObject::UpdateOptionWithinModeling);
		else
			scalarFirstSection = workPart->Scalars()->CreateScalar(1.0, Scalar::DimensionalityTypeNone, SmartObject::UpdateOptionWithinModeling);
	
		if(ReverseEnd)
			scalarEndSection = workPart->Scalars()->CreateScalar(0.0, Scalar::DimensionalityTypeNone, SmartObject::UpdateOptionWithinModeling);
		else
			scalarEndSection = workPart->Scalars()->CreateScalar(1.0, Scalar::DimensionalityTypeNone, SmartObject::UpdateOptionWithinModeling);

	std::vector<NXObject *> obj1=firstSection->GetEntities();

    Point *point1;

    point1 = workPart->Points()->CreatePoint(dynamic_cast<Line*>(obj1[0]), scalarFirstSection, SmartObject::UpdateOptionWithinModeling);
	
    
    NXObject *nXObject1;
    Xform *xform1;
    xform1 = workPart->Xforms()->CreateExtractXform(dynamic_cast<Line*>(obj1[0]), SmartObject::UpdateOptionWithinModeling, false, &nXObject1);
    
    Features::GeometricConstraintData *geometricConstraintData1;
    geometricConstraintData1 = this->ConstraintManager()->CreateGeometricConstraintData();
    
    geometricConstraintData1->SetPoint(point1);
    
    this->ConstraintManager()->Append(geometricConstraintData1);
    
	geometricConstraintData1->SetAutomaticConstraintType(Features::GeometricConstraintData::AutoConstraintTypeTangent);


	Point *point2= this->CreateBeyondPoint(tangent,dynamic_cast<Line*>(obj1[0]),ReverseStart);
    Xform *nullXform(NULL);
    
    NXObject *nXObject2;
    Xform *xform2;
    xform2 = workPart->Xforms()->CreateExtractXform(point2, SmartObject::UpdateOptionWithinModeling, false, &nXObject2);
    
    Features::GeometricConstraintData *geometricConstraintData2;
    geometricConstraintData2 = this->ConstraintManager()->CreateGeometricConstraintData();
    
    geometricConstraintData2->SetPoint(point2);
    
    this->ConstraintManager()->Append(geometricConstraintData2);
 
    
	std::vector<NXObject *> obj2=lastSection->GetEntities();
	if(!isHelix){
	Point *point3 = this->CreateBeyondPoint(tangent, dynamic_cast<Line*>(obj2[0]),ReverseEnd);
    
    Features::GeometricConstraintData *geometricConstraintData3;
    geometricConstraintData3 = this->ConstraintManager()->CreateGeometricConstraintData();
    geometricConstraintData3->SetPoint(point3);
    this->ConstraintManager()->Append(geometricConstraintData3);
	}

    Point *point4;
	if(!isHelix)
    point4 = workPart->Points()->CreatePoint(dynamic_cast<Line*>(obj2[0]), scalarEndSection, SmartObject::UpdateOptionWithinModeling);
    else
		point4 = workPart->Points()->CreatePoint(dynamic_cast<NXOpen::Spline*>(obj2[0]), helixSection, SmartObject::UpdateOptionWithinModeling);
	
    Features::GeometricConstraintData *geometricConstraintData4;
    geometricConstraintData4 = this->ConstraintManager()->CreateGeometricConstraintData();
    
    geometricConstraintData4->SetPoint(point4);
	geometricConstraintData4->SetAutomaticConstraintType(Features::GeometricConstraintData::AutoConstraintTypeTangent);
	if(isHelix){
	Scalar *scl;
	scl = workPart->Scalars()->CreateScalar(5.0, Scalar::DimensionalityTypeNone, SmartObject::UpdateOptionWithinModeling);
   
    geometricConstraintData4->SetTangentMagnitude(scl);
	}
    this->ConstraintManager()->Append(geometricConstraintData4);
    
    this->InsertPole(1);

	
	if(!this->Validate())
		throw NXException::Create("Spline ancorrect");

   // NXObject *nXObject5;
   // nXObject5 = this->Commit();
	this->Commit();

	}
		catch(NXException &ex){
		UI *TheUI=NXOpen::UI::GetUI();
		TheUI->NXMessageBox()->Show("My handle",NXMessageBox::DialogTypeError,ex.what());
	}

		return this->GetFeature();
}

Point *StudioSplineBuild::CreateBeyondPoint(double value, Line* buildingLine, bool isReversed){

		Session *theSession = NXOpen::Session::GetSession();
		Part *workPart = theSession->Parts()->Work();
		
			Scalar *scalar;
			scalar = workPart->Scalars()->CreateScalar(value, Scalar::DimensionalityTypeNone, SmartObject::UpdateOptionWithinModeling);
			Point *start, *end;
		if(!isReversed){
			start=workPart->Points()->CreatePoint(buildingLine->StartPoint());
			end=workPart->Points()->CreatePoint(buildingLine->EndPoint());
		}
		else{
			start=workPart->Points()->CreatePoint(buildingLine->EndPoint());
			end=workPart->Points()->CreatePoint(buildingLine->StartPoint());
		
		}
			return workPart->Points()->CreatePoint(start,end,scalar, SmartObject::UpdateOptionWithinModeling);	
}
//********************************
//Пока неудавшийся замысел
//*******************************
Features::Feature * StudioSplineBuild::SetStudioSplineBuild(std::vector<Hole*> holes){
	try{
		
		Features::Helix *nullFeatures_Helix(NULL);

	Session *theSession = Session::GetSession();
    Part *workPart(theSession->Parts()->Work());
    Part *displayPart(theSession->Parts()->Display());

    Point3d origin1(0.0, 0.0, 0.0);
    Vector3d normal1(0.0, 0.0, 1.0);
    Plane *plane1;
    plane1 = workPart->Planes()->CreatePlane(origin1, normal1, SmartObject::UpdateOptionWithinModeling);
    

    this->SetDrawingPlane(plane1);
	this->SetMovementPlane(plane1);

    this->OrientExpress()->SetReferenceOption(GeometricUtilities::OrientXpressBuilder::ReferenceWcsDisplayPart); //
    
    this->SetMovementMethod(Features::StudioSplineBuilderEx::MovementMethodTypeView); // 
    
	this->SetType(Features::StudioSplineBuilderEx::TypesThroughPoints);

	this->OrientExpress()->SetPlaneOption(GeometricUtilities::OrientXpressBuilder::PlanePassive);

    this ->SetDegree(3);  

    this->OrientExpress()->SetAxisOption(GeometricUtilities::OrientXpressBuilder::AxisPassive);
    
    this->Extender()->EndValue()->SetRightHandSide("0");
    
    this->SetInputCurveOption(Features::StudioSplineBuilderEx::InputCurveOptionsHide);
    
    this ->SetMatchKnotsType(Features::StudioSplineBuilderEx::MatchKnotsTypesNone); //


    std::vector<Features::GeometricConstraintData *> geometricConstraintData;
	size_t size = holes.size();

		for(int i=0;i<size;i++){

			std::pair <std::list<Point*>::iterator , std::list<Point*>::iterator > iterators =holes[i]->getPointsInHole();

				while(iterators.first!=iterators.second){
				UI *TheUI=NXOpen::UI::GetUI();
					TheUI->NXMessageBox()->Show("In while ",NXMessageBox::DialogTypeError,"213");
					geometricConstraintData.push_back(this->ConstraintManager()->CreateGeometricConstraintData());
					size_t lastNum= geometricConstraintData.size()-1;

					geometricConstraintData[lastNum]->SetPoint(*(iterators.first));

					this->ConstraintManager()->Append(geometricConstraintData[lastNum]);

					geometricConstraintData[lastNum]->SetAutomaticConstraintType(Features::GeometricConstraintData::AutoConstraintTypeNone);

					geometricConstraintData[lastNum]->SetAutomaticConstraintDirection(Features::GeometricConstraintData::ParameterDirectionSection);

					iterators.first++;
				}
			}
	
	if(!this->Validate())
		throw NXException::Create("Spline ancorrect");
	
    NXObject *nXObject5;
   nXObject5 = this->Commit();

	}
		catch(NXException &ex){
		UI *TheUI=NXOpen::UI::GetUI();
		TheUI->NXMessageBox()->Show("My handle",NXMessageBox::DialogTypeError,ex.what());
	}
		return this->GetFeature();
}
