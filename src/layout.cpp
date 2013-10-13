#include <algorithm>
#include "layout.h"

namespace Gui
{
    Layout::Layout()
    {
    }

    Layout::~Layout()
    {
//        while (!m_children.empty())
//        {
//            delete m_children.back();
//            m_children.pop_back();
//        }
    }

    void Layout::Update(float x, float y, float width, float height)
    {
        m_x = x;
        m_y = y;
        m_width = width;
        m_height = height;
    }

    void Layout::AddWidget(Widget *value)
    {
        auto it = std::find(m_children.begin(), m_children.end(), value);
        if (it != m_children.end())
            return;
        m_children.push_back(value);
        Update(m_x, m_y, m_width, m_height);
    }

    void Layout::RemoveWidget(Widget *value)
    {
        auto it = std::find(m_children.begin(), m_children.end(), value);
        if (it == m_children.end())
            return;
        m_children.erase(it);
        Update(m_x, m_y, m_width, m_height);
    }
}
