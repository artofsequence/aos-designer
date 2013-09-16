
UTILCPP_MAKE_TEST_FOR( aosdesigner-backend 
	SOURCES 
		dataprovider.hpp
		id.cpp
		workqueue.cpp
		eventdispatcher.cpp
		workspaceobject.cpp
		workspace.cpp
		sequence.cpp
		project.cpp
		editor.cpp
	DEPENDENCIES
		tbb
)
