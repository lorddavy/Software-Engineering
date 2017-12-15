#ifndef Channel_hxx
#define Channel_hxx
#include <string.h>
#include <iostream>
#include <vector>
#include "Observer.hxx"


class Channel : public Observer{

private:
	std::string _name;				//NOMBRE
	std::string _description;			//DESCRIPCION
	
	std::vector<std::string> _works_and_authors;		

public: 

	Channel()			//CONSTRUCTOR
	{
	}

	~Channel()			//DESTRUCTOR	
	{
	

	}

	const std::string & name() const	//GETTER NAME			
	{
		return _name;
	}

	void name( std::string name)		//SETTER NAME
	{ 	
		_name = name;
	}
	
	const std::string & description() const	//GETTER NAME			
	{
		return _description;
	}
	
	void description( std::string description)		//SETTER NAME
	{ 	
		_description = description;
	}
	

	//crear getter del contenido

	std::string  content()
	{
	std::stringstream ss;

	ss << "<?xml version='1.0' encoding='UTF-8' ?>\n"<<"<rss version='2.0'>\n";
	ss << "<channel>\n"<<"<title>MeltingPotOnline: " << _name << "</title>\n";
	ss << "<link>http://www.meltingpotonline.com/" << _name << "</link>\n";
	ss << "<description>" << _description << "</description>\n";
	
		
			for (int i=0; i<(int)_works_and_authors.size(); i++)
			{
				ss << "<item>\n"<<"<title>Novelty: '"<< _works_and_authors[i] << "' by '"<< _works_and_authors[i+1] <<"'</title>\n"
				<<"<link>http://www.meltingpotonline.com/infoWork?author='"<< _works_and_authors[i+1] <<"'&title='"<< _works_and_authors[i] <<"'</link>\n"
				<<"</item>\n";					
				
				i++;

			}
	ss << "</channel>\n" << "</rss>\n";
	
	return ss.str();

	}

	
	void update(std::string work,std::string author)		// Avisar actualización
	{
		//crear lista que tenga work en[i] i author en [i+1] para recorrerla succesivamente luego
		
		_works_and_authors.push_back(work);	 // posicion i
		_works_and_authors.push_back(author);	// posicion i+1
		

	}
	

};

#endif
