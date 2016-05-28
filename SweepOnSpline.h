#include <uf_defs.h>
#include <NXOpen/NXException.hxx>
#include <NXOpen/Session.hxx>
#include <NXOpen/Body.hxx>
#include <NXOpen/Builder.hxx>
#include <NXOpen/CurveDumbRule.hxx>

#include <NXOpen/Expression.hxx>
#include <NXOpen/Features_Feature.hxx>
#include <NXOpen/Features_FeatureCollection.hxx>
#include <NXOpen/Features_StudioSpline.hxx>
#include <NXOpen/Features_TubeBuilder.hxx>
#include <NXOpen/Features_VirtualCurve.hxx>
#include <NXOpen/GeometricUtilities_BooleanOperation.hxx>
#include <NXOpen/IBaseCurve.hxx>
#include <NXOpen/Line.hxx>
#include <NXOpen/ModelingView.hxx>
#include <NXOpen/ModelingViewCollection.hxx>
#include <NXOpen/NXObject.hxx>
#include <NXOpen/Part.hxx>
#include <NXOpen/PartCollection.hxx>
#include <NXOpen/Preferences_PartModeling.hxx>
#include <NXOpen/Preferences_PartPreferences.hxx>
#include <NXOpen/ScRuleFactory.hxx>
#include <NXOpen/Section.hxx>
#include <NXOpen/SelectionIntentRule.hxx>
#include <NXOpen/Session.hxx>
#include <NXOpen/Spline.hxx>
#include <NXOpen/Unit.hxx>
#include <NXOpen/View.hxx>
#include<NXOpen\CurveFeatureRule.hxx>
#include<NXOpen\CurveFeatureTangentRule.hxx>

#include"WireBuilder.h"


using namespace NXOpen;


class SweepOnSpline:public Features::TubeBuilder
{
public:
	SweepOnSpline(
	Features::TubeBuilder &builder,
	Part *workPart,
	std::vector<Features::Feature*> *spline,
	std::vector<Features::Feature*> *line,
	std::vector<Features::Feature*> *bridge,
	std::vector<Features::Feature*> *helix,
	NXString diameter): Features::TubeBuilder(builder){
	SetSweepOnSpline(workPart, spline, line,bridge,helix, diameter);
		}
	~SweepOnSpline(){
	
		this->Destroy();
	}
private:
	int SetSweepOnSpline(
	Part *workPart,
	std::vector<Features::Feature*> *spline,
	std::vector<Features::Feature*> *line,
	std::vector<Features::Feature*> *bridge,
	std::vector<Features::Feature*> *helix,
	NXString Diameter);
};