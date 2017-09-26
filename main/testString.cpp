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

DECLARE_OOP_TEST(string_test_Create_String_With_0_Characters_Reserved) {
	MyString s1{ 0L };
	assert(s1.capacity() == 0);
}

DECLARE_OOP_TEST(string_test_Length_String) {
	char * testString = "Some String";
	MyString s1{ "Some String" };
	assert(s1.length() == strlen(testString));
}

DECLARE_OOP_TEST(string_test_Length_String_1) {
	char * testString = " ";
	MyString s1{ " " };
	assert(s1.length() == strlen(testString));
}

DECLARE_OOP_TEST(string_test_EmptyTest) {
	MyString s1{ "Hello world" };
	s1.clear();
	assert( s1.empty() == true);
}

DECLARE_OOP_TEST(string_test_Copy_Constructor) {
	MyString s1{ "SomeString" };
	MyString s2 = s1;

	assert( s1.length() == s2.length() );
	for (int i = 0; i < s1.length(); i++) {
		assert(s1.begin()[i] == s1.begin()[i]);
	}
}

DECLARE_OOP_TEST(string_test_Copy_Constructor_1) {
	MyString s1{ " " };
	MyString s2 = s1;

	assert(s1.length() == s2.length());
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
	MyString s1{ "Hello World123123123" };
	MyString s2{ 50 };
	s2 = s1;
	for (int i = 0; i < s1.length(); i++) {
		assert(s1[i] == s2[i]);
	}
	assert(s1.length() == s2.length());
	int i = s2.capacity();
	assert(s2.capacity() == 50);
}

DECLARE_OOP_TEST(string_test_CapacityTest__Test_Copy_Constructor_2) {
	MyString s1 {"Hello World123123123"};
	MyString s2{ 13 };
	s2 = s1;
	for (int i = 0; i < s1.length(); i++) {
		assert(s1[i] == s2[i]);
	}
	assert(s1.length() == s2.length());
	assert( s2.capacity() >= s1.length() );
}

DECLARE_OOP_TEST(string_test_CapacityTest__Test_Copy_Constructor_3) {
	MyString s1{ "Hello World" };
	MyString s2;
	s2 = s1;
	for (int i = 0; i < s1.length(); i++) {
		assert(s1[i] == s2[i]);
	}
	assert(s1.length() == s2.length());
}

DECLARE_OOP_TEST(string_test_CapacityTest__Test_Copy_Constructor_4) {
	MyString s1{ "Hello Worldello World123123123" };
	MyString s2;
	s2 = s1;
	for (int i = 0; i < s1.length(); i++) {
		assert(s1[i] == s2[i]);
	}
	assert(s1.length() == s2.length());
}

DECLARE_OOP_TEST(string_test_CapacityTest__Test_Begin) {
	MyString s1{ "Hello World" };
	char * string = "Hello World";
	for (int i = 0; i < s1.length(); i++) {
		assert(s1.begin()[i] == string[i]);
	}
}

DECLARE_OOP_TEST(string_test_CapacityTest__Test_Begin_1) {
	MyString s1{ "Hello World Hello World" };
	char * string = "Hello World Hello World";
	for (int i = 0; i < s1.length(); i++) {
		assert(s1.begin()[i] == string[i]);
	}
}

DECLARE_OOP_TEST(string_test_CapacityTest__Test_End) {
	MyString s1 { "Hello World" };
	char  string[12];
	char  etalonString[12] = "dlroW olleH";

	for (int i = 0; i >= -s1.length(); i--) {
		string[-i] = s1.end()[i];
	}

	for (int i = 0; i <= 10; i++) {
		assert(string[i + 1] == etalonString[i]);
	}

}

DECLARE_OOP_TEST(string_test_CapacityTest__Test_End_1) {
	MyString s1{ "Hello World Hello World Hello World" };
	char  string[36];
	char  etalonString[36] = "dlroW olleH dlroW olleH dlroW olleH";

	for (int i = 0; i >= -s1.length(); i--) {
		string[-i] = s1.end()[i];
	}

	for (int i = 0; i <= 34; i++) {
		assert(string[i + 1] == etalonString[i]);
	}

}

