#include  "string.hpp"

/*!
* Realization of constructors
*/
MyString::MyString( ){
	m_DataStart  = m_StaticBuffer;
	m_DataFinish = m_DataStart + MAX_STATIC_SIZE;
	for (unsigned int i = 0; i < strlen(m_StaticBuffer)+1; i++) {
		m_StaticBuffer[i] = 0;
	}
}
MyString::MyString( const char *_string) {

	if (strlen(_string) < 16) {
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
		m_DataFinish = m_EndOfStorage + strlen(_string);
	}
}
MyString::MyString(int _N) {
	if (_N < 0) {
		throw std::exception("Incorrect size");
	}

	m_EndOfStorage = new char[_N + 1];

	for (int i = 0; i < _N; i++) {
		m_EndOfStorage[i] = NULL;
	}
	m_EndOfStorage[_N] = '/0';
	m_DataStart = m_EndOfStorage;
	m_DataFinish = m_DataStart + _N;

}

/*!
* Realization of copy constructor,assignment operator, move constructor and move operator
*/
MyString::MyString(const MyString & _string) {
	
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

MyString & MyString::operator = (const MyString & _string) {
	/**<Check self-appropriation  * */
	if (&_string == this) {
		return *this;
	}
	/**Copy assigment operator. If memmory allocated - check capacity this->m_EndOfStorage for copy
	_string data. If free memory is had - free resources and only copy. If free memory isn`t had - delete and
	allocate new segment which have size oldCapacity*2 */
	int currentCapacity = capacity();
	int memoryFactor = 1;
	if (this->IsMemAllocate()) {
		
		if (capacity() < _string.length()+1) {
			/**<Find magic memory factor:D* */
			while (capacity() <= _string.length()) {
				delete[]m_EndOfStorage;
				memoryFactor *= 2;
				
				m_EndOfStorage = new char[currentCapacity * memoryFactor];
					
				for (int i = 0; i < currentCapacity * memoryFactor; i++) {
					m_EndOfStorage[i] = NULL;
					}
				
				m_EndOfStorage[currentCapacity] = '/0';

				m_DataStart = m_EndOfStorage;
				m_DataFinish = m_EndOfStorage + currentCapacity * memoryFactor;
			}
			memcpy(m_EndOfStorage, _string.m_DataStart, _string.length() + 1);
			
			
			return *this;
		}
		else {
			delete[]m_EndOfStorage;
			m_EndOfStorage = new char[currentCapacity];

			memcpy(m_EndOfStorage, _string.m_DataStart, _string.length() + 1);

			m_DataStart = m_EndOfStorage;
			m_DataFinish = m_DataFinish;
			return *this;
		}
	}
	/**<If memory didn`t allocate. Check string length. If length< 16 - copy static array, else allocate new buffer,which
	has size strlen(_string)+1* */
	else {
		if (_string.length() < 16) {
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
	_string.m_EndOfStorage = _string.m_DataStart = _string.m_DataFinish = nullptr;
}

MyString & MyString::operator  = (MyString && _string) {
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
* Realization of system functions 
*/

bool MyString::IsMemAllocate()const {
	if (m_DataStart != m_StaticBuffer) { return true; }
	return false;
}


/*!
* Realization of public  methods
*/
int MyString::length()const{
	if (IsMemAllocate())return strlen(m_EndOfStorage);
	return strlen(m_StaticBuffer);
}

int MyString::capacity()
{
	return m_DataFinish - m_DataStart;
}

void MyString::clear(){
	if (IsMemAllocate()) {
		delete[] m_EndOfStorage;
	}
	else {
		for (int i = 0; i < MAX_STATIC_SIZE; i++) {
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

char * MyString::begin() {

	return m_DataStart;
}

char * MyString::end() {

	return m_DataStart+length();

}


/*!
* Realization of destructor
*/

MyString::~MyString() {
//	std::cout << "Destructor";
	if(IsMemAllocate())delete [] this->m_EndOfStorage;
}
