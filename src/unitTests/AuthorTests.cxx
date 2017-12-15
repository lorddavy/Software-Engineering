#include "MiniCppUnit.hxx"
#include "Author.hxx"
#include "Subject.hxx"
#include "Observer.hxx"
#include "Client.hxx"
#include "Channel.hxx"

class AuthorTests : public TestFixture<AuthorTests>
{
public:
	TEST_FIXTURE( AuthorTests )
	{
		TEST_CASE( testName_byDefault );
		TEST_CASE( testContracted_byDefault );
		TEST_CASE( testContracted_afterContracted );
		TEST_CASE( testsubscribeClient );
		TEST_CASE( testsubscribeChannel );

	}
	void testName_byDefault()
	{
		Author author;
		ASSERT_EQUALS( "-- Unnamed --", author.name() );
	}
	void testContracted_byDefault()
	{
		Author author;
		ASSERT_EQUALS( false, author.isContracted() );
	}
	void testContracted_afterContracted()
	{
		Author author;
		author.contract();
		ASSERT_EQUALS(true, author.isContracted() );
	}
	
	void testsubscribeClient()
	{
		Author autor;
		Client* clientTemp = new Client();
		clientTemp->name("A name");
		autor.subscribeClient(clientTemp);
		ASSERT_EQUALS( "A name\n", autor.listSubscribed() );
		delete clientTemp;
	}
	void testsubscribeChannel()
	{
		Author autor;
		Channel* channelTemp = new Channel();
		channelTemp->name("A name");
		autor.subscribeChannel(channelTemp);
		ASSERT_EQUALS( "A name\n", autor.listSubscribed() );
		delete channelTemp;
	}
	

};

REGISTER_FIXTURE( AuthorTests )

