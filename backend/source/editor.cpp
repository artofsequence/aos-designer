#include <aosdesigner/backend/editor.hpp>



namespace aosd {
namespace backend {

	class Editor::Impl
	{
	public:
		explicit Impl( Editor& editor )
			: m_editor( editor )
		{}
		
	private:
		Impl( const Impl& ); // = delete;
		Impl& operator=( const Impl& ); // = delete;

		Editor& m_editor;

	};

	
	Editor::Editor( Workspace& workspace, EditorInfo info )
		: WorkspaceObject( workspace, info.id )
	{

	}

	Editor::~Editor()
	{

	}

}}