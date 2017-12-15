#ifndef Observer_hxx
#define Observer_hxx
#include "MailStub.hxx"
#include <sstream>

class Observer{

private:
	
			
public: 

	Observer()										//Constructor						
	{
	}
	
	~Observer()										//Destructor
	{	
	}	
	
	virtual const std::string & name() const = 0;
	
	void name(std::string name) 	//GETTER NAME			
	{
		
	}

	virtual void update(std::string work,std::string author) = 0;		// Avisar actualización
	
	
};

#endif // Observer_hxx
