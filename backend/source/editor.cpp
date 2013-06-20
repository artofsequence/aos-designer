#include <aosdesigner/backend/editor.hpp>

#include <boost/thread/synchronized_value.hpp>
#include <utilcpp/make_unique.hpp>

#include <aosdesigner/backend/sequence.hpp>

namespace aosd {
namespace backend {

	class Editor::Impl
	{
	public:
		explicit Impl( Editor& editor, EditorInfo info, std::shared_ptr<Sequence> sequence );
		
		EditorInfo info() const { return *m_info; }

	private:
		Impl( const Impl& ); // = delete;
		Impl& operator=( const Impl& ); // = delete;

		Editor& m_editor;
		boost::synchronized_value<EditorInfo> m_info;
		std::shared_ptr<Sequence> m_sequence;

	};

	Editor::Impl::Impl( Editor& editor, EditorInfo info, std::shared_ptr<Sequence> sequence ) 
		: m_editor( editor )
		, m_info( std::move(info) )
		, m_sequence( std::move(sequence) )
	{
		// TODO: add tons of checks
	}


	///////////////////////////////////////////////////////////////
	
	Editor::Editor( Workspace& workspace, EditorInfo info, std::shared_ptr<Sequence> sequence )
		: WorkspaceObject( workspace, info.id )
		, m_impl( std::make_unique<Impl>( *this, std::move(info), std::move(sequence) ) )
	{

	}

	Editor::~Editor()
	{

	}

	EditorInfo Editor::info() const
	{
		return m_impl->info();
	}

}}