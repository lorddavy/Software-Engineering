#ifndef Work_hxx
#define Work_hxx
#include <sstream>
#include "Topic.hxx"

//using namespace std;

class Work{

private:
	std::string _title;					//Atributo Título
	int _isbn;							//Atributo isbn
	std::string _originalFile;			//Atributo Archivo origen
	std::list<Topic*> _topics;
			
public: 

	Work()										//Constructor
		:_title ("-- Untitled --"),					//Inicialización título
		_isbn (-1),									//Inicialización isbn
		_originalFile("")						//Inicialización archivo origen
	{
	}
	
	~Work()	
	{
		std::list<Topic*>::iterator it;
		for (it=_topics.begin(); it != _topics.end(); it++)
			{
				delete (*it);
			}	
	}
	
	const std::string & title() const			//Método getter de título
	{
		return _title;
	}

	void title( const std::string & title ){ 	//Método setter de título
	
		_title = title;
	
	}
	

	const int & isbn() const				//Método getter de Referencia isbn
	{
		return _isbn;	
	}

	void isbn(const int & isbn)				//Método setter de Referencia isbn
	{
		_isbn = isbn;	
	}

	const std::string & originalFile()		//Método getter de archivo origen
	{
		return _originalFile;
	}

	void originalFile(const std::string & originalFile){ 	//Método setter de archivo origen
	
		_originalFile = originalFile;
	
	}
	
	std::string aText()		//Método getter de texto info
	{
		std::list<Topic*>::iterator it;
		std::stringstream ss;
		if (_isbn == -1)
		{
		ss << _isbn;
		ss << ", '";
		ss << _title;
		ss << "', '";
		ss << _originalFile;
		ss << "'";
		}else{
		ss << _isbn;
		ss << ", '";
		ss << _title;
		ss << "', 'originals/";
		ss << _originalFile;
		ss << "'";
		}
		for (it=_topics.begin(); it != _topics.end(); it++)
			{			
					ss << "\n" << "\t\t" << "'" << (**it).name() << "'";
			}
		return ss.str();
	}
	void associateTopic(std::string name)		//Asociar topic
	{	
		Topic* topicTemp = new Topic();
		topicTemp->name(name);
		_topics.push_back(topicTemp);

	}

	std::string topics() 		//Muestra listado de topics asociados
	{	
		std::list<Topic*>::iterator it;
		std::stringstream ss;

		if (_topics.empty()) { return ""; }
		else 
		{ 
			for (it=_topics.begin(); it != _topics.end(); it++)
			{
				ss << "\t\t"<< (**it).name() << "\n";				
			}
			return ss.str();			
		} 
	}
	
};

#endif // Work_hxx
