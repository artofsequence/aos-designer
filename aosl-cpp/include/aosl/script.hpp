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
 * @brief Generated from script.xsd.
 */

#ifndef AOSLCPP_AOSL__SCRIPT_HPP
#define AOSLCPP_AOSL__SCRIPT_HPP

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

#include "aosl/script_forward.hpp"

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

#include "aosl/name_forward.hpp"

#include "aosl/activation_forward.hpp"

#include "aosl/unit_time_forward.hpp"

#undef XSD_DONT_INCLUDE_INLINE
#else

#include "aosl/name_forward.hpp"

#include "aosl/activation_forward.hpp"

#include "aosl/unit_time_forward.hpp"

#endif // XSD_DONT_INCLUDE_INLINE

/**
 * @brief C++ namespace for the %artofsequence.org/aosl/1.0
 * schema namespace.
 */
namespace aosl
{
  /**
   * @brief Class corresponding to the %script schema type.
   *
   * A script is a program that will be executed while the sequence is
   * being played, when the script's owner get activated.
   * No specific language is required but if the player don't know the
   * script's language it
   * will simply ignore it. That make scripts mostly player-specific.
   * 
   * That said, choice of a default language might occur in a future
   * version of this language.
   *
   * @nosubgrouping
   */
  class Script: public ::xml_schema::Type
  {
    public:
    /**
     * @name lang
     *
     * @brief Accessor and modifier functions for the %lang
     * required attribute.
     *
     * Identifier of the programming language used.
     * If the player don't recognize this identifier, it should ignore the
     * whole script.
     */
    //@{

    /**
     * @brief Attribute type.
     */
    typedef ::aosl::Name LangType;

    /**
     * @brief Attribute traits type.
     */
    typedef ::xsd::cxx::tree::traits< LangType, char > LangTraits;

    /**
     * @brief Return a read-only (constant) reference to the attribute.
     *
     * @return A constant reference to the attribute.
     */
    const LangType&
    lang () const;

    /**
     * @brief Return a read-write reference to the attribute.
     *
     * @return A reference to the attribute.
     */
    LangType&
    lang ();

    /**
     * @brief Set the attribute value.
     *
     * @param x A new value to set.
     *
     * This function makes a copy of its argument and sets it as
     * the new value of the attribute.
     */
    void
    lang (const LangType& x);

    /**
     * @brief Set the attribute value without copying.
     *
     * @param p A new value to use.
     *
     * This function will try to use the passed value directly
     * instead of making a copy.
     */
    void
    lang (::std::auto_ptr< LangType > p);

    //@}

    /**
     * @name activation
     *
     * @brief Accessor and modifier functions for the %activation
     * optional attribute with a default value.
     *
     * Define what should happen when an object get activated :
     * - reset : all the script's environnement and variables will be reset
     * to their initial values;
     * - continue : the script's environnement will be saved
     * and the execution process be paused on deactivation and resumed on
     * future activation;
     */
    //@{

    /**
     * @brief Attribute type.
     */
    typedef ::aosl::Activation ActivationType;

    /**
     * @brief Attribute traits type.
     */
    typedef ::xsd::cxx::tree::traits< ActivationType, char > ActivationTraits;

    /**
     * @brief Return a read-only (constant) reference to the attribute.
     *
     * @return A constant reference to the attribute.
     */
    const ActivationType&
    activation () const;

    /**
     * @brief Return a read-write reference to the attribute.
     *
     * @return A reference to the attribute.
     */
    ActivationType&
    activation ();

    /**
     * @brief Set the attribute value.
     *
     * @param x A new value to set.
     *
     * This function makes a copy of its argument and sets it as
     * the new value of the attribute.
     */
    void
    activation (const ActivationType& x);

    /**
     * @brief Set the attribute value without copying.
     *
     * @param p A new value to use.
     *
     * This function will try to use the passed value directly
     * instead of making a copy.
     */
    void
    activation (::std::auto_ptr< ActivationType > p);

    /**
     * @brief Return the default value for the attribute.
     *
     * @return A read-only (constant) reference to the attribute's
     * default value.
     */
    static const ActivationType&
    activation_default_value ();

    //@}

    /**
     * @name loop
     *
     * @brief Accessor and modifier functions for the %loop
     * optional attribute with a default value.
     *
     * A looping script will execute it's code to the end then come back to
     * the first instruction,
     * with only the interval time between each whole script execution and
     * without resetting the execution state.
     * Looping allow a script to be executed on a regular time frequency,
     * making it non-blocking for the player.
     */
    //@{

    /**
     * @brief Attribute type.
     */
    typedef ::xml_schema::Boolean LoopType;

    /**
     * @brief Attribute traits type.
     */
    typedef ::xsd::cxx::tree::traits< LoopType, char > LoopTraits;

    /**
     * @brief Return a read-only (constant) reference to the attribute.
     *
     * @return A constant reference to the attribute.
     */
    const LoopType&
    loop () const;

    /**
     * @brief Return a read-write reference to the attribute.
     *
     * @return A reference to the attribute.
     */
    LoopType&
    loop ();

    /**
     * @brief Set the attribute value.
     *
     * @param x A new value to set.
     *
     * This function makes a copy of its argument and sets it as
     * the new value of the attribute.
     */
    void
    loop (const LoopType& x);

    /**
     * @brief Return the default value for the attribute.
     *
     * @return The attribute's default value.
     */
    static LoopType
    loop_default_value ();

