#ifndef HGUARD_AOSD_BACKEND_LIBRARY_HPP__
#define HGUARD_AOSD_BACKEND_LIBRARY_HPP__
#pragma once

#include <aosdesigner/backend/api.hpp>
#include <aosdesigner/backend/workspaceobject.hpp>

namespace aosd {
namespace backend {
	
	class AOSD_BACKEND_API Library
		: public WorkspaceObject<Library>
	{
	public:
		~Library();


	private:
		friend class Project;
		explicit Library( Project& project );
		
		class Impl;
		std::unique_ptr<Impl> impl;

	};

}}


#endif
