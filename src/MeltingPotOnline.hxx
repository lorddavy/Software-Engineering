#ifndef MeltingPotOnline_hxx
#define MeltingPotOnline_hxx
#include "Author.hxx"
#include "Topic.hxx"
#include "Work.hxx"
#include "MailStub.hxx"
#include "Client.hxx"
#include "Exception.hxx"
#include "Channel.hxx"
#include <string.h>
#include "ConverterGroup.hxx"
#include "Model.hxx"
#include <vector>



class MeltingPotOnline : public Model{

private:				

	std::list<Author*> _authors;
	ConverterGroup converterGroup;
	std::list<Topic*> _listTopics;
	std::list<Client*> _listClients;
	std::list<Channel*> _listChannels;
	

public:

	MeltingPotOnline(std::string configFile)	//CONSTRUCTOR ALTERNATIVO
	{	

		std::ifstream config(configFile.c_str()) ;
		std::string format;
		while(config >> format)
	{
		
		converterGroup.add(format);

	}
		
		
	}
	MeltingPotOnline()			//CONSTRUCTOR
	{	

		
		converterGroup.add("html");
		converterGroup.add("pdf_print");
		converterGroup.add("pdf_mark");
		
	}

	~MeltingPotOnline()			//DESTRUCTOR
	{

		std::list<Author*>::const_iterator it;
		for (it=_authors.begin(); it != _authors.end(); it++)
			{
				delete (*it);
			}

		std::list<Topic*>::const_iterator it2;
		for (it2=_listTopics.begin(); it2 != _listTopics.end(); it2++)
			{
				delete (*it2);
			}
		std::list<Client*>::const_iterator it3;
		for (it3=_listClients.begin(); it3 != _listClients.end(); it3++)
			{
				delete (*it3);
			}
		std::list<Channel*>::const_iterator it4;
		for (it4=_listChannels.begin(); it4 != _listChannels.end(); it4++)
			{
				delete (*it4);
			}	
	

	}



	virtual std::string  catalogue() const		//CATALOGO
	{
		std::list<Author*>::const_iterator it;
		std::stringstream ss;

		if (_authors.empty()) { return ""; }
		else 
		{ 
			for (it=_authors.begin(); it != _authors.end(); it++)
			{
				ss << (*it)->description();
				ss << (*it)->catalogue();				
			}
			return ss.str();		
		} 		
	} 

	void addAuthor(const std::string& name, bool contracted)		//AÑADIR AUTOR
	{
		
		Author* authorTemp = new Author();
		
		authorTemp->name(name);
		if(contracted)
		{
		authorTemp->contract();
		}
		
		_authors.push_back(authorTemp);			
	}

	virtual void addWork(const std::string& autor, const std::string& title, int isbn, const std::string& originalFile)		//AÑADIR WORK
	{
		
		std::stringstream ss;
						
		Author & auxAuthor = findAuthor(autor); 	/* findAuthor */
	
		auxAuthor.addWork(title,isbn,originalFile);

		std::string path( "originals/" );
		path += originalFile;
		if( std::ifstream(path.c_str(), std::ifstream::in) == 0) throw OriginalException();
		converterGroup.convert(path,"generated/An author - A work");

		auxAuthor.notify(title, autor);
			
	}

	/*void generateConversions()
	{
		char newFile[100];
		const char* prefix = "generated/An author - A work ";
		const char* fakeGenerated[] = {
			"[multiple HTML files].war",
			"[printable].pdf",
			"[watermark].pdf",
			0 // This zero is needed to stop the loop
		};
		for (int i=0; fakeGenerated[i]; i++)
		{
			strcpy(newFile, prefix);
			strcat(newFile, fakeGenerated[i]);		
			std::ofstream newfile(newFile);
			
		} 
	}*/

	Author & findAuthor (std::string name)	//Busca un autor por su nombre
	{   		 			

	std::list<Author*>::const_iterator it;	

		for (it=_authors.begin(); it != _authors.end(); it++)
		{
				std::string nombre = (*it)->name();
				if(nombre == name)
				{
					return **it;
				}
		}
		throw AuthorException();
	}

	virtual void addTopic (const std::string& name)		//AÑADIR TOPIC
	{
		Topic* topicTemp = new Topic();
		topicTemp->name(name);
		_listTopics.push_back(topicTemp);		

	}

	virtual std::string listTopics ()	const	//MOSTRAR LISTA TOPICS
	{
		std::list<Topic*>::const_iterator it;	
		std::stringstream ss;

		if (_listTopics.empty()) { return ""; }
		else 
		{ 
			for (it=_listTopics.begin(); it != _listTopics.end(); it++)
			{
				ss << (**it).name();
				ss << "\n";				
			}
			return ss.str();		
		} 
	}
	virtual void associateTopicWithWork(const std::string& topic, const std::string& author, const std::string& work)	//ASOCIAR TOPIC Y WORK
	{
	
	Author & authorAux = findAuthor(author);
	Topic & topicAux = findTopic(topic);

	Work & workAux = authorAux.findWork(work);
	workAux.associateTopic(topic);

	//	enviar mensages
	topicAux.notify(work,author);
	
	}

