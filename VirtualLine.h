#include <uf_defs.h>
#include <uf_ui_types.h>
#include <iostream>


#include <NXOpen/Session.hxx>
#include <NXOpen/UI.hxx>
#include <NXOpen/NXMessageBox.hxx>
#include <NXOpen/Callback.hxx>
#include <NXOpen/NXException.hxx>


#include <NXOpen/BlockStyler_UIBlock.hxx>
#include <NXOpen/BlockStyler_BlockDialog.hxx>
#include <NXOpen/BlockStyler_PropertyList.hxx>
#include <NXOpen/BlockStyler_ListBox.hxx>
#include <NXOpen/BlockStyler_Group.hxx>
#include <NXOpen/BlockStyler_ExpressionBlock.hxx>
#include <NXOpen/BlockStyler_FaceCollector.hxx>
#include <NXOpen/BlockStyler_ReverseDirection.hxx>
#include <NXOpen/BlockStyler_Button.hxx>
#include <NXOpen/BlockStyler_SpecifyCSYS.hxx>

#include <NXOpen/Information.hxx>//+
#include<sstream>//+
#include <NXOpen/Face.hxx>//+
#include<NXOpen\Edge.hxx>//+
#include<NXOpen\Curve.hxx>//+
#include<NXOpen\Arc.hxx>//+
#include <NXOpen/Line.hxx>//+
#include<NXOpen\Point.hxx>
#include <NXOpen/Part.hxx>//+

#include <NXOpen/Features_Extrude.hxx>
#include <NXOpen/Features_FeatureCollection.hxx>
#include <NXOpen\Features_DatumCsysBuilder.hxx>
#include <NXOpen/Scalar.hxx>//+
#include <NXOpen/ScalarCollection.hxx>//+
#include<vector>
#include <NXOpen/SmartObject.hxx>//+
#include<iomanip>
#include<NXOpen\PartCollection.hxx>
#include <NXOpen/BasePart.hxx>
#include <NXOpen/Builder.hxx>
#include <NXOpen/Features_BaseFeatureCollection.hxx>
#include <NXOpen/Features_PointFeatureBuilder.hxx>

#include <NXOpen\Preferences_PartPreferences.hxx>
#include<NXOpen\Preferences_PartModeling.hxx>
#include<NXOpen\PointCollection.hxx>
#include<NXOpen\SmartObject.hxx>

#include <NXOpen/Features_ExtractFace.hxx>
#include <NXOpen/Features_Feature.hxx>
#include <NXOpen/Features_FeatureCollection.hxx>
#include <NXOpen/Features_HelixBuilder.hxx>
#include <NXOpen/Features_PointFeatureBuilder.hxx>
#include <NXOpen/Features_VirtualCurve.hxx>
#include <NXOpen/Features_VirtualCurveBuilder.hxx>
#include <NXOpen\ScRuleFactory.hxx>
#include <NXOpen/FaceDumbRule.hxx>

using namespace NXOpen;
using namespace std;


class VirtualLine: public Features::VirtualCurveBuilder{

public:

	VirtualLine(Features::VirtualCurveBuilder &builder): VirtualCurveBuilder(builder){}

	~VirtualLine();

	NXObject *SetVirtualLine(Face *choiceFace);

};
