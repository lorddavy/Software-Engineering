#ifndef Author_hxx
#define	Author_hxx
#include "Work.hxx"
#include "Client.hxx"
#include "Channel.hxx"
#include "Observer.hxx"
#include <list>
#include <iostream>
#include <sstream>
#include <string>
#include "Exception.hxx"
#include "Subject.hxx"

class Author : public Subject{

private:

	std::string _name;			//NOMBRE
	bool _contracted;			// CONTRATADO?
	std::list<Work*> _works;		//LISTA WORKS
	std::list<Observer*> _listSubscribed;	//SUBSCRIPTORES	

public: 

	Author()							//Constructor		
		:_name ("-- Unnamed --"),
		_contracted(false)		
	{
	}
	
	~Author()							//Destructor
	{
		std::list<Work*>::iterator it;
		for (it=_works.begin(); it != _works.end(); it++)
			{
				delete (*it);				
			}
		std::list<Observer*>::iterator it2;
		for (it2=_listSubscribed.begin(); it2 != _listSubscribed.end(); it2++)
			{
				//delete (*it2);				
			}	
	}
	
	const std::string & name() const		//GETTER NAME		
	{
		return _name;
	}

	void name( const std::string & name)		//SETTER NAME
	{ 	
		_name = name;
	}

	const bool & isContracted() const		//GETTER CONTRATADO?
	{
		return _contracted;
	}

	void contract()					//SETTER CONTRATADO?
	{
		_contracted = true;
	}
	
	void addWork(std::string title, int isbn, std::string originalF)		// AÑADIR WORK
	{
		
		Work* workTemp = new Work();
		
		workTemp->title(title);
		workTemp->isbn(isbn);
		workTemp->originalFile(originalF);
		_works.push_back(workTemp);
		
	}
	
	std::string  catalogue() 							//CATALOGAR WORKS
	{
		std::stringstream ss;
		std::list<Work*>::iterator it;

			for (it=_works.begin(); it != _works.end(); it++)
			{
				ss << "\t" << (*it)->aText() << "\n";							
			}
			return ss.str(); 
	} 
		
	Work & findWork ( const std::string & title )					//BUSCAR AUTOR
	{
		
		std::list<Work*>::iterator it;
		for (it=_works.begin(); it != _works.end(); it++)
			{
				if(title == (*it)->title())
				{
					return **it;
				}				
			}			
		throw WorkException();
	}
	
	std::string description()							//DESCRIBIR AUTOR
	{
		std::stringstream ss;
		if(isContracted())
		{
		
		ss << _name << " [contracted]" << "\n"; 	
		ss << catalogue();
					
		}else{
		ss << _name << " [external]" << "\n"; 
		
		}
		return ss.str();
	}

	void subscribeClient(Client * c)						//SUBSCRIBIR CLIENTE
	{
		_listSubscribed.push_back(c);
	}
	void subscribeChannel(Channel * c)						//SUBSCRIBIR CANAL
	{
		_listSubscribed.push_back(c);
	}
	
	void notify(std::string work,std::string author)				//NOTIFICAR SUBSCRIPTORES
	{

	std::list<Observer*>::iterator it;
	
			for (it=_listSubscribed.begin(); it != _listSubscribed.end(); it++)
			{
			(*it)->update(work,author);								
			}						
	}
	
	std::string listSubscribed()							//LISTAR SUBSCRIPTORES (CLIENTES)
	{
	
		std::list<Observer*>::iterator it;	
		std::stringstream ss;

		if (_listSubscribed.empty()) { return ""; }
		else 
		{ 
			for (it=_listSubscribed.begin(); it != _listSubscribed.end(); it++)
			{
				ss << (**it).name();
				ss << "\n";				
			}
			return ss.str();						
		} 
	}	
	
};

#endif


