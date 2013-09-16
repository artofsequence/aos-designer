// Copyright (C) 2005-2010 Code Synthesis Tools CC
//
// This program was generated by CodeSynthesis XSD, an XML Schema
// to C++ data binding compiler, in the Proprietary License mode.
// You should have received a proprietary license from Code Synthesis
// Tools CC prior to generating this code. See the license text for
// conditions.
//

#ifndef AOSLCPP_AOSL__META_INL
#define AOSLCPP_AOSL__META_INL

// Begin prologue.
//
//
// End prologue.

#include "aosl/version.hpp"
#include "aosl/version.inl"

#include "aosl/authors.hpp"
#include "aosl/authors.inl"

#include "aosl/targets.hpp"
#include "aosl/targets.inl"

#include "aosl/extension.hpp"
#include "aosl/extension.inl"

namespace aosl
{
  // Meta
  // 

  inline
  const Meta::VersionOptional& Meta::
  version () const
  {
    return this->version_;
  }

  inline
  Meta::VersionOptional& Meta::
  version ()
  {
    return this->version_;
  }

  inline
  void Meta::
  version (const VersionType& x)
  {
    this->version_.set (x);
  }

  inline
  void Meta::
  version (const VersionOptional& x)
  {
    this->version_ = x;
  }

  inline
  void Meta::
  version (::std::auto_ptr< VersionType > x)
  {
    this->version_.set (x);
  }

  inline
  const Meta::AuthorsOptional& Meta::
  authors () const
  {
    return this->authors_;
  }

  inline
  Meta::AuthorsOptional& Meta::
  authors ()
  {
    return this->authors_;
  }

  inline
  void Meta::
  authors (const AuthorsType& x)
  {
    this->authors_.set (x);
  }

  inline
  void Meta::
  authors (const AuthorsOptional& x)
  {
    this->authors_ = x;
  }

  inline
  void Meta::
  authors (::std::auto_ptr< AuthorsType > x)
  {
    this->authors_.set (x);
  }

  inline
  const Meta::DescriptionOptional& Meta::
  description () const
  {
    return this->description_;
  }

  inline
  Meta::DescriptionOptional& Meta::
  description ()
  {
    return this->description_;
  }

  inline
  void Meta::
  description (const DescriptionType& x)
  {
    this->description_.set (x);
  }

  inline
  void Meta::
  description (const DescriptionOptional& x)
  {
    this->description_ = x;
  }

  inline
  void Meta::
  description (::std::auto_ptr< DescriptionType > x)
  {
    this->description_.set (x);
  }

  inline
  const Meta::WebsiteOptional& Meta::
  website () const
  {
    return this->website_;
  }

  inline
  Meta::WebsiteOptional& Meta::
  website ()
  {
    return this->website_;
  }

  inline
  void Meta::
  website (const WebsiteType& x)
  {
    this->website_.set (x);
  }

  inline
  void Meta::
  website (const WebsiteOptional& x)
  {
    this->website_ = x;
  }

  inline
  void Meta::
  website (::std::auto_ptr< WebsiteType > x)
  {
    this->website_.set (x);
  }

  inline
  const Meta::LicenceOptional& Meta::
  licence () const
  {
    return this->licence_;
  }

  inline
  Meta::LicenceOptional& Meta::
  licence ()
  {
    return this->licence_;
  }

  inline
  void Meta::
  licence (const LicenceType& x)
  {
    this->licence_.set (x);
  }

  inline
  void Meta::
  licence (const LicenceOptional& x)
  {
    this->licence_ = x;
  }

  inline
  void Meta::
  licence (::std::auto_ptr< LicenceType > x)
  {
    this->licence_.set (x);
  }

  inline
  const Meta::TargetsOptional& Meta::
  targets () const
  {
    return this->targets_;
  }

  inline
  Meta::TargetsOptional& Meta::
  targets ()
  {
    return this->targets_;
  }

  inline
  void Meta::
  targets (const TargetsType& x)
  {
    this->targets_.set (x);
  }

  inline
  void Meta::
  targets (const TargetsOptional& x)
  {
    this->targets_ = x;
  }

  inline
  void Meta::
  targets (::std::auto_ptr< TargetsType > x)
  {
    this->targets_.set (x);
  }

  inline
  const Meta::InfosOptional& Meta::
  infos () const
  {
    return this->infos_;
  }

  inline
  Meta::InfosOptional& Meta::
  infos ()
  {
    return this->infos_;
  }

  inline
  void Meta::
  infos (const InfosType& x)
  {
    this->infos_.set (x);
  }

  inline
  void Meta::
  infos (const InfosOptional& x)
  {
    this->infos_ = x;
  }

  inline
  void Meta::
  infos (::std::auto_ptr< InfosType > x)
  {
    this->infos_.set (x);
  }
}

// Begin epilogue.
//
//
// End epilogue.

#endif // AOSLCPP_AOSL__META_INL
