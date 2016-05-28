//==============================================================================
//  WARNING!!  This file is overwritten by the Block UI Styler while generating
//  the automation code. Any modifications to this file will be lost after
//  generating the code again.
//
//       Filename:  C:\VS_NX\WireBuilder_ver_0.1\NXDialog\WireBuilderDialog_v02.cpp
//
//        This file was generated by the NX Block UI Styler
//        Created by: Asus
//              Version: NX 8.5
//              Date: 09-14-2014  (Format: mm-dd-yyyy)
//              Time: 11:42 (Format: hh-mm)
//
//==============================================================================

//==============================================================================
//  Purpose:  This TEMPLATE file contains C++ source to guide you in the
//  construction of your Block application dialog. The generation of your
//  dialog file (.dlx extension) is the first step towards dialog construction
//  within NX.  You must now create a NX Open application that
//  utilizes this file (.dlx).
//
//  The information in this file provides you with the following:
//
//  1.  Help on how to load and display your Block UI Styler dialog in NX
//      using APIs provided in NXOpen.BlockStyler namespace
//  2.  The empty callback methods (stubs) associated with your dialog items
//      have also been placed in this file. These empty methods have been
//      created simply to start you along with your coding requirements.
//      The method name, argument list and possible return values have already
//      been provided for you.
//==============================================================================

//------------------------------------------------------------------------------
//These includes are needed for the following template code
//------------------------------------------------------------------------------
#include "WireBuilderDialog_v02.hpp"
using namespace NXOpen;
using namespace NXOpen::BlockStyler;

//------------------------------------------------------------------------------
// Initialize static variables
//------------------------------------------------------------------------------
Session *(WireBuilderDialog_v02::theSession) = NULL;
UI *(WireBuilderDialog_v02::theUI) = NULL;
//------------------------------------------------------------------------------
// Constructor for NX Styler class
//------------------------------------------------------------------------------
WireBuilderDialog_v02::WireBuilderDialog_v02()
{
    try
    {
        // Initialize the NX Open C++ API environment
        WireBuilderDialog_v02::theSession = NXOpen::Session::GetSession();
        WireBuilderDialog_v02::theUI = UI::GetUI();
        theDlxFileName = "WireBuilderDialog_v.0.2.dlx";
        theDialog = WireBuilderDialog_v02::theUI->CreateDialog(theDlxFileName);
        // Registration of callback functions
        theDialog->AddApplyHandler(make_callback(this, &WireBuilderDialog_v02::apply_cb));
        theDialog->AddOkHandler(make_callback(this, &WireBuilderDialog_v02::ok_cb));
        theDialog->AddUpdateHandler(make_callback(this, &WireBuilderDialog_v02::update_cb));
        theDialog->AddInitializeHandler(make_callback(this, &WireBuilderDialog_v02::initialize_cb));
        theDialog->AddDialogShownHandler(make_callback(this, &WireBuilderDialog_v02::dialogShown_cb));

		workPart=theSession->Parts()->Work(); //��������� ��������� �� ������� ������
		workPart->Preferences()->Modeling()->SetHistoryMode(); //��������� ������ � ��������, ���� �� ��� ��������

		buttonHelixPressed=false;
		valueOfHoles=0;
		iter=lastSelectedHoles.begin();


    }
    catch(exception& ex)
    {
        UI *theUI = UI::GetUI();
		this->theUI->NXMessageBox()->Show("My Error handle", NXOpen::NXMessageBox::DialogTypeError, ex.what());
    }
}

