#include "MiniCppUnit.hxx"
#include "Work.hxx"

class WorkTests : public TestFixture<WorkTests>
{
public:
	TEST_FIXTURE( WorkTests )
	{
		TEST_CASE( testTitle_byDefault );
		TEST_CASE( testTitle_addingTitle );
		TEST_CASE( testReference_byDefault )
		TEST_CASE( testReference_addingReference )
		TEST_CASE( testOriginal_byDefault );
		TEST_CASE( testOriginal_addingOriginal );
		TEST_CASE( testAText_byDefault );
		TEST_CASE( testAText_initialized );
		TEST_CASE( testAssociateTopic_byDefault );
		TEST_CASE( testAssociateTopic );
	}
	void testTitle_byDefault()
	{
		Work work;
		ASSERT_EQUALS( "-- Untitled --", work.title() );
	}
	void testTitle_addingTitle()
	{
		Work work;
		work.title( "A Title" );
		ASSERT_EQUALS( "A Title", work.title() );
	}
	void testReference_byDefault()
	{
		Work work;
		ASSERT_EQUALS( -1, work.isbn() );
	}
	void testReference_addingReference()
	{
		Work work;
		work.isbn( 1 );
		ASSERT_EQUALS( 1, work.isbn() );
	}
	void testOriginal_byDefault()
	{
		Work work;
		ASSERT_EQUALS( "", work.originalFile() );
	}
	void testOriginal_addingOriginal()
	{
		Work work;
		work.originalFile( "AFile.odt" );
		ASSERT_EQUALS( "AFile.odt", work.originalFile() );
	}
	void testAText_byDefault()
	{
		Work work;
		ASSERT_EQUALS( "-1, '-- Untitled --', ''", work.aText() );
	}
	void testAText_initialized()
	{
		Work work;
		work.title( "A Work" );
		work.isbn( 100 );
		work.originalFile( "AFile.odt" );
		ASSERT_EQUALS( "100, 'A Work', 'originals/AFile.odt'", work.aText() );
	}

	void testAssociateTopic_byDefault()
	{
		Work work;

		ASSERT_EQUALS(
			"",
			work.topics()
		);
	}
	void testAssociateTopic()
	{
		Work work;
		work.associateTopic("Topic 1");

		ASSERT_EQUALS(
			"\t\tTopic 1\n",
			work.topics()
		);
	}

};

REGISTER_FIXTURE( WorkTests )

