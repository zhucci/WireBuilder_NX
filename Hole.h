#ifndef HOLE_H_INCLUDE
#define HOLE_H_INCLUDE

#include<NXOpen\Face.hxx>
#include<NXOpen\NXObject.hxx>
#include<NXOpen\Features_Feature.hxx>
#include<list>
#include"virtualline.h"
#include <utility>

using namespace NXOpen;

class Hole{

public:
	static Part *workPart;
	Hole(Part* workPart, Face* CylinderFace);
	Hole(){ thisFace=NULL; isReversed= false;}
	~Hole(){

		//необходимо удалить все без остатка.
	}

void ReverseDirection()
{

	isReversed = !isReversed;

}

bool isRevDir(){

	return isReversed;
}

void HighLightFace()
{

		thisFace->Highlight();
	

}
void UnHighLightFace()
{
	thisFace->Unhighlight();
}
std::pair <std::list <Point*>::iterator, std::list <Point*>::iterator> getPointsInHole()
{

		
	std::pair<std::list <Point*>::iterator, std::list <Point*>::iterator> firstEndpair(pointsInHole.begin(),pointsInHole.end());
		
	return firstEndpair;
	
}
	
Features::Feature *GetVirtualLine()
{
		
	return thisVirtCurve;
	
}

Hole &operator=(Face *choiceFace)
{

 thisFace=choiceFace;
 return *this;
}

int setTangentAttribute(double value);

private:

	Face* thisFace; 

	bool isReversed;	//Параметр устанвливает прямое или обратное направление обхода виртуальной кривой в проволоке
	
	double tangent; //Коэффициент удлинения проволоки за края выбранного отверстия.

	Features::Feature *thisVirtCurve;

	std::list<Point*> pointsInHole;

	int createPointsOnLine();
};

#endif