#ifndef Subject_hxx
#define Subject_hxx
#include <string.h>
#include "Observer.hxx"
#include "Client.hxx"
#include "Channel.hxx"


class Subject{

private:
					

public: 

	Subject()			//CONSTRUCTOR
	{
	}

	~Subject()			//DESTRUCTOR	
	{

	}	

	void subscribeClient(Client * c)	//SUBSCRIBIR CLIENTE
	{
		
	}
	void subscribeChannel(Channel * c)	//SUBSCRIBIR CLIENTE
	{
		
	}

	std::string listSubscribed()		//LISTAR SUBSCRIPTORES
	{		

		return "";

	}
	void notify(std::string work,std::string author)	//NOTIFICAR SUBSCRIPTORES
	{
	
	}


	

};

#endif
