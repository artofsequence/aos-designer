#include "aoslcpp/algorithm/execution.hpp"

#include <functional>
#include <map>
#include <typeindex>

#include "utilcpp/assert.hpp"

#include "aoslcpp/algorithm/find.hpp"
#include "aosl/aosl.hpp"

namespace aoslcpp
{
	namespace 
	{
		template< class ActionFunc >
		void get_check_act_object( aosl::Canvas& canvas, const aosl::Object_ref& object_ref, ActionFunc action )
		{
			auto object = find_object( canvas, object_ref );
			if( object )
				action( *object );
			else
			{
				UTILCPP_LOG_ERROR << "Tried to do \"" << typeid(action).name() << "\" but failed because the object \"" << object_ref << "\" was not found!";
			}
		}

		
				
	}

	


	void activate( aosl::Object& object )
	{
		object.active( true );
	}

	void activate( aosl::Canvas& canvas, const aosl::Object_ref& object_ref )
	{
		get_check_act_object( canvas, object_ref, []( aosl::Object& obj ){ activate(obj); } );
	}

	void deactivate( aosl::Object& object )
	{
		object.active( false );
	}

	void deactivate( aosl::Canvas& canvas, const aosl::Object_ref& object_ref )
	{
		get_check_act_object( canvas, object_ref, []( aosl::Object& obj ){ deactivate(obj); } );
	}

	void switch_state( aosl::Object& object )
	{
		object.active( !object.active() );
	}

	void switch_state( aosl::Canvas& canvas, const aosl::Object_ref& object_ref )
	{
		get_check_act_object( canvas, object_ref, []( aosl::Object& obj ){ switch_state(obj); } );
	}


	void transform( aosl::Properties_graphic_object& graphic_properties, const aosl::Transformation& transformation )
	{
		UTILCPP_NOT_IMPLEMENTED_YET;
	}

	void transform( aosl::Canvas& canvas, const aosl::Object_ref& object_ref, const aosl::Transformation& transformation )
	{
		UTILCPP_NOT_IMPLEMENTED_YET;
	}


	void reverse_transform( aosl::Properties_graphic_object& graphic_properties, const aosl::Transformation& transformation )
	{
		UTILCPP_NOT_IMPLEMENTED_YET;
	}

	void reverse_transform( aosl::Canvas& canvas, const aosl::Object_ref& object_ref, const aosl::Transformation& transformation )
	{
		UTILCPP_NOT_IMPLEMENTED_YET;
	}

	namespace 
	{
		struct ChangeExecutor
		{
			typedef std::function< void ( aosl::Object& object ) > ObjectModifier;

			ChangeExecutor(){}
			ChangeExecutor( ObjectModifier action, ObjectModifier reverse ) : action( action ), reverse( reverse ) {}

			ObjectModifier action;
			ObjectModifier reverse;
		};

	}
	
	void execute( const aosl::Change& change, aosl::Object& object, bool reverse )
	{
		UTILCPP_ASSERT( std::find( std::begin( change.object() ), std::end( change.object() ),  object.id() ) == std::end( change.object() )
			, "Tried to execute a change \"" << typeid(change).name() 
			<< "\" that should be executed with object(s) \""  << change.object()
			<< "\" but is executed with object \"" << object.id() << "\"!"			
			);

		typedef std::map< std::type_index, ChangeExecutor > ChangeFunctionMap;

		static const ChangeFunctionMap CHANGE_FUNCTION_MAP = []() -> ChangeFunctionMap 
		{
			ChangeFunctionMap change_function_map;
			
			change_function_map[ typeid(aosl::Change_activate) ] = ChangeExecutor( 
					[]( aosl::Object& object ) { activate( object ); } 
				,	[]( aosl::Object& object ) { reverse_activate( object ); } 
			);
			
			change_function_map[ typeid(aosl::Change_deactivate) ] = ChangeExecutor( 
					[]( aosl::Object& object ) { deactivate( object ); } 
				,	[]( aosl::Object& object ) { reverse_activate( object ); } 
			);

			change_function_map[ typeid(aosl::Change_switch) ] = ChangeExecutor( 
					[]( aosl::Object& object ) { switch_state( object ); } 
				,	[]( aosl::Object& object ) { reverse_switch_state( object ); } 
			);

			// TODO : add transformation change here
			return change_function_map;
		}();

		const auto& change_typeid = typeid(change);
		auto func_it = CHANGE_FUNCTION_MAP.find( change_typeid ); 

		if( func_it != CHANGE_FUNCTION_MAP.end() )
		{
			if( reverse )
				func_it->second.reverse( object );
			else
				func_it->second.action( object );
		}
		else
		{
			UTILCPP_LOG_ERROR << "Algorithm for Change of type \"" << change_typeid.name() << "\" not found! ";
		}
	}


	void execute( aosl::Canvas& canvas, const aosl::Change& change, bool reverse )
	{
		UTILCPP_ASSERT( !change.object().empty() , "Change with empty object reference list!" );
		const auto& object_ref_list = change.object();
		for( const auto& object_ref : object_ref_list )
		{
			get_check_act_object( canvas, object_ref, [&]( aosl::Object& object )
			{
				execute( change, object, reverse );
			});
		}
		
	}

	void execute( aosl::Canvas& canvas, const aosl::Move& move, bool reverse )
	{
		const auto& change_list = move.change();
		
		aosl::Object_ref object_ref("");
		aosl::Object* object = nullptr;

		for( const auto& change : change_list )
		{
			UTILCPP_ASSERT( !change.object().empty() , "Change with empty object reference list!" );

			const auto& object_ref_list = change.object();
			for( const auto& change_object_ref : object_ref_list )
			{
				if( object_ref != change_object_ref ) // minor optimization to avoid having to research the same object each time it is referenced.
				{
					object_ref = change_object_ref;
					object = find_object( canvas, object_ref );
				}

				UTILCPP_ASSERT_NOT_NULL( object );
			
				execute( change, *object, reverse );
			}

		}
	}

	boost::optional< aosl::Move > auto_next( const aosl::Story& story, const aosl::Stage& stage )
	{
		return auto_next( story, aosl::Stage_ref( stage.id() ) );
	}

	boost::optional< aosl::Move > auto_next( const aosl::Story& story, const aosl::Stage_ref& stage_ref )
	{
		auto& moves = story.moves().move();
		boost::optional< aosl::Move > found;
		
		for( auto& move : moves )
		{
			if( std::any_of( std::begin(move.from()), std::end(move.from())
				, [&]( const aosl::Move_ref& stage_from_ref ){  return stage_from_ref == stage_ref; } ) )
			{
				if( found ) // move already found : there is more than one moves for this stage
					return nullptr; // TODO: manage this case and take into account that there can be a default move
				else
				{
					// found the first move that comes from the stage
					found = move;
				}
			}
		}
		
		return found;
	}


	

}