	Topic & findTopic(std::string topicName)			//BUSCAR TOPIC
	{
		std::list<Topic*>::const_iterator it;
		
		for (it=_listTopics.begin(); it != _listTopics.end(); it++)
		{
				std::string nombre = (*it)->name();
				if(nombre == topicName)
				{
					return **it;
				}
		}
		throw TopicException();

	}
	
	void addClient (std::string name, std::string email)		//AÑADIR CLIENT
	{
		Client* clientTemp = new Client();
		clientTemp->name(name);
		clientTemp->email(email);
		_listClients.push_back(clientTemp);		

	}
	std::string listClients ()					//MOSTRAR LISTA CLIENTES
	{

		std::list<Client*>::const_iterator it;	
		std::stringstream ss;

		if (_listClients.empty()) { return ""; }
		else 
		{ 
			for (it=_listClients.begin(); it != _listClients.end(); it++)
			{
				ss << (**it).name() << " <";
				ss << (**it).email() << ">";
				ss << "\n";				
			}
			return ss.str();
			
			
		} 

	}
	
	void subscribeClientToTopic(std::string client, std::string topic)	//SUBSCRIBIR CLIENTE A TOPIC
	{
	
		Client & clientTemp = findClient(client);
		Topic & topicTemp = findTopic(topic);
		topicTemp.subscribeClient(&clientTemp);	

	}
	std::string listSubscribedToTopic(std::string topic)	//LISTAR SUBSCRITOS A TOPIC
	{
	
	Topic & topicTemp = findTopic(topic);
	std::string list = topicTemp.listSubscribed();
	return list;	

	}

	Client & findClient(std::string clientName)			//BUSCAR CLIENT
	{
		std::list<Client*>::const_iterator it;
		
			for (it=_listClients.begin(); it != _listClients.end(); it++)
			{
				std::string nombre = (*it)->name();
				if(nombre == clientName)
				{
					return **it;								
				}
			}

		throw ClientException();
	}
	
	void subscribeClientToAuthor(std::string client, std::string author)		//SUBSCRIBIR CLIENTE A AUTOR
	{
	
		Client & clientTemp = findClient(client);
		Author & authorTemp = findAuthor(author);
		authorTemp.subscribeClient(&clientTemp);	

	}

	std::string listSubscribedToAuthor(std::string author)	//LISTAR SUBSCRITOS A AUTOR
	{
	
	Author & authorTemp = findAuthor(author);
	std::string list = authorTemp.listSubscribed();
	return list;	

	}
	
	void addChannel(std::string name, std::string description)			//AÑADIR CANAL
	{
	
		Channel* channelTemp = new Channel();
		channelTemp->name(name);
		channelTemp->description(description);
		_listChannels.push_back(channelTemp);	

	}
	std::string listThematicChannels()							//LISTAR CANALES
	{

		std::list<Channel*>::const_iterator it;	
		std::stringstream ss;

		if (_listChannels.empty()) { return ""; }
		else 
		{ 
			for (it=_listChannels.begin(); it != _listChannels.end(); it++)
			{
				ss << (**it).name() << "\n\t";
				ss << (**it).description();
				ss << "\n";				
			}
			return ss.str();				
		} 
	}
	
	Channel & findChannel(std::string channelName)			//BUSCAR CHANNEL
	{
		std::list<Channel*>::const_iterator it;
		
			for (it=_listChannels.begin(); it != _listChannels.end(); it++)
			{
				std::string nombre = (*it)->name();
				if(nombre == channelName)
				{
					return **it;								
				}
			}

		throw ChannelException();
	}
	
	std::string rssByChannel (std::string channel)	//RSS DE UN CANAL
	{
	Channel channelTemp = findChannel(channel);
	std::stringstream ss;
		
	//llamar al getter de Channel con todo el contenido

	ss << channelTemp.content();
		
	return ss.str();

	}
	
	void subscribeChannelToAuthor(std::string channel, std::string author)		//SUBSCRIBIR CANAL A AUTOR
	{	
		Channel & channelTemp = findChannel(channel);
		Author & authorTemp = findAuthor(author);
		authorTemp.subscribeChannel(&channelTemp);
	}

	void subscribeChannelToTopic(std::string channel, std::string topic)		//SUBSCRIBIR CANAL A TOPIC
	{	
		Channel & channelTemp = findChannel(channel);
		Topic & topicTemp = findTopic(topic);
		topicTemp.subscribeChannel(&channelTemp);
	}
	
	void clientPrefersSms(std::string client, std::string num)				//SMS
	{
		Client & clientTemp = findClient(client);
		clientTemp.prefersSms(client,num);
	}
	
	void clientPrefersWhatsapp(std::string client, std::string num)			//WhatsApp
	{
		Client & clientTemp = findClient(client);
		clientTemp.prefersWhatsapp(client,num);		
	}
	
};
#endif
