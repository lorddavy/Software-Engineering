#include <fstream>
#include <string>
#include "LibFileSystem.hxx"
#include "MiniCppUnit.hxx"
#include "HtmlConverter.hxx"
#include "Converter.hxx"

class HtmlConverterTests : public TestFixture<HtmlConverterTests>
{
public:
	TEST_FIXTURE( HtmlConverterTests )
	{
		TEST_CASE( testConvert_generateFile );
		TEST_CASE( testConvert_generateContent );
		TEST_CASE( testConvert_withInexistentOriginal );
		TEST_CASE( testConvert_polymorphicCall );
	}

	/**
	 * The setUp method is automatically called before each test
	 */
	void setUp()
	{
		LibFileSystem::createNetDirectory( "config" );
		LibFileSystem::createNetDirectory( "generated" );
		LibFileSystem::createNetDirectory( "originals" );
	}
	/**
	 * The tearDown method is automatically called after each test
	 */
	void tearDown()
	{
		LibFileSystem::cleanupDirectory( "config" );
		LibFileSystem::cleanupDirectory( "generated" );
		LibFileSystem::cleanupDirectory( "originals" );
	}
	/**
	 * This method creates files used in tests
	 */
	void createOriginalFile( const std::string & name )
	{
		std::string fullname( "originals/" );
		fullname += name;
		std::ofstream os( fullname.c_str() );
		os << "An original file" << std::endl;
		os.close();
	}
	
		//TESTS

	void testConvert_generateFile()
	{
		HtmlConverter converter;
		createOriginalFile("Original.odt");
		converter.convert("originals/Original.odt","generated/Prefix");

		ASSERT_EQUALS(
			"generated/Prefix [multiple HTML files].war\n",
			LibFileSystem::listDirectoryInOrder("generated")
		);

	}
	void testConvert_generateContent()
	{
		HtmlConverter converter;
		createOriginalFile("Original.odt");
		converter.convert("originals/Original.odt","generated/Prefix");

		ASSERT_EQUALS(
			"War file generated from 'originals/Original.odt'\n",
			LibFileSystem::fileContent("generated/Prefix [multiple HTML files].war")
		);

	}
	void testConvert_withInexistentOriginal()
	{
		HtmlConverter converter;		
		
		try
		{
			converter.convert("originals/Original.odt","generated/Prefix");
		}
		catch ( std::exception & e )
		{
			ASSERT_EQUALS(
				"The original file does not exist",
				e.what()
			)
		}

	}
	void testConvert_polymorphicCall()
	{
		Converter *htmlconverter = new HtmlConverter();

		try
		{
			htmlconverter->convert("originals/Original.odt","generated/Prefix");
		}
		catch ( std::exception & e )
		{
			ASSERT_EQUALS(
				"The original file does not exist",
				e.what()
			)
		}
		 
		delete htmlconverter;

	}



};

REGISTER_FIXTURE( HtmlConverterTests )
