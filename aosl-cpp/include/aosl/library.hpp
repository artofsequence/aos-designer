// Copyright (C) 2005-2010 Code Synthesis Tools CC
//
// This program was generated by CodeSynthesis XSD, an XML Schema
// to C++ data binding compiler, in the Proprietary License mode.
// You should have received a proprietary license from Code Synthesis
// Tools CC prior to generating this code. See the license text for
// conditions.
//

/**
 * @file
 * @brief Generated from library.xsd.
 */

#ifndef AOSLCPP_AOSL__LIBRARY_HPP
#define AOSLCPP_AOSL__LIBRARY_HPP

// Begin prologue.
//

#include <aoslcpp/common.hpp>

//
// End prologue.

#include <xsd/cxx/config.hxx>

#if (XSD_INT_VERSION != 3030000L)
#error XSD runtime version mismatch
#endif

#include <xsd/cxx/pre.hxx>

#include "aosl/library_forward.hpp"

#include <memory>    // std::auto_ptr
#include <limits>    // std::numeric_limits
#include <algorithm> // std::binary_search

#include <xsd/cxx/xml/char-utf8.hxx>

#include <xsd/cxx/tree/exceptions.hxx>
#include <xsd/cxx/tree/elements.hxx>
#include <xsd/cxx/tree/containers.hxx>
#include <xsd/cxx/tree/list.hxx>

#include <xsd/cxx/xml/dom/parsing-header.hxx>

#include <xsd/cxx/tree/containers-wildcard.hxx>

#ifndef XSD_DONT_INCLUDE_INLINE
#define XSD_DONT_INCLUDE_INLINE

#include "aosl/library_include_forward.hpp"

#include "aosl/resource_forward.hpp"

#undef XSD_DONT_INCLUDE_INLINE
#else

#include "aosl/library_include_forward.hpp"

#include "aosl/resource_forward.hpp"

#endif // XSD_DONT_INCLUDE_INLINE

/**
 * @brief C++ namespace for the %artofsequence.org/aosl/1.0
 * schema namespace.
 */
namespace aosl
{
  /**
   * @brief Class corresponding to the %library schema type.
   *
   * The Library contain informations about a set of Resources that can be
   * used in a Sequence.
   *
   * @nosubgrouping
   */
  class Library: public ::xml_schema::Type
  {
    public:
    /**
     * @name include
     *
     * @brief Accessor and modifier functions for the %include
     * sequence element.
     *
     * External libraries to import.
     * Importing a library means getting the resources of the target library
     * and
     * putting them in this one.
     */
    //@{

    /**
     * @brief Element type.
     */
    typedef ::aosl::Library_include IncludeType;

    /**
     * @brief Element sequence container type.
     */
    typedef ::xsd::cxx::tree::sequence< IncludeType > IncludeSequence;

    /**
     * @brief Element iterator type.
     */
    typedef IncludeSequence::iterator IncludeIterator;

    /**
     * @brief Element constant iterator type.
     */
    typedef IncludeSequence::const_iterator IncludeConstIterator;

    /**
     * @brief Element traits type.
     */
    typedef ::xsd::cxx::tree::traits< IncludeType, char > IncludeTraits;

    /**
     * @brief Return a read-only (constant) reference to the element
     * sequence.
     *
     * @return A constant reference to the sequence container.
     */
    const IncludeSequence&
    include () const;

    /**
     * @brief Return a read-write reference to the element sequence.
     *
     * @return A reference to the sequence container.
     */
    IncludeSequence&
    include ();

    /**
     * @brief Copy elements from a given sequence.
     *
     * @param s A sequence to copy elements from.
     *
     * For each element in @a s this function makes a copy and adds it 
     * to the sequence. Note that this operation completely changes the 
     * sequence and all old elements will be lost.
     */
    void
    include (const IncludeSequence& s);

    //@}

    /**
     * @name resource
     *
     * @brief Accessor and modifier functions for the %resource
     * sequence element.
     *
     * Resource to load to play this Sequence.
     * Referenced by one or more objects.
     */
    //@{

    /**
     * @brief Element type.
     */
    typedef ::aosl::Resource ResourceType;