DECLARE_OOP_TEST(string_test_ReserveTest_1) {
	MyString s1;
	s1.reserve(100);
	assert(s1.capacity() == 116);

}

DECLARE_OOP_TEST(string_test_ReserveTest_2) {
	MyString s1{ "Hello World" };
	char * etalonString = "Hello World";
	s1.reserve(100);
	assert(s1.capacity() == 116);
	for (int i = 0; i < s1.length(); i++) {
		assert(s1.begin()[i] == etalonString[i]);
	}
}

DECLARE_OOP_TEST(string_test_ReserveTest_3) {
	MyString s1 { "Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World" };
	char * etalonString = "Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World Hello World ";
	s1.reserve(100);

	assert(s1.capacity() == 208);
	
	for (int i = 0; i < s1.length(); i++) {
		assert(s1.begin()[i] == etalonString[i]);
	}
}

DECLARE_OOP_TEST(string_test_ReserveTest_4) {
	MyString s1{ 50 };
	s1.reserve(100);

	assert(s1.capacity() == 150);
}

DECLARE_OOP_TEST(string_test_ReserveTest_5) {
	MyString s1{ 50 };
	MyString s2{ "HELLO WORLD" };
	s1 = s2;
	s1.reserve(100);
	assert(s1.capacity() == 150);

	for (int i = 0; i < s1.length(); i++) {
		assert(s1.begin()[i] == s2.begin()[i]);
	}
}

DECLARE_OOP_TEST(string_test_ReserveTest_6) {
	MyString s1( (long)0 );
	s1.reserve(100);
	assert(s1.capacity() == 100);
}

DECLARE_OOP_TEST(string_test_ConcatenationTest_1) {
	MyString s1{ "Hello world" };
	MyString s2{ "abc" };
	s1 += s2;
	char str1[16] = "Hello world";
	char str2[4] = "abc";
	strcat_s(str1, sizeof(str1) / sizeof(char), str2);

	for (int i = 0; i < s1.length(); i++) {
		assert(s1.begin()[i] == str1[i]);
	}
	assert(s1.length() + s2.length() + 1 == strlen(str1) + strlen(str2) + 1);
}

DECLARE_OOP_TEST(string_test_ConcatenationTest_2) {
	MyString s1{ "Hello world ab" };
	MyString s2{ "abc" };
	s1 += s2;
	char str1[20] = "Hello world ab";
	char str2[4] = "abc";
	strcat_s(str1, sizeof(str1) / sizeof(char), str2);

	for (int i = 0; i < s1.length(); i++) {
		assert(s1.begin()[i] == str1[i]);
	}
	assert(s1.length() + s2.length() + 1 == strlen(str1) + strlen(str2) + 1);
}

DECLARE_OOP_TEST(string_test_ConcatenationTest_3) {
	MyString s1{ "Hello world Hello world Hello world " };
	MyString s2{ "abc" };
	s1 += s2;
	char str1[47] = "Hello world Hello world Hello world ";
	char str2[4] = "abc";
	strcat_s(str1, sizeof(str1) / sizeof(char), str2);

	for (int i = 0; i < s1.length(); i++) {
		assert(s1.begin()[i] == str1[i]);
	}
	assert(s1.length() + s2.length() + 1 == strlen(str1) + strlen(str2) + 1);
}

DECLARE_OOP_TEST(string_test_ConcatenationTest_4) {
	MyString s1{ "Hello world Hello world Hello world " };
	MyString s2{ "Hello world Hello world Hello world Hello world Hello world Hello world" };
	s1 += s2;
	char str1[200] = "Hello world Hello world Hello world ";
	char str2[72] = "Hello world Hello world Hello world Hello world Hello world Hello world";
	strcat_s(str1, sizeof(str1) / sizeof(char), str2);

	for (int i = 0; i < s1.length(); i++) {
		assert(s1.begin()[i] == str1[i]);
	}
	assert(s1.length() + s2.length() + 1 == strlen(str1) + strlen(str2) + 1);
}

