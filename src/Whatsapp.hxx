#ifndef Whatsapp_hxx
#define Whatsapp_hxx
#include "MailStub.hxx"
#include <sstream>
#include "Strategy.hxx"


class Whatsapp : public Strategy{

private:

			
public: 

	Whatsapp()										//Constructor	
	{
	}
	
	~Whatsapp()	
	{	
	}

	void update(std::string to,std::string subject)		// Avisar actualización
	{

		WhatsappStub::theInstance().sendWhatsapp(to,subject);
                                 
	}	
	
};

#endif // Whatsapp_hxx
