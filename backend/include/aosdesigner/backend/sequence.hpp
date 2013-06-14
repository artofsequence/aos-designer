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

	class Workspace;
	
	class AOSD_BACKEND_API Sequence
		: public WorkspaceObject<Sequence>
	{
	public:

		explicit Sequence( Workspace& workspace, SequenceInfo info );
		explicit Sequence( Workspace& workspace, SequenceInfo info, aosl::Sequence aosl_data );
		~Sequence();

		SequenceInfo info() const;
		aosl::Sequence aosl_source() const;


	private:
		
		class Impl;
		std::unique_ptr<Impl> impl;
		void after_update(){}
	};


}}


#endif
