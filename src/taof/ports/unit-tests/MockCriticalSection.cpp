////////////////////////////////////////////////////////////////////////////////
//                          The Active Object Framework
//
// This file is distributed under the 3-clause Berkeley Software Distribution
// License. See LICENSE for details.
////////////////////////////////////////////////////////////////////////////////
#include "MockCriticalSection.h"

using ::testing::NiceMock;

MockCriticalSection * MockCriticalSection::activeMockPtr = nullptr;

taof::ports::CriticalSection & taof::ports::CriticalSection::globalInstance(void)
{
    return MockCriticalSection::activeMock();
}

MockCriticalSection & MockCriticalSection::activeMock(void)
{

    if(not MockCriticalSection::activeMockPtr)
        MockCriticalSection::setDiscardOnUnexpectedCallMock();

    return *MockCriticalSection::activeMockPtr;
}

MockCriticalSection & MockCriticalSection::warningOnUnexpectedCallMock(void)
{
    static MockCriticalSection instance;

    return instance;
}

MockCriticalSection & MockCriticalSection::discardOnUnexpectedCallMock(void)
{
    static ::testing::NiceMock<MockCriticalSection> instance;

    return instance;
}

MockCriticalSection & MockCriticalSection::failureOnUnexpectedCallMock(void)
{
    static ::testing::StrictMock<MockCriticalSection> instance;

    return instance;
}

void MockCriticalSection::setWarningOnUnexpectedCallMock(void)
{
    MockCriticalSection::activeMockPtr = &MockCriticalSection::warningOnUnexpectedCallMock();
}

void MockCriticalSection::setDiscardOnUnexpectedCallMock(void)
{
    MockCriticalSection::activeMockPtr = &MockCriticalSection::discardOnUnexpectedCallMock();
}

void MockCriticalSection::setFailureOnUnexpectedCallMock(void)
{
    MockCriticalSection::activeMockPtr = &MockCriticalSection::failureOnUnexpectedCallMock();
}
