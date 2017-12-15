#ifndef Collection_hxx
#define Collection_hxx
#include <sstream>
#include <list>
#include "Work.hxx"
#include "Subject.hxx"

class Collection : public Subject{

private:
	std::string _title;
	bool _published;
	std::list<Work*> _works;				

public: 

	Collection()			
		:_title ("-- Untitled --"),
		_published(false)
	{
	}
	~Collection()		
	{
		if (!_works.empty())
		{
			_works.erase(_works.begin(),_works.end());
				
			
		}
	}
	const std::string & title() const			
	{
		return _title;
	}

	void title( std::string title)
	{ 	
		_title = title;
	}

	const bool & isPublished() const
	{
		return _published;
	}

	void publish()
	{
		_published = true;
	}

	void withdraw()
	{
		_published = false;
	}
	

	
	void addWork(Work workTemp)
	{
		_works.push_back(&workTemp);	
	}
	
	
	
	std::string workList()
	{
		std::stringstream ss;
		int index=1;
		std::list<Work*>::iterator it;
		
		if (_works.empty()) { return ""; }
		else 
		{ 
			for (it=_works.begin(); it != _works.end(); it++)
			{

				ss << index<< ": " << (*it)->aText() << "\n";

				index++;
			}
			return ss.str(); 
			
		} 
	}

};

#endif
