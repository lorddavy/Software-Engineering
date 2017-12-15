#include <fstream>
#include "LibFileSystem.hxx"
#include "MiniCppUnit.hxx"
#include "PdfConverter.hxx"

class PdfConverterTests : public TestFixture<PdfConverterTests>
{
public:
	TEST_FIXTURE( PdfConverterTests )
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
		PdfConverter converter;
		createOriginalFile("Original.odt");
		converter.convert("originals/Original.odt","generated/Prefix");

		ASSERT_EQUALS(
			"generated/Prefix [multiple PDF files].pdf\n",
			LibFileSystem::listDirectoryInOrder("generated")
		);

	}
	void testConvert_generateContent()
	{
		std::string prueba1; 
		PdfConverter converter;
		createOriginalFile("Original.odt");
		converter.convert("originals/Original.odt","generated/Prefix");

		ASSERT_EQUALS(
			"PDF generated from 'originals/Original.odt'. Watermark: ''\n",
			LibFileSystem::fileContent("generated/Prefix [multiple PDF files].pdf")
		);

	}
	void testConvert_withInexistentOriginal()
	{
		PdfConverter converter;		
		
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
		Converter *pdfconverter = new PdfConverter();
		Converter *pdfconverter2 = new PdfConverter();
		createOriginalFile("Original.odt");

		try
		{
			pdfconverter->convert("originals/Original.odt","generated/Prefix");
			ASSERT_EQUALS(
			"PDF generated from 'originals/Original.odt'. Watermark: ''\n",
			LibFileSystem::fileContent("generated/Prefix [multiple PDF files].pdf")
			);			
		}
		catch ( std::exception & e )
		{
			ASSERT_EQUALS(
				"The original file does not exist",
				e.what()
			)
		}
	

		try
		{
			((PdfConverter *)pdfconverter2)->activateWatermark("contenido watermark");


			pdfconverter2->convert("originals/Original.odt","generated/Prefix");
			ASSERT_EQUALS(
			"PDF generated from 'originals/Original.odt'. Watermark: 'contenido watermark'\n",
			LibFileSystem::fileContent("generated/Prefix [multiple PDF watermarked].pdf")
		);
			
		}
		catch ( std::exception & e )
		{
			ASSERT_EQUALS(
				"The original file does not exist",
				e.what()
			)
		}
		 
		delete pdfconverter;
		delete pdfconverter2;

	}



};

REGISTER_FIXTURE( PdfConverterTests )
