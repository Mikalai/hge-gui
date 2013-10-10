#include <algorithm>
#include "action.h"
#include "signal.h"

namespace Gui
{
    Signal::~Signal()
    {
        while (!m_actions.empty())
        {
            delete m_actions.back();
            m_actions.pop_back();
        }
    }

    void Signal::Connect(Action* value)
    {
        auto it = std::find(m_actions.begin(), m_actions.end(), value);
        if (it != m_actions.end())
            return;
        m_actions.push_back(value);
    }

    void Signal::Disconnect(Action* value)
    {
        auto it = std::find(m_actions.begin(), m_actions.end(), value);
        if (it == m_actions.end())
            return;
        m_actions.erase(it);
    }

    void Signal::operator () (const ActionParameter& value)
    {
        for (auto action : m_actions)
        {
            (*action)(value);
        }
    }
}
