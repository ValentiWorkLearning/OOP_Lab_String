// Valentyn Korniienko, KNURE, 2 cource , Kharkiv, Ukraine
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
	bool IsMemAllocate();

	void ExpandMultipleTwoStringBuffer( long _strLength, char * _stringToCopy);
	void RequestMemoryOfString(long _strlen, bool _allocateNewMemory = false);
    char * GetCurentMemoryBuffer()const;
public:
	
	MyString( );
	
	MyString( const char * _string);

    MyString( long _N );

	//Operators

	MyString(const MyString & _string);
	MyString & operator = (const  MyString & _string);
	MyString(MyString && _string);
	MyString & operator  = (MyString && _string);

	MyString & operator += (MyString _string);
	MyString operator + (MyString _string) const;

	char operator [] (long _index) const;
	char & operator [] (long _index);


	//Methods
	long   length()const;
	
	long   capacity()const;
	
	char * c_str();
	
	void   clear();
	
	bool   empty();
	
	void   reserve(long _N);
	
	char * begin() const;
	
	char * end();
	
	void   insert(long pos, const char * data);

	void   erase(long pos, long len);

	MyString substring(long pos, long len);
	
	~MyString();
};

MyString operator "" _s(const char *_string, std::size_t _size);


inline bool MyString::MyString::empty()
{
	if (length() == 0)return true;
	return false;
}

/*!
* Realization begin method which return pointer to begin of string
*/
inline char * MyString::MyString::begin()const
{
	return m_DataStart;
}

/*!
* Realization end method which return pointer to end of string
*/
inline  char * MyString::MyString::end()
{
	return m_DataStart + length();
}

#endif
