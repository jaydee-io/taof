////////////////////////////////////////////////////////////////////////////////
//                          The Active Object Framework
//
// This file is distributed under the 3-clause Berkeley Software Distribution
// License. See LICENSE for details.
////////////////////////////////////////////////////////////////////////////////
#include "MockCriticalSection.h"

taof::ports::CriticalSection & taof::ports::CriticalSection::globalInstance(void)
{
    static MockCriticalSection instance;

    return instance;
}
