#include "linked_list.hpp"

#include <sstream>

namespace stdlib
{

LinkedList::LinkedList(const std::initializer_list<long>& vals)
{
	for (const auto& val : vals)
	{
		this->PushBack(val);
	}
}

LinkedList::LinkedList(const LinkedList& other)
{
	auto currNode = other.m_head;
	while (currNode != nullptr)
	{
		this->PushBack(currNode->value);
		currNode = currNode->next;
	}
}

LinkedList& LinkedList::operator =(const LinkedList& other)
{
	LinkedList newThis{ other };
	std::swap(*this, newThis);

	return *this;
}

LinkedList::LinkedList(LinkedList&& other) noexcept
	: m_size{ other.m_size }, m_head{ other.m_head }, m_tail{ other.m_tail }
{
	other.m_size = 0;
	other.m_head = other.m_tail = nullptr;
}

LinkedList& LinkedList::operator =(LinkedList&& other) noexcept
{
	this->m_size = other.m_size;
	this->m_head = other.m_head;
	this->m_tail = other.m_tail;

	other.m_size = 0;
	other.m_head = other.m_tail = nullptr;

	return *this;
}

bool LinkedList::operator ==(const LinkedList& other) const
{
	if (this->m_size != other.m_size)
	{
		return false;
	}

	auto thisCurrNode{ this->m_head };
	auto otherCurrNode{ other.m_head };
	while (thisCurrNode != nullptr && otherCurrNode != nullptr)
	{
		if (thisCurrNode->value != otherCurrNode->value)
		{
			return false;
		}

		thisCurrNode = thisCurrNode->next;
		otherCurrNode = otherCurrNode->next;
	}

	return true;
}

bool LinkedList::operator !=(const LinkedList& other) const
{
	return !(*this == other);
}

void LinkedList::PushFront(const long& val)
{
	if (this->m_head == nullptr || this->m_tail == nullptr)
	{
		this->m_head = this->m_tail = std::make_shared<ListNode>(val, nullptr, nullptr);
	}
	else
	{
		this->m_head->prev = std::make_shared<ListNode>(val, nullptr, this->m_head);
		this->m_head->prev->next = this->m_head;
		this->m_head = this->m_head->prev;
	}

	this->m_size++;
}

void LinkedList::PushBack(const long& val)
{
	if (this->m_head == nullptr || this->m_tail == nullptr)
	{
		this->m_head = this->m_tail = std::make_shared<ListNode>(val, nullptr, nullptr);
	}
	else
	{
		this->m_tail->next = std::make_shared<ListNode>(val, this->m_tail, nullptr);
		this->m_tail->next->prev = this->m_tail;
		this->m_tail = this->m_tail->next;
	}

	this->m_size++;
}

long& LinkedList::Front()
{
	if (this->IsEmpty())
	{
		throw std::runtime_error{ "List is empty" };
	}

	return this->m_head->value;
}

const long& LinkedList::Front() const
{
	if (this->IsEmpty())
	{
		throw std::runtime_error{ "List is empty" };
	}

	return this->m_head->value;
}

long& LinkedList::Back()
{
	if (this->IsEmpty())
	{
		throw std::runtime_error{ "List is empty" };
	}

	return this->m_tail->value;
}

const long& LinkedList::Back() const
{
	if (this->IsEmpty())
	{
		throw std::runtime_error{ "List is empty" };
	}

	return this->m_tail->value;
}

void LinkedList::PopFront()
{
	if (this->IsEmpty())
	{
		throw std::runtime_error{ "List is empty" };
	}

	this->m_head = this->m_head->next;
	if (this->m_head != nullptr)
	{
		this->m_head->prev = nullptr;
	}

	this->m_size--;

	if (this->IsEmpty())
	{
		this->m_tail = nullptr;
	}
}

void LinkedList::PopBack()
{
	if (this->IsEmpty())
	{
		throw std::runtime_error{ "List is empty" };
	}

	this->m_tail = this->m_tail->prev;
	if (this->m_tail != nullptr)
	{
		this->m_tail->next = nullptr;
	}

	this->m_size--;

	if (this->IsEmpty())
	{
		this->m_head = nullptr;
	}
}

std::size_t LinkedList::Size() const
{
	return this->m_size;
}

bool LinkedList::IsEmpty() const
{
	return this->m_size == 0;
}

LinkedList::operator std::string()
{
	return (std::stringstream{} << *this).str();
}

LinkedList::~LinkedList()
{
	while (!this->IsEmpty())
	{
		this->PopFront();
	}
}

std::ostream& operator <<(std::ostream& os, const LinkedList& list)
{
	auto currNode{ list.m_head };
	while (currNode != nullptr)
	{
		os << currNode->value;
		if (currNode->next != nullptr)
		{
			os << ' ';
		}

		currNode = currNode->next;
	}

	return os;
}



} // namespace stdlib

namespace std
{
	void swap(stdlib::LinkedList& lhs, stdlib::LinkedList& rhs)
	{
		stdlib::LinkedList tmp{ std::move(lhs) };

		lhs = std::move(rhs);
		rhs = std::move(tmp);
	}
}