#ifndef Exception_hxx
#define Exception_hxx
#include <exception>

class WorkException : public std::exception
{
	public:
	virtual const char* what() const throw()
	{
			return "The work does not exist";
	}
};

class AuthorException : public std::exception
{
	public:
	virtual const char* what() const throw()
	{
			return "The author does not exist";
	}
};

class OriginalException : public std::exception
{
	public:
	virtual const char* what() const throw()
	{
			return "The original file does not exist";
	}
};

class TopicException : public std::exception
{
	public:
	virtual const char* what() const throw()
	{
			return "The topic does not exist";
	}
};

class ClientException : public std::exception
{
	public:
	virtual const char* what() const throw()
	{
			return "The client does not exist";
	}
};


class FormatException : public std::exception
{
	public:
	virtual const char* what() const throw()
	{
			return "Unsupported format";
	}
};

class ChannelException : public std::exception
{
	public:
	virtual const char* what() const throw()
	{
			return "The thematic channel does not exist";
	}
};

#endif
