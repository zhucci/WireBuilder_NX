#include "Parameter.h"
#include <uf_defs.h>
#include<NXOpen\BlockStyler_UIBlock.hxx>
#include <NXOpen/NXException.hxx>
#include <NXOpen/Session.hxx>
#include <NXOpen/BasePart.hxx>
#include <NXOpen/CartesianCoordinateSystem.hxx>
#include <NXOpen/CoordinateSystem.hxx>
#include <NXOpen/CoordinateSystemCollection.hxx>
#include <NXOpen/DatumAxis.hxx>
#include <NXOpen/DatumCollection.hxx>
#include <NXOpen/Direction.hxx>
#include <NXOpen/DirectionCollection.hxx>
#include <NXOpen/DisplayableObject.hxx>
#include <NXOpen/Expression.hxx>
#include <NXOpen/ExpressionCollection.hxx>
#include <NXOpen/Features_AssociativeLine.hxx>
#include <NXOpen/Features_AssociativeLineBuilder.hxx>
#include <NXOpen/Features_BaseFeatureCollection.hxx>
#include <NXOpen/Features_DatumCsys.hxx>
#include <NXOpen/Features_DatumCsysBuilder.hxx>
#include <NXOpen/Features_FeatureCollection.hxx>
#include <NXOpen/Features_HelixBuilder.hxx>
#include <NXOpen/Features_PointFeature.hxx>
#include <NXOpen/Features_PointFeatureBuilder.hxx>
#include <NXOpen/GeometricUtilities_AlongSpineBuilder.hxx>
#include <NXOpen/GeometricUtilities_CurveExtendData.hxx>
#include <NXOpen/GeometricUtilities_CurveLimitsData.hxx>
#include <NXOpen/GeometricUtilities_LawBuilder.hxx>
#include <NXOpen/GeometricUtilities_MultiTransitionLawBuilder.hxx>
#include <NXOpen/GeometricUtilities_NonInflectingLawBuilder.hxx>
#include <NXOpen/GeometricUtilities_OnPathDimensionBuilder.hxx>
#include <NXOpen/GeometricUtilities_SShapedLawBuilder.hxx>
#include <NXOpen/GeometricUtilities_SupportPlaneData.hxx>
#include <NXOpen/Line.hxx>
#include <NXOpen/ModelingView.hxx>
#include <NXOpen/ModelingViewCollection.hxx>
#include <NXOpen/NXObject.hxx>
#include <NXOpen/ObjectList.hxx>
#include <NXOpen/Part.hxx>
#include <NXOpen/PartCollection.hxx>
#include <NXOpen/Plane.hxx>
#include <NXOpen/PlaneCollection.hxx>
#include <NXOpen/Point.hxx>
#include <NXOpen/PointCollection.hxx>
#include <NXOpen/Preferences_PartModeling.hxx>
#include <NXOpen/Preferences_PartPreferences.hxx>
#include <NXOpen/Scalar.hxx>
#include <NXOpen/ScalarCollection.hxx>
#include <NXOpen/Section.hxx>
#include <NXOpen/SelectCartesianCoordinateSystem.hxx>
#include <NXOpen/SelectDisplayableObject.hxx>
#include <NXOpen/SelectICurve.hxx>
#include <NXOpen/SelectLine.hxx>
#include <NXOpen/SelectObject.hxx>
#include <NXOpen/SelectPoint.hxx>
#include <NXOpen/Session.hxx>
#include <NXOpen/SmartObject.hxx>
#include <NXOpen/TaggedObject.hxx>
#include <NXOpen/Unit.hxx>
#include <NXOpen/UnitCollection.hxx>
#include <NXOpen/Update.hxx>
#include <NXOpen/View.hxx>
#include <NXOpen/WCS.hxx>
#include <NXOpen/Xform.hxx>
#include <NXOpen/XformCollection.hxx>
#include <NXOpen/UI.hxx>
#include<NXOpen\NXMessageBox.hxx>//include-//-
#include<sstream>
#include<ios>
#include<fstream>

using namespace NXOpen;


class HelixInWire:public Features::HelixBuilder {
public:
	HelixInWire(Point* originPoint,
		Line* helpLine,
		Line* normalLine,
		const NXOpen::Features::HelixBuilder &builder,
		double startAngle=0.0,
		CartesianCoordinateSystem *coordsys=NULL
		): HelixBuilder(builder)
	{
		SetHelixInWire(originPoint, helpLine, normalLine, startAngle, coordsys);
	}
	HelixInWire(
		double rotation, 
		CartesianCoordinateSystem *coordsys,
		const NXOpen::Features::HelixBuilder &builder,
		NXString LengthHelix,
		NXString DiameterHelix,
		NXString PitchHelix
		): HelixBuilder(builder){
		SetHelixInWire(coordsys, rotation, LengthHelix,DiameterHelix,PitchHelix);
	}
	~HelixInWire();
private:
	
    CartesianCoordinateSystem * cartesianCoordinateSystem;
	CartesianCoordinateSystem *GetCoordSystem(){return cartesianCoordinateSystem;}

	int	SetHelixInWire(
		Point* originPoint,
		Line* helpLine,
		Line* normalLine, 
		double startAngle=0.0,
		CartesianCoordinateSystem *coordsys=NULL);

	int	SetHelixInWire(
		CartesianCoordinateSystem *coordsys, 
		double rotation,
		NXString LengthHelix,
		NXString DiameterHelix, 
		NXString PitchHelix);
	
};