DECLARE_OOP_TEST(string_test_ConcatenationTest_5) {
	MyString s1{ " " };
	MyString s2{ "Hello world Hello world Hello world Hello world Hello world Hello world" };
	s1 += s2;
	char str1[200] = " ";
	char str2[72] = "Hello world Hello world Hello world Hello world Hello world Hello world";
	strcat_s(str1, sizeof(str1) / sizeof(char), str2);

	for (int i = 0; i < s1.length(); i++) {
		assert(s1.begin()[i] == str1[i]);
	}
	assert(s1.length() + s2.length() + 1 == strlen(str1) + strlen(str2) + 1);
}

DECLARE_OOP_TEST(string_test_ConcatenationTest_6) {
	MyString s1{ "Hello world ab" };
	MyString s2{ "Hello world ab" };
	s1 += s2;
	char str1[200] = "Hello world ab";
	char str2[72] = "Hello world ab";
	strcat_s(str1, sizeof(str1) / sizeof(char), str2);

	for (int i = 0; i < s1.length(); i++) {
		assert(s1.begin()[i] == str1[i]);
	}
	assert(s1.length() + s2.length() + 1 == strlen(str1) + strlen(str2) + 1);
}

DECLARE_OOP_TEST(string_test_ConcatenationTest_7) {
	MyString s1{ "a1" };
	MyString s2{ " " };
	s1 += s2;
	char str1[200] = "a1";
	char str2[72] = " ";
	strcat_s(str1, sizeof(str1) / sizeof(char), str2);

	for (int i = 0; i < s1.length(); i++) {
		assert(s1.begin()[i] == str1[i]);
	}
	assert(s1.length() + s2.length() + 1 == strlen(str1) + strlen(str2) + 1);
}

DECLARE_OOP_TEST(string_test_ConcatenationTest_8) {
	MyString s1{ "a1" };
	MyString s2 = s1;
	s1 += s2;
	char str1[200] = "a1";
	char str2[72] = "a1";
	strcat_s(str1, sizeof(str1) / sizeof(char), str2);

	for (int i = 0; i < s1.length(); i++) {
		assert(s1.begin()[i] == str1[i]);
	}
	assert(s1.length() + s2.length() + 1 == strlen(str1) + strlen(str2) + 1);
}

DECLARE_OOP_TEST(string_test_ConcatenationTest_9) {
	MyString s1{ "\0\0\0\0" };
	MyString s2 = s1;
	s1 += s2;
	char str1[200] = "\0\0\0\0";
	char str2[72] = "\0\0\0\0\0";
	strcat_s(str1, sizeof(str1) / sizeof(char), str2);

	for (int i = 0; i < s1.length(); i++) {
		assert(s1.begin()[i] == str1[i]);
	}
	assert(s1.length() + s2.length() + 1 == strlen(str1) + strlen(str2) + 1);
}

DECLARE_OOP_TEST(string_test_ConcatenationTest_10) {
	MyString s1{ "Hello" };
	MyString s2{ "Hello" };
	s1 += s2;
	char str1[200] = "Hello";
	char str2[72] = "Hello";
	strcat_s(str1, sizeof(str1) / sizeof(char), str2);

	for (int i = 0; i < s1.length(); i++) {
		assert(s1.begin()[i] == str1[i]);
	}
	assert(s1.length() + s2.length() + 1 == strlen(str1) + strlen(str2) + 1);
}



DECLARE_OOP_TEST(string_test_ConcatenationTest_11) {
	MyString s1{ "Hello World" };
	MyString s2 = s1;
	MyString s3 = s1 + s2;
	char * resultString = "Hello WorldHello World";

	for (int i = 0; i < s3.length(); i++) {
		assert(s3.begin()[i] == resultString[i]);
	}
	assert(s1.length() + s2.length() == s3.length());
}