//------------------------------------------------------------------------------
// Destructor for NX Styler class
//------------------------------------------------------------------------------
WireBuilderDialog_v02::~WireBuilderDialog_v02()
{
    if (theDialog != NULL)
    {
        delete theDialog;
        theDialog = NULL;
    }
}
//------------------------------- DIALOG LAUNCHING ---------------------------------
//
//    Before invoking this application one needs to open any part/empty part in NX
//    because of the behavior of the blocks.
//
//    Make sure the dlx file is in one of the following locations:
//        1.) From where NX session is launched
//        2.) $UGII_USER_DIR/application
//        3.) For released applications, using UGII_CUSTOM_DIRECTORY_FILE is highly
//            recommended. This variable is set to a full directory path to a file 
//            containing a list of root directories for all custom applications.
//            e.g., UGII_CUSTOM_DIRECTORY_FILE=$UGII_ROOT_DIR\menus\custom_dirs.dat
//
//    You can create the dialog using one of the following way:
//
//    1. USER EXIT
//
//        1) Create the Shared Library -- Refer "Block UI Styler programmer's guide"
//        2) Invoke the Shared Library through File->Execute->NX Open menu.
//
//------------------------------------------------------------------------------
extern "C" DllExport void  ufusr(char *param, int *retcod, int param_len)
{
    WireBuilderDialog_v02 *theWireBuilderDialog_v02 = NULL;
    try
    {
        theWireBuilderDialog_v02 = new WireBuilderDialog_v02();
        // The following method shows the dialog immediately
        theWireBuilderDialog_v02->Show();
    }
    catch(exception& ex)
    {
        //---- Enter your exception handling code here -----
        WireBuilderDialog_v02::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
    }
    if(theWireBuilderDialog_v02 != NULL)
    {
        delete theWireBuilderDialog_v02;
        theWireBuilderDialog_v02 = NULL;
    }
}

//------------------------------------------------------------------------------
// This method specifies how a shared image is unloaded from memory
// within NX. This method gives you the capability to unload an
// internal NX Open application or user  exit from NX. Specify any
// one of the three constants as a return value to determine the type
// of unload to perform:
//
//
//    Immediately : unload the library as soon as the automation program has completed
//    Explicitly  : unload the library from the "Unload Shared Image" dialog
//    AtTermination : unload the library when the NX session terminates
//
//
// NOTE:  A program which associates NX Open applications with the menubar
// MUST NOT use this option since it will UNLOAD your NX Open application image
// from the menubar.
//------------------------------------------------------------------------------
extern "C" DllExport int ufusr_ask_unload()
{
    //return (int)Session::LibraryUnloadOptionExplicitly;
    return (int)Session::LibraryUnloadOptionImmediately;
    //return (int)Session::LibraryUnloadOptionAtTermination;
}

//------------------------------------------------------------------------------
// Following method cleanup any housekeeping chores that may be needed.
// This method is automatically called by NX.
//------------------------------------------------------------------------------
extern "C" DllExport void ufusr_cleanup(void)
{
    try
    {
        //---- Enter your callback code here -----
    }
    catch(exception& ex)
    {
        //---- Enter your exception handling code here -----
        WireBuilderDialog_v02::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
    }
}

int WireBuilderDialog_v02::Show()
{
    try
    {
        theDialog->Show();
    }
    catch(exception& ex)
    {
        //---- Enter your exception handling code here -----
        WireBuilderDialog_v02::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
    }
    return 0;
}

