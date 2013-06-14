#ifndef HGUARD_AOSD_BACKEND_WORKSPACEINTERNALAPI_HPP__
#define HGUARD_AOSD_BACKEND_WORKSPACEINTERNALAPI_HPP__

#include <memory>
#include <aosdesigner/backend/workspace.hpp>

namespace aosd {
namespace backend {

	class Workspace::InternalAPI
	{
	public:
		
		explicit InternalAPI( Workspace::Impl& workspace_impl );

		void add_to_registry( std::shared_ptr<Sequence> sequence );

	private:
		Workspace::Impl& m_workspace_impl;

	};


}}


#endif
