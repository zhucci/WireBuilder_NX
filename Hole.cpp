#include"Hole.h"

using namespace std;

Part *(Hole::workPart) = NULL;

Hole::Hole(Part *part, Face *choiceFace){
	try{

		this->workPart = part;

		thisFace=choiceFace; //Сохрание грани отверстия, с которой мы хотим ассоциировать данный экземпляр класса Hole.

		Features::VirtualCurve *nullFeatures_VirtualCurve(NULL); //создание нулевого указателя на кривую для начальной инициализации VirtualCurveBuilder

		Features::VirtualCurveBuilder *virtualCurveBuilder1;

		virtualCurveBuilder1 = workPart->Features()->CreateVirtualCurveBuilder(nullFeatures_VirtualCurve); //Создание Builder-а с помощью элемента класса Part
	//Создание собственного класса виртуальной кривой
		VirtualLine *line = new VirtualLine(*virtualCurveBuilder1);
	//Инициализация собственного класса используя выбранное отверстие
		line->SetVirtualLine(choiceFace);
	//Получаем сущность типа кривой 
		thisVirtCurve = line->GetFeature();

	}
	catch(NXException &ex){
		UI *theUI = UI::GetUI();
		theUI->NXMessageBox()->Show("Error handler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	}

}

int Hole::createPointsOnLine() //функция пригодится в дальнейшем, если понадобится укорачивать виртуальную кривую.
{
try{
    Scalar *scalarOfSection;
	Point *points[2];
	double tempScalarValue;

		if(pointsInHole.size()) 
			pointsInHole.clear(); 
	
			if(!thisVirtCurve)
				NXException::Create("virtualLine wrong");

			points[0]=workPart->Points()->CreatePoint(dynamic_cast<Line*>(thisVirtCurve)->StartPoint());
			points[1]=workPart->Points()->CreatePoint(dynamic_cast<Line*>(thisVirtCurve)->EndPoint());
	
		for(int i=0;i<3;i++){

				switch(i){

				case(0) : tempScalarValue=1-tangent;
							break;
				case(1): tempScalarValue= 0.5;
							break;
				case(2): tempScalarValue= tangent;
							break;
				default: NXException::Create("Scalar built wrong");
							break;
				}
			  scalarOfSection= workPart->Scalars()->CreateScalar(tempScalarValue, Scalar::DimensionalityTypeNone, SmartObject::UpdateOptionWithinModeling);
			  Features::PointFeatureBuilder *pointFeatureBuilder1;
			  Features::Feature *nullFeatures_Feature(NULL);
			  pointFeatureBuilder1 = workPart->BaseFeatures()->CreatePointFeatureBuilder(nullFeatures_Feature);
    
			  pointsInHole.push_back(workPart->Points()->CreatePoint(points[0],points[1],scalarOfSection,SmartObject::UpdateOptionAfterModeling));

			  pointFeatureBuilder1->SetPoint(*pointsInHole.end());
				
			  pointFeatureBuilder1->Commit();

			  pointFeatureBuilder1->Destroy();
		
		}

}
catch(NXException &ex){
		UI *theUI = UI::GetUI();
		theUI->NXMessageBox()->Show("Programme Error Handler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
	
}	
	return 0;
}

int Hole::setTangentAttribute(double value){

	tangent = value;


	createPointsOnLine();

	if(isReversed)
		pointsInHole.reverse();

	return 0;

}

