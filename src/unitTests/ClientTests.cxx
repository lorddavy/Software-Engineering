#include "MiniCppUnit.hxx"
#include "LibFileSystem.hxx"
#include "Client.hxx"

class ClientTests : public TestFixture<ClientTests>
{
public:
	TEST_FIXTURE( ClientTests )
	{
		TEST_CASE( testName );
		TEST_CASE( testEmail );
		TEST_CASE( testUpdate );
		
	}
	
	/**
	 * setUp is automatically called before each test case
	 */
	void setUp()
	{
		LibFileSystem::createNetDirectory( "config" );
		LibFileSystem::createNetDirectory( "generated" );
		LibFileSystem::createNetDirectory( "originals" );
	}

	/**
	 * tearDown is automatically called after each test case
	 */
	void tearDown()
	{
		LibFileSystem::cleanupDirectory( "config" );
		LibFileSystem::cleanupDirectory( "generated" );
		LibFileSystem::cleanupDirectory( "originals" );
		MailStub::theInstance().removeSent();
	}
	
	void testName()
	{
		Client client;
		client.name("A name");
		ASSERT_EQUALS( "A name", client.name() );
	}
	void testEmail()
	{
		Client client;
		client.email("email@domain.com");
		ASSERT_EQUALS( "email@domain.com", client.email() );
	}
	void testUpdate()
	{
		Client client;
		client.name("A client");
		client.email("email@domain.com");
		client.update("A work", "An author");
		ASSERT_EQUALS(
			"To: A client <email@domain.com>\n"
			"Subject: new work A work by An author\n"
			"\n",
			MailStub::theInstance().sentMails()
		);
	}
	

};

REGISTER_FIXTURE( ClientTests )
