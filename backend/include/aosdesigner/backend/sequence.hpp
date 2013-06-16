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
	
	/** AOSL sequence data, loaded in memory and ready to be modified.
		Each time this Sequence data is modified, it emits events
		which allows observers to update their view of the Sequence.
		@par
		It also provide an AOSL representation, but all modification
		of the source must go through the public interface of Sequence.

		@remark The public member functions are all thread-safe.
		They return futures when the action will be done later 
		(usually on update, which is managed by the associated Workspace,
		@see WorkspaceObject ).
		They return by value or void when the action will be performed
		synchronously, which might imply waiting.
	*/
	class AOSD_BACKEND_API Sequence
		: public WorkspaceObject<Sequence>
	{
	public:

		explicit Sequence( Workspace& workspace, SequenceInfo info );
		explicit Sequence( Workspace& workspace, SequenceInfo info, aosl::Sequence aosl_data );
		~Sequence();

		/** Information about a Sequence, excluding AOSL data. */
		SequenceInfo info() const;

		/** AOSL data representing the current state of the sequence. */
		aosl::Sequence aosl_source() const;


	private:
		
		class Impl;
		std::unique_ptr<Impl> impl;
		void after_update(){}
	};


}}


#endif
