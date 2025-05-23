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

#include <StepAP214_AutoDesignPersonAndOrganizationAssignment.hxx>
#include <StepBasic_PersonAndOrganization.hxx>
#include <StepBasic_PersonAndOrganizationRole.hxx>

IMPLEMENT_STANDARD_RTTIEXT(StepAP214_AutoDesignPersonAndOrganizationAssignment,
                           StepBasic_PersonAndOrganizationAssignment)

StepAP214_AutoDesignPersonAndOrganizationAssignment::
  StepAP214_AutoDesignPersonAndOrganizationAssignment()
{
}

void StepAP214_AutoDesignPersonAndOrganizationAssignment::Init(
  const Handle(StepBasic_PersonAndOrganization)&             aAssignedPersonAndOrganization,
  const Handle(StepBasic_PersonAndOrganizationRole)&         aRole,
  const Handle(StepAP214_HArray1OfAutoDesignGeneralOrgItem)& aItems)
{
  // --- classe own fields ---
  items = aItems;
  // --- classe inherited fields ---
  StepBasic_PersonAndOrganizationAssignment::Init(aAssignedPersonAndOrganization, aRole);
}

void StepAP214_AutoDesignPersonAndOrganizationAssignment::SetItems(
  const Handle(StepAP214_HArray1OfAutoDesignGeneralOrgItem)& aItems)
{
  items = aItems;
}

Handle(StepAP214_HArray1OfAutoDesignGeneralOrgItem)
  StepAP214_AutoDesignPersonAndOrganizationAssignment::Items() const
{
  return items;
}

StepAP214_AutoDesignGeneralOrgItem StepAP214_AutoDesignPersonAndOrganizationAssignment::ItemsValue(
  const Standard_Integer num) const
{
  return items->Value(num);
}

Standard_Integer StepAP214_AutoDesignPersonAndOrganizationAssignment::NbItems() const
{
  return items->Length();
}
