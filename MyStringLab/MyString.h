#pragma once
#include <stdexcept>
#include <string>

class MyStringIterator
{
public:
	using iterator_category = std::random_access_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = char;
	using pointer = value_type*;
	using reference = value_type&;

	MyStringIterator(pointer ptr);

	MyStringIterator& operator++();
	MyStringIterator operator++(int);
	MyStringIterator& operator--();
	MyStringIterator operator--(int);
	MyStringIterator& operator+=(int offset);
	reference operator[](int index) const;
	reference operator*() const;
	pointer operator->();
	friend const MyStringIterator operator+(const MyStringIterator& iter, int offset);
	friend const MyStringIterator operator+(int offset, const MyStringIterator& iter);
	friend difference_type operator-(const MyStringIterator& left, const MyStringIterator& right);
	friend bool operator==(const MyStringIterator& left, const MyStringIterator& right);
	friend bool operator!=(const MyStringIterator& left, const MyStringIterator& right);

private:
	pointer m_ptr;
};

class MyStringConstIterator
{
public:
	using iterator_category = std::random_access_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = char;
	using pointer = const value_type*;
	using reference = const value_type&;

	MyStringConstIterator(pointer ptr);

	MyStringConstIterator& operator++();
	MyStringConstIterator operator++(int);
	MyStringConstIterator& operator--();
	MyStringConstIterator operator--(int);
	MyStringConstIterator& operator+=(int offset);
	reference operator[](int index) const;
	reference operator*() const;
	pointer operator->();
	friend const MyStringConstIterator operator+(const MyStringConstIterator& iter, int offset);
	friend const MyStringConstIterator operator+(int offset, const MyStringConstIterator& iter);
	friend difference_type operator-(const MyStringConstIterator& left, const MyStringConstIterator& right);
	friend bool operator==(const MyStringConstIterator& left, const MyStringConstIterator& right);
	friend bool operator!=(const MyStringConstIterator& left, const MyStringConstIterator& right);

protected:
	pointer m_ptr;
};


class MyString
{
public:
	using Iterator = MyStringIterator;
	using ConstIterator = MyStringConstIterator;

	MyString() noexcept;
	MyString(const char* pStr);
	MyString(const char* pStr, size_t length);
	MyString(const MyString& other) noexcept;
	MyString(MyString&& other) noexcept;
	MyString(const std::string& str) noexcept;
	~MyString() noexcept;

	MyString& operator=(const MyString& other) noexcept;
	MyString& operator=(MyString&& other) noexcept;
	MyString& operator+=(const MyString& other) noexcept;

	friend MyString operator+(const MyString& left, const MyString& right) noexcept;
	friend bool operator==(const MyString& left, const MyString& right) noexcept;
	friend bool operator!=(const MyString& left, const MyString& right) noexcept;
	friend bool operator<(const MyString& left, const MyString& right) noexcept;
	friend bool operator<=(const MyString& left, const MyString& right) noexcept;
	friend bool operator>(const MyString& left, const MyString& right) noexcept;
	friend bool operator>=(const MyString& left, const MyString& right) noexcept;
	friend std::ostream& operator<<(std::ostream& os, const MyString& myString) noexcept;
	friend std::istream& operator>>(std::istream& is, MyString& myString) noexcept;

	const char& operator[](size_t index) const;
	char& operator[](size_t index);

	static int Compare(const MyString& left, const MyString& right) noexcept;
	static void Swap(MyString& left, MyString& right) noexcept;

	size_t GetLength() const noexcept;
	const char* GetStringData() const noexcept;
	MyString SubString(size_t start, size_t length = SIZE_MAX) const;
	void Clear() noexcept;

	Iterator begin();
	Iterator end();
	ConstIterator begin() const;
	ConstIterator end() const;
	ConstIterator cbegin() const;
	ConstIterator cend() const;

private:
	void SetEmpty() noexcept;
	void AllocateMemoryAndCopyString(size_t size, const char* source);

	char* m_data{ nullptr };
	size_t m_size{ 0 };
};