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

#ifndef _XCAFDoc_SupGeomTool_HeaderFile
#define _XCAFDoc_SupGeomTool_HeaderFile

#include <Standard.hxx>
// #include <Standard_Type.hxx>
#include <TDataStd_GenericEmpty.hxx>
#include <TDF_LabelSequence.hxx>

class gp_Ax2;
class gp_Ax3;
class Standard_GUID;
class TCollection_ExtendedString;
class TDF_Label;

class XCAFDoc_SupGeomTool : public TDataStd_GenericEmpty
{
public:
  DEFINE_DERIVED_ATTRIBUTE(XCAFDoc_SupGeomTool, TDataStd_GenericEmpty)

  //! Returns default attribute GUID
  Standard_EXPORT static const Standard_GUID& GetID();

  //! Create (if not exist) a supplemental geometry tool from XCAFDoc on theLabel.
  Standard_EXPORT static Handle(XCAFDoc_SupGeomTool) Set(const TDF_Label& theLabel);

  //! Creates an empty supplemental geometry tool.
  Standard_EXPORT XCAFDoc_SupGeomTool();

  //! Returns the number of labels in the supplemental geometry.
  Standard_EXPORT Standard_Integer NbSupGeomItems() const;

  //! Returns all labels from the supplemental geometry hive.
  //! The label sequence isn't cleared beforehand.
  //! \param[out]  theSupGeomLabels - sequence of labels.
  Standard_EXPORT void GetAllSupGeom(TDF_LabelSequence& theSupGeomLabels) const;

  //! Adds a a new supplemental geometry item (Coordinate system).
  //! \param[in]  theAx2 - coordinate system to add.
  //! \param[in]  theName - name of the item to add.
  //! \return     the label of the created item.
  Standard_EXPORT TDF_Label
    AddSupGeomItem(const gp_Ax2&                     theAx2,
                   const TCollection_ExtendedString& theName = TCollection_ExtendedString());

  //! Adds a a new supplemental geometry item (Coordinate system).
  //! \param[in]  theAx3 - coordinate system to add.
  //! \param[in]  theName - name of the item to add.
  //! \return     the label of the created item.
  Standard_EXPORT TDF_Label
    AddSupGeomItem(const gp_Ax3&                     theAx3,
                   const TCollection_ExtendedString& theName = TCollection_ExtendedString());

  //! Adds a reference between the given supplemental geometry label and shape label.
  //! \param[in]  theSupGeomLabel - label of supplemental geometry item.
  //! \param[in]  theShapeLabel - label of shape item.
  Standard_EXPORT void AddShapeReference(const TDF_Label& theSupGeomLabel,
                                         const TDF_Label& theShapeLabel) const;

  //! Adds a reference between the given supplemental geometry label and PMI label.
  //! \param[in]  theSupGeomLabel - label of supplemental geometry item.
  //! \param[in]  thePMILabel - label of PMI item.
  Standard_EXPORT void AddPMIReference(const TDF_Label& theSupGeomLabel,
                                       const TDF_Label& thePMILabel) const;

public:
  // Overrides TDF_Attribute virtuals
  Standard_EXPORT const Standard_GUID& ID() const Standard_OVERRIDE;
  Standard_EXPORT Standard_OStream&    Dump(Standard_OStream& theOS) const Standard_OVERRIDE;
};

DEFINE_STANDARD_HANDLE(XCAFDoc_SupGeomTool, TDataStd_GenericEmpty)

#endif // _XCAFDoc_SupGeomTool_HeaderFile
