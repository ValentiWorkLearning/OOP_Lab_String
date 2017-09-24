#include  "string.hpp"

/*!
* Realization of constructors
*/
MyString::MyString( )
{
	m_DataStart  = m_StaticBuffer;
	m_DataFinish = m_DataStart + MAX_STATIC_SIZE;

	for (unsigned long i = 0; i < strlen(m_StaticBuffer)+1; i++) {
		m_StaticBuffer[i] = 0;
	}
}
MyString::MyString( const char *_string) 
{

	if (strlen(_string) < MAX_STATIC_SIZE) {
		/**< Init buffer array. */
		memcpy(m_StaticBuffer, _string, strlen(_string)+1);

		m_DataStart = m_StaticBuffer;
		m_DataFinish =m_StaticBuffer + MAX_STATIC_SIZE;
	}
	else {
		/**<Init m_EndOfStorage - char* */
		m_EndOfStorage = new char[strlen(_string)+1];
		memcpy(m_EndOfStorage, _string, strlen(_string)+1);

		m_DataStart = m_EndOfStorage;
		m_DataFinish = m_EndOfStorage + strlen(_string)+1;
	}
}
MyString::MyString(long _N) 
{
	if (_N < 0L) {
		throw std::exception("Incorrect size");
	}

	m_EndOfStorage = new char[_N + 1L];

	for (long i = 0; i < _N; i++) {
		m_EndOfStorage[i] = NULL;
	}
	m_EndOfStorage[_N] = '/0';

	m_DataStart = m_EndOfStorage;
	m_DataFinish = m_DataStart + _N;

}

/*!
* Realization of copy constructor,assignment operator, move constructor and move operator
*/
MyString::MyString(const MyString & _string) 
{
	
	/**Create a copy. If memory allocated for _string - allocate memory in copy string. 
	If not - copy only static array*/
	if (_string.m_DataStart != _string.m_StaticBuffer) {
		m_EndOfStorage = new char[strlen(_string.m_EndOfStorage) + 1];

		memcpy(m_EndOfStorage, _string.m_EndOfStorage, strlen(_string.m_EndOfStorage) + 1);

		m_DataStart = m_EndOfStorage;
		m_DataFinish = m_EndOfStorage + strlen(_string.m_EndOfStorage);
	}
	else
	{
		strcpy_s(m_StaticBuffer, strlen(_string.m_StaticBuffer) + 1, _string.m_StaticBuffer);

		m_DataStart = m_StaticBuffer;
		m_DataFinish = m_StaticBuffer + strlen(m_StaticBuffer);
	}
}

MyString & MyString::operator = (const MyString & _string) 
{
	/**<Check self-appropriation  * */
	if (&_string == this) {
		return *this;
	}
	/**Copy assigment operator. If memmory allocated - check capacity this->m_EndOfStorage for copy
	_string data. If free memory is had - free resources and only copy. If free memory isn`t had - delete and
	allocate new segment which have size oldCapacity*2 */
	long currentCapacity = capacity();
	if (this->IsMemAllocate()) {
		
		if (capacity() < _string.length()+1) {
			
			/**<Find memory factor for expand array memory multiples of two*/
			long memoryFactor = FactorMemoryMultipleTwo(capacity(), _string.length());
			delete[] m_EndOfStorage;

			m_EndOfStorage = new char[currentCapacity *memoryFactor];
			
			memcpy(m_EndOfStorage, _string.m_DataStart, _string.length() + 1);
			
			m_DataFinish = m_EndOfStorage + currentCapacity * memoryFactor;
			m_DataStart = m_EndOfStorage;
			
			return *this;
		}
		else {
			delete[]m_EndOfStorage;

			m_EndOfStorage = new char[currentCapacity];

			memcpy(m_EndOfStorage, _string.m_DataStart, _string.length() + 1);

			m_DataStart = m_EndOfStorage;
			m_DataFinish = m_EndOfStorage+currentCapacity;
			return *this;
		}
	}
	/**<If memory didn`t allocate. Check string length. If length< MAX_STATIC_SIZE - copy static array, else allocate new buffer,which
	has size strlen(_string)+1* */
	else {
		if (_string.length() < MAX_STATIC_SIZE) {
			strcpy_s(m_StaticBuffer, strlen(_string.m_StaticBuffer) + 1, _string.m_StaticBuffer);
			m_DataStart = m_StaticBuffer;
			m_DataFinish = m_DataStart+MAX_STATIC_SIZE;
		}
		else {
			/**<Classic copy data* */
			m_EndOfStorage = new char[_string.length() + 1];
			memcpy(m_EndOfStorage, _string.m_DataStart, _string.length() + 1);
			m_DataStart = m_EndOfStorage;
			m_DataFinish = m_EndOfStorage + strlen(m_EndOfStorage);
		
		}
	}
	
}


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