DECLARE_OOP_TEST(string_test_ConcatenationTest_12) {
	MyString s1{ "Hello World Hello World" };
	MyString s2{ "Hm... Maybe it`s working."};
	MyString s3 = s1 + s2;
	char * resultString = "Hello World Hello WorldHm... Maybe it`s working.";

	for (int i = 0; i < s3.length(); i++) {
		assert(s3.begin()[i] == resultString[i]);
	}
	assert(s1.length() + s2.length() == s3.length());
}

DECLARE_OOP_TEST(string_test_ConcatenationTest_13) {
	MyString s1{ "abc" };
	MyString s2{ "Hello World" };
	MyString s3 = (s1 + s2);
	char * resultString = "abcHello World";

	for (int i = 0; i < s3.length(); i++) {
		assert(s3.begin()[i] ==resultString[i]);
	}
	assert(s1.length() + s2.length() == s3.length());
}

DECLARE_OOP_TEST(string_test_ConcatenationTest_14) {
	MyString s1{ " " };
	MyString s2{ "Hello World" };
	MyString s3 = s1 + s2;
	char * resultString = " Hello World";

	for (int i = 0; i < s3.length(); i++) {
		assert(s3.begin()[i] == resultString[i]);
	}
	assert(s1.length() + s2.length() == s3.length());
}

DECLARE_OOP_TEST(string_test_ConcatenationTest_15) {
	MyString s1{ "Hello" };
	MyString s2{ "Hello" };
	MyString s3 = s1 + s2;
	char * resultString = "HelloHello";

	for (int i = 0; i < s3.length(); i++) {
		assert(s3.begin()[i] == resultString[i]);
	}
	assert(s1.length() + s2.length() == s3.length());
}

DECLARE_OOP_TEST(string_test_ConcatenationTest_16) {
	MyString s1{ " " };
	MyString s2{ " " };
	MyString s3 = s1 + s2;
	char * resultString = "  ";

	for (int i = 0; i < s3.length(); i++) {
		assert(s3.begin()[i] == resultString[i]);
	}
	assert(s1.length() + s2.length() == s3.length());
}

DECLARE_OOP_TEST(string_test_OperatorIndexAccessReadWrite_1) {
	MyString s1{ "Hello World" };;
	s1[3L] = 'F';
	assert(s1[3L] == 'F');
}

DECLARE_OOP_TEST(string_test_OperatorIndexAcessReadWrite_2) {
	MyString s1{ "Hello World Hello World" };
	char testChar[22] = "TEST ACCESS TO ";
	
	for (long i = 0L; i < strlen(testChar); i++) {
		s1[(long)i] = testChar[i];
	}
	
	for (long i = 0L; i < strlen(testChar); i++) {
		assert(s1[(long)i] == testChar[i]);
	}
}

DECLARE_OOP_TEST(string_test_OperatorIndexAccessReadWrite_3) {
	MyString s1{ 24 };
	char testChar[22] = "TEST ACCESS TO ";
	
	for (long i = 0L; i < strlen(testChar); i++) {
		s1[(long)i] = testChar[i];
	}
	
	for (long i = 0L; i < strlen(testChar); i++) {
		assert(s1[(long)i] == testChar[i]);
	}
}

DECLARE_OOP_TEST(string_test_OperatorIndexAccessReadWrite_4) {
	MyString s1{ 20 };
	try
	{
		s1[25] = 'F';
	
		assert(!"Exception must have been thrown");
	}
	catch (std::logic_error &e) {

		assert(!strcmp(e.what(), "Out of range"));
	}
}

DECLARE_OOP_TEST(string_test_OperatorIndexAccessReadWrite_5) {
	MyString s1{ "Hello World" };
	try
	{
		if (s1[25] == 'F');
		assert(!"Exception must have been thrown");
	}
	catch (std::logic_error &e) {

		assert(!strcmp(e.what(), "Out of range"));
	}
}

DECLARE_OOP_TEST(string_test_UserLiteral_s_1) {
	"Test user literal"_s;
	MyString s1("Test user literal");
	
	assert(s1.length() == "Test user literal"_s.length());
	
	MyString s2 = "Test literal"_s;
	MyString s3{"Test literal"};
	
	for (int i = 0; i < s2.length(); i++) {
		assert(s3[i] == s2[i]);
	}
}

