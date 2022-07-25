////////////////////////////////////////////////////////////////////////////////
//                          The Active Object Framework
//
// This file is distributed under the 3-clause Berkeley Software Distribution
// License. See LICENSE for details.
////////////////////////////////////////////////////////////////////////////////
#ifndef TAOF_EVENT_QUEUE_H
#define TAOF_EVENT_QUEUE_H
#include "Event.h"

#include <span>

namespace taof {

/*************************************************
 * Queue of event pointers
 * (Queue events storage is allocated externally)
 *************************************************/
template<std::size_t QUEUE_LENGTH, typename Counter = uint8_t>
class EventQueue
{
public:
    EventQueue(void) {} /* Create a queue with a depth of just one event */

    explicit EventQueue(std::span<Event *, QUEUE_LENGTH> rawStorage)
    : ring(rawStorage)
    {}

    EventQueue(const EventQueue &) = delete; /* No copy */
    EventQueue(EventQueue &&) = delete; /* No move */


    bool isEmpty(void) { return nullptr == frontEvent; }

    void push(Event * event)
    {
        // TODO : LOCK
        event->incrementReferenceCount();   /* An event is referenced when it's added to a queue */

        if(isEmpty())                       /* Queue is empty => insert into optimized pointer */
        {
            frontEvent = event;
            // TODO : Signal that the queue is not empty
        }
        else                                /* Queue isn't empty, insert into the ring buffer */
        {
            // TODO : Assert (nFree != 0)
            ring[head] = event;
            if(head == Counter(0))          /* Need to wrap the head ? */
                head = end;                 /* Wrap around */

            --head;
            --nFree;                        /* One less free event in the ring */

            if(nMin > nFree)
                nMin = nFree;               /* Update statistics */
        }

        // TODO : UNLOCK
    }

    Event * pop(void)
    {
        // TODO : LOCK

        // TODO : Wait for the queue to be not empty

        Event * event = frontEvent;

        if(nFree != end)                /* Any event in the ring ? */
        {
            frontEvent = ring[tail];    /* Remove event from tail */
            if(tail == Counter(0))      /* Need to wrap the tail ? */
                tail = end;             /* Wrap around */

            --tail;
            ++nFree;                    /* One more free event in the ring */
        }
        else
        {
            frontEvent = nullptr;       /* Queue become empty */

            // TODO : Notify empty queue
        }

        // TODO : UNLOCK
        return event;
    }


protected:
    const std::span<Event *, QUEUE_LENGTH> ring;  /* The ring buffer raw storage */

    Event * frontEvent = nullptr;   /* Optimisation to quickly access queue containing just one event */
    Counter end = QUEUE_LENGTH;
    Counter head = 0;
    Counter tail = 0;
    Counter nFree = QUEUE_LENGTH;
    Counter nMin = QUEUE_LENGTH;
};

}; /* namespace taof */

#endif /* TAOF_EVENT_QUEUE_H */