#ifndef SIGNAL_H
#define SIGNAL_H

#include <vector>

namespace Gui
{
    class ActionBase;
    class ActionParameterBase;

    class Signal
    {
    public:
        ~Signal();
        void Connect(ActionBase* value);
        void Disconnect(ActionBase* value);
        void operator () (const ActionParameterBase& value);

    private:
        std::vector<ActionBase*> m_actions;
    };
}

#endif // SIGNAL_H
