////////////////////////////////////////////////////////////////////////////////
//                          The Active Object Framework
//
// This file is distributed under the 3-clause Berkeley Software Distribution
// License. See LICENSE for details.
////////////////////////////////////////////////////////////////////////////////
#ifndef TAOF_PORTS_UNIT_TESTS_MOCK_CRITICAL_SECTION_H
#define TAOF_PORTS_UNIT_TESTS_MOCK_CRITICAL_SECTION_H
#include "CriticalSection.h"
#include "gmock/gmock.h"

class MockCriticalSection : public taof::ports::CriticalSection
{
public:
    virtual ~MockCriticalSection(void) = default;

    MOCK_METHOD(void, lock, (), (override));
    MOCK_METHOD(void, unlock, (), (override));

    static MockCriticalSection & activeMock(void);

    static MockCriticalSection & warningOnUnexpectedCallMock(void);
    static MockCriticalSection & discardOnUnexpectedCallMock(void);
    static MockCriticalSection & failureOnUnexpectedCallMock(void);

    static void setWarningOnUnexpectedCallMock(void);
    static void setDiscardOnUnexpectedCallMock(void);
    static void setFailureOnUnexpectedCallMock(void);

protected:
    static MockCriticalSection * activeMockPtr;
};

#endif /* TAOF_PORTS_UNIT_TESTS_MOCK_CRITICAL_SECTION_H */