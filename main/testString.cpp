#include "string.hpp"
#include "testlib.hpp"


DECLARE_OOP_TEST(string_test_Create_String_1) {
	MyString s1;
	assert(s1.empty());
}

DECLARE_OOP_TEST(string_test_Create_String_3) {
	MyString s1{ 0L };
	assert(s1.capacity() == 16);
}

DECLARE_OOP_TEST(string_test_Create_String_4) {
	MyString s1{ "Hello World" };
	assert(s1.capacity() == 16);
	assert(!strcmp(s1.c_str(), "Hello World"));
}

DECLARE_OOP_TEST(string_test_Create_String_5) {
	MyString s1{ "Hello World Hello World" };
	assert(s1.capacity() == 24);
	assert(!strcmp(s1.c_str(), "Hello World Hello World"));
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

DECLARE_OOP_TEST(string_test_Copy_Constructor_1) {
	MyString s1{ "Hello World123123123" };
	MyString s2{ 50 };
	s2 = s1;
	assert( !strcmp ( s1.c_str(), s2.c_str() ) );
	assert(s2.capacity() == 50);
}

DECLARE_OOP_TEST(string_test_Copy_Constructor_2) {
	MyString s1{ "Hello World" };
	MyString s2{ 50 };
	s2 = s1;
	assert(!strcmp(s1.c_str(), s2.c_str()));
	assert(s2.capacity() == 50);
};

DECLARE_OOP_TEST(string_test_Copy_Constructor_3) {
	MyString s1{ "Hello World" };
	MyString s2{ 0L };
	s2 = s1;
	assert(!strcmp(s1.c_str(), s2.c_str()));
	assert(s2.capacity() == 16);
};

DECLARE_OOP_TEST(string_test_CapacityTest__Test_Copy_Constructor_4) {
	MyString s1{ "Hello Worldello World123123123" };
	MyString s2= s1;
	assert(!strcmp(s1.c_str(), s2.c_str()));
}

DECLARE_OOP_TEST(string_test_ReserveTest_1) {
	MyString s1;
	s1.reserve(100);
	assert(s1.capacity() == 116);
	assert(s1.empty());
}

DECLARE_OOP_TEST(string_test_ReserveTest_2) {
	MyString s1{ "Hello World" };
	s1.reserve(100);
	assert(s1.capacity() == 116);
	assert(!strcmp(s1.c_str(), "Hello World"));
}

DECLARE_OOP_TEST(string_test_ConcatenationTest_1) {
	MyString s1{ "Hello World" };
	MyString s2{ "abc" };
	s1 += s2;
	assert(!strcmp(s1.c_str(), "Hello Worldabc"));
}

DECLARE_OOP_TEST(string_test_ConcatenationTest_2) {
	MyString s1{ "Hello world Hello world Hello world " };
	MyString s2{ "abc" };
	s1 += s2;
	assert(!strcmp(s1.c_str(), "Hello world Hello world Hello world abc"));
}

DECLARE_OOP_TEST(string_test_ConcatenationTest_3) {
	MyString s1{ "Hello world Hello world Hello world " };
	MyString s2{ "Hello world Hello world Hello world" };
	s1 += s2;
	assert(!strcmp(s1.c_str(), "Hello world Hello world Hello world Hello world Hello world Hello world"));
}

DECLARE_OOP_TEST(string_test_ConcatenationTest_4) {
	MyString s1{ "Hello World" };
	MyString s2 = s1;
	MyString s3 = s1 + s2;
	assert(!strcmp(s3.c_str(), "Hello WorldHello World"));
}

DECLARE_OOP_TEST(string_test_Insert_Test_1) {
	MyString s1{ "Hello World" };
	s1.insert(6, "Hello World ");
	assert(!strcmp(s1.c_str(), "Hello Hello World World"));
}

DECLARE_OOP_TEST(string_test_Insert_Test_2) {
	try
	{
		MyString s("Incorrect position add");
		s.insert(-1, "abort");
		assert(!"Exception must have been thrown");
	}
	catch (std::logic_error &e) {

		assert(!strcmp(e.what(), "Out of range"));
	}
	try
	{
		MyString s("Incorrect position add");
		s.insert(50, "abort");
		assert(!"Exception must have been thrown");
	}
	catch (std::logic_error &e) {

		assert(!strcmp(e.what(), "Out of range"));
	}

}

DECLARE_OOP_TEST(string_test_Insert_Test_3) {
	MyString s1{ "Hello" };
	s1.insert(5, "Hello");
	assert(!strcmp(s1.c_str(), "HelloHello"));
}

DECLARE_OOP_TEST(string_test_Insert_Test_4) {
	MyString s1{ "Hello" };
	s1.insert(0, "Hello");
	assert(!strcmp(s1.c_str(), "HelloHello"));
}
