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

#include "aosl/stage.hpp"

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
  // Stage
  //

  Stage::
  Stage (const IdType& id)
  : ::xml_schema::Type (),
    navigation_ (::xml_schema::Flags (), this),
    script_ (::xml_schema::Flags (), this),
    extension_ (::xml_schema::Flags (), this),
    id_ (id, ::xml_schema::Flags (), this)
  {
  }

  Stage::
  Stage (const Stage& x,
         ::xml_schema::Flags f,
         ::xml_schema::Container* c)
  : ::xml_schema::Type (x, f, c),
    navigation_ (x.navigation_, f, this),
    script_ (x.script_, f, this),
    extension_ (x.extension_, f, this),
    id_ (x.id_, f, this)
  {
  }

  Stage::
  Stage (const ::xercesc::DOMElement& e,
         ::xml_schema::Flags f,
         ::xml_schema::Container* c)
  : ::xml_schema::Type (e, f | ::xml_schema::Flags::base, c),
    navigation_ (f, this),
    script_ (f, this),
    extension_ (f, this),
    id_ (f, this)
  {
    if ((f & ::xml_schema::Flags::base) == 0)
    {
      ::xsd::cxx::xml::dom::parser< char > p (e, true, true);
      this->parse (p, f);
    }
  }

  void Stage::
  parse (::xsd::cxx::xml::dom::parser< char >& p,
         ::xml_schema::Flags f)
  {
    for (; p.more_elements (); p.next_element ())
    {
      const ::xercesc::DOMElement& i (p.cur_element ());
      const ::xsd::cxx::xml::qualified_name< char > n (
        ::xsd::cxx::xml::dom::name< char > (i));

      // navigation
      //
      if (n.name () == "navigation" && n.namespace_ () == "artofsequence.org/aosl/1.0")
      {
        ::std::auto_ptr< NavigationType > r (
          NavigationTraits::create (i, f, this));

        if (!this->navigation_)
        {
          this->navigation_.set (r);
          continue;
        }
      }

      // script
      //
      if (n.name () == "script" && n.namespace_ () == "artofsequence.org/aosl/1.0")
      {
        ::std::auto_ptr< ScriptType > r (
          ScriptTraits::create (i, f, this));

        if (!this->script_)
        {
          this->script_.set (r);
          continue;
        }
      }

      // extension
      //
      if (n.name () == "extension" && n.namespace_ () == "artofsequence.org/aosl/1.0")
      {
        ::std::auto_ptr< ExtensionType > r (
          ExtensionTraits::create (i, f, this));

        if (!this->extension_)
        {
          this->extension_.set (r);
          continue;
        }
      }

      break;
    }

    while (p.more_attributes ())
    {
      const ::xercesc::DOMAttr& i (p.next_attribute ());
      const ::xsd::cxx::xml::qualified_name< char > n (
        ::xsd::cxx::xml::dom::name< char > (i));

      if (n.name () == "id" && n.namespace_ ().empty ())
      {
        ::std::auto_ptr< IdType > r (
          IdTraits::create (i, f, this));

        this->id_.set (r);
        continue;
      }
    }

    if (!id_.present ())
    {
      throw ::xsd::cxx::tree::expected_attribute< char > (
        "id",
        "");
    }
  }

  Stage* Stage::
  _clone (::xml_schema::Flags f,
          ::xml_schema::Container* c) const
  {
    return new class Stage (*this, f, c);
  }

  Stage::
  ~Stage ()
  {
  }

  bool
  operator== (const Stage& x, const Stage& y)
  {
    if (!(x.navigation () == y.navigation ()))
      return false;

    if (!(x.script () == y.script ()))
      return false;

    if (!(x.extension () == y.extension ()))
      return false;

    if (!(x.id () == y.id ()))
      return false;

    return true;
  }

  bool
  operator!= (const Stage& x, const Stage& y)
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
  operator<< (::std::ostream& o, const Stage& i)
  {
    if (i.navigation ())
    {
      o << ::std::endl << "navigation: " << *i.navigation ();
    }

    if (i.script ())
    {
      o << ::std::endl << "script: " << *i.script ();
    }

    if (i.extension ())
    {
      o << ::std::endl << "extension: " << *i.extension ();
    }

    o << ::std::endl << "id: " << i.id ();
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
  operator<< (::xercesc::DOMElement& e, const Stage& i)
  {
    e << static_cast< const ::xml_schema::Type& > (i);

    // navigation
    //
    if (i.navigation ())
    {
      ::xercesc::DOMElement& s (
        ::xsd::cxx::xml::dom::create_element (
          "navigation",
          "artofsequence.org/aosl/1.0",
          e));

      s << *i.navigation ();
    }

    // script
    //
    if (i.script ())
    {
      ::xercesc::DOMElement& s (
        ::xsd::cxx::xml::dom::create_element (
          "script",
          "artofsequence.org/aosl/1.0",
          e));

      s << *i.script ();
    }

    // extension
    //
    if (i.extension ())
    {
      ::xercesc::DOMElement& s (
        ::xsd::cxx::xml::dom::create_element (
          "extension",
          "artofsequence.org/aosl/1.0",
          e));

      s << *i.extension ();
    }

    // id
    //
    {
      ::xercesc::DOMAttr& a (
        ::xsd::cxx::xml::dom::create_attribute (
          "id",
          e));

      a << i.id ();
    }
  }
}

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.
