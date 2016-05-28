#ifndef WIREBUILDER_H_INCLUDE
#define WIREBUILDER_H_INCLUDE

#include"HelixBuilder.h"
#include"SweepOnSpline.h"
#include"Hole.h"
#include<NXOpen\ExpressionCollection.hxx>

#include"StudioSplineBuilder.h"
#include<NXOpen\Preferences_SessionModeling.hxx>
#include<NXOpen\PointCollection.hxx>
#include<NXOpen\LineCollection.hxx>
#include<NXOpen\SelectPoint.hxx>
#include<NXOpen\PointCollection.hxx>
#include<NXOpen\BasePart.hxx>
#include <NXOpen/CartesianCoordinateSystem.hxx>
#include <NXOpen/CoordinateSystem.hxx>
#include <NXOpen/CoordinateSystemCollection.hxx>
#include<NXOpen\CurveCollection.hxx>
#include<NXOpen\Update.hxx>
using namespace NXOpen;

class WireBuilder {
public:
//Указателя на рабочую деталь и текущую сессию
	 Session *theSession;
	 Part *workPart;
     Part *displayPart;

	 WireBuilder();
	~WireBuilder();
//Добавление нового отверстия в holes, через которое будет проходить проволока
	int AddPlaceForWire(Face * choiceCylinder);
//Создание сплайна, как альтернатива стандартному мостику
	int AddBridgeToWire();
//Построить сплайн через имеющиеся отверстия 
	int AddStudioSplineToWire(bool isfirst=true,size_t inPlace=0);
	Line *CreateLine(Features::Feature* feature1,Features::Feature* feature2);
	int AddHelixToWire();
//Меняет траеткторию проволоки, путем смены направления обхода отверстия с номером "number"
	int ReverseWire(int NumberOfHole);

	int WireBuilder::ReverseSplineWithNumber(int number);

	int DeleteSpline(int number);

	int DeleteHoleFromWire(int number);

	int HighLightHole(int number);

	int DeleteHelixFromWire();

	int AddNewHoleBelow(Face *choiceCylinder,int number);

	int CreateSweepOnSpline();
		 
	int DeleteTube();

	int SetWireDiameter(double diameter){DiameterOfTube = diameter; return 0;}
	int SetWireDiameterAsString(NXString str){DiameterAsString=str; return 0;}

	double GetWireDiameter(){return DiameterOfTube;}

	NXString GetWireDiameterAsString(){ return DiameterAsString;}

	CartesianCoordinateSystem * GetCartesianCoordinateSystem(){
		return cartesianCoordinateSystem;}

	CartesianCoordinateSystem * CreateCartesianCoordinateSystem(Point* helpPoint, Line* helpLine, Line* normal);

	int CreateCartesianCoordinateSystem(CartesianCoordinateSystem *coord);

	int SetCartesianCoordinateSystem(CartesianCoordinateSystem *coord);

	void SetTangentAttribute(double value){ tangent=value;}

	double GetTangentAttribute(){return tangent;}

	void SetIsSpline3Attribute(bool value){isSpline3= value;}

	bool GetIsSpline3Attribute(){return isSpline3;}

	void SetDiameterHelixAttribute(NXString str){DiameterHelix=str;}
	 
	void SetLengthHelixAttribute(NXString str){LengthHelix=str;}

	void SetPitchHelixAttribute(NXString str){PitchHelix=str;}

	void SetWidthOutAttribute(NXString str){WidthOut=str;}

	void SetLengthOutAttribute(NXString str){LengthOut=str;}
	
	tag_t cartesianCoordinateSystemTag;

	int NumberOfHoles()
	{
		return static_cast<int>(holes.size());
	}
private:

	std::vector<Hole*> holes;
	
//Основные элементы проволоки
	std::vector<Features::Feature *> AllSplineInWire;
	std::vector<Features::Feature *> AllHelixInWire;
	std::vector<Features::Feature *> AllBridgeInWire;


	CartesianCoordinateSystem *cartesianCoordinateSystem;

	NXObject *SolideTube;
//Вспомогательная точка для построения системы координат
	Point3d helpPoint;
//Параметры спирали
	NXString DiameterAsString;
	double DiameterOfTube;
	NXString PitchHelix;
	NXString DiameterHelix;
	NXString LengthHelix;
//Параметры сплайна
	bool isSpline3;
	double tangent;
//Параметры выхода под крепление пломбы
	NXString LengthOut;
	NXString WidthOut;
//Создает вспомогательную точку для построения системы координат смотки
	Point *GetOriginalPoint();
//СОздает вспомогательную прямую для задания ориентации системы координат смотки
Line *CreateLine(Point* point1,Point* point2)
	{
		return workPart->Curves()->CreateLine(point1,point2);
	}
//Управляет созданием сплайна между виртуальными кривыми
int AddTraceBetweenHoles(int FS, int LS);
//
int CreateCoordSYS(Part* workPart, std::vector<Point*>::iterator , std::vector<Point*>::iterator);

};

#endif