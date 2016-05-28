#include"SweepOnSpline.h"

int SweepOnSpline::SetSweepOnSpline(
	Part *workPart, 
	std::vector<Features::Feature*> *spline,
	std::vector<Features::Feature*> *line,
	std::vector<Features::Feature*> *bridge,
	std::vector<Features::Feature*> *helix,
	NXString diameter)
{


    this->SetTolerance(0.001);
	
   
    this->OuterDiameter()->SetRightHandSide(diameter);
    
    this->InnerDiameter()->SetRightHandSide("0");
    
    this->BooleanOption()->SetType(GeometricUtilities::BooleanOperation::BooleanTypeCreate);

    
    this->SetOutputOption(Features::TubeBuilder::OutputSingleSegment);
    
    this->PathSection()->SetDistanceTolerance(0.001);
    
    this->PathSection()->SetChainingTolerance(0.001);
    
    this->PathSection()->SetAllowedEntityTypes(Section::AllowTypesOnlyCurves);

	
	
	std::vector<SelectionIntentRule *> rules;
 
	  if(!spline->empty())
      rules.push_back(workPart->ScRuleFactory()->CreateRuleCurveFeature(*spline));
	
	  if(!line->empty())
	  rules.push_back(workPart->ScRuleFactory()->CreateRuleCurveFeature(*line));
	 
	  if(!bridge->empty())
	  rules.push_back(workPart->ScRuleFactory()->CreateRuleCurveFeature(*bridge));
	 
	  if(!helix->empty())
	  rules.push_back(workPart->ScRuleFactory()->CreateRuleCurveFeature(*helix));
	  

    this->PathSection()->AllowSelfIntersection(true);

    NXObject *nullNXObject(NULL);
	
	std::vector<NXObject*> obj1=line[0][0]->GetEntities();

	Point3d helpPoint1 = dynamic_cast<Line*>(obj1[0])->StartPoint();

	this->PathSection()->AddToSection(rules, dynamic_cast<Line*>(obj1[0]), nullNXObject, nullNXObject, helpPoint1, Section::ModeCreate, false);
    
    NXObject *nXObject1;
    nXObject1 = this->Commit();

}

