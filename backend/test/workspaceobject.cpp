#include <gtest/gtest.h>


#include <memory>
#include <aosdesigner/backend/workspaceobject.hpp>


using namespace aosd::backend;

struct DummyEvent {};

class Object
	: public WorkspaceObject<Object>
{
	int m_k;
public:

	explicit Object( Workspace& workspace ) 
		: WorkspaceObject( workspace, make_new_id<Object>() )
		, m_k(0)
	{
	}

	using WorkspaceObject::update;

	boost::future<void> dummy_action()
	{
		return schedule( [&]{ publish( DummyEvent() ); } );
	}
};

class ObjectGroup
	: public WorkspaceObject<ObjectGroup>
{
	std::vector< std::shared_ptr<Object> > m_objects;
public:

	explicit ObjectGroup( Workspace& workspace ) 
		: WorkspaceObject( workspace, make_new_id<ObjectGroup>() )
	{
	}

	boost::future<void> add( std::shared_ptr<Object> object )
	{
		if(!object)
			throw std::invalid_argument( "Object have to be provided in ObjectGroupe::add()!" );
		return schedule( [this, object]{
			m_objects.emplace_back( object );
		});
	}

	void update()
	{ 
		WorkspaceObject::update();
		for( const auto& object : m_objects )
		{
			async( [=]{ object->update(); } );
		}
	}


};



TEST( Test_WorkspaceObject, simple_use )
{
	TaskExecutor_Immediate executor;
	Workspace workspace( executor );
	auto test = Object( workspace );

	ASSERT_TRUE( is_valid( test.id() ) );

	int k = 0;
	

	test.on<DummyEvent>( [&]{ ++k; } );
	ASSERT_EQ( 0, k );
	test.dummy_action();
	ASSERT_EQ( 0, k );
	test.update();
	ASSERT_EQ( 0, k );
	workspace.dispatch_events();
	ASSERT_EQ( 1, k );
	test.update();
	workspace.dispatch_events();
	ASSERT_EQ( 1, k );
	test.dummy_action();
	test.update();
	workspace.dispatch_events();
	ASSERT_EQ( 2, k );

	Object* target_object = nullptr;
	test.on_next_update( [&]( Object& object ){ target_object= &object; } );
	test.update();
	workspace.dispatch_events();
	ASSERT_EQ( &test, target_object );

}

TEST( Test_WorkspaceObject, object_group )
{
	TaskExecutor_Immediate executor;
	Workspace workspace( executor );

	ObjectGroup group( workspace );

	auto a = std::make_shared<Object>( workspace );
	auto b = std::make_shared<Object>( workspace );

	group.add( a );
	group.add( b );

	int k = 0;

	a->on<DummyEvent>( [&]{ ++k; } );
	b->on<DummyEvent>( [&]{ ++k; } );
	ASSERT_EQ( 0, k );

	group.update();
	ASSERT_EQ( 0, k );
	workspace.dispatch_events();
	ASSERT_EQ( 0, k );

	a->dummy_action();
	ASSERT_EQ( 0, k );
	group.update();
	ASSERT_EQ( 0, k );
	workspace.dispatch_events();
	ASSERT_EQ( 1, k );

	a->dummy_action();
	b->dummy_action();
	ASSERT_EQ( 1, k );
	group.update();
	ASSERT_EQ( 1, k );
	workspace.dispatch_events();
	ASSERT_EQ( 3, k );

}