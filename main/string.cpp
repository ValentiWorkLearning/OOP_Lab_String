#include  "string.hpp"

/*!
* Constructors
*/
MyString::MyString( )
{
	RequestMemoryOfString(0, true);
	GetCurentMemoryBuffer()[0] = NULL;
}

MyString::MyString( const char *_string) 
{
	RequestMemoryOfString(strlen(_string),true);
	memcpy(GetCurentMemoryBuffer(), _string , strlen(_string) + 1);
}

MyString::MyString(long _N) 
{
	if (_N < 0L) {
		throw std::exception("Incorrect size");
	}
	RequestMemoryOfString(_N-1, true);
	GetCurentMemoryBuffer()[0] = NULL;
}

/*!
* Copy constructor
*/
MyString::MyString(const  MyString & _string) 
{
	/**Create a copy.*/
	RequestMemoryOfString(strlen(_string.GetCurentMemoryBuffer()),true);
	memcpy(GetCurentMemoryBuffer(), _string.GetCurentMemoryBuffer(), strlen(_string.GetCurentMemoryBuffer()) + 1);
}

/*!
* Copy assigment operator
*/
MyString & MyString::operator = (const MyString & _string) 
{
//**<Check self-appropriation  * */
	if (&_string == this) {
			return *this;
		}
	RequestMemoryOfString(strlen(_string.GetCurentMemoryBuffer()));
	memcpy(GetCurentMemoryBuffer(), _string.GetCurentMemoryBuffer(), strlen(_string.GetCurentMemoryBuffer()) + 1);
	return *this;
}

/*!
* Move constructor
*/
MyString::MyString(MyString && _string)
	:m_DataStart(_string.m_DataStart),
	m_EndOfStorage(_string.m_EndOfStorage),
	m_DataFinish(_string.m_DataFinish)
{
		
	memcpy(m_StaticBuffer,_string.m_StaticBuffer,strlen(_string.m_StaticBuffer) + 1);
	if (_string.IsMemAllocate()) {
		_string.m_EndOfStorage = _string.m_DataStart = _string.m_DataFinish = nullptr;
	}
	else {
		m_DataStart = m_StaticBuffer;
		m_DataFinish = m_DataStart + MAX_STATIC_SIZE;
		_string.m_EndOfStorage = _string.m_DataStart = _string.m_DataFinish = nullptr;
	}
	
}

/*!
* Move operator
*/
MyString & MyString::operator  = (MyString && _string) 
{
	if (&_string == this) {
		return * this;
	}
	
	std::swap(m_DataStart, _string.m_DataStart);
	std::swap(m_DataFinish, _string.m_DataFinish);
	std::swap(m_EndOfStorage, _string.m_EndOfStorage);
	std::swap(m_StaticBuffer, _string.m_StaticBuffer);
	return * this;
}

/*!
* Concatenation operator
*/
MyString & MyString::operator += (MyString _string) {
	RequestMemoryOfString(length() + _string.length() + 1);
	strcat_s(GetCurentMemoryBuffer(),capacity(),_string.GetCurentMemoryBuffer());
return  * this;
}

MyString MyString::operator+(const MyString _string) const
{
	MyString resultString = *this;
	resultString += _string;
	return resultString;
}

/*!
*  R|W and R index acess operators
*/
char MyString::operator[](long _index) const
{
	if (_index > length()-1) {
		throw std::logic_error("Out of range");
	}
	return begin()[_index];
}

char & MyString::operator[](long _index)
{
	if (_index > length() - 1) {
		throw std::logic_error("Out of range");
	}
	return begin()[_index];
}

/*!
* Return true if memory for string allocated 
*/
bool MyString::IsMemAllocate()
{
	if (m_DataStart != m_StaticBuffer) { return true; }
	return false;
}

/*!
* Expand string buffer multiple 2
*/
void MyString::ExpandMultipleTwoStringBuffer(long _strLength,char* _stringToCopy)
{
	long tempCapacity = capacity();
	while (tempCapacity <= _strLength + 1)
	{
		tempCapacity *=2;
	}

	m_EndOfStorage = new char[tempCapacity];
	memcpy(m_EndOfStorage, _stringToCopy, _strLength + 1);
	m_DataStart = m_EndOfStorage;
	m_DataFinish = m_EndOfStorage + tempCapacity;
}

