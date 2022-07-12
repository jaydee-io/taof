////////////////////////////////////////////////////////////////////////////////
//                                ActiveObjects
//
// This file is distributed under the 3-clause Berkeley Software Distribution
// License. See LICENSE for details.
////////////////////////////////////////////////////////////////////////////////
#ifndef ACTIVE_OBJECTS_UTILS_SINGLY_LINKED_LIST_H
#define ACTIVE_OBJECTS_UTILS_SINGLY_LINKED_LIST_H
#include <compare>

namespace utils {

/*************************************************
 * Singly linked list node
 *************************************************/
class SinglyLinkedNode
{
public:
    template<typename T> friend class SinglyLinkedListIterator;
    template<typename T> friend class SinglyLinkedList;

    constexpr auto operator <=>(const SinglyLinkedNode &) const = default;

    constexpr void insertAfter(SinglyLinkedNode & node)
    {
        assert(next == nullptr);

        next = node.next;
        node.next = this;
    }

protected:
    constexpr SinglyLinkedNode(void) = default;
    constexpr SinglyLinkedNode(SinglyLinkedNode * next) : next(next) {}

    SinglyLinkedNode * next = nullptr;
};

/*************************************************
 * Singly linked list iterator
 *************************************************/
template<typename T>
class SinglyLinkedListIterator
{
public:
    constexpr SinglyLinkedListIterator(void) = default;
    constexpr explicit SinglyLinkedListIterator(SinglyLinkedNode * node) : node(node) {}

    constexpr auto operator <=>(const SinglyLinkedListIterator & it) const = default;

    constexpr T & operator*(void)  { return *reinterpret_cast<T *>(node); }
    constexpr T * operator->(void) { return  reinterpret_cast<T *>(node); }

    constexpr SinglyLinkedListIterator & operator ++(void) { return forward(); }                                 // Prefix
    constexpr SinglyLinkedListIterator   operator ++(int)  { return execFuncAndReturnPreviousValue(&forward); }  // Postfix

protected:
    constexpr SinglyLinkedListIterator execFuncAndReturnPreviousValue(SinglyLinkedListIterator & (*func)(void))
    {
        auto old = *this;
        (*func)();

        return old;
    }

    constexpr SinglyLinkedListIterator & forward(void)
    {
        if(node)
            node = node->next;

        return *this;
    }

    SinglyLinkedNode * node = nullptr;
};

/*************************************************
 * Singly linked list
 *************************************************/
template<typename T>
class SinglyLinkedList
{
    static_assert(std::is_base_of_v<SinglyLinkedNode, T>);

public:
    constexpr SinglyLinkedList(void) = default;
    constexpr SinglyLinkedList(T & node) { node.insertAfter(list); }

    constexpr SinglyLinkedListIterator<T> begin(void)  { return SinglyLinkedListIterator<T>(list.next); }
    constexpr SinglyLinkedListIterator<T> end(void)    { return SinglyLinkedListIterator<T>(&list); }

    constexpr bool isEmpty(void) const { return list.next == &list; }

    constexpr const T & head(void) const { return *begin(); }
    constexpr       T & head(void)       { return *begin(); }

    constexpr void pushHead(T & node) { node.insertAfter(list); }

    constexpr void popHead(void)
    {
        auto & headNode = head();

        list.next = headNode.next;
        headNode.next = nullptr;
    }

    constexpr void clear(void)
    {
        while(not isEmpty())
            popHead();
    }

protected:
    SinglyLinkedNode list = { &list };
};

/*************************************************
 * Singly linked list free functions
 *************************************************/
template<typename T>
SinglyLinkedListIterator<T> begin(SinglyLinkedList<T> & list) { return list.begin(); }

template<typename T>
SinglyLinkedListIterator<T> end(SinglyLinkedList<T> & list) { return list.end(); }

}; // namespace utils

#endif /* ACTIVE_OBJECTS_UTILS_SINGLY_LINKED_LIST_H */