#include "FreeWindowManager.hpp"

#include <QMdiArea>
#include <QMdiSubWindow>

namespace aosd
{
namespace view
{

	FreeWindowManager::FreeWindowManager( QMdiArea& internal_area )
		: m_internal_area( internal_area )
	{

	}

	FreeWindowManager::~FreeWindowManager()
	{
		clear();
	}

	FreeWindow& FreeWindowManager::add_window( QWidget& widget )
	{
		{
			auto free_window = std::unique_ptr<FreeWindow>( new FreeWindow( widget, m_internal_area ) );
			m_windows_registry.insert( std::make_pair( &widget, std::move( free_window ) ) );

		}

		{
			auto& free_window = *m_windows_registry[ &widget ];
			free_window.go_inside();

			return free_window;
		}
	}

	void FreeWindowManager::remove_window( QWidget& widget )
	{
		// TODO : do it in one search instead of two
		auto free_window = find_window( widget );
		if( free_window )
		{
			m_windows_registry.erase( &widget );
		}
		
	}

	void FreeWindowManager::clear()
	{
		m_windows_registry.clear();
	}

	FreeWindow* FreeWindowManager::find_window( QWidget& widget )
	{
		auto free_window_it = m_windows_registry.find( &widget );
		if( free_window_it != m_windows_registry.end() )
			return free_window_it->second.get();
		else
			return nullptr;
	}

}
}