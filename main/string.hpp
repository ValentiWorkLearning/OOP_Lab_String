#ifndef STRING_H
#define STRING_H

#include <cstring>
#include <iostream>

class MyString
{
private:

	static const int MAX_STATIC_SIZE = 16;

	union
	{
		char* m_EndOfStorage;
		char m_StaticBuffer[MAX_STATIC_SIZE];
	};

	char* m_DataStart;
	char* m_DataFinish;
	bool IsMemAllocate()const;
	long FactorMemoryMultipleTwo(long _capacity, long _strLength);
public:
	
	MyString( );
	
	MyString( const char * _string);

	MyString( int _N );
	//MyString( int N );

	//Operators

	MyString(const MyString & _string);
	MyString & operator = (const  MyString & _string);
	MyString(MyString && _string);
	MyString & operator  = (MyString && _string);

	MyString & operator += (MyString _string);

	//Methods
	int	   length()const;
	
	int	   capacity();
	
	char * c_str();
	
	void   clear();
	
	bool   empty();
	
	void   reserve(long _N);
	
	char * begin();
	
	char * end();
	
	void   insert(long pos, const char * data);

	void   erase(long pos, long len);

	MyString * substring(long pos, long len);
	
	~MyString();
};



#endif
