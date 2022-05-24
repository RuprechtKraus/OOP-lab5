#include "MyStringIterator.h"
#include <cassert>

#pragma region MyStringConstIterator

MyStringConstIterator::MyStringConstIterator() noexcept
	: m_ptr(nullptr)
	, m_cptr(nullptr)
{
}

MyStringConstIterator::MyStringConstIterator(pointer ptr, const Container* cptr) noexcept
	: m_ptr(ptr)
	, m_cptr(cptr)
{
}

MyStringConstIterator::reference MyStringConstIterator::operator*() const noexcept
{
	_STL_ASSERT(m_ptr >= m_cptr->m_data && m_ptr < (m_cptr->m_data + m_cptr->m_size),
		"Cannot dereference mystring iterator because it's out of range");
	return *m_ptr;
}

MyStringConstIterator::reference MyStringConstIterator::operator[](difference_type index) const noexcept
{
	return *(*this + index);
}

MyStringConstIterator& MyStringConstIterator::operator++() noexcept
{
	_STL_ASSERT(m_ptr < (m_cptr->m_data + m_cptr->m_size), "Cannot increment mystring iterator past end");
	m_ptr++;
	return *this;
}

MyStringConstIterator MyStringConstIterator::operator++(int) noexcept
{
	MyStringConstIterator tmp{ *this };
	++(*this);
	return tmp;
}

MyStringConstIterator& MyStringConstIterator::operator--() noexcept
{
	_STL_ASSERT(m_ptr > m_cptr->m_data, "Cannot decrement mystring iterator before begin");
	m_ptr--;
	return *this;
}

MyStringConstIterator MyStringConstIterator::operator--(int) noexcept
{

	MyStringConstIterator tmp{ *this };
	--(*this);
	return tmp;
}

MyStringConstIterator& MyStringConstIterator::operator+=(difference_type offset) noexcept
{
#if _DEBUG
	VerifyOffset(offset);
#endif // _DEBUG
	m_ptr += offset;
	return *this;
}

MyStringConstIterator& MyStringConstIterator::operator-=(difference_type offset) noexcept
{
	return *this += -offset;
}

MyStringConstIterator::difference_type operator-(const MyStringConstIterator& left, const MyStringConstIterator& right) noexcept
{
	return left.m_ptr - right.m_ptr;
}

const MyStringConstIterator operator+(const MyStringConstIterator& iter,
	MyStringConstIterator::difference_type offset) noexcept
{
	MyStringConstIterator tmp{ iter };
	tmp += offset;
	return tmp;
}
const MyStringConstIterator operator+(MyStringConstIterator::difference_type offset,
	const MyStringConstIterator& iter) noexcept
{
	return iter + offset;
}

const MyStringConstIterator operator-(const MyStringConstIterator& iter,
	MyStringConstIterator::difference_type offset) noexcept
{
	return { iter.m_ptr - offset, iter.m_cptr };
}

const MyStringConstIterator operator-(MyStringConstIterator::difference_type offset,
	const MyStringConstIterator& iter) noexcept
{
	return iter - offset;
}

bool operator==(const MyStringConstIterator& left, const MyStringConstIterator& right) noexcept
{
	return left.m_ptr == right.m_ptr;
}

bool operator!=(const MyStringConstIterator& left, const MyStringConstIterator& right) noexcept
{
	return left.m_ptr != right.m_ptr;
}

bool operator<(const MyStringConstIterator& left, const MyStringConstIterator& right) noexcept
{
	return left.m_ptr < right.m_ptr;
}

bool operator>(const MyStringConstIterator& left, const MyStringConstIterator& right) noexcept
{
	return right.m_ptr < left.m_ptr;
}

bool operator<=(const MyStringConstIterator& left, const MyStringConstIterator& right) noexcept
{
	return !(right.m_ptr < left.m_ptr);
}

bool operator>=(const MyStringConstIterator& left, const MyStringConstIterator& right) noexcept
{
	return !(left.m_ptr < right.m_ptr);
}

void MyStringConstIterator::VerifyOffset(difference_type offset) const noexcept
{
#if _DEBUG
	if (offset == 0)
	{
		return;
	}

	if (offset < 0)
	{
		_STL_ASSERT(m_cptr->m_data - m_ptr <= offset, "Cannot seek mystring iterator before begin");
	}

	_STL_ASSERT((m_cptr->m_data + m_cptr->m_size) - m_ptr >= offset, "Cannot seek mystring iterator after end");
#endif // _DEBUG
}

#pragma endregion MyStringConstIterator

#pragma region MyStringIterator

MyStringIterator::MyStringIterator()
	: MyStringConstIterator(nullptr, nullptr)
{
}

MyStringIterator::MyStringIterator(pointer ptr, const Container* cptr) noexcept
	: MyStringConstIterator(ptr, cptr)
{
}

MyStringIterator::reference MyStringIterator::operator*() const noexcept
{
	return const_cast<reference>(MyBase::operator*());
}

MyStringIterator::reference MyStringIterator::operator[](difference_type index) const noexcept
{
	return const_cast<reference>(MyBase::operator[](index));
}

MyStringIterator& MyStringIterator::operator++() noexcept
{
	MyBase::operator++();
	return *this;
}

MyStringIterator MyStringIterator::operator++(int) noexcept
{
	MyStringIterator tmp{ *this };
	MyBase::operator++();
	return tmp;
}

MyStringIterator& MyStringIterator::operator--() noexcept
{
	MyBase::operator--();
	return *this;
}

MyStringIterator MyStringIterator::operator--(int) noexcept
{

	MyStringIterator tmp{ *this };
	MyBase::operator--();
	return tmp;
}

MyStringIterator& MyStringIterator::operator+=(difference_type offset) noexcept
{
	MyBase::operator+=(offset);
	return *this;
}

MyStringIterator& MyStringIterator::operator-=(difference_type offset) noexcept
{
	MyBase::operator-=(offset);
	return *this;
}

const MyStringIterator operator+(const MyStringIterator& iter, MyStringIterator::difference_type offset) noexcept
{
	MyStringIterator tmp{ iter };
	tmp += offset;
	return tmp;
}

const MyStringIterator operator+(MyStringIterator::difference_type offset, const MyStringIterator& iter) noexcept
{
	return iter + offset;
}

const MyStringIterator operator-(const MyStringIterator& iter, MyStringIterator::difference_type offset) noexcept
{
	MyStringIterator tmp{ iter };
	tmp -= offset;
	return tmp;
}

const MyStringIterator operator-(MyStringIterator::difference_type offset, const MyStringIterator& iter) noexcept
{
	return iter - offset;
}

#pragma endregion MyStringIterator