//------------------------------------------------------------------------------
//---------------------Block UI Styler Callback Functions--------------------------
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//Callback Name: initialize_cb
//------------------------------------------------------------------------------
void WireBuilderDialog_v02::initialize_cb()
{
    try
    {
        group1 = dynamic_cast<NXOpen::BlockStyler::Group*>(theDialog->TopBlock()->FindBlock("group1"));
        exprDiameter = dynamic_cast<NXOpen::BlockStyler::LinearDimension*>(theDialog->TopBlock()->FindBlock("exprDiameter"));
        isSpline3 = dynamic_cast<NXOpen::BlockStyler::Toggle*>(theDialog->TopBlock()->FindBlock("isSpline3"));
        group2 = dynamic_cast<NXOpen::BlockStyler::Group*>(theDialog->TopBlock()->FindBlock("group2"));
		group2->SetExpanded(false);
        DiameterHelix = dynamic_cast<NXOpen::BlockStyler::LinearDimension*>(theDialog->TopBlock()->FindBlock("DiameterHelix"));
        LengthHelix = dynamic_cast<NXOpen::BlockStyler::LinearDimension*>(theDialog->TopBlock()->FindBlock("LengthHelix"));
        PitchHelix = dynamic_cast<NXOpen::BlockStyler::LinearDimension*>(theDialog->TopBlock()->FindBlock("PitchHelix"));
        tangent = dynamic_cast<NXOpen::BlockStyler::ExpressionBlock*>(theDialog->TopBlock()->FindBlock("tangent"));
        group0 = dynamic_cast<NXOpen::BlockStyler::Group*>(theDialog->TopBlock()->FindBlock("group0"));
        FaceSelect = dynamic_cast<NXOpen::BlockStyler::FaceCollector*>(theDialog->TopBlock()->FindBlock("FaceSelect"));
        IsReversed = dynamic_cast<NXOpen::BlockStyler::ReverseDirection*>(theDialog->TopBlock()->FindBlock("IsReversed"));
        group = dynamic_cast<NXOpen::BlockStyler::Group*>(theDialog->TopBlock()->FindBlock("group"));
        buttonHelix = dynamic_cast<NXOpen::BlockStyler::Button*>(theDialog->TopBlock()->FindBlock("buttonHelix"));
        HelixCoordinateSystem = dynamic_cast<NXOpen::BlockStyler::SpecifyCSYS*>(theDialog->TopBlock()->FindBlock("HelixCoordinateSystem"));
        group3 = dynamic_cast<NXOpen::BlockStyler::Group*>(theDialog->TopBlock()->FindBlock("group3"));
        buttonSeal = dynamic_cast<NXOpen::BlockStyler::Button*>(theDialog->TopBlock()->FindBlock("buttonSeal"));
        lengthOUT = dynamic_cast<NXOpen::BlockStyler::ExpressionBlock*>(theDialog->TopBlock()->FindBlock("lengthOUT"));
        widthOUT = dynamic_cast<NXOpen::BlockStyler::ExpressionBlock*>(theDialog->TopBlock()->FindBlock("widthOUT"));
		
		Wire.SetWireDiameter(0.8);
		exprDiameter->SetValue(Wire.GetWireDiameter());//!!! ������������� �������� �������� ���������

		Wire.SetWireDiameterAsString(exprDiameter->GetProperties()->GetString("Formula"));

		DiameterHelix->SetValue(Wire.GetWireDiameter()+0.4);
		Wire.SetDiameterHelixAttribute(DiameterHelix->GetProperties()->GetString("Formula"));

		PitchHelix->SetValue(Wire.GetWireDiameter()+0.3);
		Wire.SetPitchHelixAttribute(PitchHelix->GetProperties()->GetString("Formula"));

		LengthHelix->SetValue((Wire.GetWireDiameter()+0.3)*4.);
		Wire.SetLengthHelixAttribute(LengthHelix->GetProperties()->GetString("Formula"));

    }
    catch(exception& ex)
    {
        //---- Enter your exception handling code here -----
        WireBuilderDialog_v02::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
    }
}

//------------------------------------------------------------------------------
//Callback Name: dialogShown_cb
//This callback is executed just before the dialog launch. Thus any value set 
//here will take precedence and dialog will be launched showing that value. 
//------------------------------------------------------------------------------
void WireBuilderDialog_v02::dialogShown_cb()
{
    try
    {
        //---- Enter your callback code here -----
    }
    catch(exception& ex)
    {
        //---- Enter your exception handling code here -----
        WireBuilderDialog_v02::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
    }
}

//------------------------------------------------------------------------------
//Callback Name: apply_cb
//------------------------------------------------------------------------------
int WireBuilderDialog_v02::apply_cb()
{
    int errorCode = 0;
    try
    {
		Wire.CreateSweepOnSpline();
    }
    catch(exception& ex)
    {
        //---- Enter your exception handling code here -----
        errorCode = 1;
        WireBuilderDialog_v02::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
    }
    return errorCode;
}

