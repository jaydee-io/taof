////////////////////////////////////////////////////////////////////////////////
//                          The Active Object Framework
//
// This file is distributed under the 3-clause Berkeley Software Distribution
// License. See LICENSE for details.
////////////////////////////////////////////////////////////////////////////////
#ifndef TAOF_PORTS_CRITICAL_SECTION_H
#define TAOF_PORTS_CRITICAL_SECTION_H

namespace taof::ports {

/*************************************************
 * Critical section
 *************************************************/
class CriticalSection
{
public:
    virtual ~CriticalSection(void) = default;

    virtual void lock(void) = 0;
    virtual void unlock(void) = 0;


    static CriticalSection & globalInstance(void);
};

class ScopedCriticalSection
{
public:
    ScopedCriticalSection(CriticalSection & criticalSection)
    : criticalSection(criticalSection)
    {
        criticalSection.lock();
    }

    ~ScopedCriticalSection(void)
    {
        criticalSection.unlock();
    }

private:
    CriticalSection & criticalSection;
};

}; /* namespace taof::ports */

#endif /* TAOF_PORTS_CRITICAL_SECTION_H */