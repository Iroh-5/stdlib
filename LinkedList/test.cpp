#include "pch.h"
#include "../Linked List/linked_list.cpp"

#include <vector>
#include <string>
#include <sstream>

namespace stdlib
{

TEST(Basic, DefaultConstructor)
{
	LinkedList list;

	ASSERT_EQ(0, list.Size());
	ASSERT_TRUE(list.IsEmpty());

	ASSERT_EQ("", static_cast<std::string>(list));
}

TEST(Basic, CreateInitializerList)
{
	LinkedList list{ 1, 2, 3, 4, 5 };

	ASSERT_EQ(5, list.Size());
	ASSERT_FALSE(list.IsEmpty());

	ASSERT_EQ("1 2 3 4 5", static_cast<std::string>(list));
}

TEST(Basic, OutputOperator)
{
	LinkedList list;
	std::stringstream ss;

	ss << list;
	ASSERT_EQ("", ss.str());

	list.PushBack(1);
	ss << list;
	ASSERT_EQ("1", ss.str());

	ss = std::stringstream{};
	list.PushBack(2);
	list.PushBack(3);
	ss << list;
	ASSERT_EQ("1 2 3", ss.str());
}

TEST(Basic, ToStringConversion)
{
	LinkedList list;

	ASSERT_EQ("", static_cast<std::string>(list));

	list.PushBack(1);
	ASSERT_EQ("1", static_cast<std::string>(list));

	list.PushBack(2);
	list.PushBack(3);
	ASSERT_EQ("1 2 3", static_cast<std::string>(list));
}

TEST(Basic, ComparisonOperators)
{
	ASSERT_TRUE(LinkedList{} == LinkedList{});
	ASSERT_TRUE(LinkedList{ 1 } == LinkedList{ 1 });
	ASSERT_TRUE((LinkedList{ 1, 2, 3 }) == (LinkedList{ 1, 2, 3 }));
	ASSERT_FALSE(LinkedList{} == LinkedList{ 1 });

	ASSERT_TRUE(LinkedList{} != LinkedList{ 1 });
	ASSERT_TRUE((LinkedList{ 1, 2, 3 }) != (LinkedList{ 1, 2, 4 }));
}

TEST(Basic, PushBack)
{
	LinkedList list;

	for (long i = 1; i <= 5; ++i)
	{
		list.PushBack(i);
	}

	ASSERT_EQ("1 2 3 4 5", static_cast<std::string>(list));
	ASSERT_EQ(5, list.Size());
}

TEST(Basic, PushFront)
{
	LinkedList list;

	for (long i = 1; i <= 5; ++i)
	{
		list.PushFront(i);
	}

	ASSERT_EQ("5 4 3 2 1", static_cast<std::string>(list));
	ASSERT_EQ(5, list.Size());
}

TEST(Basic, PopFrontEmptyList)
{
	LinkedList list;

	ASSERT_THROW(list.PopFront(), std::runtime_error);
}

TEST(Basic, PopFrontNonEmptyList)
{
	LinkedList list{ 1, 2 };

	ASSERT_EQ("1 2", static_cast<std::string>(list));
	ASSERT_EQ(2, list.Size());

	list.PopFront();
	ASSERT_EQ("2", static_cast<std::string>(list));
	ASSERT_EQ(1, list.Size());

	list.PopFront();
	ASSERT_EQ("", static_cast<std::string>(list));
	ASSERT_EQ(0, list.Size());
	ASSERT_TRUE(list.IsEmpty());
}

TEST(Basic, PopBackEmptyList)
{
	LinkedList list;

	ASSERT_THROW(list.PopBack(), std::runtime_error);
}

TEST(Basic, PopBackNonEmptyList)
{
	LinkedList list{ 1, 2 };

	ASSERT_EQ("1 2", static_cast<std::string>(list));
	ASSERT_EQ(2, list.Size());

	list.PopBack();
	ASSERT_EQ("1", static_cast<std::string>(list));
	ASSERT_EQ(1, list.Size());

	list.PopBack();
	ASSERT_EQ("", static_cast<std::string>(list));
	ASSERT_EQ(0, list.Size());
	ASSERT_TRUE(list.IsEmpty());
}

TEST(Basic, FrontEmptyList)
{
	LinkedList list;

	EXPECT_THROW(list.Front(), std::runtime_error);
}

TEST(Basic, FrontNonEmptyList)
{
	LinkedList list{ 1 };

	EXPECT_EQ(1, list.Front());

	list.Front() = 2;
	EXPECT_EQ(2, list.Front());

	list.PushFront(5);
	EXPECT_EQ(5, list.Front());
}

TEST(Basic, BackEmptyList)
{
	LinkedList list;

	EXPECT_THROW(list.Back(), std::runtime_error);
}

TEST(Basic, BackNonEmptyList)
{
	LinkedList list{ 1 };

	EXPECT_EQ(1, list.Back());

	list.Back() = 2;
	EXPECT_EQ(2, list.Back());

	list.PushBack(5);
	EXPECT_EQ(5, list.Back());
}

TEST(Basic, CopyConstructor)
{
	LinkedList list{ 1, 2, 3, 4, 5 };

	LinkedList anotherList = list;
	ASSERT_TRUE(list == anotherList);

	list.PopBack();
	ASSERT_FALSE(list == anotherList);
}

TEST(Basic, CopyOperator)
{
	LinkedList list{ 1, 2, 3, 4, 5 };
	LinkedList anotherList;

	anotherList = list;
	ASSERT_TRUE(list == anotherList);

	list.PopBack();
	ASSERT_FALSE(list == anotherList);
}

TEST(Basic, MoveConstructor)
{
	LinkedList list{ 1, 2, 3, 4, 5 };

	LinkedList anotherList = std::move(list);
	ASSERT_EQ("1 2 3 4 5", static_cast<std::string>(anotherList));
	ASSERT_EQ(5, anotherList.Size());

	ASSERT_EQ("", static_cast<std::string>(list));
	ASSERT_TRUE(list.IsEmpty());
}

TEST(Basic, MoveOperator)
{
	LinkedList list{ 1, 2, 3, 4, 5 };
	LinkedList anotherList;

	anotherList = std::move(list);
	ASSERT_EQ("1 2 3 4 5", static_cast<std::string>(anotherList));
	ASSERT_EQ(5, anotherList.Size());

	ASSERT_EQ("", static_cast<std::string>(list));
	ASSERT_TRUE(list.IsEmpty());
}

TEST(Advanced, Swap)
{
	LinkedList list{ 1, 2, 3 };
	LinkedList anotherList{ 4, 5 };

	ASSERT_EQ("1 2 3", static_cast<std::string>(list));
	ASSERT_EQ(3, list.Size());
	ASSERT_EQ("4 5", static_cast<std::string>(anotherList));
	ASSERT_EQ(2, anotherList.Size());

	std::swap(list, anotherList);
	ASSERT_EQ("1 2 3", static_cast<std::string>(anotherList));
	ASSERT_EQ(2, list.Size());
	ASSERT_EQ("4 5", static_cast<std::string>(list));
	ASSERT_EQ(3, anotherList.Size());
}

} // namespace stdlib