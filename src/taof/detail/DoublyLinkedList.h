////////////////////////////////////////////////////////////////////////////////
//                          The Active Object Framework
//
// This file is distributed under the 3-clause Berkeley Software Distribution
// License. See LICENSE for details.
////////////////////////////////////////////////////////////////////////////////
#ifndef TAOF_DETAIL_DOUBLY_LINKED_LIST_H
#define TAOF_DETAIL_DOUBLY_LINKED_LIST_H
#include <compare>

namespace taof::detail {

/*************************************************
 * Doubly linked list node
 *************************************************/
class DoublyLinkedNode
{
public:
    template<typename T> friend class DoublyLinkedListIterator;
    template<typename T> friend class DoublyLinkedList;

    constexpr auto operator <=>(const DoublyLinkedNode &) const = default;

    constexpr bool isInList(void) { return (next != nullptr) or (previous != nullptr); }

    constexpr void insertAfter(DoublyLinkedNode & node)
    {
        assert(previous == nullptr and next == nullptr);

        previous = &node;
        next = node.next;

        node.next = this;
        if(next)
            next->previous = this;
    }

    constexpr void insertBefore(DoublyLinkedNode & node)
    {
        assert(previous == nullptr and next == nullptr);

        previous = node.previous;
        next = &node;

        node.previous = this;
        if(previous)
            previous->next = this;
    }

    constexpr void remove(void)
    {
        assert(not (previous == nullptr and next == nullptr));

        if(previous)
            previous->next = next;
        if(next)
            next->previous = previous;

        next = nullptr;
        previous = nullptr;
    }

protected:
    constexpr DoublyLinkedNode(void) = default;
    constexpr DoublyLinkedNode(DoublyLinkedNode * next, DoublyLinkedNode * previous) : next(next), previous(previous) {}

    DoublyLinkedNode * next = nullptr;
    DoublyLinkedNode * previous = nullptr;
};

/*************************************************
 * Doubly linked list iterator
 *************************************************/
template<typename T>
class DoublyLinkedListIterator
{
public:
    constexpr DoublyLinkedListIterator(void) = default;
    constexpr explicit DoublyLinkedListIterator(DoublyLinkedNode * node) : node(node) {}

    constexpr auto operator <=>(const DoublyLinkedListIterator & it) const = default;

    constexpr T & operator*(void)  { return *reinterpret_cast<T *>(node); }
    constexpr T * operator->(void) { return  reinterpret_cast<T *>(node); }

    constexpr DoublyLinkedListIterator & operator ++(void) { return forward(); }                                 // Prefix
    constexpr DoublyLinkedListIterator   operator ++(int)  { return execFuncAndReturnPreviousValue(&forward); }  // Postfix
    constexpr DoublyLinkedListIterator & operator --(void) { return backward(); }                                // Prefix
    constexpr DoublyLinkedListIterator   operator --(int)  { return execFuncAndReturnPreviousValue(&backward); } // Postfix

protected:
    constexpr DoublyLinkedListIterator execFuncAndReturnPreviousValue(DoublyLinkedListIterator & (*func)(void))
    {
        auto old = *this;
        (*func)();

        return old;
    }

    constexpr DoublyLinkedListIterator & forward(void)
    {
        if(node)
            node = node->next;

        return *this;
    }

    constexpr DoublyLinkedListIterator & backward(void)
    {
        if(node)
            node = node->previous;

        return *this;
    }

    DoublyLinkedNode * node = nullptr;
};

template<typename T>
class ReverseDoublyLinkedListIterator
{
public:
    constexpr ReverseDoublyLinkedListIterator(void) = default;
    constexpr explicit ReverseDoublyLinkedListIterator(DoublyLinkedNode * node) : it(node) {}

    constexpr auto operator <=>(const ReverseDoublyLinkedListIterator & it) const = default;

    constexpr T & operator*(void)  { return it.operator *(); }
    constexpr T * operator->(void) { return it.operator ->(); }

    constexpr ReverseDoublyLinkedListIterator & operator ++(void) { --it; return  *this; } // Prefix
    constexpr ReverseDoublyLinkedListIterator   operator ++(int)  { it--; return  *this; } // Postfix
    constexpr ReverseDoublyLinkedListIterator & operator --(void) { ++it; return  *this; } // Prefix
    constexpr ReverseDoublyLinkedListIterator   operator --(int)  { it++; return  *this; } // Postfix

protected:
    DoublyLinkedListIterator<T> it;
};

/*************************************************
 * Doubly linked list
 *************************************************/
template<typename T>
class DoublyLinkedList
{
    static_assert(std::is_base_of_v<DoublyLinkedNode, T>);

public:
    constexpr DoublyLinkedList(void) = default;
    constexpr DoublyLinkedList(T & node) { node.insertAfter(list); }

    constexpr DoublyLinkedListIterator<T> begin(void)  { return DoublyLinkedListIterator<T>(list.next); }
    constexpr DoublyLinkedListIterator<T> end(void)    { return DoublyLinkedListIterator<T>(&list); }
    constexpr ReverseDoublyLinkedListIterator<T> rbegin(void) { return ReverseDoublyLinkedListIterator<T>(list.previous); }
    constexpr ReverseDoublyLinkedListIterator<T> rend(void)   { return ReverseDoublyLinkedListIterator<T>(&list); }

    constexpr bool isEmpty(void) const { return list.next == &list and list.previous == &list; }

    constexpr const T & head(void) const { return *begin(); }
    constexpr       T & head(void)       { return *begin(); }
    constexpr       T & tail(void)       { return *rbegin(); }
    constexpr const T & tail(void) const { return *rbegin(); }

    constexpr void pushHead(T & node) { node.insertAfter(list); }
    constexpr void pushTail(T & node) { node.insertBefore(list); }

    constexpr void popHead(void) { list.next->remove(); }
    constexpr void popTail(void) { list.previous->remove(); }

    constexpr void clear(void)
    {
        while(not isEmpty())
            popHead();
    }

protected:
    DoublyLinkedNode list = { &list, &list };
};

/*************************************************
 * Doubly linked list free functions
 *************************************************/
template<typename T>
DoublyLinkedListIterator<T> begin(DoublyLinkedList<T> & list) { return list.begin(); }
template<typename T>
DoublyLinkedListIterator<T> rbegin(DoublyLinkedList<T> & list) { return list.rbegin(); }

template<typename T>
DoublyLinkedListIterator<T> end(DoublyLinkedList<T> & list) { return list.end(); }
template<typename T>
DoublyLinkedListIterator<T> rend(DoublyLinkedList<T> & list) { return list.rend(); }

}; /* namespace taof::detail */

#endif /* TAOF_DETAIL_DOUBLY_LINKED_LIST_H */