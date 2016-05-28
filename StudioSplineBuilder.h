#ifndef STUDIOSPLINEBUILDER_H_INCLUDE
#define STUDIOSPLINEBUILDER_H_INCLUDE

#include<NXOpen\Features_StudioSplineBuilderEx.hxx>//Базовый класс

#include"Hole.h" // Контейнерный класс, содержащий необходимые вспомогательные построения


#include <NXOpen/CoordinateSystem.hxx>
#include <NXOpen/Direction.hxx>
#include <NXOpen/Expression.hxx>
#include <NXOpen/ExpressionCollection.hxx>

#include <NXOpen/Features_GeometricConstraintData.hxx>
#include <NXOpen/Features_GeometricConstraintDataManager.hxx>
#include <NXOpen/Features_PointFeature.hxx>
#include <NXOpen/Features_VirtualCurve.hxx>
#include <NXOpen/GeometricUtilities_OrientXpressBuilder.hxx>
#include <NXOpen/GeometricUtilities_SplineExtensionBuilder.hxx>
#include <NXOpen/Line.hxx>
#include <NXOpen/NXObject.hxx>
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
#include <NXOpen/Session.hxx>
#include <NXOpen/Spline.hxx>
#include <NXOpen/Unit.hxx>
#include <NXOpen/Xform.hxx>
#include <NXOpen/XformCollection.hxx>
#include<NXOpen\UI.hxx>
#include<NXOpen\NXMessageBox.hxx>
#include<typeinfo>
#include<sstream>
#include<ios>
#include <NXOpen/Features_HelixBuilder.hxx>
#include<NXOpen\Features_Helix.hxx>
//


using namespace NXOpen;

class StudioSplineBuild: public Features::StudioSplineBuilderEx{

public:
	StudioSplineBuild(Features::StudioSplineBuilderEx &builder): Features::StudioSplineBuilderEx(builder){}
	//Используемый вариант функции
	//Униерсальная реализация

	Features::Feature *SetStudioSplineBuild(
		Features::Feature *firstSection,
		bool ReverseStart,
		Features::Feature *lastSection,
		bool ReverseEnd,
		double tangent,
		bool isSpline3
		);
	//*********************
	Features::Feature *SetStudioSplineBuild(std::vector<Hole*> holes);

	
	~StudioSplineBuild(){
		this->Destroy();	
	}
private:

 Point *CreateBeyondPoint(double value, Line * buildingLine, bool isReversed = false);


};

#endif