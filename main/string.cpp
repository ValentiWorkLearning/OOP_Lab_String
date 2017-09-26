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
	m_EndOfStorage[_N] = '\0';

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
	
			delete[]m_EndOfStorage;
			ExpandMultipleTwoStringBuffer(capacity(), _string.length(), _string.m_DataStart);
			return *this;
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
			ExpandMultipleTwoStringBuffer(capacity(), _string.length(), _string.m_DataStart);
		}
	}
	return *this;
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
			if (_string.IsMemAllocate()) {
				strcat_s(m_EndOfStorage, capacity(), _string.m_EndOfStorage);
			}
			else {
				strcat_s(m_EndOfStorage, capacity(), _string.m_StaticBuffer);
			}
		}
		else {
			/**<Init temponary variables * */
			char * tempString = new char[length() + 1];
			
			/**<Copy source to temp string * */
			memcpy(tempString, m_EndOfStorage, length() + 1);

			/* Memory operations* */
			delete[] m_EndOfStorage;
			ExpandMultipleTwoStringBuffer(capacity(), length() + _string.length(), tempString);

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
			char * tempString = new char[length() + 1];
			
			/**<Copy source to temp string * */
			memcpy(tempString, m_StaticBuffer, length() + 1);

			ExpandMultipleTwoStringBuffer(capacity(), length() + _string.length() + 1, tempString);
			
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

void MyString::ExpandMultipleTwoStringBuffer(long _capacity, long _strLength, char * _stringToCopy)
{
	long tempCapacity = _capacity;
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

char * MyString::c_str()
{
	if (IsMemAllocate())return m_EndOfStorage;
	return m_StaticBuffer;
}

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

bool MyString::empty()
{
	if (length() == 0)return true;
	return false;
}

/*!
* Realization reserve  method which reservate _N characters 
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
* Realization begin method which return pointer to begin of string
*/
char * MyString::begin()const 
{
	return m_DataStart;
}

/*!
* Realization end method which return pointer to end of string
*/
char * MyString::end() 
{
	return m_DataStart+length();
}

/*!
* Realization erase method which insert segment to string in position
*/
void MyString::insert(long pos, const char * data) {
	if (pos<0)throw std::logic_error("Out of range");
	
	if (IsMemAllocate()) {
		/**<Check free place in string* */
		if(capacity() > pos+strlen(data)+length()){

			/**<If  insert position > length of string - copy data to begin+pos area * */
			if (pos > length()) {
				if (empty()) {
					for (long i = 0; i < pos; i++)m_EndOfStorage[i] = ' ';
					memcpy(begin() + pos, data, strlen(data) + 1);
				}

			/**<If  insert position > length of string but string isn`t empty now. Copy begin +pos area, but fill from length() to position * */
				else {
					for (long i = length(); i <= pos; i++) {
						m_EndOfStorage[i] = ' ';
					}
					memcpy(begin() + pos, data, strlen(data) + 1);
				}
			}

			/**<If  insert position < length of string. * */
			else { 
				char * tempString = new char[length() - pos];
				memcpy(tempString, begin() + pos, strlen(begin() +pos )+1);
				memcpy(begin()+pos,data,strlen(data));
				memcpy(begin() + pos + strlen(data), tempString, strlen(tempString)+1);
			}
		}
		else {
			/**<If nothing free memory* */
			char * tempString = new char[length()+1];
			
			memcpy(tempString, m_EndOfStorage, strlen(m_EndOfStorage) + 1);
			delete[] m_EndOfStorage;
			
			ExpandMultipleTwoStringBuffer(capacity(),strlen(tempString)+1+pos+strlen(data), tempString);
		
			insert(pos, data);
			delete[] tempString;
		}

	}
	/**<If  static buffer using now * */
	else {
		if (capacity() > pos + strlen(data) + length()) {
			if (pos > length()) {
				/**<If  insert position > length of string - copy data to begin+pos area * */
				if (empty()) {
					for (long i = 0; i < pos; i++)m_StaticBuffer[i] = ' ';
					memcpy(begin() + pos, data, strlen(data) + 1);
				}
			}
			/**<If  insert position > length of string but string isn`t empty now. Copy begin +pos area, but fill from length() to position * */
			else {
				for (long i = length(); i <= pos; i++) {
					m_StaticBuffer[i] = ' ';
				}
				memcpy(begin() + pos, data, strlen(data) + 1);
			}
		}
		else {
			/**<If nothing free memory* */
			char * tempString = new char[length() + 1];

			memcpy(tempString, m_StaticBuffer, strlen(m_StaticBuffer) + 1);
		
			ExpandMultipleTwoStringBuffer(capacity(), strlen(tempString) + 1 + pos + strlen(data), tempString);

			insert(pos, data);
			delete[] tempString;
		}
	}
}

/*!
* Realization erase method which erase segment in string which have size position + length
*/
void MyString::erase(long pos, long len)
{
	if(pos+len>length()||pos<0||len<0)throw std::logic_error("Out of range");

	if (IsMemAllocate()) {
		char* tempString = new char[length()+1 - len];
		memcpy(tempString, begin() + pos + len, length() + 1 - len);
		
		for (long i = pos; i < len; i++) {
			begin()[pos + i] = ' ';
		}
		
		memcpy(m_EndOfStorage + pos, tempString, strlen(tempString) + 1);
		delete[] tempString;
	}
	else {
		char* tempString = new char[length() + 1 - len];
		memcpy(tempString, begin() + pos + len, length() + 1 - len);
		for (long i = pos; i < len; i++) {
			begin()[pos + i] = ' ';
		}
		memcpy(m_StaticBuffer + pos, tempString, strlen(tempString) + 1);
		delete[] tempString;
	
	}
}

/*!
* Realization substring method which return copy of original string from position to length
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
	memcpy(tempString, begin() + pos, len+1);
	
	MyString returnString{ tempString };
	delete[] tempString;
	return  returnString;
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
