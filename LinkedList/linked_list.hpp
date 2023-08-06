#pragma once

/* TODO List:
*    * Basic functions:
*          - Constructors              DONE
*          - Copy ctr and operator     DONE
*          - Move cnr and operator     DONE 
*          - Comparison operators      DONE
*          - Output operator           DONE
*          - ToString conversion oper. DONE
*          - Desctructor               DONE
*          - Front()                   DONE
*          - Back()                    DONE
*          - IsEmpty()                 DONE
*          - Size()                    DONE
*          - PushBack()                DONE
*          - PushFront()               DONE
*          - PopFront()                DONE
*          - PopBack()                 DONE
* 
*   * Iterators
* 
*   * Advanced Functions:
*          - Swap                      DONE
*          - Insert()
*          - Emplace()
*          - Erase()
* 
*   * Exception safe
*/

#include <iostream>
#include <memory>
#include <string>
#include <initializer_list>

namespace stdlib
{

class LinkedList
{
public:
	LinkedList() = default;
	LinkedList(const std::initializer_list<long>& vals);

	LinkedList(const LinkedList& other);
	LinkedList& operator =(const LinkedList& other);

	LinkedList(LinkedList&& other) noexcept;
	LinkedList& operator =(LinkedList&& other) noexcept;

	bool operator ==(const LinkedList& other) const;
	bool operator !=(const LinkedList& other) const;

	void PushFront(const long& val);
	void PushBack(const long& val);

	long& Front();
	const long& Front() const;
	long& Back();
	const long& Back() const;

	void PopFront();
	void PopBack();

	std::size_t Size() const;
	bool IsEmpty() const;

	operator std::string();

	friend std::ostream& operator <<(std::ostream& os, const LinkedList& list);
	friend void std::swap(LinkedList& lhs, LinkedList& rhs);

	~LinkedList();

private:
	struct ListNode
	{
		ListNode(const long& val, std::shared_ptr<ListNode> prev, std::shared_ptr<ListNode> next)
			: value{val}, prev{prev}, next{next} {}

		long value;
		std::shared_ptr<ListNode> prev;
		std::shared_ptr<ListNode> next;
	};

private:
	std::shared_ptr<ListNode> m_head{ nullptr };
	std::shared_ptr<ListNode> m_tail{ nullptr };

	std::size_t m_size{ 0 };
};

} // namespace stdlib