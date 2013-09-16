// Copyright (C) 2005-2010 Code Synthesis Tools CC
//
// This program was generated by CodeSynthesis XSD, an XML Schema
// to C++ data binding compiler, in the Proprietary License mode.
// You should have received a proprietary license from Code Synthesis
// Tools CC prior to generating this code. See the license text for
// conditions.
//

#ifndef AOSLCPP_AOSL__CHANGE_TRANSFORM_INL
#define AOSLCPP_AOSL__CHANGE_TRANSFORM_INL

// Begin prologue.
//
//
// End prologue.

#include "aosl/change.inl"

#include "aosl/transformation.hpp"
#include "aosl/transformation.inl"

namespace aosl
{
  // Change_transform
  // 

  inline
  const Change_transform::RelativeSequence& Change_transform::
  relative () const
  {
    return this->relative_;
  }

  inline
  Change_transform::RelativeSequence& Change_transform::
  relative ()
  {
    return this->relative_;
  }

  inline
  void Change_transform::
  relative (const RelativeSequence& s)
  {
    this->relative_ = s;
  }

  inline
  const Change_transform::AbsoluteSequence& Change_transform::
  absolute () const
  {
    return this->absolute_;
  }

  inline
  Change_transform::AbsoluteSequence& Change_transform::
  absolute ()
  {
    return this->absolute_;
  }

  inline
  void Change_transform::
  absolute (const AbsoluteSequence& s)
  {
    this->absolute_ = s;
  }
}

// Begin epilogue.
//
//
// End epilogue.

#endif // AOSLCPP_AOSL__CHANGE_TRANSFORM_INL
