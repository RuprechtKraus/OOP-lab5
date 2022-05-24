#pragma once
#include "MyString.h"
#include <iterator>

class MyString;

class MyStringConstIterator
{
	friend class MyString;

public:
	using iterator_category = std::random_access_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = char;
	using pointer = const value_type*;
	using reference = const value_type&;
	using Container = MyString;

	MyStringConstIterator() noexcept;

	reference operator*() const noexcept;
	reference operator[](difference_type index) const noexcept;

	MyStringConstIterator& operator++() noexcept;
	MyStringConstIterator operator++(int) noexcept;
	MyStringConstIterator& operator--() noexcept;
	MyStringConstIterator operator--(int) noexcept;
	MyStringConstIterator& operator+=(difference_type offset) noexcept;
	MyStringConstIterator& operator-=(difference_type offset) noexcept;

	friend difference_type operator-(const MyStringConstIterator& left, const MyStringConstIterator& right) noexcept;
	friend const MyStringConstIterator operator+(const MyStringConstIterator& iter, difference_type offset) noexcept;
	friend const MyStringConstIterator operator+(difference_type offset, const MyStringConstIterator& iter) noexcept;
	friend const MyStringConstIterator operator-(const MyStringConstIterator& iter, difference_type offset) noexcept;
	friend const MyStringConstIterator operator-(difference_type offset, const MyStringConstIterator& iter) noexcept;
	friend bool operator==(const MyStringConstIterator& left, const MyStringConstIterator& right) noexcept;
	friend bool operator!=(const MyStringConstIterator& left, const MyStringConstIterator& right) noexcept;
	friend bool operator<(const MyStringConstIterator& left, const MyStringConstIterator& right) noexcept;
	friend bool operator>(const MyStringConstIterator& left, const MyStringConstIterator& right) noexcept;
	friend bool operator<=(const MyStringConstIterator& left, const MyStringConstIterator& right) noexcept;
	friend bool operator>=(const MyStringConstIterator& left, const MyStringConstIterator& right) noexcept;

protected:
	MyStringConstIterator(pointer ptr, const Container* cptr) noexcept;
	void VerifyOffset(difference_type offset) const noexcept;

	pointer m_ptr;
	const Container* m_cptr;
};

class MyStringIterator : public MyStringConstIterator
{
	friend class MyString;

public:
	using iterator_category = std::random_access_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = char;
	using pointer = value_type*;
	using reference = value_type&;
	using ContainerPointer = MyString*;
	using MyBase = MyStringConstIterator;

	MyStringIterator();

	reference operator*() const noexcept;
	reference operator[](difference_type index) const noexcept;

	MyStringIterator& operator++() noexcept;
	MyStringIterator operator++(int) noexcept;
	MyStringIterator& operator--() noexcept;
	MyStringIterator operator--(int) noexcept;
	MyStringIterator& operator+=(difference_type offset) noexcept;
	MyStringIterator& operator-=(difference_type offset) noexcept;

	friend const MyStringIterator operator+(const MyStringIterator& iter, difference_type offset) noexcept;
	friend const MyStringIterator operator+(difference_type offset, const MyStringIterator& iter) noexcept;
	friend const MyStringIterator operator-(const MyStringIterator& iter, difference_type offset) noexcept;
	friend const MyStringIterator operator-(difference_type offset, const MyStringIterator& iter) noexcept;

private:
	MyStringIterator(pointer ptr, const Container* cptr) noexcept;
};