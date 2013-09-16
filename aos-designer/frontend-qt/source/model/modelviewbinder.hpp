#ifndef HGUARD_AOSD_VIEW_MODELREGISTRY_HPP__
#define HGUARD_AOSD_VIEW_MODELREGISTRY_HPP__
#pragma once

#include <map>
#include <memory>
#include <QAbstractItemView>

#include <utilcpp/assert.hpp>


namespace aosd
{
namespace view
{

	/** Keep a set of view models associated to a session id and allow association with a view.
		Allow views to keep a set of models for all open edition sessions and switch between models 
		when the user switch between edition sessions.
	*/
	template< class IdType >
	class ModelViewBinder
	{
	public:

		explicit ModelViewBinder( QAbstractItemView& viewer );
		~ModelViewBinder();

		void add( std::unique_ptr< QAbstractItemModel > model, const IdType& editor_id );
		void remove( const IdType& editor_id );
		void clear();

		/**	Will load the model associated with the provided session id.
			@return True if the model is found and associated, false otherwise.
		**/
		bool load( const IdType& id );

		/** Remove the current model from the view.
		**/
		void unload();

		QAbstractItemModel* current_model() const { return m_model; }
		IdType current_id() const { return m_id; }

		bool is_model_loaded() const { return m_model != nullptr; }

		QAbstractItemModel* find( const IdType& id );


	private:

		std::map< IdType, std::unique_ptr< QAbstractItemModel > > m_registry;
		QAbstractItemView& m_view;
		QAbstractItemModel* m_model;
		IdType m_id;

		void bind_to_view( QAbstractItemModel* model );
		
	};
	
	template< class IdType >
	ModelViewBinder<IdType>::ModelViewBinder( QAbstractItemView& viewer )
		: m_view( viewer )
		, m_model( nullptr )
	{

	}

	template< class IdType >
	ModelViewBinder<IdType>::~ModelViewBinder()
	{

	}

	template< class IdType >
	void ModelViewBinder<IdType>::add( std::unique_ptr< QAbstractItemModel > model, const IdType& editor_id )
	{
		UTILCPP_ASSERT( m_registry.find( editor_id ) == m_registry.end(), "Tried to begin editor already registered : " << editor_id );
		m_registry.insert( std::make_pair( editor_id, std::move( model ) ) );
	}

	template< class IdType >
	void ModelViewBinder<IdType>::remove( const IdType& editor_id )
	{
		m_registry.erase( editor_id );
	}

	template< class IdType >
	void ModelViewBinder<IdType>::clear()
	{
		unload();
		m_registry.clear();
	}

	template< class IdType >
	bool ModelViewBinder<IdType>::load( const IdType& editor_id )
	{
		auto model = find( editor_id );
		if( model )
		{
			bind_to_view( model );
			m_id = editor_id;
			return true;
		}
		else
			return false;
	}

	template< class IdType >
	void ModelViewBinder<IdType>::unload()
	{
		bind_to_view( nullptr );
		m_id = IdType();
	}

	template< class IdType >
	QAbstractItemModel* ModelViewBinder<IdType>::find( const IdType& editor_id )
	{
		auto find_it = m_registry.find( editor_id );
		if( find_it != m_registry.end() )
			return find_it->second.get();

		return nullptr;
	}

	template< class IdType >
	void ModelViewBinder<IdType>::bind_to_view( QAbstractItemModel* model )
	{
		m_view.setModel( model );
		m_model = model;
	}

	

}
}


#endif
