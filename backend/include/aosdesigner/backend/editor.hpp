#ifndef HGUARD_AOSD_BACKEND_EDITOR_HPP__
#define HGUARD_AOSD_BACKEND_EDITOR_HPP__
#pragma once

#include <aosdesigner/backend/id.hpp>
#include <aosdesigner/backend/workspaceobject.hpp>
#include <aosdesigner/backend/info/editorinfo.hpp>
#include <aosdesigner/backend/events/editorevents.hpp>

namespace aosd {
namespace backend {

	class Sequence;

	class AOSD_BACKEND_API Editor
		: public WorkspaceObject<Editor>
	{
	public:
		explicit Editor( Workspace& workspace, EditorInfo info, std::shared_ptr<Sequence> sequence );
		~Editor();

		EditorInfo info() const;

	private:
		

		class Impl;
		std::unique_ptr<Impl> m_impl;

	};

}}


#endif