/*!
* Reqyest free memory (size == _strlen) in string, second parameter - if true -only allocate  new memory
*/
void MyString::RequestMemoryOfString(long _strlen, bool _allocateNewMemory )
{
	if (_allocateNewMemory) {
		if (_strlen < MAX_STATIC_SIZE) {
			m_DataStart = m_StaticBuffer;
			m_DataFinish = m_DataStart + MAX_STATIC_SIZE;
		}
		else {
			m_EndOfStorage = new char[_strlen + 1];
			m_DataStart = m_EndOfStorage;
			m_DataFinish = m_EndOfStorage + _strlen + 1;
		}
	}
	else {
		if (capacity() < _strlen + 1) {
			char * tempString = new char[length() + 1];
			memcpy(tempString, GetCurentMemoryBuffer(), length() + 1);
			if (IsMemAllocate())delete[] m_EndOfStorage;
			ExpandMultipleTwoStringBuffer(_strlen + strlen(tempString) + 1, tempString);
			delete[] tempString;
		}
	}
}

 char * MyString::GetCurentMemoryBuffer()const
{ 
	if(m_DataStart!=m_StaticBuffer)return m_EndOfStorage;
	return m_DataStart;
}

/*!
* Return string length
*/
long MyString::length() const 
{	
	return strlen(GetCurentMemoryBuffer());
}

/*!
* Return string capacity
*/
long MyString::capacity()const
{
	long stringCapacity = m_DataFinish - m_DataStart;
	return stringCapacity;
}

/*!
* Return char* pointer to strnig
*/
char * MyString::c_str()
{
	return GetCurentMemoryBuffer();
}

/*!
* Clear string
*/
void MyString::clear()
{
	if (IsMemAllocate()) {
		delete m_EndOfStorage;
	}
	else {
		for (long i = 0; i < MAX_STATIC_SIZE; i++) {
			m_StaticBuffer[i] = 0;
		}
	}
	m_DataStart = m_StaticBuffer;
	m_DataFinish = m_StaticBuffer+MAX_STATIC_SIZE;
}

/*!
* Reserve N characters in string
*/
void MyString::reserve(long _N)
{
	/**<Copy this->string data and allocate new memory. If buffer is used - allocate memory in m_EndOfData.* */

	char * tempString = new char[ length()+1 ];
	long currentCapacity = capacity();

	if (IsMemAllocate()) { 
		memcpy(tempString, m_EndOfStorage, length() + 1);
		delete[] m_EndOfStorage;
	}
	else {
		memcpy(tempString, m_StaticBuffer, length() + 1);
	}

	m_EndOfStorage = new char[currentCapacity + _N];
	memcpy(m_EndOfStorage, tempString, strlen(tempString) + 1);
	m_DataStart = m_EndOfStorage;
	m_DataFinish = m_DataStart + currentCapacity + _N;

	delete[] tempString;
}

/*!
* Insert char * to position in string
*/
void MyString::insert(long pos, const char * data) {
	
	if (pos<0 || pos >length())throw std::logic_error("Out of range");
	char * tempString = new char [length()-pos+1];

	RequestMemoryOfString(pos + strlen(data) + length());
	
	memcpy(tempString, GetCurentMemoryBuffer() + pos, strlen(begin() + pos) + 1);
	memcpy(GetCurentMemoryBuffer() + pos, data, strlen(data));
	memcpy(GetCurentMemoryBuffer() + pos + strlen(data), tempString, strlen(tempString) + 1);

	delete [] tempString;
}

/*!
* Erase fragment in string
*/
void MyString::erase(long pos, long len)
{
	if(pos+len>length()||pos<0||len<0)throw std::logic_error("Out of range");
	
	char* tempString = new char[length() + 1 - len];
	
	memcpy(tempString, GetCurentMemoryBuffer() + pos + len, length() + 1 - len);
	
	for (long i = pos; i < len; i++) {
		begin()[pos + i] = ' ';
	}

	memcpy(GetCurentMemoryBuffer() + pos, tempString, strlen(tempString) + 1);
	delete[] tempString;
}

/*!
* Return copy of original string 
*/
MyString MyString::substring(long pos, long len)
{
	if ((len == -1)&&(pos>0)) {
		char*tempString = new char[length()-pos+1];
		
		memcpy(tempString, begin() + pos, length() - pos + 1);

		MyString returnString{ tempString };

		delete[] tempString;

		return  returnString;
	}

	if (pos + len>length() || pos<0 || len<0)throw std::logic_error("Out of range");
		
	char*tempString = new char[pos + len+1];
	
	for (int i = 0; i < pos + len + 1; i++) {
		tempString[i] = '\0';
	}
	memcpy(tempString, GetCurentMemoryBuffer() + pos, len+1);
	
	MyString returnString{ tempString };
	delete[] tempString;
	return  returnString;
}

/*!
* Destructor
*/
MyString::~MyString() 
{
	if(IsMemAllocate())delete [] this->m_EndOfStorage;
}

/*!
* Global user literal _s for declare MyString using "Some String"_s
*/
MyString operator"" _s(const char * _string, std::size_t _size)
{
	return MyString( _string);
}
