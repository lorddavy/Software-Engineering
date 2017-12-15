#ifndef Topic_hxx
#define Topic_hxx
#include <string.h>
#include "Client.hxx"
#include "Subject.hxx"
#include "Observer.hxx"


class Topic : public Subject{

private:
	std::string _name;	//NOMBRE
	std::list<Observer*> _listSubscribed;		//SUBSCRIPTORES					

public: 

	Topic()	:_name("-- Unnamed --")	//CONSTRUCTOR
	{
	}

	~Topic()			//DESTRUCTOR	
	{

		std::list<Observer*>::iterator it;
		for (it=_listSubscribed.begin(); it != _listSubscribed.end(); it++)
			{
				//delete (*it);
			}

	}

	const std::string & name() const	//GETTER NAME			
	{
		return _name;
	}

	void name( std::string name)		//SETTER NAME
	{ 	
		_name = name;
	}

	void subscribeClient(Client * c)	//SUBSCRIBIR CLIENTE
	{
		_listSubscribed.push_back(c);
	}

	void subscribeChannel(Channel * c)	//SUBSCRIBIR CANAL
	{
		_listSubscribed.push_back(c);
	}

	std::string listSubscribed()		//LISTAR SUBSCRIPTORES
	{
	
		std::list<Observer*>::iterator it;	
		std::stringstream ss;

		
			for (it=_listSubscribed.begin(); it != _listSubscribed.end(); it++)
			{
				ss << (**it).name();
				ss << "\n";				
			}
			return ss.str();
		
						
	 

	}
	void notify(std::string work,std::string author)	//NOTIFICAR SUBSCRIPTORES
	{

	std::list<Observer*>::iterator it;
	
			for (it=_listSubscribed.begin(); it != _listSubscribed.end(); it++)
			{
			(*it)->update(work,author);								
			}						
	}


	

};

#endif
