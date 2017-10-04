#include "string.hpp"
#include "testlib.hpp"


DECLARE_OOP_TEST(string_test_create_string_1) {
	MyString s1;
	assert(s1.empty());
}

DECLARE_OOP_TEST(string_test_create_string_3) {
	MyString s1{ 0L };
	assert(s1.capacity() == 15);
}

DECLARE_OOP_TEST(string_test_create_string_4) {
	MyString s1{ "Hello World" };
	assert(s1.capacity() == 15);
	assert(!strcmp(s1.c_str(), "Hello World"));
}

DECLARE_OOP_TEST(string_test_create_string_5) {
	MyString s1{ "Hello World Hello World" };
	assert(s1.capacity() == 23);
	assert(!strcmp(s1.c_str(), "Hello World Hello World"));
}

DECLARE_OOP_TEST(string_test_exeption_Incorrect_size) {
	try
	{
		MyString s(-1);
		assert(!"Exception must have been thrown");
	}
	catch (std::exception &e) {

		assert(!strcmp(e.what(), "Incorrect size"));
	}

}

DECLARE_OOP_TEST(string_test_copy_constructor_1) {
	MyString s1{ "Hello World123123123" };
	MyString s2{ 50 };
	s2 = s1;
	assert(!strcmp(s1.c_str(), s2.c_str()));
	assert(s2.capacity() == 50);
}

DECLARE_OOP_TEST(string_test_copy_constructor_2) {
	MyString s1{ "Hello World" };
	MyString s2{ 50 };
	s2 = s1;
	assert(!strcmp(s1.c_str(), s2.c_str()));
	assert(s2.capacity() == 50);
};

DECLARE_OOP_TEST(string_test_copy_constructor_3) {
	MyString s1{ "Hello World" };
	MyString s2{ 0L };
	s2 = s1;
	assert(!strcmp(s1.c_str(), s2.c_str()));
	assert(s2.capacity() == 15);
};

DECLARE_OOP_TEST(string_test_copy_constructor_4) {
	MyString s1{ "Hello Worldello World123123123" };
	MyString s2 = s1;
	assert(!strcmp(s1.c_str(), s2.c_str()));
}

DECLARE_OOP_TEST(string_test_reserve_test_1) {
	MyString s1;
	s1.reserve(100);
	assert(s1.capacity() == 115);
	assert(s1.empty());
}

DECLARE_OOP_TEST(string_test_reserve_test_2) {
	MyString s1{ "Hello World" };
	s1.reserve(100);
	assert(s1.capacity() == 115);
	assert(!strcmp(s1.c_str(), "Hello World"));
}

DECLARE_OOP_TEST(string_test_concatenation_test_1) {
	MyString s1{ "Hello World" };
	MyString s2{ "abc" };
	s1 += s2;
	assert(!strcmp(s1.c_str(), "Hello Worldabc"));
}

DECLARE_OOP_TEST(string_test_concatenation_test_2) {
	MyString s1{ "Hello world Hello world Hello world " };
	MyString s2{ "abc" };
	s1 += s2;
	assert(!strcmp(s1.c_str(), "Hello world Hello world Hello world abc"));
}

DECLARE_OOP_TEST(string_test_concatenation_test_3) {
	MyString s1{ "Hello world Hello world Hello world " };
	MyString s2{ "Hello world Hello world Hello world" };
	s1 += s2;
	assert(!strcmp(s1.c_str(), "Hello world Hello world Hello world Hello world Hello world Hello world"));
}

DECLARE_OOP_TEST(string_test_concatenation_test_4) {
	MyString s1{ "Hello World" };
	MyString s2 = s1;
	MyString s3 = s1 + s2;
	assert(!strcmp(s3.c_str(), "Hello WorldHello World"));
}

DECLARE_OOP_TEST(string_test_insert_test_1) {
	MyString s1{ "Hello World" };
	s1.insert(6, "Hello World ");
	assert(!strcmp(s1.c_str(), "Hello Hello World World"));
}

DECLARE_OOP_TEST(string_test_insert_test_2) {
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

DECLARE_OOP_TEST(string_test_insert_test_3) {
	MyString s1{ "Hello" };
	s1.insert(5, "Hello");
	assert(!strcmp(s1.c_str(), "HelloHello"));
}

DECLARE_OOP_TEST(string_test_insert_test_4) {
	MyString s1{ "Hello" };
	s1.insert(0, "Hello");
	assert(!strcmp(s1.c_str(), "HelloHello"));
}

DECLARE_OOP_TEST(string_test_erase_test_1) {
	MyString s1{ "Hello World" };
	s1.erase(3, 5);
	assert(!strcmp(s1.c_str(), "Helrld"));
}

DECLARE_OOP_TEST(string_test_erase_test_2) {
	MyString s1{ "Hello World" };
	try
	{
		s1.erase(20, 2);
		assert(!"Exception must have been thrown");
	}
	catch (std::logic_error &e) {

		assert(!strcmp(e.what(), "Out of range"));
	}
}

DECLARE_OOP_TEST(string_test_substring_1) {
	MyString s1{ "Hello World" };
	try
	{
		MyString s2 = s1.substring(20, 2);
		assert(!"Exception must have been thrown");
	}
	catch (std::logic_error &e) {

		assert(!strcmp(e.what(), "Out of range"));
	}
}

DECLARE_OOP_TEST(string_test_substring_2) {
	MyString s1{ "Hello World" };
	MyString s2 = s1.substring(0, 5);
	assert(!strcmp(s2.c_str(), "Hello"));
}

DECLARE_OOP_TEST(string_test_substring_3) {
	MyString s1{ "Hello World" };
	MyString s2 = s1.substring(0, -1);
	assert(!strcmp(s2.c_str(), "Hello World"));
}

DECLARE_OOP_TEST(string_test_operator_index_acess_read_write_1) {
	MyString s1{ "TEST ACCESS TO" };
	char * testChar = "TEST ACCESS TO";

	for (long i = 0L; i < s1.length(); i++) {
		assert(s1[i] == testChar[i]);
	}
}

DECLARE_OOP_TEST(string_test_operator_index_acess_read_write_2) {
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

DECLARE_OOP_TEST(string_test_operator_index_acess_read_write_3) {
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

DECLARE_OOP_TEST(string_test_clear) {
	MyString s1{ "Hello World" };
	s1.clear();
	assert(s1.empty());
}

DECLARE_OOP_TEST(string_test_move_assigment_operator) {
	MyString s1 = MyString{ "Helloworld" };

}