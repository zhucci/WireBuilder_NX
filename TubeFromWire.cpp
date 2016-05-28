#include "TubeFromWire.h"


TubeFromWire::TubeFromWire(void)
{
}


TubeFromWire::~TubeFromWire(void)
{
}


int TubeFromWire::SetSplineToTube(Routing::SplinePathBuilder *spline)	//Ek
{
	
	return 0;

}

int TubeFromWire::SetOuterDiameter(NXString outerDiameter, Routing::SplinePathBuilder *spline)	//Ek
{
	return 0;
}

int TubeFromWire::CreateTube(NXOpen::Part *workPart, NXString outerDiameter, Routing::SplinePathBuilder *spline)	//Ek
{
		Features::Feature *nullFeatures_Feature(NULL);
		// создаем объект трубы как указатель 
		//this = workPart->Features()->CreateTubeBuilder(nullFeatures_Feature);
		
		this->SetTolerance(0.001); // припуск
		this->OuterDiameter()->SetRightHandSide(outerDiameter);	//внешний диаметр
		this->InnerDiameter()->SetRightHandSide(INNER_DIAMETER);   //внутренний диаметр
	 
		this->BooleanOption()->SetType(GeometricUtilities::BooleanOperation::BooleanTypeCreate); // булевы операции 
    

		
		
    
		this->PathSection()->SetDistanceTolerance(DISTANCE_TOLERANCE_TUBE); // допуск
		this->PathSection()->SetChainingTolerance(CHAINING_TOLERANCE_TUBE); // допуск
    
		
		// про булевы операции
		std::vector<Body *> targetBodies1(1);
		Body *nullBody(NULL);
		targetBodies1[0] = nullBody;
		this->BooleanOption()->SetTargetBodies(targetBodies1);


		this->PathSection()->SetAllowedEntityTypes(Section::AllowTypesOnlyCurves); // вывод "Один сегмент"
    
    
	
		// создаем из Curve объект CurveDumbRule,который потом добавим в объект трубы

		Curve *curve1;
		curve1 = spline->GetRouteSegment();

		std::vector<IBaseCurve *> curves1(1);
		Routing::SplineSegment *splineSegment1(dynamic_cast<Routing::SplineSegment *>(spline->GetRouteSegment()));
		curves1[0] = splineSegment1;
		CurveDumbRule *curveDumbRule1;
		curveDumbRule1 = workPart->ScRuleFactory()->CreateRuleBaseCurveDumb(curves1);

		//CurveDumbRule *curveDumbRule1;
		//curveDumbRule1 = workPart->ScRuleFactory()->CreateRuleBaseCurveDumb(curve1);


    
		this->PathSection()->AllowSelfIntersection(true);
    
		std::vector<SelectionIntentRule *> rules1(1);
		rules1[0] = curveDumbRule1;
		NXObject *nullNXObject(NULL);
		Point3d helpPoint1(-1711.72322949462, 778.153286292641, 0.0);
		this->PathSection()->AddToSection(rules1, splineSegment1, nullNXObject, nullNXObject, helpPoint1, Section::ModeCreate, false);
    

    
		//Session::UndoMarkId markId4;
		//markId4 = theSession->SetUndoMark(Session::MarkVisibilityInvisible, "Tube");
    
		NXObject *nXObject1;
		nXObject1 = this->Commit();
   
	return 0;
}
