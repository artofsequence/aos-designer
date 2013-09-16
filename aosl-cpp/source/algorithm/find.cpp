#include "aoslcpp/algorithm/find.hpp"

#include "aosl/aosl.hpp"

namespace aoslcpp
{
	namespace impl
	{
		// note: those implementations are made template to allow easy generation of const and non-const versions.

		template< class ObjectType, class ObjectList >
		ObjectType* recursive_find_object( ObjectList& list_objects, const aosl::Object_ref& object_ref ) 
		{
			auto& objects = list_objects.object();

			if( objects.empty() ) // be lazy!
				return nullptr;

			for( auto it = objects.begin(); it != objects.end(); ++it )
			{
				auto& object = *it;
				if( object.id() == object_ref )
					return &object;

				auto child_found = find_object( object, object_ref );
				if( child_found )
					return child_found;
			}

			return nullptr;
	
		}


		template< class ObjectType, class CanvasType >
		ObjectType* find_object( CanvasType& canvas, const aosl::Object_ref& object_ref )
		{
			return recursive_find_object<ObjectType>( canvas.objects(), object_ref );
		}

		template< class ObjectType >
		ObjectType* find_object( ObjectType& parent, const aosl::Object_ref& object_ref )
		{
			return parent.children() ? recursive_find_object<ObjectType>( *parent.children(), object_ref ) : nullptr;
		}
		
		template< class MoveType, class StoryType >
		MoveType* find_move( StoryType& story, const aosl::Move_ref& move_ref )
		{
			auto& moves = story.moves().move();

			if( moves.empty() ) // be lazy!
				return nullptr;

			auto find_it = std::find_if( moves.begin(), moves.end(), [&]( const MoveType& move ){ return move.id() == move_ref; });

			if( find_it != moves.end() )
			{
				auto& move = *find_it;
				return &move;
			}
			else
				return nullptr;
		}

		template< class StageType, class StoryType >
		StageType* find_stage( StoryType& story, const aosl::Stage_ref& stage_ref )
		{
			auto& stages = story.stages().stage();

			if( stages.empty() )
				return nullptr;

			auto find_it = std::find_if( stages.begin(), stages.end(), [&]( const StageType& stage ){ return stage.id() == stage_ref; });

			if( find_it != stages.end() )
			{
				auto& stage = *find_it;
				return &stage;
			}
			else
				return nullptr;
		}

	}
	

	const aosl::Object* find_object( const aosl::Canvas& canvas, const aosl::Object_ref& object_ref )
	{
		return impl::find_object<const aosl::Object>( canvas, object_ref );
	}
	
	aosl::Object* find_object( aosl::Canvas& canvas, const aosl::Object_ref& object_ref )
	{
		return impl::find_object<aosl::Object>( canvas, object_ref );
	}

	
	const aosl::Object* find_object( const aosl::Object& parent, const aosl::Object_ref& object_ref )
	{
		return impl::find_object( parent, object_ref );
	}

	aosl::Object* find_object( aosl::Object& parent, const aosl::Object_ref& object_ref )
	{
		return impl::find_object( parent, object_ref );
	}
	
	const aosl::Move* find_move( const aosl::Story& story, const aosl::Move_ref& move_ref )
	{
		return impl::find_move<const aosl::Move>( story, move_ref );
	}

	aosl::Move* find_move( aosl::Story& story, const aosl::Move_ref& move_ref )
	{
		return impl::find_move<aosl::Move>( story, move_ref );
	}

	const aosl::Stage* find_stage( const aosl::Story& story, const aosl::Stage_ref& stage_ref )
	{
		return impl::find_stage<const aosl::Stage>( story, stage_ref );
	}
	
	aosl::Stage* find_stage( aosl::Story& story, const aosl::Stage_ref& stage_ref )
	{
		return impl::find_stage<aosl::Stage>( story, stage_ref );
	}

}