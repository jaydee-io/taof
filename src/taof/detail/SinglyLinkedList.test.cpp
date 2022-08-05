#include <gtest/gtest.h>
#include "SinglyLinkedList.h"

#include <array>

using namespace taof::detail;

struct SElem : public SinglyLinkedNode
{
    SElem(int data) : data(data) {}

    constexpr auto operator <=>(const SElem &) const = default;

    int data = 5;
};

TEST(SinglyLinkedList, List_Construct)
{
    SinglyLinkedList<SElem> emptyList;

    ASSERT_TRUE(emptyList.isEmpty());

    SElem elem = 10;
    SinglyLinkedList<SElem> notEmptyList(elem);

    ASSERT_FALSE(notEmptyList.isEmpty());
    ASSERT_EQ(notEmptyList.head().data, 10);
}

TEST(SinglyLinkedList, List_PushHead)
{
    SinglyLinkedList<SElem> list;
    #define ELEM_VALUES { 1, 2, 3, 4, 5 };
    std::array<SElem, 5> elems = ELEM_VALUES;

    for(auto & elem : elems)
    {
        list.pushHead(elem);

        ASSERT_EQ(list.head().data, elem.data);
    }
}

TEST(SinglyLinkedList, List_PopHead)
{
    SinglyLinkedList<SElem> list;
    #define ELEM_VALUES { 1, 2, 3, 4, 5 };
    std::array<SElem, 5> elems = ELEM_VALUES;

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
    SinglyLinkedList<SElem> list;
    #define ELEM_VALUES { 1, 2, 3, 4, 5 };
    std::array<SElem, 5> elems = ELEM_VALUES;

    for(auto & elem : elems)
        list.pushHead(elem);

    ASSERT_FALSE(list.isEmpty());

    list.clear();

    ASSERT_TRUE(list.isEmpty());
}

TEST(SinglyLinkedList, List_Traveral)
{
    SinglyLinkedList<SElem> list;
    #define ELEM_VALUES { 1, 2, 3, 4, 5 };
    std::array<SElem, 5> elems = ELEM_VALUES;

    for(auto it = std::rbegin(elems); it != std::rend(elems); ++it)
        list.pushHead(*it);

    auto idx = 0;
    for(auto it = std::begin(list); it != std::end(list); ++it, ++idx)
        ASSERT_EQ(*it, elems[idx]);
}
