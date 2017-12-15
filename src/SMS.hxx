#ifndef SMS_hxx
#define SMS_hxx
#include "MailStub.hxx"
#include <sstream>
#include "Strategy.hxx"


class SMS : public Strategy{

private:

			
public: 

	SMS()										//Constructor	
	{
	}
	
	~SMS()	
	{	
	}

	void update(std::string to,std::string subject)		// Avisar actualización
	{

		SmsStub::theInstance().sendSms(to,subject);

	}

	
	
};

#endif // SMS_hxx
