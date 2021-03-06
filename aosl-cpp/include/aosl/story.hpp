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
 * @brief Generated from story.xsd.
 */

#ifndef AOSLCPP_AOSL__STORY_HPP
#define AOSLCPP_AOSL__STORY_HPP

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

#include "aosl/story_forward.hpp"

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

#include "aosl/property_forward.hpp"

#include "aosl/navigation_forward.hpp"

#include "aosl/stages_forward.hpp"

#include "aosl/moves_forward.hpp"

#include "aosl/stage_ref_forward.hpp"

#undef XSD_DONT_INCLUDE_INLINE
#else

#include "aosl/property_forward.hpp"

#include "aosl/navigation_forward.hpp"

#include "aosl/stages_forward.hpp"

#include "aosl/moves_forward.hpp"

#include "aosl/stage_ref_forward.hpp"

#endif // XSD_DONT_INCLUDE_INLINE

/**
 * @brief C++ namespace for the %artofsequence.org/aosl/1.0
 * schema namespace.
 */
namespace aosl
{
  /**
   * @brief Class corresponding to the %story schema type.
   *
   * The Story describe the structure of the sequence : the relation
   * between the different stages of the sequence.
   * It's made of Stages connected by Moves, describing what should happens
   * when we get from one Stage to another.
   *
   * @nosubgrouping
   */
  class Story: public ::xml_schema::Type
  {
    public:
    /**
     * @name properties
     *
     * @brief Accessor and modifier functions for the %properties
     * optional element.
     *
     * Initial custom properties available through the playing of this
     * Sequence.
     * Those properties are available to all scripts and can be used by the
     * interpreter too.
     */
    //@{

    /**
     * @brief Element type.
     */
    typedef ::aosl::Property PropertiesType;

    /**
     * @brief Element optional container type.
     */
    typedef ::xsd::cxx::tree::optional< PropertiesType > PropertiesOptional;

    /**
     * @brief Element traits type.
     */
    typedef ::xsd::cxx::tree::traits< PropertiesType, char > PropertiesTraits;

    /**
     * @brief Return a read-only (constant) reference to the element
     * container.
     *
     * @return A constant reference to the optional container.
     */
    const PropertiesOptional&
    properties () const;

    /**
     * @brief Return a read-write reference to the element container.
     *
     * @return A reference to the optional container.
     */
    PropertiesOptional&
    properties ();

    /**
     * @brief Set the element value.
     *
     * @param x A new value to set.
     *
     * This function makes a copy of its argument and sets it as
     * the new value of the element.
     */
    void
    properties (const PropertiesType& x);

    /**
     * @brief Set the element value.
     *
     * @param x An optional container with the new value to set.
     *
     * If the value is present in @a x then this function makes a copy 
     * of this value and sets it as the new value of the element.
     * Otherwise the element container is set the 'not present' state.
     */
    void
    properties (const PropertiesOptional& x);

    /**
     * @brief Set the element value without copying.
     *
     * @param p A new value to use.
     *
     * This function will try to use the passed value directly instead
     * of making a copy.
     */
    void
    properties (::std::auto_ptr< PropertiesType > p);

    //@}

    /**
     * @name navigation
     *
     * @brief Accessor and modifier functions for the %navigation
     * optional element.
     *
     * Navigation configuration used for the whole sequence. Can be
     * overloaded at each Stage of the Sequence.
     */
    //@{

    /**
     * @brief Element type.
     */
    typedef ::aosl::Navigation NavigationType;

    /**
     * @brief Element optional container type.
     */
    typedef ::xsd::cxx::tree::optional< NavigationType > NavigationOptional;

    /**
     * @brief Element traits type.
     */
    typedef ::xsd::cxx::tree::traits< NavigationType, char > NavigationTraits;

    /**
     * @brief Return a read-only (constant) reference to the element
     * container.
     *
     * @return A constant reference to the optional container.
     */
    const NavigationOptional&
    navigation () const;

    /**
     * @brief Return a read-write reference to the element container.
     *
     * @return A reference to the optional container.
     */
    NavigationOptional&
    navigation ();

    /**
     * @brief Set the element value.
     *
     * @param x A new value to set.
     *
     * This function makes a copy of its argument and sets it as
     * the new value of the element.
     */
    void
    navigation (const NavigationType& x);

    /**
     * @brief Set the element value.
     *
     * @param x An optional container with the new value to set.
     *
     * If the value is present in @a x then this function makes a copy 
     * of this value and sets it as the new value of the element.
     * Otherwise the element container is set the 'not present' state.
     */
    void
    navigation (const NavigationOptional& x);

    /**
     * @brief Set the element value without copying.
     *
     * @param p A new value to use.
     *
     * This function will try to use the passed value directly instead
     * of making a copy.
     */
    void
    navigation (::std::auto_ptr< NavigationType > p);

    //@}

    /**
     * @name stages
     *
     * @brief Accessor and modifier functions for the %stages
     * required element.
     *
     * Stages of this Sequence.
     */
    //@{

    /**
     * @brief Element type.
     */
    typedef ::aosl::Stages StagesType;

    /**
     * @brief Element traits type.
     */
    typedef ::xsd::cxx::tree::traits< StagesType, char > StagesTraits;

    /**
     * @brief Return a read-only (constant) reference to the element.
     *
     * @return A constant reference to the element.
     */
    const StagesType&
    stages () const;

