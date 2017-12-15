#ifndef PdfConverter_hxx
#define PdfConverter_hxx
#include "libLibreOffice2Pdf.hxx"
#include "Converter.hxx"
#include "Exception.hxx"
//using namespace LibreOfficeTools;



class PdfConverter : public Converter{

private:				
	
	bool watermarked;
	std::string path;
	std::string watermark;

public:
	~PdfConverter()	//Destructor
	{
	}

	PdfConverter()		//Constructor
	{
		watermarked = false;
	}


	
	void convert(const std::string & file, const std::string & newFile)
	{
		//const char* cPath;
		if (watermarked == false) path = newFile + " [multiple PDF files].pdf";
		else path = newFile + " [multiple PDF watermarked].pdf";
		//cPath=(const char*)path;

		try
		{ 
			LibreOfficeTools::convertToPdf(file,path,watermark);	//Usamos la librería LibreOfficeTools para la conversión
		}
		catch(LibreOfficeTools::LOWriterFileNotFound &e)
		{
			throw OriginalException();	//Se lanza excepción si no hay archivo original
		}	
	}

	void activateWatermark( const std::string & string)
	{
		watermarked = true;
		watermark = string;
	}

	
};
#endif
