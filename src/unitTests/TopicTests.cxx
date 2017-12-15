#include "MiniCppUnit.hxx"
#include "Topic.hxx"

class TopicTests : public TestFixture<TopicTests>
{
public:
	TEST_FIXTURE( TopicTests )
	{
		TEST_CASE( testName_byDefault );
		TEST_CASE( testName );
		TEST_CASE( testsubscribeClient );
		
	}
	void testName_byDefault()
	{
		Topic topic;
		ASSERT_EQUALS( "-- Unnamed --", topic.name() );
	}
	void testName()
	{
		Topic topic;
		topic.name("A name");
		ASSERT_EQUALS( "A name", topic.name() );
	}

	void testsubscribeClient()
	{
		Topic topic;
		Client* clientTemp = new Client();
		clientTemp->name("A name");
		topic.subscribeClient(clientTemp);
		ASSERT_EQUALS( "A name\n", topic.listSubscribed() );
		delete clientTemp;
	}
	

};

REGISTER_FIXTURE( TopicTests )
