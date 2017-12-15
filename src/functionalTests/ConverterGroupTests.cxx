#include <fstream>
#include <string>
#include "LibFileSystem.hxx"
#include "MiniCppUnit.hxx"
#include "HtmlConverter.hxx"
#include "Converter.hxx"
#include "ConverterGroup.hxx"
#include "Exception.hxx"

class ConverterGroupTests : public TestFixture<ConverterGroupTests>
{
public:
	TEST_FIXTURE( ConverterGroupTests )
	{
		TEST_CASE( testConvert_withHtmlConverter );
		TEST_CASE( testConvert_withoutConverter );
		TEST_CASE( testConvert_withPrintablePdfConverter );
		TEST_CASE( testConvert_withWatermarkPdfConverter );
		TEST_CASE( testConvert_withHtmlAndPdfConverters );
		TEST_CASE( testConvert_withUnknownConverter );
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

	void testConvert_withHtmlConverter()
	{
		ConverterGroup converterGroup;
		converterGroup.add("html") ;
		createOriginalFile("Original.odt");
				
		converterGroup.convert("originals/Original.odt","generated/Prefix");

		ASSERT_EQUALS(
			"War file generated from 'originals/Original.odt'\n",
			LibFileSystem::fileContent("generated/Prefix [multiple HTML files].war")
		);	
	}
	void testConvert_withoutConverter()
	{
		ConverterGroup converterGroup;
		
			
		try
		{
			converterGroup.add("html") ;
			converterGroup.convert("originals/Original.odt","generated/Prefix");
		}
		catch ( std::exception & e )
		{
			ASSERT_EQUALS(
				"The original file does not exist",
				e.what()
			)
		}	 
			
	}
	void testConvert_withPrintablePdfConverter()
	{
		ConverterGroup converterGroup;
		converterGroup.add("pdf_print") ;
		createOriginalFile("Original.odt");
				
		converterGroup.convert("originals/Original.odt","generated/Prefix");

		ASSERT_EQUALS(
			"PDF generated from 'originals/Original.odt'. Watermark: ''\n",
			LibFileSystem::fileContent("generated/Prefix [multiple PDF files].pdf")
		);	
	}
	void testConvert_withWatermarkPdfConverter()
	{
		ConverterGroup converterGroup;
		converterGroup.add("pdf_mark") ;
		createOriginalFile("Original.odt");		
		
		converterGroup.convert("originals/Original.odt","generated/Prefix");
		

		ASSERT_EQUALS(
			"PDF generated from 'originals/Original.odt'. Watermark: 'contenido watermark'\n",
			LibFileSystem::fileContent("generated/Prefix [multiple PDF watermarked].pdf")
		);	
	}
	void testConvert_withHtmlAndPdfConverters()
	{
		ConverterGroup converterGroup;
		converterGroup.add("pdf_print") ;
		converterGroup.add("pdf_mark") ;		
		createOriginalFile("Original.odt");		
		
		converterGroup.convert("originals/Original.odt","generated/Prefix");
		ASSERT_EQUALS(
			"PDF generated from 'originals/Original.odt'. Watermark: 'contenido watermark'\n",
			LibFileSystem::fileContent("generated/Prefix [multiple PDF watermarked].pdf")
		);
		ASSERT_EQUALS(
			"PDF generated from 'originals/Original.odt'. Watermark: ''\n",
			LibFileSystem::fileContent("generated/Prefix [multiple PDF files].pdf")
		);

			
	}
	void testConvert_withUnknownConverter()
	{
		ConverterGroup converterGroup;
						
		createOriginalFile("Original.odt");		
		
		try
		{
			converterGroup.add("xml") ;
			converterGroup.convert("originals/Original.odt","generated/Prefix");
		}
		catch ( std::exception & e )
		{
			ASSERT_EQUALS(
				"Unsupported format",
				e.what()
			)
		}	
		
		

			
	}




};

REGISTER_FIXTURE( ConverterGroupTests )
