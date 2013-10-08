#include <iostream>
#include <algorithm>
#include <hge.h>
#include "hge_render.h"
#include "gui_manager.h"
#include "widget.h"
#include "action.h"

namespace Gui
{
    Manager::Manager(HGE *hge)
        : m_hge(hge)
        , m_render(new HgeRender(hge))
    {
    }

    Manager::~Manager()
    {
        while (!m_children.empty())
        {
            delete m_children.back();
            m_children.pop_back();
        }

        if (m_render)
        {
            delete m_render;
            m_render = nullptr;
        }
    }

    void Manager::OnMouseMove(const Event &e)
    {
        m_prev_x = m_x;
        m_prev_y = m_y;
        m_x = e.x;
        m_y = e.y;

        if (m_left_down)
        {
            if (m_focus)
            {
                m_focus->SetLocalPosition(m_focus->LocalX() + (m_x - m_prev_x), m_focus->LocalY() + m_y - m_prev_y);
            }
        }

        m_cursor_widget = GetWidget(m_x, m_y);
        if (m_cursor_widget)
        {
            ActionParameter1<Event> p(e);
            m_cursor_widget->MouseMove(p);
        }
    }

    void Manager::OnMousePress(const Event &e)
    {
        m_left_down = (e.key == HGEK_LBUTTON ? true : m_left_down);
        m_right_down = (e.key == HGEK_RBUTTON ? true : m_right_down);
        m_middle_down = (e.key == HGEK_MBUTTON ? true : m_middle_down);

        m_focus = GetWidget(e.x, e.y);
        if (m_focus)
        {
            auto parent = m_focus;
            while (parent->Parent())
                parent = parent->Parent();
            MoveToFront(parent);
        }

        if (m_cursor_widget)
        {
            ActionParameter1<Event> p(e);
            m_cursor_widget->MousePress(p);
        }
    }

    void Manager::OnMouseRelease(const Event &e)
    {
        m_left_down = (e.key == HGEK_LBUTTON ? false : m_left_down);
        m_right_down = (e.key == HGEK_RBUTTON ? false : m_right_down);
        m_middle_down = (e.key == HGEK_MBUTTON ? false : m_middle_down);

        if (m_cursor_widget)
        {
            ActionParameter1<Event> p(e);
            m_cursor_widget->MouseRelease(p);
        }
    }

    void Manager::OnMouseWheel(const Event &e)
    {
        if (m_cursor_widget)
        {
            ActionParameter1<Event> p(e);
            m_cursor_widget->MouseWheel(p);
        }
    }

    void Manager::OnKeyDown(const Event &e)
    {
        if (m_focus)
        {
            ActionParameter1<Event> p(e);
            m_focus->KeyDown(p);
        }
    }

    void Manager::OnKeyUp(const Event &e)
    {
        if (m_focus)
        {
            ActionParameter1<Event> p(e);
            m_focus->KeyUp(p);
        }
    }

    bool Manager::GetKeyState(int key)
    {
        return m_hge->Input_GetKeyState(key);
    }

    bool Manager::GetMouseState(int key)
    {
        return m_hge->Input_GetKeyState(key);
    }

    void Manager::Add(Widget* value)
    {
        auto it = std::find(m_children.begin(), m_children.end(), value);
        if (it != m_children.end())
            return;
        m_children.push_back(value);
        value->SetManager(this);
    }

    void Manager::Remove(Widget* value)
    {
        auto it = std::find(m_children.begin(), m_children.end(), value);
        if (it == m_children.end())
            return;
        m_children.erase(it);
    }

    Widget* Manager::GetWidget(int x, int y)
    {
        for (Widget* w : m_children)
        {
            Widget* res = w->GetWidget(x - w->LocalX(), y - w->LocalY());
            if (res)
                return res;
        }
        return nullptr;
    }

    void Manager::MoveToFront(Widget *widget)
    {
        if (m_children.front() == widget)
            return;

        auto it = std::find(m_children.begin(), m_children.end(), widget);
        if (it == m_children.end())
            m_children.push_front(widget);
        m_children.erase(it);
        m_children.push_front(widget);
    }

    void Manager::Repaint()
    {
        for (auto  it = m_children.rbegin(); it != m_children.rend(); ++it)
        {
            Widget* w = *it;
            w->Repaint(m_render);
        }
        m_render->DrawQuad(m_x, m_y, 5, 5);
    }

    int Manager::GetWindowWidth()
    {
        return m_hge->System_GetState(HGE_SCREENWIDTH);
    }

    int Manager::GetWindowHeight()
    {
        return m_hge->System_GetState(HGE_SCREENHEIGHT);
    }
}
