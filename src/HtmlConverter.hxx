#ifndef HtmlConverter_hxx
#define HtmlConverter_hxx
#include "libLibreOffice2Html.hxx"
#include "Converter.hxx"
#include "Exception.hxx"

class HtmlConverter : public Converter{

private:				
	std::string path;
	int result;
	

public:
	HtmlConverter()		//Constructor
	{

	}

	~HtmlConverter()	//Destructor
	{
	}

	
	void convert(const std::string & file, const std::string & newFile)
	{
		//const char* cPath;
		path = newFile + " [multiple HTML files].war";
		//cPath=(const char*)path;

		
		result = OO_WarGeneration(file.c_str(),path.c_str());	//Usamos la librería LibreOfficeTools para la conversión
		if(result == -1)
		{
			throw OriginalException();	//Se lanza excepción si no hay archivo original
		}
	}
	

	
};
#endif