DECLARE_OOP_TEST(string_test_UserLiteral_s_2) {
	MyString s1 = "Test literal"_s;
	MyString s2{ "Test literal" };
	MyString s3 = s2 + s1;
	MyString sEtalon = "Test literalTest literal"_s;
	
	for (int i = 0; i < sEtalon.length();  i++) {
		assert(s3[i] == sEtalon[i]);
	}
}

DECLARE_OOP_TEST(string_test_c_str_1) {
	MyString s1 = "Simple test c_str method"_s;
	char * str1 = s1.c_str();
	
	for (int i = 0; i < s1.length(); i++) {
		assert(s1[i] == str1[i]);
	}
}

DECLARE_OOP_TEST(string_test_c_str_2) {
	MyString s1 = "c_str method"_s;
	char * str1 = s1.c_str();

	for (int i = 0; i < s1.length(); i++) {
		assert(s1[i] == str1[i]);
	}
}

DECLARE_OOP_TEST(string_test_c_str_3) {
	MyString s1("c_str method");
	char * str1 = new char[s1.length() + 1];
	char etalonString[13] = "c_str method";

	memcpy(str1, s1.c_str(), s1.length() + 1);
	s1.clear();

	for (int i = 0; i < strlen(str1); i++) {
		assert(str1[i] == etalonString[i]);
	}

	delete[] str1;
}

DECLARE_OOP_TEST(string_test_c_str_4) {
	MyString s1("c_str method c_str method c_str method c_str method c_str methodc_str method\
	c_str methodc_str methodc_str methodc_str methodc_str methodc_str methodc_str methodc_str \
	methodc_str methodc_str methodc_str method c_str methodc_str methodc_str methodc_str method \
	c_str methodc_str methodc_str methodc_str methodc_str methodc_str methodc_str methodc_str meth\
	od c_str methodc_str methodc_str methodc_str method c_str methodc_str methodc_str methodc_str method\
	c_str method c_str method c_str method c_str method c_str methodc_str method\
	c_str methodc_str methodc_str methodc_str methodc_str methodc_str methodc_str methodc_str \
	methodc_str methodc_str methodc_str method c_str methodc_str methodc_str methodc_str method \
	c_str methodc_str methodc_str methodc_str methodc_str methodc_str methodc_str methodc_str meth\
	od c_str methodc_str methodc_str methodc_str method c_str methodc_str methodc_str methodc_str \
	methodc_str method c_str method c_str method c_str method c_str methodc_str method\
	c_str methodc_str methodc_str methodc_str methodc_str methodc_str methodc_str methodc_str \
	methodc_str methodc_str methodc_str method c_str methodc_str methodc_str methodc_str method \
	c_str methodc_str methodc_str methodc_str methodc_str methodc_str methodc_str methodc_str meth\
	od c_str methodc_str methodc_str methodc_str method c_str methodc_str methodc_str methodc_str method");
	char * str1 = new char[s1.length() + 1];
	MyString etalonString("c_str method c_str method c_str method c_str method c_str methodc_str method\
	c_str methodc_str methodc_str methodc_str methodc_str methodc_str methodc_str methodc_str \
	methodc_str methodc_str methodc_str method c_str methodc_str methodc_str methodc_str method \
	c_str methodc_str methodc_str methodc_str methodc_str methodc_str methodc_str methodc_str meth\
	od c_str methodc_str methodc_str methodc_str method c_str methodc_str methodc_str methodc_str method\
	c_str method c_str method c_str method c_str method c_str methodc_str method\
	c_str methodc_str methodc_str methodc_str methodc_str methodc_str methodc_str methodc_str \
	methodc_str methodc_str methodc_str method c_str methodc_str methodc_str methodc_str method \
	c_str methodc_str methodc_str methodc_str methodc_str methodc_str methodc_str methodc_str meth\
	od c_str methodc_str methodc_str methodc_str method c_str methodc_str methodc_str methodc_str \
	methodc_str method c_str method c_str method c_str method c_str methodc_str method\
	c_str methodc_str methodc_str methodc_str methodc_str methodc_str methodc_str methodc_str \
	methodc_str methodc_str methodc_str method c_str methodc_str methodc_str methodc_str method \
	c_str methodc_str methodc_str methodc_str methodc_str methodc_str methodc_str methodc_str meth\
	od c_str methodc_str methodc_str methodc_str method c_str methodc_str methodc_str methodc_str method");

	memcpy(str1, s1.c_str(), s1.length() + 1);
	s1.clear();
	for (int i = 0; i < strlen(str1); i++) {
		assert(str1[i] == etalonString[i]);
	}

	delete[] str1;
}

