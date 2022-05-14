#pragma once
#include <string>

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

	size_t GetLength() const noexcept;
	const char* GetStringData() const noexcept;
	MyString SubString(size_t start, size_t length = SIZE_MAX) const;
	void Clear() noexcept;

private:
	void SetEmpty() noexcept;

	char* m_data;
	size_t m_size;
};