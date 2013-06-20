#ifndef HGUARD_AOSD_BACKEND_WORKSPACEINTERNALAPI_HPP__
#define HGUARD_AOSD_BACKEND_WORKSPACEINTERNALAPI_HPP__

#include <memory>
#include <boost/thread/mutex.hpp>

#include <aosdesigner/backend/workspace.hpp>
#include <aosdesigner/backend/tools/uri.hpp>

namespace aosd {
namespace backend {


	class Workspace::InternalAPI
	{
	public:
		
		explicit InternalAPI( Workspace::Impl& workspace_impl );

		void add_to_registry( std::shared_ptr<Sequence> sequence );
		void add_to_registry( std::shared_ptr<Editor> sequence );
		void add_to_registry( std::shared_ptr<Library> sequence );

		std::shared_ptr<Sequence> find_or_load( const SequenceId& id, const URI& location );
		std::shared_ptr<Library> find_or_load( const LibraryId& id, const URI& location );

	private:
		Workspace::Impl& m_workspace_impl;
		
	};


}}


#endif
