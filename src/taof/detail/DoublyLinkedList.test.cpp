#include <gtest/gtest.h>
#include "DoublyLinkedList.h"

#include <array>

using namespace taof::detail;

struct DElem : public DoublyLinkedNode
{
    DElem(int data) : data(data) {}

    constexpr auto operator <=>(const DElem &) const = default;

    int data = 5;
};

TEST(DoublyLinkedList, Node_Construct)
{
    DElem elem = { 1 };

    ASSERT_FALSE(elem.isInList());
}

TEST(DoublyLinkedList, Node_Chained)
{
    DElem elem1 = { 1 };
    DElem elem2 = { 2 };

    ASSERT_FALSE(elem1.isInList());
    ASSERT_FALSE(elem2.isInList());

    elem2.insertAfter(elem1);

    ASSERT_TRUE(elem1.isInList());
    ASSERT_TRUE(elem2.isInList());
}

TEST(DoublyLinkedList, List_Construct)
{
    DoublyLinkedList<DElem> emptyList;

    ASSERT_TRUE(emptyList.isEmpty());

    DElem elem = 10;
    DoublyLinkedList<DElem> notEmptyList(elem);

    ASSERT_FALSE(notEmptyList.isEmpty());
    ASSERT_EQ(notEmptyList.head().data, 10);
    ASSERT_EQ(notEmptyList.tail().data, 10);
}

TEST(DoublyLinkedList, List_PushHead)
{
    DoublyLinkedList<DElem> list;
    #define ELEM_VALUES { 1, 2, 3, 4, 5 };
    std::array<DElem, 5> elems = ELEM_VALUES;

    for(auto & elem : elems)
    {
        ASSERT_FALSE(elem.isInList());
        list.pushHead(elem);
        ASSERT_TRUE(elem.isInList());

        ASSERT_EQ(list.head().data, elem.data);
        ASSERT_EQ(list.tail().data, elems.front().data);
    }
}

TEST(DoublyLinkedList, List_PushTail)
{
    DoublyLinkedList<DElem> list;
    #define ELEM_VALUES { 1, 2, 3, 4, 5 };
    std::array<DElem, 5> elems = ELEM_VALUES;

    for(auto & elem : elems)
    {
        ASSERT_FALSE(elem.isInList());
        list.pushTail(elem);
        ASSERT_TRUE(elem.isInList());

        ASSERT_EQ(list.tail().data, elem.data);
        ASSERT_EQ(list.head().data, elems.front().data);
    }
}

TEST(DoublyLinkedList, List_PopHead)
{
    DoublyLinkedList<DElem> list;
    #define ELEM_VALUES { 1, 2, 3, 4, 5 };
    std::array<DElem, 5> elems = ELEM_VALUES;

    for(auto & elem : elems)
        list.pushTail(elem);

    for(auto & elem : elems)
    {
        auto & head = list.head();
        ASSERT_EQ(head.data, elem.data);
        ASSERT_TRUE(head.isInList());

        list.popHead();

        ASSERT_FALSE(head.isInList());
    }
}

TEST(DoublyLinkedList, List_PopTail)
{
    DoublyLinkedList<DElem> list;
    #define ELEM_VALUES { 1, 2, 3, 4, 5 };
    std::array<DElem, 5> elems = ELEM_VALUES;

    for(auto & elem : elems)
        list.pushHead(elem);

    for(auto & elem : elems)
    {
        auto & tail = list.tail();
        ASSERT_EQ(tail.data, elem.data);
        ASSERT_TRUE(tail.isInList());

        list.popTail();

        ASSERT_FALSE(tail.isInList());
    }
}

TEST(DoublyLinkedList, List_Clear)
{
    DoublyLinkedList<DElem> list;
    #define ELEM_VALUES { 1, 2, 3, 4, 5 };
    std::array<DElem, 5> elems = ELEM_VALUES;

    for(auto & elem : elems)
        list.pushHead(elem);

    for(auto & elem : elems)
        ASSERT_TRUE(elem.isInList());

    list.clear();

    ASSERT_TRUE(list.isEmpty());
    for(auto & elem : elems)
        ASSERT_FALSE(elem.isInList());
}

TEST(DoublyLinkedList, List_Traveral)
{
    DoublyLinkedList<DElem> list;
    #define ELEM_VALUES { 1, 2, 3, 4, 5 };
    std::array<DElem, 5> elems = ELEM_VALUES;

    for(auto & elem : elems)
        list.pushTail(elem);

    auto idx = 0;
    for(auto it = std::begin(list); it != std::end(list); ++it, ++idx)
        ASSERT_EQ(*it, elems[idx]);
}

TEST(DoublyLinkedList, List_ReverseTraveral)
{
    DoublyLinkedList<DElem> list;
    #define ELEM_VALUES { 1, 2, 3, 4, 5 };
    std::array<DElem, 5> elems = ELEM_VALUES;

    for(auto & elem : elems)
        list.pushTail(elem);

    auto idx = 1;
    for(auto it = std::rbegin(list); it != std::rend(list); ++it, ++idx)
        ASSERT_EQ(*it, elems[elems.size() - idx]);
}