MyString & MyString::operator += (MyString _string) {
	
	if (IsMemAllocate()) {
		if ( capacity() >=  length()+_string.length()+1) {
		strcat_s(m_EndOfStorage,capacity(), _string.m_EndOfStorage);
		}
		else {
			/**<Init temponary variables * */
			char * tempString = new char[length() + 1];
			long currentCapacity = capacity();
			long memoryFactor = FactorMemoryMultipleTwo(capacity(), length()+_string.length());
			
			/**<Copy source to temp string * */
			memcpy(tempString, m_EndOfStorage, length() + 1);

			/* Memory operations and allocation* */
			/* Free old allocated memory and allocate new * */
			delete[] m_EndOfStorage;
			m_EndOfStorage = new char[currentCapacity *memoryFactor];
			
			/* Restore original string in new allocated buffer * */
			memcpy(m_EndOfStorage, tempString, strlen(tempString) + 1);
			m_DataStart = m_EndOfStorage;
			m_DataFinish = m_EndOfStorage + currentCapacity * memoryFactor;

			/* Concatenation strings* */
			if (_string.IsMemAllocate()) {
				strcat_s(m_EndOfStorage, capacity(), _string.m_EndOfStorage);
			}
			else {
				strcat_s(m_EndOfStorage, capacity(), _string.m_StaticBuffer);
			}
			/* Delete temponary buffer* */
			delete[] tempString;
		}

	}
	else {
		/* If static buffer has free memory - concatenation strings without allocate memory* */
		if (length() + _string.length()+1 < MAX_STATIC_SIZE) {
			memcpy(m_StaticBuffer + length(), _string.m_StaticBuffer, _string.length() + 1);
			m_DataStart = m_StaticBuffer;
			m_DataFinish = m_DataStart + MAX_STATIC_SIZE;
		}
		else {
			/**<Init temponary variables * */
			long currentLength = length();
			long allocateBuffer = length() + _string.length() + 1;
			char * tempString = new char[length() + 1];
			
			/**<Copy source to temp string * */
			memcpy(tempString, m_StaticBuffer, length() + 1);

			/* Allocate new  memory* */
			m_EndOfStorage = new char[allocateBuffer];
			m_DataStart = m_EndOfStorage;
			m_DataFinish = m_EndOfStorage + allocateBuffer;
			
			/* Restore original string in new allocated buffer * */
			memcpy(m_EndOfStorage, tempString,currentLength+1);
			
			/* Concatenation strings* */
			if (_string.IsMemAllocate()) {
				strcat_s(m_EndOfStorage, capacity(), _string.m_EndOfStorage);
			}
			else {
				strcat_s(m_EndOfStorage, capacity(), _string.m_StaticBuffer);
			}

			/* Delete temponary buffer* */
			delete[] tempString;
		}
	}
	return  * this;
}

MyString MyString::operator+(MyString _string) const
{
	MyString resultString = *this;
	resultString += _string;
	return resultString;
}

char MyString::operator[](long _index) const
{
	if (_index > capacity()-1) {
		throw std::logic_error("Out of range");
	}
	return begin()[_index];
}

char & MyString::operator[](long _index)
{
	if (_index > capacity() - 1) {
		throw std::logic_error("Out of range");
	}
	return begin()[_index];
}
/*!
* Realization of system functions 
*/

bool MyString::IsMemAllocate()const
{
	/* System method.Return true if memory for m_EndOfStorage was allocated or return false if m_StaticBuffer was used* */
	if (m_DataStart != m_StaticBuffer) { return true; }
	return false;
}

long MyString::FactorMemoryMultipleTwo(long _capacity, long _strLength)
{
	/* System method. Calculate a value which need to allocate new buffer which have size multiple two * */
	long memFactor = 1;
	while (_capacity <= _strLength+1)
	{
		memFactor *= 2;
		_capacity *= memFactor;
	}
	return memFactor;
}


/*!
* Realization of public  methods
*/
long MyString::length()const
{
	if (IsMemAllocate())return strlen(m_EndOfStorage);
	return strlen(m_StaticBuffer);
}

long MyString::capacity()const
{
	long stringCapacity = m_DataFinish - m_DataStart;
	return stringCapacity;
}

void MyString::clear()
{
	if (IsMemAllocate()) {
		delete[] m_EndOfStorage;
	}
	else {
		for (long i = 0; i < MAX_STATIC_SIZE; i++) {
			m_StaticBuffer[i] = 0;
		}
	}
	m_DataStart = m_StaticBuffer;
	m_DataFinish = m_StaticBuffer+MAX_STATIC_SIZE;
}

bool MyString::empty()
{
	if (length() == 0)return true;
	return false;
}

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

char * MyString::begin()const 
{
	return m_DataStart;
}

char * MyString::end() 
{
	return m_DataStart+length();
}


/*!
* Realization of destructor
*/

MyString::~MyString() 
{
	if(IsMemAllocate())delete [] this->m_EndOfStorage;
}

/*!
* Realization of global user literal _s for declare MyString using "Some String"_s
*/

MyString operator"" _s(const char * _string, std::size_t _size)
{
	return MyString( _string);

}
