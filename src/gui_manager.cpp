#include <iostream>
#include <algorithm>
#include <hge.h>
#include "hge_render.h"
#include "gui_manager.h"
#include "widget.h"
#include "action.h"
#include "widget_animation.h"

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
        m_x = e.e.x;
        m_y = e.e.y;

        if (m_left_down)
        {
            if (m_focus && m_focus->Moveable())
            {
                m_focus->SetLocalPosition(m_focus->LocalX() + (m_x - m_prev_x), m_focus->LocalY() + m_y - m_prev_y);
            }
        }

        auto new_widget = GetWidget(m_x, m_y);
        if (m_cursor_widget != new_widget)
        {
            if (m_cursor_widget)
                m_cursor_widget->MouseLeave(e);
            if (new_widget)
                new_widget->MouseEnter(e);
            m_cursor_widget = new_widget;
        }

        if (m_cursor_widget)
        {            
            m_cursor_widget->MouseMove(e);
        }
    }

    void Manager::OnMousePress(const Event &e)
    {
        m_left_down = (e.e.key == HGEK_LBUTTON ? true : m_left_down);
        m_right_down = (e.e.key == HGEK_RBUTTON ? true : m_right_down);
        m_middle_down = (e.e.key == HGEK_MBUTTON ? true : m_middle_down);

        auto new_focus = GetWidget(e.e.x, e.e.y);
        if (new_focus != m_focus)
        {
            if (m_focus)
                m_focus->Unfocused(e);
            if (new_focus)
                new_focus->Focused(e);
            m_focus = new_focus;
        }

        if (m_focus)
        {
            auto parent = m_focus;
            while (parent->Parent())
                parent = parent->Parent();
            MoveToFront(parent);
        }

        if (m_cursor_widget)
        {
            m_cursor_widget->MousePress(e);
        }
    }

    void Manager::OnMouseRelease(const Event &e)
    {
        m_left_down = (e.e.key == HGEK_LBUTTON ? false : m_left_down);
        m_right_down = (e.e.key == HGEK_RBUTTON ? false : m_right_down);
        m_middle_down = (e.e.key == HGEK_MBUTTON ? false : m_middle_down);

        auto w = GetWidget(e.e.x, e.e.y);
        if (w && w == m_focus)
        {
            w->MouseClicked(e);
        }

        if (m_cursor_widget)
        {            
            m_cursor_widget->MouseRelease(e);
        }
    }

    void Manager::OnMouseWheel(const Event &e)
    {
        if (m_cursor_widget)
        {            
            m_cursor_widget->MouseWheel(e);
        }
    }

    void Manager::OnKeyDown(const Event &e)
    {
        if (m_focus)
        {            
            m_focus->KeyDown(e);
        }
    }

    void Manager::OnKeyUp(const Event &e)
    {
        if (m_focus)
        {            
            m_focus->KeyUp(e);
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

    void Manager::Add(Animation *value)
    {
        auto it = std::find(m_animation.begin(), m_animation.end(), value);
        if (it != m_animation.end())
            return;
        m_animation.push_back(value);
    }

    void Manager::Remove(Animation *value)
    {
        auto it = std::find(m_animation.begin(), m_animation.end(), value);
        if (it == m_animation.end())
            return;
        m_animation.erase(it);
    }

    void Manager::AddAnimation(Animation* value)
    {
        Add(value);
    }

    void Manager::RemoveAnimation(Animation* value)
    {
        Remove(value);
    }

    void Manager::Update(float dt)
    {
        for (auto animation : m_animation)
        {
            if (animation->Active())
                animation->Update(dt);
        }
    }
}
