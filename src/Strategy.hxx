#ifndef Strategy_hxx
#define Strategy_hxx
#include "MailStub.hxx"
#include <sstream>
#include "Observer.hxx"


class Strategy{

private:

			
public: 

	Strategy()										//Constructor	
	{
	}
	
	~Strategy()	
	{	
	}

	virtual void update(std::string to,std::string subject) = 0;		//Método virtual de actualizar
	
	
};

#endif // Strategy_hxx
