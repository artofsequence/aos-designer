#include <aosdesigner/backend/sequence.hpp>

#include <boost/thread/synchronized_value.hpp>

#include <utilcpp/make_unique.hpp>
#include <aoslcpp/algorithm/edition.hpp>

#include <aosdesigner/backend/project.hpp>


namespace aosd {
namespace backend {


	class Sequence::Impl
	{
	public:
		explicit Impl( Sequence& sequence, SequenceInfo info );
		explicit Impl( Sequence& sequence, SequenceInfo info, aosl::Sequence aosl_data );

		SequenceInfo info() const { return *m_info; }
		aosl::Sequence aosl_source() const { return *m_aosl; }

	private:
		Impl( const Impl& ); // = delete;
		Impl& operator=( const Impl& ); // = delete;

		Sequence& m_sequence;
		boost::synchronized_value<SequenceInfo> m_info;
		boost::synchronized_value<aosl::Sequence> m_aosl;

		static aosl::Sequence merge_info_in_aosl( aosl::Sequence aosl_source, const SequenceInfo& info );

	};

	Sequence::Impl::Impl( Sequence& sequence, SequenceInfo info )
		: m_info( info )
		, m_aosl( aoslcpp::make_empty_sequence( info.name, to_string(info.id) ) )
		, m_sequence( sequence )
	{
		if( !is_valid( *m_info ) )
		{
			std::stringstream error_message;
			error_message << "Tried to build a Sequence with invalid informations!"; // TODO: add informations
			throw std::invalid_argument( error_message.str() );
		}

	}

	Sequence::Impl::Impl( Sequence& sequence, SequenceInfo info, aosl::Sequence aosl_data ) // TODO: c++11 constructor...
		: m_info( info ) 
		, m_aosl( merge_info_in_aosl( aosl_data, info ) )
		, m_sequence( sequence )
	{  
		if( !is_valid( info ) )
		{
			std::stringstream error_message;
			error_message << "Tried to build a Sequence with invalid informations!"; // TODO: add informations
			throw std::invalid_argument( error_message.str() );
		}

	}

	aosl::Sequence Sequence::Impl::merge_info_in_aosl( aosl::Sequence aosl_source, const SequenceInfo& info )
	{
		aosl_source.id( aosl::Unique_id(to_string(info.id)) );
		aosl_source.name( info.name );
		return aosl_source;
	}


	///////////////////////////////////


	Sequence::Sequence( Workspace& workspace, SequenceInfo info )
		: WorkspaceObject( workspace, info.id )
		, impl( std::make_unique<Impl>( *this, std::move(info) ) )
	{

	}

	Sequence::Sequence( Workspace& workspace, SequenceInfo info, aosl::Sequence aosl_data )
		: WorkspaceObject( workspace, info.id )
		, impl( std::make_unique<Impl>( *this, std::move(info), std::move(aosl_data) ) ) 
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