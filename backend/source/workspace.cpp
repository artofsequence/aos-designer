#include <aosdesigner/backend/workspace.hpp>



namespace aosd {
namespace backend {

	
	Workspace::Workspace( TaskExecutor executor )
		: m_executor( std::move(executor) )
	{

	}

	Workspace::~Workspace()
	{

	}

}}