    /**
     * @brief Return a read-write reference to the element.
     *
     * @return A reference to the element.
     */
    StagesType&
    stages ();

    /**
     * @brief Set the element value.
     *
     * @param x A new value to set.
     *
     * This function makes a copy of its argument and sets it as
     * the new value of the element.
     */
    void
    stages (const StagesType& x);

    /**
     * @brief Set the element value without copying.
     *
     * @param p A new value to use.
     *
     * This function will try to use the passed value directly
     * instead of making a copy.
     */
    void
    stages (::std::auto_ptr< StagesType > p);

    //@}

    /**
     * @name moves
     *
     * @brief Accessor and modifier functions for the %moves
     * required element.
     *
     * Moves, containing Changes between Stages.
     */
    //@{

    /**
     * @brief Element type.
     */
    typedef ::aosl::Moves MovesType;

    /**
     * @brief Element traits type.
     */
    typedef ::xsd::cxx::tree::traits< MovesType, char > MovesTraits;

    /**
     * @brief Return a read-only (constant) reference to the element.
     *
     * @return A constant reference to the element.
     */
    const MovesType&
    moves () const;

    /**
     * @brief Return a read-write reference to the element.
     *
     * @return A reference to the element.
     */
    MovesType&
    moves ();

    /**
     * @brief Set the element value.
     *
     * @param x A new value to set.
     *
     * This function makes a copy of its argument and sets it as
     * the new value of the element.
     */
    void
    moves (const MovesType& x);

    /**
     * @brief Set the element value without copying.
     *
     * @param p A new value to use.
     *
     * This function will try to use the passed value directly
     * instead of making a copy.
     */
    void
    moves (::std::auto_ptr< MovesType > p);

    //@}

    /**
     * @name begin
     *
     * @brief Accessor and modifier functions for the %begin
     * required attribute.
     *
     * The Stage to begin the Sequence with.
     */
    //@{

    /**
     * @brief Attribute type.
     */
    typedef ::aosl::Stage_ref BeginType;

    /**
     * @brief Attribute traits type.
     */
    typedef ::xsd::cxx::tree::traits< BeginType, char > BeginTraits;

    /**
     * @brief Return a read-only (constant) reference to the attribute.
     *
     * @return A constant reference to the attribute.
     */
    const BeginType&
    begin () const;

    /**
     * @brief Return a read-write reference to the attribute.
     *
     * @return A reference to the attribute.
     */
    BeginType&
    begin ();

    /**
     * @brief Set the attribute value.
     *
     * @param x A new value to set.
     *
     * This function makes a copy of its argument and sets it as
     * the new value of the attribute.
     */
    void
    begin (const BeginType& x);

    /**
     * @brief Set the attribute value without copying.
     *
     * @param p A new value to use.
     *
     * This function will try to use the passed value directly
     * instead of making a copy.
     */
    void
    begin (::std::auto_ptr< BeginType > p);

    //@}

    /**
     * @name Constructors
     */
    //@{

    /**
     * @brief Create an instance from the ultimate base and
     * initializers for required elements and attributes.
     */
    Story (const StagesType&,
           const MovesType&,
           const BeginType&);

    /**
     * @brief Create an instance from the ultimate base and
     * initializers for required elements and attributes
     * (auto_ptr version).
     *
     * This constructor will try to use the passed values directly
     * instead of making copies.
     */
    Story (::std::auto_ptr< StagesType >&,
           ::std::auto_ptr< MovesType >&,
           const BeginType&);

    /**
     * @brief Create an instance from a DOM element.
     *
     * @param e A DOM element to extract the data from.
     * @param f Flags to create the new instance with.
     * @param c A pointer to the object that will contain the new
     * instance.
     */
    Story (const ::xercesc::DOMElement& e,
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
    Story (const Story& x,
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
    virtual Story*
    _clone (::xml_schema::Flags f = 0,
            ::xml_schema::Container* c = 0) const;

    //@}

    /**
     * @brief Destructor.
     */
    virtual 
    ~Story ();

    // Implementation.
    //

    //@cond

    protected:
    void
    parse (::xsd::cxx::xml::dom::parser< char >&,
           ::xml_schema::Flags);

    protected:
    PropertiesOptional properties_;
    NavigationOptional navigation_;
    ::xsd::cxx::tree::one< StagesType > stages_;
    ::xsd::cxx::tree::one< MovesType > moves_;
    ::xsd::cxx::tree::one< BeginType > begin_;

    //@endcond
  };

  bool
  operator== (const Story&, const Story&);

  bool
  operator!= (const Story&, const Story&);
}

#ifndef XSD_DONT_INCLUDE_INLINE

#include "aosl/property.hpp"
#include "aosl/property.inl"

#include "aosl/navigation.hpp"
#include "aosl/navigation.inl"

#include "aosl/stages.hpp"
#include "aosl/stages.inl"

#include "aosl/moves.hpp"
#include "aosl/moves.inl"

#include "aosl/stage_ref.hpp"
#include "aosl/stage_ref.inl"

#endif // XSD_DONT_INCLUDE_INLINE

#include <iosfwd>

namespace aosl
{
  ::std::ostream&
  operator<< (::std::ostream&, const Story&);
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
  operator<< (::xercesc::DOMElement&, const Story&);
}

#ifndef XSD_DONT_INCLUDE_INLINE
#include "aosl/story.inl"
#endif // XSD_DONT_INCLUDE_INLINE

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.

#endif // AOSLCPP_AOSL__STORY_HPP
