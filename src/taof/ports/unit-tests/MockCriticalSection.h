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
    MOCK_METHOD(void, lock, (), (override));
    MOCK_METHOD(void, unlock, (), (override));
};

#endif /* TAOF_PORTS_UNIT_TESTS_MOCK_CRITICAL_SECTION_H */