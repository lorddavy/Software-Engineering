#ifndef ConverterGroup_hxx
#define ConverterGroup_hxx
#include "HtmlConverter.hxx"
#include "PdfConverter.hxx"
#include "Exception.hxx"
#include "Converter.hxx"
#include <string.h>

class ConverterGroup {

private:				
	
	std::list<Converter*> _converterGroup;

public:
	
	ConverterGroup()	//CONSTRUCTOR
	{
	}

	~ConverterGroup()	//DESTRUCTOR
	{

		std::list<Converter*>::iterator it;
		for (it=_converterGroup.begin(); it != _converterGroup.end(); it++)
			{
				delete (*it);
				
			}			
	}	



	void add(std::string type)		//AÑADIR CONVERSOR
	{
		if(type=="html")
		{

		Converter *htmlconverter = new HtmlConverter();
				
		_converterGroup.push_back(htmlconverter);
	
		
		}
		else if(type=="pdf_print")
		{

		Converter *pdfconverter = new PdfConverter();
				
		_converterGroup.push_back(pdfconverter);
			

		}
		else if(type=="pdf_mark")
		{

		Converter *pdfconverter = new PdfConverter();
		((PdfConverter *)pdfconverter)->activateWatermark("contenido watermark");		
		_converterGroup.push_back(pdfconverter);	
		
		}
		else
		{
		throw FormatException();
		}
	
			
	}

	
	void  convert(const std::string & file, const std::string & newFile) 		//CATALOGO
	{
		std::list<Converter*>::iterator it;
		

		if (!_converterGroup.empty())
		{
			for (it=_converterGroup.begin(); it != _converterGroup.end(); it++)
			{
				(*it)->convert(file,newFile);
				
				
			}			
		} 
		
	} 



};
#endif