//------------------------------------------------------------------------------
//Callback Name: update_cb
//------------------------------------------------------------------------------
int WireBuilderDialog_v02::update_cb(NXOpen::BlockStyler::UIBlock* block)
{
    try
    {
        if(block == exprDiameter)
        {
			  Wire.SetWireDiameter(exprDiameter->Value());
			  Wire.SetWireDiameterAsString(exprDiameter->GetProperties()->GetString("Formula"));

			  DiameterHelix->SetValue(Wire.GetWireDiameter()+0.4);
			  Wire.SetDiameterHelixAttribute(DiameterHelix->GetProperties()->GetString("Formula"));

			  PitchHelix->SetValue(Wire.GetWireDiameter()+0.3);
			  Wire.SetPitchHelixAttribute(PitchHelix->GetProperties()->GetString("Formula"));

			  LengthHelix->SetValue((Wire.GetWireDiameter()+0.3)*4.);
			  Wire.SetLengthHelixAttribute(LengthHelix->GetProperties()->GetString("Formula"));
			  	
        }
        else if(block == isSpline3)
        {
			  Wire.SetIsSpline3Attribute(isSpline3->Value());

        }
        else if(block == DiameterHelix)
        {
			  Wire.SetDiameterHelixAttribute(DiameterHelix->GetProperties()->GetString("Formula"));
        }
        else if(block == LengthHelix)
        {
			  Wire.SetLengthHelixAttribute(LengthHelix->GetProperties()->GetString("Formula"));
        }
        else if(block == PitchHelix)
        {
			  Wire.SetPitchHelixAttribute(PitchHelix->GetProperties()->GetString("Formula"));
        }
        else if(block == tangent)
        {
			
			  Wire.SetTangentAttribute(tangent->Value());
        }

        else if(block == FaceSelect)
        {
			Wire.SetTangentAttribute(tangent->Value());
	
			std::vector< NXOpen::TaggedObject*> SelectedCylinders(FaceSelect->GetSelectedObjects());

			Face* FaceCylinder= dynamic_cast<Face*>(SelectedCylinders[SelectedCylinders.size()-1]);

			Wire.AddPlaceForWire(FaceCylinder);

        }
        else if(block == IsReversed)
        {
			
			Wire.ReverseWire(Wire.NumberOfHoles());
			
        }
        else if(block == buttonHelix)
        {
			buttonHelixPressed=true;
			Wire.SetPitchHelixAttribute(PitchHelix->GetProperties()->GetString("Formula"));
			Wire.SetLengthHelixAttribute(LengthHelix->GetProperties()->GetString("Formula"));
			Wire.SetDiameterHelixAttribute(DiameterHelix->GetProperties()->GetString("Formula"));
			Wire.DeleteHelixFromWire();
			Wire.AddHelixToWire();
        }
        else if(block == HelixCoordinateSystem)
        {
        
			const std::vector< NXOpen::TaggedObject*> SelectedCoordSys(HelixCoordinateSystem->GetSelectedObjects());
			size_t ValueOfCS=SelectedCoordSys.size();

					 if(ValueOfCS && buttonHelixPressed){

							if(dynamic_cast<CartesianCoordinateSystem*>(SelectedCoordSys[ValueOfCS-1])){
								
								Wire.DeleteHelixFromWire();
						
								Wire.CreateCartesianCoordinateSystem(dynamic_cast<CartesianCoordinateSystem*>(HelixCoordinateSystem->GetSelectedObjects()[0]));
									
								Wire.AddHelixToWire();
							}
					 }
        }
        else if(block == buttonSeal)
        {

			WireBuilderDialog_v02::theUI->NXMessageBox()->Show("MVZsoftware", NXOpen::NXMessageBox::DialogTypeInformation, "This option don't complete yet! Sorry!");
     //   Wire.SetLengthOutAttribute(lengthOUT->GetProperties()->GetString("Formula"));

	//	Wire.SetWidthOutAttribute(widthOUT->GetProperties()->GetString("Formula"));
        }
        else if(block == lengthOUT)
        {
      // Wire.SetLengthOutAttribute(lengthOUT->GetProperties()->GetString("Formula"));
        }
        else if(block == widthOUT)
        {
      // Wire.SetWidthOutAttribute(widthOUT->GetProperties()->GetString("Formula"));
        }
    }
    catch(exception& ex)
    {
        //---- Enter your exception handling code here -----
        WireBuilderDialog_v02::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
    }
    return 0;
}

//------------------------------------------------------------------------------
//Callback Name: ok_cb
//------------------------------------------------------------------------------
int WireBuilderDialog_v02::ok_cb()
{
    int errorCode = 0;
    try
    {
        errorCode = apply_cb();
    }
    catch(exception& ex)
    {
        //---- Enter your exception handling code here -----
        errorCode = 1;
        WireBuilderDialog_v02::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
    }
    return errorCode;
}

//------------------------------------------------------------------------------
//Function Name: GetBlockProperties
//Description: Returns the propertylist of the specified BlockID
//------------------------------------------------------------------------------
PropertyList* WireBuilderDialog_v02::GetBlockProperties(const char *blockID)
{
    return theDialog->GetBlockProperties(blockID);
}