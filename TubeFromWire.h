#include "Parameter.h"

#include <uf_defs.h>
#include <uf_ui_types.h>
#include <iostream>

#include <NXOpen/UI.hxx>

#include <NXOpen/CurveDumbRule.hxx> //+
#include <NXOpen/Expression.hxx> //+
#include <NXOpen/ExpressionCollection.hxx> //+

#include <NXOpen/Features_FeatureCollection.hxx>
#include <NXOpen/Features_TubeBuilder.hxx> //+
#include <NXOpen/NXException.hxx> //+
#include <NXOpen/NXString.hxx> //+

#include <NXOpen/Part.hxx> //+

#include <NXOpen/Routing_SplinePathBuilder.hxx> //+
#include <NXOpen/Routing_SplineSegment.hxx> // +

#include <NXOpen/ScRuleFactory.hxx> // +


using namespace std;

using namespace NXOpen;


#pragma once
namespace NXOpen
{
	class TubeFromWire: public Features::TubeBuilder
{
	public:
		TubeFromWire(void);
		~TubeFromWire(void);
		int CreateTube(Part *workPart, NXString outerDiameter, Routing::SplinePathBuilder *spline);
		int SetSplineToTube(Routing::SplinePathBuilder *spline);
		int SetOuterDiameter( NXString outerDiameter, Routing::SplinePathBuilder *spline);

	private:
		Routing::SplinePathBuilder *spline;
};
}