    //@}

    /**
     * @name interval
     *
     * @brief Accessor and modifier functions for the %interval
     * optional attribute with a default value.
     *
     * Time interval between each script execution.
     * This interval will be used only if the script is looping.
     * The first execution don't take account of the interval and should be
     * immediate
     * on script activation.
     */
    //@{

    /**
     * @brief Attribute type.
     */
    typedef ::aosl::Unit_time IntervalType;

    /**
     * @brief Attribute traits type.
     */
    typedef ::xsd::cxx::tree::traits< IntervalType, char > IntervalTraits;

    /**
     * @brief Return a read-only (constant) reference to the attribute.
     *
     * @return A constant reference to the attribute.
     */
    const IntervalType&
    interval () const;

    /**
     * @brief Return a read-write reference to the attribute.
     *
     * @return A reference to the attribute.
     */
    IntervalType&
    interval ();

    /**
     * @brief Set the attribute value.
     *
     * @param x A new value to set.
     *
     * This function makes a copy of its argument and sets it as
     * the new value of the attribute.
     */
    void
    interval (const IntervalType& x);

    /**
     * @brief Set the attribute value without copying.
     *
     * @param p A new value to use.
     *
     * This function will try to use the passed value directly
     * instead of making a copy.
     */
    void
    interval (::std::auto_ptr< IntervalType > p);

    /**
     * @brief Return the default value for the attribute.
     *
     * @return The attribute's default value.
     */
    static IntervalType
    interval_default_value ();

    //@}

    /**
     * @name source
     *
     * @brief Accessor and modifier functions for the %source
     * optional attribute.
     *
     * URI to a file containing the source code of the script.
     * The source code will be inserted before any source code written
     * directly in this script element.
     * Therefore, if this script element don't have inner code but just a
     * source,
     * only the source script code will be the executed.
     */
    //@{

    /**
     * @brief Attribute type.
     */
    typedef ::xml_schema::Uri SourceType;

    /**
     * @brief Attribute optional container type.
     */
    typedef ::xsd::cxx::tree::optional< SourceType > SourceOptional;

    /**
     * @brief Attribute traits type.
     */
    typedef ::xsd::cxx::tree::traits< SourceType, char > SourceTraits;

    /**
     * @brief Return a read-only (constant) reference to the attribute
     * container.
     *
     * @return A constant reference to the optional container.
     */
    const SourceOptional&
    source () const;

    /**
     * @brief Return a read-write reference to the attribute container.
     *
     * @return A reference to the optional container.
     */
    SourceOptional&
    source ();

    /**
     * @brief Set the attribute value.
     *
     * @param x A new value to set.
     *
     * This function makes a copy of its argument and sets it as
     * the new value of the attribute.
     */
    void
    source (const SourceType& x);

    /**
     * @brief Set the attribute value.
     *
     * @param x An optional container with the new value to set.
     *
     * If the value is present in @a x then this function makes a copy 
     * of this value and sets it as the new value of the attribute.
     * Otherwise the attribute container is set the 'not present' state.
     */
    void
    source (const SourceOptional& x);

    /**
     * @brief Set the attribute value without copying.
     *
     * @param p A new value to use.
     *
     * This function will try to use the passed value directly instead
     * of making a copy.
     */
    void
    source (::std::auto_ptr< SourceType > p);

    //@}

    /**
     * @name Constructors
     */
    //@{

    /**
     * @brief Create an instance from the ultimate base and
     * initializers for required elements and attributes.
     */
    Script (const LangType&);

    /**
     * @brief Create an instance from a DOM element.
     *
     * @param e A DOM element to extract the data from.
     * @param f Flags to create the new instance with.
     * @param c A pointer to the object that will contain the new
     * instance.
     */
    Script (const ::xercesc::DOMElement& e,
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
    Script (const Script& x,
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
    virtual Script*
    _clone (::xml_schema::Flags f = 0,
            ::xml_schema::Container* c = 0) const;

    //@}

    /**
     * @brief Destructor.
     */
    virtual 
    ~Script ();

    // Implementation.
    //

    //@cond

    protected:
    void
    parse (::xsd::cxx::xml::dom::parser< char >&,
           ::xml_schema::Flags);

    protected:
    ::xsd::cxx::tree::one< LangType > lang_;
    ::xsd::cxx::tree::one< ActivationType > activation_;
    static const ActivationType activation_default_value_;
    ::xsd::cxx::tree::one< LoopType > loop_;
    ::xsd::cxx::tree::one< IntervalType > interval_;
    SourceOptional source_;

    //@endcond
  };

  bool
  operator== (const Script&, const Script&);

  bool
  operator!= (const Script&, const Script&);
}

#ifndef XSD_DONT_INCLUDE_INLINE

#include "aosl/name.hpp"
#include "aosl/name.inl"

#include "aosl/activation.hpp"
#include "aosl/activation.inl"

#include "aosl/unit_time.hpp"
#include "aosl/unit_time.inl"

#endif // XSD_DONT_INCLUDE_INLINE

#include <iosfwd>

namespace aosl
{
  ::std::ostream&
  operator<< (::std::ostream&, const Script&);
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
  operator<< (::xercesc::DOMElement&, const Script&);
}

#ifndef XSD_DONT_INCLUDE_INLINE
#include "aosl/script.inl"
#endif // XSD_DONT_INCLUDE_INLINE

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.

#endif // AOSLCPP_AOSL__SCRIPT_HPP
