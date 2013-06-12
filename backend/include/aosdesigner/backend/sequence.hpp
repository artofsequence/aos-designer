#ifndef HGUARD_AOSD_BACKEND_SEQUENCE_HPP__
#define HGUARD_AOSD_BACKEND_SEQUENCE_HPP__
#pragma once

#include <memory>

#include <aosl/sequence.hpp>

#include <aosdesigner/backend/api.hpp>
#include <aosdesigner/backend/id.hpp>
#include <aosdesigner/backend/sequenceinfo.hpp>
#include <aosdesigner/backend/workspaceobject.hpp>


namespace aosd {
namespace backend {

	class Project;

	class AOSD_BACKEND_API Sequence
		: public WorkspaceObject<Sequence>
	{
	public:

		~Sequence();

		SequenceInfo info() const;
		aosl::Sequence aosl_model() const;


	private:
		friend class Project;
		explicit Sequence( Project& project, SequenceInfo info );

		class Impl;
		std::unique_ptr<Impl> impl;

	};


}}


#endif
