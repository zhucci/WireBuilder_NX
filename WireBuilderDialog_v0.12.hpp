//==============================================================================
//  WARNING!!  This file is overwritten by the Block Styler while generating
//  the automation code. Any modifications to this file will be lost after
//  generating the code again.
//
//       Filename:  C:\VS_NX\WireBuilder_ver_0.1\NXDialog\WireBuilderDialog_v02.hpp
//
//        This file was generated by the NX Block Styler
//        Created by: Asus
//              Version: NX 8.5
//              Date: 09-13-2014  (Format: mm-dd-yyyy)
//              Time: 22:37
//
//==============================================================================

#ifndef WIREBUILDERDIALOG_V02_H_INCLUDED
#define WIREBUILDERDIALOG_V02_H_INCLUDED

//------------------------------------------------------------------------------
//These includes are needed for the following template code
//------------------------------------------------------------------------------
#include"WireBuilder.h"

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
#include <NXOpen/BlockStyler_Group.hxx>
#include <NXOpen/BlockStyler_ExpressionBlock.hxx>
#include <NXOpen/BlockStyler_FaceCollector.hxx>
#include <NXOpen/BlockStyler_ReverseDirection.hxx>
#include <NXOpen/BlockStyler_Button.hxx>
#include <NXOpen/BlockStyler_SpecifyCSYS.hxx>
#include <NXOpen/BlockStyler_Toggle.hxx>

//------------------------------------------------------------------------------
//Bit Option for Property: EntityType
//------------------------------------------------------------------------------
#define                          EntityType_AllowFaces (1 << 4);
#define                         EntityType_AllowDatums (1 << 5);
#define                         EntityType_AllowBodies (1 << 6);
//------------------------------------------------------------------------------
//Bit Option for Property: FaceRules
//------------------------------------------------------------------------------
#define                           FaceRules_SingleFace (1 << 0);
#define                          FaceRules_RegionFaces (1 << 1);
#define                         FaceRules_TangentFaces (1 << 2);
#define                   FaceRules_TangentRegionFaces (1 << 3);
#define                            FaceRules_BodyFaces (1 << 4);
#define                         FaceRules_FeatureFaces (1 << 5);
#define                        FaceRules_AdjacentFaces (1 << 6);
#define                  FaceRules_ConnectedBlendFaces (1 << 7);
#define                        FaceRules_AllBlendFaces (1 << 8);
#define                             FaceRules_RibFaces (1 << 9);
#define                            FaceRules_SlotFaces (1 <<10);
#define                   FaceRules_BossandPocketFaces (1 <<11);
#define                       FaceRules_MergedRibFaces (1 <<12);
#define                  FaceRules_RegionBoundaryFaces (1 <<13);
#define                 FaceRules_FaceandAdjacentFaces (1 <<14);
//------------------------------------------------------------------------------
// Namespaces needed for following template
//------------------------------------------------------------------------------
using namespace std;
using namespace NXOpen;
using namespace NXOpen::BlockStyler;

class DllExport WireBuilderDialog_v02
{
    // class members
public:
    static Session *theSession;
    static UI *theUI;
	Part* workPart;
    WireBuilderDialog_v02();
    ~WireBuilderDialog_v02();
    int Show();
    
    //----------------------- BlockStyler Callback Prototypes ---------------------
    // The following member function prototypes define the callbacks 
    // specified in your BlockStyler dialog.  The empty implementation
    // of these prototypes is provided in the WireBuilderDialog_v02.cpp file. 
    // You are REQUIRED to write the implementation for these functions.
    //------------------------------------------------------------------------------
    void initialize_cb();
    void dialogShown_cb();
    int apply_cb();
    int ok_cb();
    int update_cb(NXOpen::BlockStyler::UIBlock* block);
    PropertyList* GetBlockProperties(const char *blockID);
    
private:
	
	bool flag;
	WireBuilder Wire; //������������ ����� ��� ���� ������� � ������� ����������� ��� ���������� ���������


    const char* theDlxFileName;
    NXOpen::BlockStyler::BlockDialog* theDialog;
    NXOpen::BlockStyler::Group* group1;// Block type: Group
    NXOpen::BlockStyler::ExpressionBlock* exprDiameter;// Block type: Expression
    NXOpen::BlockStyler::Group* group0;// Block type: Group
    NXOpen::BlockStyler::FaceCollector* FaceSelect;// Block type: Face Collector
    NXOpen::BlockStyler::ReverseDirection* IsReversed;// Block type: Reverse Direction
    NXOpen::BlockStyler::Group* group;// Block type: Group
    NXOpen::BlockStyler::Button* buttonHelix;// Block type: Button
    NXOpen::BlockStyler::SpecifyCSYS* HelixCoordinateSystem;// Block type: Specify Csys
    NXOpen::BlockStyler::Group* group2;// Block type: Group
    NXOpen::BlockStyler::Toggle* isSpline3;// Block type: Toggle
    NXOpen::BlockStyler::ExpressionBlock* tangent;// Block type: Expression
    NXOpen::BlockStyler::Group* group3;// Block type: Group
    NXOpen::BlockStyler::Button* buttonSeal;// Block type: Button
    NXOpen::BlockStyler::ExpressionBlock* lengthOUT;// Block type: Expression
    NXOpen::BlockStyler::ExpressionBlock* widthOUT;// Block type: Expression
    
};
#endif //WIREBUILDERDIALOG_V02_H_INCLUDED
