#pragma once
#include <string>
#include <stdexcept>

class MyString
{
public:
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

	size_t GetLength() const noexcept;
	const char* GetStringData() const noexcept;
	MyString SubString(size_t start, size_t length = SIZE_MAX) const;
	void Clear() noexcept;

	static int Compare(const MyString& left, const MyString& right) noexcept;
	static void Swap(MyString& left, MyString& right) noexcept;

private:
	void SetEmpty() noexcept;
	void AllocateMemoryAndCopyString(size_t size, const char* source);

	char* m_data{ nullptr };
	size_t m_size{ 0 };
};