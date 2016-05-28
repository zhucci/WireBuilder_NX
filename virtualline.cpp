#include"virtualline.h"



 NXObject *VirtualLine::SetVirtualLine(Face *choiceFace){
	
	Session *theSession = NXOpen::Session::GetSession();
	Part *workPart = theSession->Parts()->Work();

	std::vector<Face *> faceVector(1);
	faceVector[0] = choiceFace;
	FaceDumbRule *faceDumbRule1;
	faceDumbRule1 = workPart->ScRuleFactory()->CreateRuleFaceDumb(faceVector);

	std::vector<SelectionIntentRule *> rules5(1);
	rules5[0] = faceDumbRule1;

	this->RevolvedFace()->ReplaceRules(rules5, false);
	
	this->Commit();
	
	return 0;

}
VirtualLine::~VirtualLine(){

	this->Destroy();

}
