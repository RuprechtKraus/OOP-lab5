#include "MyString.h"
#include <iostream>
#include <stdexcept>

#pragma region MyString

MyString::MyString()
{
}

MyString::MyString(const char* pStr)
{
	if (!pStr)
	{
		throw std::invalid_argument("Null pointer");
	}

	size_t len = strlen(pStr);
	AllocateMemoryAndCopyString(len, pStr);
}

MyString::MyString(const char* pStr, size_t length)
{
	if (!pStr)
	{
		throw std::invalid_argument("Null pointer");
	}

	AllocateMemoryAndCopyString(length, pStr);
}

MyString::MyString(const MyString& other)
{
	AllocateMemoryAndCopyString(other.m_size, other.GetStringData());
}

MyString::MyString(MyString&& other) noexcept
{
	MyString::Swap(*this, other);
}

MyString::MyString(const std::string& str)
{
	AllocateMemoryAndCopyString(str.size(), str.c_str());
}

MyString::MyString(char** pStr)
{
	// Имеет ли смысл выбрасывать это исключение для такого специфичного конструктора?
	if (!(pStr && *pStr))
	{
		throw std::invalid_argument("Null pointer");	
	}

	std::swap(m_data, *pStr);
	m_size = strlen(m_data);
}

MyString& MyString::operator=(const MyString& other)
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

MyString& MyString::operator+=(const MyString& other)
{
	*this = *this + other;
	return *this;
}

MyString::~MyString() noexcept
{
	delete[] m_data;
}

MyString operator+(const MyString& left, const MyString& right)
{
	size_t size{ left.m_size + right.m_size };
	char* buff = new char[size + 1];

	memcpy(buff, left.GetStringData(), left.m_size);
	memcpy(buff + left.m_size, right.GetStringData(), right.m_size);
	buff[size] = '\0';

	MyString tmp(&buff);
	return tmp;
}

bool operator==(const MyString& left, const MyString& right) noexcept
{
	return left.m_size == right.m_size && MyString::Compare(left, right) == 0;
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
	int res{ MyString::Compare(left, right) };
	return res == -1 || res == 0;
}

bool operator>(const MyString& left, const MyString& right) noexcept
{
	return MyString::Compare(left, right) == 1;
}

bool operator>=(const MyString& left, const MyString& right) noexcept
{
	int res{ MyString::Compare(left, right) };
	return res == 1 || res == 0;
}

std::ostream& operator<<(std::ostream& os, const MyString& myString)
{
	return os.write(myString.GetStringData(), myString.m_size);
}

std::istream& operator>>(std::istream& is, MyString& myString)
{
	int capacity{ 10 };
	char* buff = new char[capacity];
	char ch{};
	int len{};

	while ((ch = is.get()) != ' ' && is)
	{
		if (len == capacity)
		{
			char* tmp{};

			try
			{
				tmp = new char[capacity];
				memcpy(tmp, buff, len);
				capacity *= 2;
				delete[] buff;

				buff = new char[capacity];
				memcpy(buff, tmp, len);
				delete[] tmp;
			}
			catch (const std::bad_alloc&)
			{
				delete[] tmp;
				throw;
			}
		}

		buff[len++] = ch;
	}

	try
	{
		MyString tmp(buff, len);
		MyString::Swap(myString, tmp);
	}
	catch (const std::bad_alloc&)
	{
		delete[] buff;
		throw;
	}

	is.clear();
	delete[] buff;
	return is;
}

const char& MyString::operator[](size_t index) const
{
	_STL_ASSERT(index <= m_size, "Mystring subscript out of range");
	return m_data[index];
}

char& MyString::operator[](size_t index)
{
	_STL_ASSERT(index <= m_size, "Mystring subscript out of range");
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
	if (m_size == 0)
	{
		return "";
	}

	if (start >= m_size)
	{
		throw std::out_of_range("Start position is out of bounds");
	}

	if (start + length > m_size)
	{
		length = m_size - start;
	}

	const char* dataPtr{ GetStringData() + start };
	size_t buffSize{ strlen(dataPtr) };
	char* buff = new char[buffSize + 1];

	strncpy_s(buff, buffSize + 1, dataPtr, length);
	buff[buffSize] = '\0';

	MyString substr(&buff);

	return substr;
}

void MyString::Clear() noexcept
{
	delete[] m_data;
	m_data = nullptr;
	m_size = 0;
}

void MyString::AllocateMemoryAndCopyString(size_t size, const char* source)
{
	m_data = new char[size + 1];
	m_size = size;
	memcpy(m_data, source, size);
	m_data[size] = '\0';
}

int MyString::Compare(const MyString& left, const MyString& right) noexcept
{
	size_t minLen{ std::min(left.m_size, right.m_size) };
	int res{ memcmp(left.GetStringData(), right.GetStringData(), minLen) };

	if (res == 0)
	{
		if (left.m_size < right.m_size)
		{
			return -1;
		}
		
		if (left.m_size > right.m_size)
		{
			return 1;
		}

		return 0;
	}

	return res;
}

void MyString::Swap(MyString& left, MyString& right) noexcept
{
	std::swap(left.m_size, right.m_size);
	std::swap(left.m_data, right.m_data);
}

MyString::Iterator MyString::begin() noexcept
{
	return Iterator(m_data, this);
}

MyString::Iterator MyString::end() noexcept
{
	return Iterator(m_data + m_size, this);
}

MyString::ConstIterator MyString::begin() const noexcept
{
	return ConstIterator(m_data, this);
}	

MyString::ConstIterator MyString::end() const noexcept
{
	return ConstIterator(m_data + m_size, this);
}

MyString::ConstIterator MyString::cbegin() const noexcept
{
	return begin();
}

MyString::ConstIterator MyString::cend() const noexcept
{
	return end();
}

MyString::ReverseIterator MyString::rbegin() noexcept
{
	return ReverseIterator(end());
}

MyString::ReverseIterator MyString::rend() noexcept
{
	return ReverseIterator(begin());
}

MyString::ConstReverseIterator MyString::rbegin() const noexcept
{
	return ConstReverseIterator(end());
}

MyString::ConstReverseIterator MyString::rend() const noexcept
{
	return ConstReverseIterator(begin());
}

MyString::ConstReverseIterator MyString::crbegin() const noexcept
{
	return rbegin();
}

MyString::ConstReverseIterator MyString::crend() const noexcept
{
	return rend();
}

#pragma endregion MyString