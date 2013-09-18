// Copyright (C) 2005-2010 Code Synthesis Tools CC
//
// This program was generated by CodeSynthesis XSD, an XML Schema
// to C++ data binding compiler, in the Proprietary License mode.
// You should have received a proprietary license from Code Synthesis
// Tools CC prior to generating this code. See the license text for
// conditions.
//

#ifndef AOSLCPP_AOSL__RESOURCE_TYPE_GENERIC_INL
#define AOSLCPP_AOSL__RESOURCE_TYPE_GENERIC_INL

// Begin prologue.
//
//
// End prologue.

namespace aosl
{
  // Resource_type_generic
  // 

  inline
  Resource_type_generic::
  Resource_type_generic (Value v)
  : ::xml_schema::String (_xsd_Resource_type_generic_literals_[v])
  {
  }

  inline
  Resource_type_generic::
  Resource_type_generic (const char* v)
  : ::xml_schema::String (v)
  {
  }

  inline
  Resource_type_generic::
  Resource_type_generic (const ::std::string& v)
  : ::xml_schema::String (v)
  {
  }

  inline
  Resource_type_generic::
  Resource_type_generic (const ::xml_schema::String& v)
  : ::xml_schema::String (v)
  {
  }

  inline
  Resource_type_generic::
  Resource_type_generic (const Resource_type_generic& v,
                         ::xml_schema::Flags f,
                         ::xml_schema::Container* c)
  : ::xml_schema::String (v, f, c)
  {
  }

  inline
  Resource_type_generic& Resource_type_generic::
  operator= (Value v)
  {
    static_cast< ::xml_schema::String& > (*this) = 
    ::xml_schema::String (_xsd_Resource_type_generic_literals_[v]);

    return *this;
  }
}

// Begin epilogue.
//
//
// End epilogue.

#endif // AOSLCPP_AOSL__RESOURCE_TYPE_GENERIC_INL