#ifndef SIGNAL_H
#define SIGNAL_H

#include <vector>

namespace Gui
{
    class Action;
    class ActionParameter;

    class Signal
    {
    public:
        ~Signal();
        void Connect(Action* value);
        void Disconnect(Action* value);
        void operator () (const ActionParameter& value);

    private:
        std::vector<Action*> m_actions;
    };
}

#endif // SIGNAL_H
