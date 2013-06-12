#include <aosdesigner/backend/sequence.hpp>

#include <boost/thread/synchronized_value.hpp>

#include <utilcpp/make_unique.hpp>

#include <aosdesigner/backend/project.hpp>

namespace aosd {
namespace backend {

	class Sequence::Impl
	{
	public:
		explicit Impl( SequenceInfo info )
			: m_info( std::move(info) )
		{  }

		SequenceInfo info() const { return *m_info; }
		aosl::Sequence aosl_source() const { return *m_aosl; }

	private:
		boost::synchronized_value<SequenceInfo> m_info;
		boost::synchronized_value<aosl::Sequence> m_aosl;

	};

	Sequence::Sequence( Workspace& workspace, SequenceInfo info )
		: WorkspaceObject( workspace )
		, impl( std::make_unique<Impl>( std::move(info) ) )
	{

	}

	Sequence::~Sequence()
	{

	}

	SequenceInfo Sequence::info() const
	{
		return impl->info();
	}

	aosl::Sequence Sequence::aosl_source() const
	{
		return impl->aosl_source();
	}




}}