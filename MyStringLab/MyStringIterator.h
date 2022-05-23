#pragma once
#include <iterator>

class MyStringIterator
{
public:
	using iterator_category = std::random_access_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = char;
	using pointer = value_type*;
	using reference = value_type&;

	MyStringIterator(pointer ptr); // TODO: �������� ����������� �� ���������

	MyStringIterator& operator++();
	MyStringIterator operator++(int);
	MyStringIterator& operator--();
	MyStringIterator operator--(int);
	MyStringIterator& operator+=(int offset);
	reference operator[](int index) const;
	reference operator*() const;
	friend const MyStringIterator operator+(const MyStringIterator& iter, int offset);
	friend const MyStringIterator operator+(int offset, const MyStringIterator& iter);
	friend difference_type operator-(const MyStringIterator& left, const MyStringIterator& right);
	friend bool operator==(const MyStringIterator& left, const MyStringIterator& right);
	friend bool operator!=(const MyStringIterator& left, const MyStringIterator& right);

private:
	pointer m_ptr;
};

// TODO: ���������� �� ������������ ����. 1: ������������. 2: ������������ �������
class MyStringConstIterator
{
public:
	using iterator_category = std::random_access_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = char;
	using pointer = const value_type*;
	using reference = const value_type&;

	MyStringConstIterator(pointer ptr); // TODO: �������� ����������� �� ���������

	MyStringConstIterator& operator++();
	MyStringConstIterator operator++(int);
	MyStringConstIterator& operator--();
	MyStringConstIterator operator--(int);
	MyStringConstIterator& operator+=(int offset);
	reference operator[](int index) const;
	reference operator*() const;
	// TODO: ��������� ������������� ������� ������ ����� ��������� ���������
	friend const MyStringConstIterator operator+(const MyStringConstIterator& iter, int offset); // TODO: ������������ ptrdiff_t ��� ����. ����� ���� �����.
	friend const MyStringConstIterator operator+(int offset, const MyStringConstIterator& iter);
	friend difference_type operator-(const MyStringConstIterator& left, const MyStringConstIterator& right);
	friend bool operator==(const MyStringConstIterator& left, const MyStringConstIterator& right);
	friend bool operator!=(const MyStringConstIterator& left, const MyStringConstIterator& right);

protected:
	pointer m_ptr;
};