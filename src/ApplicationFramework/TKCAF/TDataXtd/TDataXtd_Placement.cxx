// Created on: 2009-04-06
// Created by: Sergey ZARITCHNY
// Copyright (c) 2009-2014 OPEN CASCADE SAS
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

#include <BRepBuilderAPI_MakeVertex.hxx>
#include <Standard_GUID.hxx>
#include <Standard_Type.hxx>
#include <TDataStd_RealArray.hxx>
#include <TDataXtd_Placement.hxx>
#include <TDF_Attribute.hxx>
#include <TDF_Label.hxx>
#include <TDF_RelocationTable.hxx>
#include <TNaming_Builder.hxx>
#include <TNaming_NamedShape.hxx>
#include <TopoDS.hxx>

IMPLEMENT_DERIVED_ATTRIBUTE(TDataXtd_Placement, TDataStd_GenericEmpty)

//=================================================================================================

const Standard_GUID& TDataXtd_Placement::GetID()
{
  static Standard_GUID TDataXtd_PlacementID("2a96b60b-ec8b-11d0-bee7-080009dc3333");
  return TDataXtd_PlacementID;
}

//=================================================================================================

Handle(TDataXtd_Placement) TDataXtd_Placement::Set(const TDF_Label& L)
{
  Handle(TDataXtd_Placement) A;
  if (!L.FindAttribute(TDataXtd_Placement::GetID(), A))
  {
    A = new TDataXtd_Placement();
    L.AddAttribute(A);
  }
  return A;
}

//=================================================================================================

Handle(TDataXtd_Placement) TDataXtd_Placement::Set(const TDF_Label& theL, const gp_Ax3& theCS)
{
  Handle(TDataXtd_Placement) theAttr = Set(theL);

  gp_Pnt          aLocPoint = theCS.Location();
  TNaming_Builder B(theL);
  B.Generated(BRepBuilderAPI_MakeVertex(aLocPoint));

  Handle(TColStd_HArray1OfReal) aCSArr = new TColStd_HArray1OfReal(1, 9);
  for (Standard_Integer i = 1; i <= 3; i++)
  {
    aCSArr->SetValue(i, theCS.Direction().Coord(i));
    aCSArr->SetValue(i + 3, theCS.XDirection().Coord(i));
    aCSArr->SetValue(i + 6, theCS.YDirection().Coord(i));
  }

  Handle(TDataStd_RealArray) aLoc = TDataStd_RealArray::Set(theL, 1, 9);
  if (!aLoc.IsNull())
    aLoc->ChangeArray(aCSArr);

  return theAttr;
}

//=================================================================================================

Handle(TDataXtd_Placement) TDataXtd_Placement::Set(const TDF_Label& L, const gp_Ax2& theCS)
{
  gp_Ax3 aCS(theCS.Location(), theCS.Direction(), theCS.XDirection());
  return Set(L, aCS);
}

//=================================================================================================

TDataXtd_Placement::TDataXtd_Placement() {}

//=================================================================================================

const Standard_GUID& TDataXtd_Placement::ID() const
{
  return GetID();
}

//=================================================================================================

Standard_OStream& TDataXtd_Placement::Dump(Standard_OStream& anOS) const
{
  anOS << "Placement";
  return anOS;
}
