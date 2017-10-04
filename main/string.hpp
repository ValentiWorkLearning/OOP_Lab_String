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

	void ExpandMultipleTwoStringBuffer(long _strLength, char * _stringToCopy);
	void RequestMemoryOfString(long _strlen);
	void InitBuffer(void);
	char * GetCurentMemoryBuffer()const;
public:

	MyString();

	MyString(const char * _string);

	MyString(long _N);

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


/*!
* Return true if string is empty
*/
inline bool MyString::MyString::empty()
{
	if (length() == 0)return true;
	return false;

}

/*!
* Return pointer to begin of string
*/
inline char * MyString::begin()const
{
	return m_DataStart;
}

/*!
* Return pointer to end of string
*/
inline  char * MyString::end()
{
	return m_DataStart + length();
}

/*!
* Return char* pointer to strnig
*/
inline char * MyString::c_str()
{
	return GetCurentMemoryBuffer();
}

/*!
* Return string capacity
*/
inline long MyString::capacity()const
{
	long stringCapacity = m_DataFinish - m_DataStart - 1;
	return stringCapacity;
}

/*!
* Return string length
*/
inline long MyString::length() const
{
	return strlen(GetCurentMemoryBuffer());
}

/*!
* Return true if memory for string allocated
*/
inline bool MyString::IsMemAllocate()
{
	if (m_DataStart != m_StaticBuffer) { return true; }
	return false;
}
#endif