DECLARE_OOP_TEST(string_test_Insert_Test_1) {
	MyString s1{22};
	MyString etalonString{""};
	s1.insert(7, "Hello world");
}

DECLARE_OOP_TEST(string_test_Insert_Test_2) {
	MyString s1{ 20 };
	s1+= "Some test string"_s;
	MyString etalonString{ "" };
	s1.insert(41, "Hello");
}

DECLARE_OOP_TEST(string_test_Insert_Test_3) {
	MyString s1{ 20 };
	MyString etalonString{ "HELLO  IT`S WORK?                                        Hello" };
	s1.insert(41, "Hello");
	s1.insert(0, "HELLO");
	s1.insert(6, " IT`S WORK?");
	for (int i = 0; i <s1.length(); i++) {
		assert(s1[i] == etalonString[i]);
	}
}
DECLARE_OOP_TEST(string_test_Insert_Test_4) {
	MyString s1{};
	MyString etalonString{ "HELLO  IT`S WORK?                                        Hello" };
	s1.insert(41, "Hello");
	s1.insert(0, "HELLO");
	s1.insert(6, " IT`S WORK?");
	for (int i = 0; i <s1.length(); i++) {
		assert(s1[i] == etalonString[i]);
	}
} 

DECLARE_OOP_TEST(string_test_Insert_Test_5) {
	MyString s1{};
	MyString etalonString{ "HELLO  IT`S WORK?                                        Hello" };
	s1.insert(41, "Hello");
	s1.insert(0, "HELLO");
	s1.insert(6, " IT`S WORK?");
	for (int i = 0; i <s1.length(); i++) {
		assert(s1[i] == etalonString[i]);
	}
}

DECLARE_OOP_TEST(string_test_Erase_Test_1) {
	MyString s1{};
	s1.insert(41, "Hello");
	s1.insert(0, "HELLO");
	s1.insert(6, " IT`S WORK?");
	s1.erase(20, 20);
	s1.erase(0, 40);
}

DECLARE_OOP_TEST(string_test_Erase_Test2) {
	MyString s1{};
	s1.insert(0, "HELLO");
	try
	{
		s1.erase(20,2);
		assert(!"Exception must have been thrown");
	}
	catch (std::logic_error &e) {

		assert(!strcmp(e.what(), "Out of range"));
	}
	s1.erase(0, 3);

}

DECLARE_OOP_TEST(string_test_Erase_Test3) {
	MyString s1{};
	s1.insert(4, "HELLO");
	
	s1.insert(8, "HELLO");

	s1.erase(0, 3);
	s1.erase(5, 4);
}

DECLARE_OOP_TEST(string_test_Substring_Test_1) {
	MyString s1{};
	s1.insert(4, "HELLO");

	MyString s2 = s1.substring(4, 3);

}

DECLARE_OOP_TEST(string_test_Substring_Test_2) {
	MyString s1{49};
	s1.insert(4, "HELLO");
	s1.insert(20, "Out of range");
	MyString s2 = s1.substring(4, 3);
	MyString s3 = s1.substring(20, 12);
}

DECLARE_OOP_TEST(string_test_Substring_Test_3) {
	MyString s1{ 49 };
	s1.insert(4, "HELLO");
	s1.insert(20, "Out of range");

	MyString s2 = s1.substring(4, 3);
	MyString s3 = s1.substring(1, -1);
	s3 += s1;
}













