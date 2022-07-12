#include <gtest/gtest.h>
#include "SinglyLinkedList.h"

#include <array>

using namespace utils;

struct Elem : public SinglyLinkedNode
{
    Elem(int data) : data(data) {}

    constexpr auto operator <=>(const Elem &) const = default;

    int data = 5;
};

TEST(SinglyLinkedList, List_Construct)
{
    SinglyLinkedList<Elem> emptyList;

    ASSERT_TRUE(emptyList.isEmpty());

    Elem elem = 10;
    SinglyLinkedList<Elem> notEmptyList(elem);

    ASSERT_FALSE(notEmptyList.isEmpty());
    ASSERT_EQ(notEmptyList.head().data, 10);
}

TEST(SinglyLinkedList, List_PushHead)
{
    SinglyLinkedList<Elem> list;
    #define ELEM_VALUES { 1, 2, 3, 4, 5 };
    std::array<Elem, 5> elems = ELEM_VALUES;

    for(auto & elem : elems)
    {
        list.pushHead(elem);

        ASSERT_EQ(list.head().data, elem.data);
    }
}

TEST(SinglyLinkedList, List_PopHead)
{
    SinglyLinkedList<Elem> list;
    #define ELEM_VALUES { 1, 2, 3, 4, 5 };
    std::array<Elem, 5> elems = ELEM_VALUES;

    for(auto it = std::rbegin(elems); it != std::rend(elems); ++it)
        list.pushHead(*it);

    for(auto & elem : elems)
    {
        auto & head = list.head();
        ASSERT_EQ(head.data, elem.data);

        list.popHead();
    }
}

TEST(SinglyLinkedList, List_Clear)
{
    SinglyLinkedList<Elem> list;
    #define ELEM_VALUES { 1, 2, 3, 4, 5 };
    std::array<Elem, 5> elems = ELEM_VALUES;

    for(auto & elem : elems)
        list.pushHead(elem);

    ASSERT_FALSE(list.isEmpty());

    list.clear();

    ASSERT_TRUE(list.isEmpty());
}

TEST(SinglyLinkedList, List_Traveral)
{
    SinglyLinkedList<Elem> list;
    #define ELEM_VALUES { 1, 2, 3, 4, 5 };
    std::array<Elem, 5> elems = ELEM_VALUES;

    for(auto it = std::rbegin(elems); it != std::rend(elems); ++it)
        list.pushHead(*it);

    auto idx = 0;
    for(auto it = std::begin(list); it != std::end(list); ++it, ++idx)
        ASSERT_EQ(*it, elems[idx]);
}