    /**
     * @brief Element sequence container type.
     */
    typedef ::xsd::cxx::tree::sequence< ResourceType > ResourceSequence;

    /**
     * @brief Element iterator type.
     */
    typedef ResourceSequence::iterator ResourceIterator;

    /**
     * @brief Element constant iterator type.
     */
    typedef ResourceSequence::const_iterator ResourceConstIterator;

    /**
     * @brief Element traits type.
     */
    typedef ::xsd::cxx::tree::traits< ResourceType, char > ResourceTraits;

    /**
     * @brief Return a read-only (constant) reference to the element
     * sequence.
     *
     * @return A constant reference to the sequence container.
     */
    const ResourceSequence&
    resource () const;

    /**
     * @brief Return a read-write reference to the element sequence.
     *
     * @return A reference to the sequence container.
     */
    ResourceSequence&
    resource ();

    /**
     * @brief Copy elements from a given sequence.
     *
     * @param s A sequence to copy elements from.
     *
     * For each element in @a s this function makes a copy and adds it 
     * to the sequence. Note that this operation completely changes the 
     * sequence and all old elements will be lost.
     */
    void
    resource (const ResourceSequence& s);

    //@}

    /**
     * @name Constructors
     */
    //@{

    /**
     * @brief Create an instance from the ultimate base and
     * initializers for required elements and attributes.
     */
    Library ();

    /**
     * @brief Create an instance from a DOM element.
     *
     * @param e A DOM element to extract the data from.
     * @param f Flags to create the new instance with.
     * @param c A pointer to the object that will contain the new
     * instance.
     */
    Library (const ::xercesc::DOMElement& e,
             ::xml_schema::Flags f = 0,
             ::xml_schema::Container* c = 0);

    /**
     * @brief Copy constructor.
     *
     * @param x An instance to make a copy of.
     * @param f Flags to create the copy with.
     * @param c A pointer to the object that will contain the copy.
     *
     * For polymorphic object models use the @c _clone function instead.
     */
    Library (const Library& x,
             ::xml_schema::Flags f = 0,
             ::xml_schema::Container* c = 0);

    /**
     * @brief Copy the instance polymorphically.
     *
     * @param f Flags to create the copy with.
     * @param c A pointer to the object that will contain the copy.
     * @return A pointer to the dynamically allocated copy.
     *
     * This function ensures that the dynamic type of the instance is
     * used for copying and should be used for polymorphic object
     * models instead of the copy constructor.
     */
    virtual Library*
    _clone (::xml_schema::Flags f = 0,
            ::xml_schema::Container* c = 0) const;

    //@}

    /**
     * @brief Destructor.
     */
    virtual 
    ~Library ();

    // Implementation.
    //

    //@cond

    protected:
    void
    parse (::xsd::cxx::xml::dom::parser< char >&,
           ::xml_schema::Flags);

    protected:
    IncludeSequence include_;
    ResourceSequence resource_;

    //@endcond
  };

  bool
  operator== (const Library&, const Library&);

  bool
  operator!= (const Library&, const Library&);
}

#ifndef XSD_DONT_INCLUDE_INLINE

#include "aosl/library_include.hpp"
#include "aosl/library_include.inl"

#include "aosl/resource.hpp"
#include "aosl/resource.inl"

#endif // XSD_DONT_INCLUDE_INLINE

#include <iosfwd>

namespace aosl
{
  ::std::ostream&
  operator<< (::std::ostream&, const Library&);
}

#include <iosfwd>

#include <xercesc/sax/InputSource.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMErrorHandler.hpp>

namespace aosl
{
}

#include <iosfwd>

#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMErrorHandler.hpp>
#include <xercesc/framework/XMLFormatter.hpp>

#include <xsd/cxx/xml/dom/auto-ptr.hxx>

namespace aosl
{
  void
  operator<< (::xercesc::DOMElement&, const Library&);
}

#ifndef XSD_DONT_INCLUDE_INLINE
#include "aosl/library.inl"
#endif // XSD_DONT_INCLUDE_INLINE

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.

#endif // AOSLCPP_AOSL__LIBRARY_HPP
