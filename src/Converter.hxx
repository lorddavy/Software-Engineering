#ifndef Converter_hxx
#define Converter_hxx


class Converter{

private:				


public:

	virtual ~Converter()
	{
	}

	virtual void convert(const std::string & file, const std::string & newFile) = 0;	
	
	

};
#endif
