// Copyright (C) 2005-2010 Code Synthesis Tools CC
//
// This program was generated by CodeSynthesis XSD, an XML Schema
// to C++ data binding compiler, in the Proprietary License mode.
// You should have received a proprietary license from Code Synthesis
// Tools CC prior to generating this code. See the license text for
// conditions.
//

// Begin prologue.
//

#define AOSLCPP_SOURCE 

//
// End prologue.

#include <xsd/cxx/pre.hxx>

#include "aosl/effect.hpp"

#include <xsd/cxx/xml/dom/wildcard-source.hxx>

#include <xsd/cxx/xml/dom/parsing-source.hxx>

#include <xsd/cxx/tree/type-factory-map.hxx>

#include <xsd/cxx/tree/comparison-map.hxx>

namespace _xsd
{
  static
  const ::xsd::cxx::tree::type_factory_plate< 0, char >
  type_factory_plate_init;

  static
  const ::xsd::cxx::tree::comparison_plate< 0, char >
  comparison_plate_init;
}

namespace aosl
{
  // Effect
  //

  Effect::
  Effect (const TypeType& type)
  : ::xml_schema::Type (),
    dom_document_ (::xsd::cxx::xml::dom::create_document< char > ()),
    any_ (this->dom_document ()),
    type_ (type, ::xml_schema::Flags (), this)
  {
  }

  Effect::
  Effect (const Effect& x,
          ::xml_schema::Flags f,
          ::xml_schema::Container* c)
  : ::xml_schema::Type (x, f, c),
    dom_document_ (::xsd::cxx::xml::dom::create_document< char > ()),
    any_ (x.any_, this->dom_document ()),
    type_ (x.type_, f, this)
  {
  }

  Effect::
  Effect (const ::xercesc::DOMElement& e,
          ::xml_schema::Flags f,
          ::xml_schema::Container* c)
  : ::xml_schema::Type (e, f | ::xml_schema::Flags::base, c),
    dom_document_ (::xsd::cxx::xml::dom::create_document< char > ()),
    any_ (this->dom_document ()),
    type_ (f, this)
  {
    if ((f & ::xml_schema::Flags::base) == 0)
    {
      ::xsd::cxx::xml::dom::parser< char > p (e, true, true);
      this->parse (p, f);
    }
  }

  void Effect::
  parse (::xsd::cxx::xml::dom::parser< char >& p,
         ::xml_schema::Flags f)
  {
    for (; p.more_elements (); p.next_element ())
    {
      const ::xercesc::DOMElement& i (p.cur_element ());
      const ::xsd::cxx::xml::qualified_name< char > n (
        ::xsd::cxx::xml::dom::name< char > (i));

      // any
      //
      if (true)
      {
        ::xercesc::DOMElement* r (
          static_cast< ::xercesc::DOMElement* > (
            this->dom_document ().importNode (
              const_cast< ::xercesc::DOMElement* > (&i), true)));
        this->any_ .push_back (r);
        continue;
      }

      break;
    }

    while (p.more_attributes ())
    {
      const ::xercesc::DOMAttr& i (p.next_attribute ());
      const ::xsd::cxx::xml::qualified_name< char > n (
        ::xsd::cxx::xml::dom::name< char > (i));

      if (n.name () == "type" && n.namespace_ ().empty ())
      {
        ::std::auto_ptr< TypeType > r (
          TypeTraits::create (i, f, this));

        this->type_.set (r);
        continue;
      }
    }

    if (!type_.present ())
    {
      throw ::xsd::cxx::tree::expected_attribute< char > (
        "type",
        "");
    }
  }

  Effect* Effect::
  _clone (::xml_schema::Flags f,
          ::xml_schema::Container* c) const
  {
    return new class Effect (*this, f, c);
  }

  Effect::
  ~Effect ()
  {
  }

  bool
  operator== (const Effect& x, const Effect& y)
  {
    if (!(x.any () == y.any ()))
      return false;

    if (!(x.type () == y.type ()))
      return false;

    return true;
  }

  bool
  operator!= (const Effect& x, const Effect& y)
  {
    return !(x == y);
  }
}

#include <ostream>

#include <xsd/cxx/tree/std-ostream-map.hxx>

namespace _xsd
{
  static
  const ::xsd::cxx::tree::std_ostream_plate< 0, char >
  std_ostream_plate_init;
}

namespace aosl
{
  ::std::ostream&
  operator<< (::std::ostream& o, const Effect& i)
  {
    o << ::std::endl << "type: " << i.type ();
    return o;
  }
}

#include <istream>
#include <xsd/cxx/xml/sax/std-input-source.hxx>
#include <xsd/cxx/tree/error-handler.hxx>

namespace aosl
{
}

#include <ostream>
#include <xsd/cxx/tree/error-handler.hxx>
#include <xsd/cxx/xml/dom/serialization-source.hxx>

#include <xsd/cxx/tree/type-serializer-map.hxx>

namespace _xsd
{
  static
  const ::xsd::cxx::tree::type_serializer_plate< 0, char >
  type_serializer_plate_init;
}

namespace aosl
{
  void
  operator<< (::xercesc::DOMElement& e, const Effect& i)
  {
    e << static_cast< const ::xml_schema::Type& > (i);

    // any
    //
    for (Effect::AnyConstIterator
         b (i.any ().begin ()), n (i.any ().end ());
         b != n; ++b)
    {
      e.appendChild (
        e.getOwnerDocument ()->importNode (
          const_cast< ::xercesc::DOMElement* > (&(*b)), true));
    }

    // type
    //
    {
      ::xercesc::DOMAttr& a (
        ::xsd::cxx::xml::dom::create_attribute (
          "type",
          e));

      a << i.type ();
    }
  }
}

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.

