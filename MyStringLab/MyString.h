#pragma once
#include "MyStringIterator.h"
#include <stdexcept>
#include <string>

class MyString
{
public:
	using Iterator = MyStringIterator;
	using ConstIterator = MyStringConstIterator;
	using ReverseIterator = std::reverse_iterator<MyStringIterator>;
	using ConstReverseIterator = std::reverse_iterator<MyStringConstIterator>;

	MyString();
	MyString(const char* pStr);
	MyString(const char* pStr, size_t length);
	MyString(const MyString& other);
	MyString(MyString&& other) noexcept;
	MyString(const std::string& str);
	~MyString() noexcept;

	MyString& operator=(const MyString& other);
	MyString& operator=(MyString&& other) noexcept;
	MyString& operator+=(const MyString& other);

	friend MyString operator+(const MyString& left, const MyString& right);
	friend bool operator==(const MyString& left, const MyString& right) noexcept;
	friend bool operator!=(const MyString& left, const MyString& right) noexcept;
	friend bool operator<(const MyString& left, const MyString& right) noexcept;
	friend bool operator<=(const MyString& left, const MyString& right) noexcept;
	friend bool operator>(const MyString& left, const MyString& right) noexcept;
	friend bool operator>=(const MyString& left, const MyString& right) noexcept;
	friend std::ostream& operator<<(std::ostream& os, const MyString& myString);
	friend std::istream& operator>>(std::istream& is, MyString& myString);

	const char& operator[](size_t index) const;
	char& operator[](size_t index);

	static int Compare(const MyString& left, const MyString& right) noexcept;
	static void Swap(MyString& left, MyString& right) noexcept;

	size_t GetLength() const noexcept;
	const char* GetStringData() const noexcept;
	MyString SubString(size_t start, size_t length = SIZE_MAX) const;
	void Clear() noexcept;

	Iterator begin() noexcept;
	Iterator end() noexcept;
	ConstIterator begin() const noexcept;
	ConstIterator end() const noexcept;
	ConstIterator cbegin() const noexcept;
	ConstIterator cend() const noexcept;
	ReverseIterator rbegin() noexcept;
	ReverseIterator rend() noexcept;
	ConstReverseIterator rbegin() const noexcept;
	ConstReverseIterator rend() const noexcept;
	ConstReverseIterator crbegin() const noexcept;
	ConstReverseIterator crend() const noexcept;

private:
	void AllocateMemoryAndCopyString(size_t size, const char* source);

	char* m_data{ nullptr };
	size_t m_size{ 0 };
};