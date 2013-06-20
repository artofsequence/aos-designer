#include <aosdesigner/backend/editor.hpp>

#include <boost/thread/synchronized_value.hpp>
#include <utilcpp/make_unique.hpp>

namespace aosd {
namespace backend {

	class Editor::Impl
	{
	public:
		explicit Impl( Editor& editor, EditorInfo info )
			: m_editor( editor )
			, m_info( info )
		{}
		
		EditorInfo info() const { return *m_info; }

	private:
		Impl( const Impl& ); // = delete;
		Impl& operator=( const Impl& ); // = delete;

		Editor& m_editor;
		boost::synchronized_value<EditorInfo> m_info;
	};


	///////////////////////////////////////////////////////////////
	
	Editor::Editor( Workspace& workspace, EditorInfo info )
		: WorkspaceObject( workspace, info.id )
		, m_impl( std::make_unique<Impl>( *this, info ) )
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