#include "MyStringIterator.h"

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

const MyStringIterator operator+(const MyStringIterator& iter, int offset)
{
	return { iter.m_ptr + offset };
}

// TODO: использовать ptrdiff_t ибо смещ. может быть отриц.
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