#include "MyString.h"
#include <iostream>
#include <stdexcept>

MyString::MyString() noexcept
{
	SetEmpty();
}

MyString::MyString(const char* pStr)
{
	if (!pStr)
	{
		throw std::invalid_argument("Null pointer");
	}

	size_t len = strlen(pStr);

	if (len == 0)
	{
		SetEmpty();
	}
	else
	{
		AllocateMemoryAndCopyString(len, pStr);
	}
}

MyString::MyString(const char* pStr, size_t length)
{
	if (!pStr)
	{
		throw std::invalid_argument("Null pointer");
	}

	AllocateMemoryAndCopyString(length, pStr);
}

MyString::MyString(const MyString& other) noexcept
{
	AllocateMemoryAndCopyString(other.m_size, other.m_data);
}

MyString::MyString(MyString&& other) noexcept
{
	MyString::Swap(*this, other);
}

MyString::MyString(const std::string& str) noexcept
{

	AllocateMemoryAndCopyString(str.size(), str.c_str());
}

MyString& MyString::operator=(const MyString& other) noexcept
{
	if (this != &other)
	{
		MyString tmp(other);
		MyString::Swap(*this, tmp);
	}

	return *this;
}

MyString& MyString::operator=(MyString&& other) noexcept
{
	if (this != &other)
	{
		MyString::Swap(*this, other);
	}

	return *this;
}

MyString& MyString::operator+=(const MyString& other) noexcept
{
	*this = *this + other;
	return *this;
}

MyString::~MyString() noexcept
{
	delete[] m_data;
}

MyString operator+(const MyString& left, const MyString& right) noexcept
{
	size_t size{ left.m_size + right.m_size };
	char* buff = new char[size + 1];

	memcpy(buff, left.m_data, left.m_size);
	memcpy(buff + left.m_size, right.m_data, right.m_size);
	buff[size] = '\0';

	MyString tmp(buff);
	delete[] buff;

	return tmp;
}

bool operator==(const MyString& left, const MyString& right) noexcept
{
	return MyString::Compare(left, right) == 0;
}

bool operator!=(const MyString& left, const MyString& right) noexcept
{
	return !(left == right);
}

bool operator<(const MyString& left, const MyString& right) noexcept
{
	return MyString::Compare(left, right) == -1;
}

bool operator<=(const MyString& left, const MyString& right) noexcept
{
	return left < right || left == right;
}

bool operator>(const MyString& left, const MyString& right) noexcept
{
	return MyString::Compare(left, right) == 1;
}

bool operator>=(const MyString& left, const MyString& right) noexcept
{
	return left > right || left == right;
}

std::ostream& operator<<(std::ostream& os, const MyString& myString) noexcept
{
	return os.write(myString.m_data, myString.m_size);
}

std::istream& operator>>(std::istream& is, MyString& myString) noexcept
{
	int capacity{ 10 };
	char* buff = new char[capacity];
	char ch{};
	int len{};

	while ((ch = is.get()) != ' ' && is)
	{
		if (len == capacity)
		{
			char* tmp = new char[capacity];
			memcpy(tmp, buff, len);
			capacity *= 2;
			delete[] buff;

			buff = new char[capacity];
			memcpy(buff, tmp, len);
			delete[] tmp;
		}

		buff[len++] = ch;
	}

	MyString tmp(buff, len);
	MyString::Swap(myString, tmp);

	is.clear();
	delete[] buff;

	return is;
}

const char& MyString::operator[](size_t index) const
{
	if (index >= m_size)
	{
		throw std::out_of_range("Subscript is out of bounds");
	}

	return m_data[index];
}

char& MyString::operator[](size_t index)
{
	if (index >= m_size)
	{
		throw std::out_of_range("Subscript is out of bounds");
	}

	return m_data[index];
}

size_t MyString::GetLength() const noexcept
{
	return m_size;
}

const char* MyString::GetStringData() const noexcept
{
	return m_data ? m_data : "";
}

MyString MyString::SubString(size_t start, size_t length) const
{
	return MyString();
}

void MyString::Clear() noexcept
{
	delete[] m_data;
	SetEmpty();
}

void MyString::SetEmpty() noexcept
{
	m_size = 0;
	m_data = new char[1];
	m_data[0] = '\0';
}

void MyString::AllocateMemoryAndCopyString(size_t size, const char* source)
{
	m_size = size;
	m_data = new char[size + 1];
	memcpy(m_data, source, size);
	m_data[size] = '\0';
}

int MyString::Compare(const MyString& left, const MyString& right) noexcept
{
	if (left.m_size < right.m_size)
	{
		return -1;
	}

	if (left.m_size > right.m_size)
	{
		return 1;
	}

	return memcmp(left.m_data, right.m_data, left.m_size);
}

void MyString::Swap(MyString& left, MyString& right) noexcept
{
	std::swap(left.m_size, right.m_size);
	std::swap(left.m_data, right.m_data);
}