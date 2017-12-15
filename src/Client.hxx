#ifndef Client_hxx
#define Client_hxx
#include "MailStub.hxx"
#include <sstream>
#include "Observer.hxx"
#include "Strategy.hxx"
#include "Email.hxx"
#include "Whatsapp.hxx"
#include "SMS.hxx"


class Client : public Observer{

private:

	std::string _name;					//Atributo Nombre
	std::string _email;					//Atributo Email
	std::string _num;					//Atributo Num
	std::string _pref;					//Atributo Pref
	Strategy * _strategy;				//Atributo Strategy
			
public: 

	Client()										//Constructor	
	{
		_pref = "Email";
		_strategy = new Email ();
	}
	
	~Client()	
	{	
		delete _strategy;
	}
	
	const std::string & name() const			//Método getter de nombre
	{
		return _name;
	}

	void name( const std::string & name ){ 		//Método setter de nombre
	
		_name = name;
	
	}
	

	const std::string & email() const				//Método getter de email
	{
		return _email;	
	}

	void email(const std::string & email)				//Método setter de email
	{
		_email = email;	
	}

	void update(std::string work,std::string author)		// Avisar actualización
	{
	
		if(_pref=="Email")
		{
			std::string to = _name + " <" + _email + ">";
			std::string subject = "new work " + work + " by " + author;						
			_strategy->update(to,subject);					
		}
		if(_pref=="SMS")
		{
			std::string to = _num;
			std::string subject = "[MeltingPot] new work " + work + " by " + author;	
			delete _strategy;
			_strategy = new SMS ();				
			_strategy->update(to,subject);					
		}
		if(_pref=="Whatsapp")
		{
			std::string to = _num;
			std::string subject = "[MeltingPot] new work " + work + " by " + author;	
			delete _strategy;
			_strategy = new Whatsapp();					
			_strategy->update(to,subject);					
		}

	}

	void prefersSms(std::string client, std::string num)				//Preferencia SMS
	{
	
		_num = num;
		_pref = "SMS";
			
	}
	void prefersWhatsapp(std::string client, std::string num)			//Preferencia Whatsapp
	{
		
		_num = num;
		_pref = "Whatsapp";
		
	}
	
};

#endif // Client_hxx
