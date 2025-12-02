// Copyright (c) 2025 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#include <XCAFDoc_SupGeomTool.hxx>

#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <Geom_Curve.hxx>
#include <Geom_Surface.hxx>
#include <gp_Ax2.hxx>
#include <gp_Ax3.hxx>
#include <TCollection_ExtendedString.hxx>
#include <TDataStd_Name.hxx>
#include <TDataStd_TreeNode.hxx>
#include <TDataXtd_Placement.hxx>
#include <TDF_ChildIterator.hxx>
#include <TDF_LabelSequence.hxx>
#include <TNaming_Builder.hxx>
#include <TNaming_NamedShape.hxx>
#include <XCAFDoc.hxx>

IMPLEMENT_DERIVED_ATTRIBUTE(XCAFDoc_SupGeomTool, TDataStd_GenericEmpty)

//=================================================================================================

const Standard_GUID& XCAFDoc_SupGeomTool::GetID()
{
  static Standard_GUID aID("7c12bb38-8090-4a91-b720-32dcdcf161f8");
  return aID;
}

//=================================================================================================

Handle(XCAFDoc_SupGeomTool) XCAFDoc_SupGeomTool::Set(const TDF_Label& theLabel)
{
  Handle(XCAFDoc_SupGeomTool) aTool;
  if (!theLabel.IsNull() && !theLabel.FindAttribute(XCAFDoc_SupGeomTool::GetID(), aTool))
  {
    aTool = new XCAFDoc_SupGeomTool();
    theLabel.AddAttribute(aTool);
  }
  return aTool;
}

//=================================================================================================

XCAFDoc_SupGeomTool::XCAFDoc_SupGeomTool() {}

//=================================================================================================

Standard_Integer XCAFDoc_SupGeomTool::NbSupGeomItems() const
{
  Standard_Integer aNbItems = 0;
  for (TDF_ChildIterator anIter(Label()); anIter.More(); anIter.Next())
  {
    Handle(TNaming_NamedShape) aNS;
    if (anIter.Value().FindAttribute(TNaming_NamedShape::GetID(), aNS))
      ++aNbItems;
  }
  return aNbItems;
}

//=================================================================================================

void XCAFDoc_SupGeomTool::GetAllSupGeom(TDF_LabelSequence& theLabels) const
{
  for (TDF_ChildIterator anIter(Label()); anIter.More(); anIter.Next())
  {
    Handle(TNaming_NamedShape) aNS;
    if (anIter.Value().FindAttribute(TNaming_NamedShape::GetID(), aNS))
      theLabels.Append(anIter.Value());
  }
}

//=================================================================================================

TDF_Label XCAFDoc_SupGeomTool::AddSupGeomItem(const gp_Ax2&                     theAx2,
                                              const TCollection_ExtendedString& theName)
{
  gp_Ax3 anAx3(theAx2);
  return AddSupGeomItem(anAx3, theName);
}

//=================================================================================================

TDF_Label XCAFDoc_SupGeomTool::AddSupGeomItem(const gp_Ax3&                     theAx3,
                                              const TCollection_ExtendedString& theName)
{
  TDF_Label aNewLabel = Label().NewChild();
  TDataXtd_Placement::Set(aNewLabel, theAx3);
  if (!theName.IsEmpty())
  {
    TDataStd_Name::Set(aNewLabel, theName);
  }
  return aNewLabel;
}

//=================================================================================================

TDF_Label XCAFDoc_SupGeomTool::AddSupGeomItem(const gp_Pnt&                     thePnt,
                                              const TCollection_ExtendedString& theName)
{
  TDF_Label aNewLabel = Label().NewChild();
  TNaming_Builder aB(aNewLabel);
  aB.Generated(BRepBuilderAPI_MakeVertex(thePnt));
  if (!theName.IsEmpty())
  {
    TDataStd_Name::Set(aNewLabel, theName);
  }
  return aNewLabel;
}

//=================================================================================================

TDF_Label XCAFDoc_SupGeomTool::AddSupGeomItem(const Handle(Geom_Curve)&         theCurve,
                                              const TCollection_ExtendedString& theName)
{
  TDF_Label       aNewLabel = Label().NewChild();
  TNaming_Builder aB(aNewLabel);

  BRepBuilderAPI_MakeEdge aMaker;
  aMaker.Init(theCurve);
  if (!aMaker.IsDone())
  {
    return aNewLabel;
  }

  aB.Generated(aMaker.Shape());
  if (!theName.IsEmpty())
  {
    TDataStd_Name::Set(aNewLabel, theName);
  }
  return aNewLabel;
}

//=================================================================================================

TDF_Label XCAFDoc_SupGeomTool::AddSupGeomItem(const Handle(Geom_Surface)&       theSurface,
                                              const TCollection_ExtendedString& theName)
{
  TDF_Label       aNewLabel = Label().NewChild();
  TNaming_Builder aB(aNewLabel);

  BRepBuilderAPI_MakeFace aMaker;
  aMaker.Init(theSurface, Standard_True, Precision::Confusion());
  if (!aMaker.IsDone())
  {
    return aNewLabel;
  }

  aB.Generated(aMaker.Shape());
  if (!theName.IsEmpty())
  {
    TDataStd_Name::Set(aNewLabel, theName);
  }
  return aNewLabel;
}

//=================================================================================================

void XCAFDoc_SupGeomTool::AddShapeReference(const TDF_Label& theSupGeomLabel,
                                            const TDF_Label& theShapeLabel) const
{
  Handle(TDataStd_TreeNode) aMainNode =
    TDataStd_TreeNode::Set(theShapeLabel, XCAFDoc::SupplementalRefShapeGUID());
  Handle(TDataStd_TreeNode) aRefNode =
    TDataStd_TreeNode::Set(theSupGeomLabel, XCAFDoc::SupplementalRefShapeGUID());
  aRefNode->Remove();
  aMainNode->Append(aRefNode);
}

//=================================================================================================

void XCAFDoc_SupGeomTool::AddPMIReference(const TDF_Label& theSupGeomLabel,
                                          const TDF_Label& thePMILabel) const
{
  Handle(TDataStd_TreeNode) aMainNode =
    TDataStd_TreeNode::Set(thePMILabel, XCAFDoc::SupplementalRefPMIGUID());
  Handle(TDataStd_TreeNode) aRefNode =
    TDataStd_TreeNode::Set(theSupGeomLabel, XCAFDoc::SupplementalRefPMIGUID());
  aRefNode->Remove();
  aMainNode->Append(aRefNode);
}

//=================================================================================================

const Standard_GUID& XCAFDoc_SupGeomTool::ID() const
{
  return GetID();
}

//=================================================================================================

Standard_OStream& XCAFDoc_SupGeomTool::Dump(Standard_OStream& theOS) const
{
  theOS << "SupGeom items   : " << NbSupGeomItems() << "\n";
  return theOS;
}
