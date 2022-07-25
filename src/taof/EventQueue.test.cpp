#include <gtest/gtest.h>
#include "EventQueue.h"

using namespace taof;

TEST(EventQueue, Construct)
{
    std::array<Event *, 3> eventBuffer;
    EventQueue<3> queue(eventBuffer);

    ASSERT_TRUE(queue.isEmpty());
}

TEST(EventQueue, PopEmpty)
{
    std::array<Event *, 3> eventBuffer;
    EventQueue<3> queue(eventBuffer);

    ASSERT_EQ(queue.pop(), nullptr);
    ASSERT_TRUE(queue.isEmpty());

    ASSERT_EQ(queue.pop(), nullptr);
    ASSERT_TRUE(queue.isEmpty());
}

TEST(EventQueue, PushOneEvent)
{
    std::array<Event *, 3> eventBuffer;
    EventQueue<3> queue(eventBuffer);

    Event event1;
    queue.push(&event1);
    ASSERT_FALSE(queue.isEmpty());

    Event * tmpEvent = nullptr;
    tmpEvent = queue.pop();
    ASSERT_EQ(tmpEvent, &event1);
}

TEST(EventQueue, PushSeveralEvents)
{
    std::array<Event *, 3> eventBuffer;
    EventQueue<3> queue(eventBuffer);

    Event event1;
    queue.push(&event1);
    ASSERT_FALSE(queue.isEmpty());

    Event event2;
    queue.push(&event2);
    ASSERT_FALSE(queue.isEmpty());

    Event event3;
    queue.push(&event3);
    ASSERT_FALSE(queue.isEmpty());

    Event * tmpEvent = nullptr;
    tmpEvent = queue.pop();
    ASSERT_EQ(tmpEvent, &event1);

    tmpEvent = queue.pop();
    ASSERT_EQ(tmpEvent, &event2);

    tmpEvent = queue.pop();
    ASSERT_EQ(tmpEvent, &event3);
}