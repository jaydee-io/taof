#include <gtest/gtest.h>
#include "EventQueue.h"
#include "MockCriticalSection.h"

using namespace taof;

TEST(EventQueue, Construct)
{
    std::array<Event *, 6> eventBuffer;
    EventQueue<6> queue(eventBuffer);

    ASSERT_TRUE(queue.isEmpty());
}

TEST(EventQueue, PopEmpty)
{
    std::array<Event *, 6> eventBuffer;
    EventQueue<6> queue(eventBuffer);

    ASSERT_EQ(queue.pop(), nullptr);
    ASSERT_TRUE(queue.isEmpty());

    ASSERT_EQ(queue.pop(), nullptr);
    ASSERT_TRUE(queue.isEmpty());
}

TEST(EventQueue, PushOneEvent)
{
    std::array<Event *, 6> eventBuffer;
    EventQueue<6> queue(eventBuffer);

    Event event1;
    queue.push(&event1);
    ASSERT_FALSE(queue.isEmpty());

    Event * tmpEvent = nullptr;
    tmpEvent = queue.pop();
    ASSERT_EQ(tmpEvent, &event1);
}

TEST(EventQueue, PushSeveralEvents)
{
    std::array<Event *, 6> eventBuffer;
    EventQueue<6> queue(eventBuffer);
    Event * tmpEvent = nullptr;

    Event event1; queue.push(&event1); ASSERT_FALSE(queue.isEmpty());
    Event event2; queue.push(&event2); ASSERT_FALSE(queue.isEmpty());
    Event event3; queue.push(&event3); ASSERT_FALSE(queue.isEmpty());

    tmpEvent = queue.pop(); ASSERT_EQ(tmpEvent, &event1);
    tmpEvent = queue.pop(); ASSERT_EQ(tmpEvent, &event2);
    tmpEvent = queue.pop(); ASSERT_EQ(tmpEvent, &event3);
}

TEST(EventQueue, CriticalSection)
{
    ::testing::InSequence seq;

    MockCriticalSection::setFailureOnUnexpectedCallMock();

    std::array<Event *, 6> eventBuffer;
    EventQueue<6> queue(eventBuffer);

    Event event1;
    EXPECT_CALL(MockCriticalSection::failureOnUnexpectedCallMock(), lock());
    EXPECT_CALL(MockCriticalSection::failureOnUnexpectedCallMock(), unlock());
    queue.push(&event1);

    Event event2;
    EXPECT_CALL(MockCriticalSection::failureOnUnexpectedCallMock(), lock());
    EXPECT_CALL(MockCriticalSection::failureOnUnexpectedCallMock(), unlock());
    queue.push(&event2);

    Event event3;
    EXPECT_CALL(MockCriticalSection::failureOnUnexpectedCallMock(), lock());
    EXPECT_CALL(MockCriticalSection::failureOnUnexpectedCallMock(), unlock());
    queue.push(&event3);

    Event * tmpEvent = nullptr;
    EXPECT_CALL(MockCriticalSection::failureOnUnexpectedCallMock(), lock());
    EXPECT_CALL(MockCriticalSection::failureOnUnexpectedCallMock(), unlock());
    tmpEvent = queue.pop();

    EXPECT_CALL(MockCriticalSection::failureOnUnexpectedCallMock(), lock());
    EXPECT_CALL(MockCriticalSection::failureOnUnexpectedCallMock(), unlock());
    tmpEvent = queue.pop();

    EXPECT_CALL(MockCriticalSection::failureOnUnexpectedCallMock(), lock());
    EXPECT_CALL(MockCriticalSection::failureOnUnexpectedCallMock(), unlock());
    tmpEvent = queue.pop();

    MockCriticalSection::setDiscardOnUnexpectedCallMock();
}

TEST(EventQueue, PushUrgent)
{
    std::array<Event *, 6> eventBuffer;
    EventQueue<6> queue(eventBuffer);
    Event * tmpEvent = nullptr;

    Event eventUrgent1; queue.pushUrgent(&eventUrgent1);
    Event event1;       queue.push(&event1);
    Event event2;       queue.push(&event2);
    Event eventUrgent2; queue.pushUrgent(&eventUrgent2);
    Event event3;       queue.push(&event3);
    Event eventUrgent3; queue.pushUrgent(&eventUrgent3);

    tmpEvent = queue.pop(); ASSERT_EQ(tmpEvent, &eventUrgent3);
    tmpEvent = queue.pop(); ASSERT_EQ(tmpEvent, &eventUrgent2);
    tmpEvent = queue.pop(); ASSERT_EQ(tmpEvent, &eventUrgent1);
    tmpEvent = queue.pop(); ASSERT_EQ(tmpEvent, &event1);
    tmpEvent = queue.pop(); ASSERT_EQ(tmpEvent, &event2);
    tmpEvent = queue.pop(); ASSERT_EQ(tmpEvent, &event3);
}

TEST(EventQueue, WrapAround)
{
    std::array<Event *, 6> eventBuffer;
    EventQueue<6> queue(eventBuffer);
    Event * tmpEvent = nullptr;

    Event eventUrgent1;
    for(auto i=0; i<eventBuffer.size(); i++)
        queue.push(&eventUrgent1);
    tmpEvent = queue.pop();

    Event eventUrgent2; queue.pushUrgent(&eventUrgent2);
    tmpEvent = queue.pop();
    ASSERT_EQ(tmpEvent, &eventUrgent2);
}