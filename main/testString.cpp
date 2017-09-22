#include "string.hpp"
#include "testlib.hpp"

DECLARE_OOP_TEST(string_test_Create_Empty_String) {
	MyString s1;
	assert(s1.empty());
}

DECLARE_OOP_TEST(string_test_Create_String_With_N_Characters_Reserved) {
	MyString s1{60};
	assert(s1.capacity() == 60);
}

DECLARE_OOP_TEST(string_test_Length_String) {
	char * testString = "Some String";
	MyString s1{ "SomeString" };
	assert(s1.length() != strlen(testString));
}

DECLARE_OOP_TEST(string_test_Copy_Constructor) {
	MyString s1{ "SomeString" };
	MyString s2 = s1;

	assert( s1.length() == s2.length() );
	for (int i = 0; i < s1.length(); i++) {
		assert(s1.begin()[i] == s1.begin()[i]);
	}
}

DECLARE_OOP_TEST(string_test_Exeption_Incorrect_Size) {
	try
	{
		MyString s(-1);
		assert(!"Exception must have been thrown");
	}
	catch (std::exception &e) {
	
		assert(!strcmp(e.what(), "Incorrect size"));
	}

}

DECLARE_OOP_TEST(string_test_CapacityTest__Test_Copy_Constructor_1) {
	MyString s1 = "Hello World123123123";
	MyString s2{ 50 };
	s2 = s1;
	assert(s1.length() == s2.length());
	assert(s2.capacity() == 50);;
}

DECLARE_OOP_TEST(string_test_CapacityTest__Test_Copy_Constructor_2) {
	MyString s1 = "Hello World123123123";
	MyString s2{ 13 };
	s2 = s1;
	assert(s1.length() == s2.length());
	assert( s2.capacity() >= s1.length() );
}

DECLARE_OOP_TEST(string_test_CapacityTest__Test_Copy_Constructor_3) {
	MyString s1 = "Hello World";
	MyString s2;
	s2 = s1;
	assert(s1.length() == s2.length());
}

DECLARE_OOP_TEST(string_test_CapacityTest__Test_Begin) {
	MyString s1 = "Hello World";
	char * string = "Hello World";
	for (int i = 0; i < s1.length(); i++) {
		assert(s1.begin()[i] == string[i]);
	}
}

DECLARE_OOP_TEST(string_test_CapacityTest__Test_End) {
	MyString s1 = "Hello World";
	char  string[12];
	char  etalonString[12] = "dlroW olleH";
	
	for (int i = 0; i >= - s1.length(); i--) {
		string[-i] = s1.end()[i];
	}

	for (int i = 0; i <=10; i++) {
		assert(string[i + 1] == etalonString[i]);
	}

}

DECLARE_OOP_TEST(string_test_CapacityTest__Test_Begin_1) {
	MyString s1 = "Hello World Hello World";
	char * string = "Hello World Hello World";
	for (int i = 0; i < s1.length(); i++) {
		assert(s1.begin()[i] == string[i]);
	}
}


DECLARE_OOP_TEST(string_test_CapacityTest__Test_End_1) {
	MyString s1 = "Hello World Hello World Hello World";
	char  string[36];
	char  etalonString[36] = "dlroW olleH dlroW olleH dlroW olleH";

	for (int i = 0; i >= -s1.length(); i--) {
		string[-i] = s1.end()[i];
	}

	for (int i = 0; i <= 34; i++) {
		assert(string[i + 1] == etalonString[i]);
	}

}



