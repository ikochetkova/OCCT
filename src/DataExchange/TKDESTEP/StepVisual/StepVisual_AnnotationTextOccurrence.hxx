// Created on: 1995-12-01
// Created by: EXPRESS->CDL V0.2 Translator
// Copyright (c) 1995-1999 Matra Datavision
// Copyright (c) 1999-2014 OPEN CASCADE SAS
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

#ifndef _StepVisual_AnnotationTextOccurrence_HeaderFile
#define _StepVisual_AnnotationTextOccurrence_HeaderFile

#include <Standard.hxx>

#include <StepVisual_AnnotationOccurrence.hxx>

class StepVisual_AnnotationTextOccurrence;
DEFINE_STANDARD_HANDLE(StepVisual_AnnotationTextOccurrence, StepVisual_AnnotationOccurrence)

class StepVisual_AnnotationTextOccurrence : public StepVisual_AnnotationOccurrence
{

public:
  //! Returns a AnnotationTextOccurrence
  Standard_EXPORT StepVisual_AnnotationTextOccurrence();

  DEFINE_STANDARD_RTTIEXT(StepVisual_AnnotationTextOccurrence, StepVisual_AnnotationOccurrence)

protected:
private:
};

#endif // _StepVisual_AnnotationTextOccurrence_HeaderFile
