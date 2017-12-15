#ifndef Email_hxx
#define Email_hxx
#include "MailStub.hxx"
#include <sstream>
#include "Strategy.hxx"


class Email : public Strategy{

private:

			
public: 

	Email()										//Constructor	
	{
	}
	
	~Email()	
	{	
	}

	void update(std::string to, std::string subject)		// Avisar actualización
	{
		
		MailStub::theInstance().sendMail(to,subject);
		
	}
};

#endif // Email_hxx
