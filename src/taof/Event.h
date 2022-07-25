////////////////////////////////////////////////////////////////////////////////
//                          The Active Object Framework
//
// This file is distributed under the 3-clause Berkeley Software Distribution
// License. See LICENSE for details.
////////////////////////////////////////////////////////////////////////////////
#ifndef TAOF_EVENT_H
#define TAOF_EVENT_H

namespace taof {

/*************************************************
 * Event base type
 *************************************************/
class Event
{
public:
    Event(void) = default;

    void incrementReferenceCount(void) { ++refCount; }

protected:
    enum class Type
    {
        STATIC,
        DYNAMIC,
    };

    Type type = Type::STATIC;
    unsigned int refCount = 0;
};

}; /* namespace taof */

#endif /* TAOF_EVENT_H */