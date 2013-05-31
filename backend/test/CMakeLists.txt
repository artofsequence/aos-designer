cmake_minimum_required( VERSION 2.8 )

UTILCPP_MAKE_TEST_FOR( aosdesigner-backend 
	SOURCES 
		id.cpp
		workqueue.cpp
	DEPENDENCIES
		tbb
)
