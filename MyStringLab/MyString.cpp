#include "MyString.h"
#include <cassert>
#include <iostream>
#include <stdexcept>

#pragma region MyString

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

MyString::Iterator MyString::begin()
{
	return Iterator(m_data);
}

MyString::Iterator MyString::end()
{
	return Iterator(m_data + m_size);
}

MyString::ConstIterator MyString::begin() const
{
	return ConstIterator(m_data);
}

MyString::ConstIterator MyString::end() const
{
	return ConstIterator(m_data + m_size);
}

MyString::ConstIterator MyString::cbegin() const
{
	return begin();
}

MyString::ConstIterator MyString::cend() const
{
	return end();
}

#pragma endregion MyString

#pragma region MyStringIterator

MyStringIterator::MyStringIterator(pointer ptr)
	: m_ptr(ptr)
{
}

MyStringIterator& MyStringIterator::operator++()
{
	m_ptr++;
	return *this;
}

MyStringIterator MyStringIterator::operator++(int)
{
	MyStringIterator tmp{ *this };
	++(*this);
	return tmp;
}

MyStringIterator& MyStringIterator::operator--()
{
	m_ptr--;
	return *this;
}

MyStringIterator MyStringIterator::operator--(int)
{

	MyStringIterator tmp{ *this };
	--(*this);
	return tmp;
}

MyStringIterator& MyStringIterator::operator+=(int offset)
{
	*this = *this + offset;
	return *this;
}

MyStringIterator::reference MyStringIterator::operator[](int index) const
{
	return *(m_ptr + index);
}

MyStringIterator::reference MyStringIterator::operator*() const
{
	return *m_ptr;
}

MyStringIterator::pointer MyStringIterator::operator->()
{
	return m_ptr;
}

const MyStringIterator operator+(const MyStringIterator& iter, int offset)
{
	return { iter.m_ptr + offset };
}

const MyStringIterator operator+(int offset, const MyStringIterator& iter)
{
	return iter + offset;
}

MyStringIterator::difference_type operator-(const MyStringIterator& left, const MyStringIterator& right)
{
	return left.m_ptr - right.m_ptr;
}

bool operator==(const MyStringIterator& left, const MyStringIterator& right)
{
	return left.m_ptr == right.m_ptr;
}

bool operator!=(const MyStringIterator& left, const MyStringIterator& right)
{
	return left.m_ptr != right.m_ptr;
}

#pragma endregion MyStringIterator

#pragma region MyStringConstIterator

MyStringConstIterator::MyStringConstIterator(pointer ptr)
	: m_ptr(ptr)
{
}

MyStringConstIterator& MyStringConstIterator::operator++()
{
	m_ptr++;
	return *this;
}

MyStringConstIterator MyStringConstIterator::operator++(int)
{
	MyStringConstIterator tmp{ *this };
	++(*this);
	return tmp;
}

MyStringConstIterator& MyStringConstIterator::operator--()
{
	m_ptr--;
	return *this;
}

MyStringConstIterator MyStringConstIterator::operator--(int)
{

	MyStringConstIterator tmp{ *this };
	--(*this);
	return tmp;
}

MyStringConstIterator& MyStringConstIterator::operator+=(int offset)
{
	*this = *this + offset;
	return *this;
}

MyStringConstIterator::reference MyStringConstIterator::operator[](int index) const
{
	return *(m_ptr + index);
}

MyStringConstIterator::reference MyStringConstIterator::operator*() const
{
	return *m_ptr;
}

MyStringConstIterator::pointer MyStringConstIterator::operator->()
{
	return m_ptr;
}

const MyStringConstIterator operator+(const MyStringConstIterator& iter, int offset)
{
	return { iter.m_ptr + offset };
}

const MyStringConstIterator operator+(int offset, const MyStringConstIterator& iter)
{
	return iter + offset;
}

MyStringConstIterator::difference_type operator-(const MyStringConstIterator& left, const MyStringConstIterator& right)
{
	return left.m_ptr - right.m_ptr;
}

bool operator==(const MyStringConstIterator& left, const MyStringConstIterator& right)
{
	return left.m_ptr == right.m_ptr;
}

bool operator!=(const MyStringConstIterator& left, const MyStringConstIterator& right)
{
	return left.m_ptr != right.m_ptr;
}

#pragma endregion MyStringConstIterator