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

	m_size = strlen(pStr);

	if (m_size == 0)
	{
		SetEmpty();
	}
	else
	{
		m_data = new char[m_size + 1];
		memcpy(m_data, pStr, m_size);
		m_data[m_size] = '\0';
	}
}

MyString::MyString(const char* pStr, size_t length)
{
	if (!pStr)
	{
		throw std::invalid_argument("Null pointer");
	}

	m_size = length;

	m_data = new char[m_size + 1];
	memcpy(m_data, pStr, m_size);
	m_data[m_size] = '\0';
}

MyString::MyString(const MyString& other) noexcept
{
	m_size = other.m_size;
	
	m_data = new char[m_size + 1];
	memcpy(m_data, other.m_data, m_size);
	m_data[m_size] = '\0';
}

MyString::MyString(MyString&& other) noexcept
{
	m_data = other.m_data;
	m_size = other.m_size;

	other.m_data = nullptr;
	other.m_size = 0;
}

MyString::MyString(const std::string& str) noexcept
{
	m_size = str.size();
	
	m_data = new char[m_size + 1];
	memcpy(m_data, str.c_str(), m_size);
	m_data[m_size] = '\0';
}

MyString::~MyString() noexcept
{
	delete m_data;
}

size_t MyString::GetLength() const noexcept
{
	return m_size;
}

const char* MyString::GetStringData() const noexcept
{
	return m_data;
}

MyString MyString::SubString(size_t start, size_t length) const
{
	return MyString();
}

void MyString::Clear() noexcept
{
	delete m_data;
	SetEmpty();
}

void MyString::SetEmpty() noexcept
{
	m_size = 0;
	m_data = new char[1];
	m_data[0] = '\0';
}