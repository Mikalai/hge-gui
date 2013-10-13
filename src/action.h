#ifndef ACTION_H
#define ACTION_H

#include <tuple>
#include <new>
#include <cstddef>

namespace Gui
{
    class ActionParameter
    {
    public:
        virtual ~ActionParameter() {}
    };

    class Action
    {
    public:
        virtual ~Action() {}
        virtual void operator() (const ActionParameter& value) = 0;
    };
}

#endif // ACTION_H
