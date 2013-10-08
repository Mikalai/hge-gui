#include <algorithm>
#include "render_adapter.h"
#include "action.h"
#include "widget.h"
#include "desktop_adapter.h"

namespace Gui
{
    Widget::Widget(float x, float y, float width, float height, Widget *parent)
        : m_x(x)
        , m_y(y)
        , m_width(width)
        , m_height(height)
        , m_parent(parent)
    {
        if (m_parent)
            m_parent->AddWidget(this);
    }

    Widget::~Widget()
    {
        if (m_parent)
            m_parent->RemoveWidget(this);

        while (!m_children.empty())
        {
            auto w = m_children.back();
            m_children.pop_back();
            delete w;
        }
    }

    void Widget::Invalidate()
    {
        m_need_repaint = true;
    }

    void Widget::Repaint(RenderAdapter *r)
    {
        if (!m_need_repaint)
            return;
        r->PushSate();
        r->SetColor(m_back_color[0], m_back_color[1], m_back_color[2]);
        r->SetAlpha(m_back_color[3]);
        r->DrawQuad(m_x, m_y, m_width, m_height);
        r->Translate(m_x, m_y);
        for (auto child : m_children)
        {
            child->Repaint(r);
        }
        r->PopState();
    }

    int Widget::Width() const
    {
        return m_width;
    }

    int Widget::Height() const
    {
        return m_height;
    }

    void Widget::Width(int value)
    {
        m_width = value;
    }

    void Widget::Height(int value)
    {
        m_height = value;
    }

    int Widget::LocalX() const
    {
        return m_x;
    }

    int Widget::LocalY() const
    {
        return m_y;
    }

    void Widget::LocalX(int value)
    {
        m_x = value;
    }

    void Widget::LocalY(int value)
    {
        m_y = value;
    }

    int Widget::GlobalX() const
    {
        if (m_parent)
            return m_parent->GlobalX() + m_x;
        return m_x;
    }

    int Widget::GlobalY() const
    {
        if (m_parent)
            return m_parent->GlobalY() + m_y;
        return m_y;
    }

    /// Set position relative to parent.
    void Widget::SetLocalPosition(int x, int y)
    {
        float w = (m_parent ? m_parent->Width() : m_manager->GetWindowWidth()) - m_width;
        float h = (m_parent ? m_parent->Height() : m_manager->GetWindowHeight()) - m_height;
        m_x = std::min(std::max((float)x, 0.0f), w);
        m_y = std::min(std::max((float)y, 0.0f), h);
    }

    Widget* Widget::GetWidget(int x, int y)
    {
        if (x < 0 || x > m_width)
            return nullptr;
        if (y < 0 || y > m_height)
            return nullptr;
        Widget* res = nullptr;
        for (Widget* child : m_children)
        {
            res = child->GetWidget(x - child->LocalX(), y - child->LocalY());
            if (res)
                return res;
        }
        return this;
    }

    void Widget::SetManager(DesktopAdapter* value)
    {
        m_manager = value;
    }

    DesktopAdapter* Widget::GetManager() const
    {
        return m_manager;
    }

    void Widget::SetBackgroundColor(float r, float g, float b, float a)
    {
        m_back_color[0] = r;
        m_back_color[1] = g;
        m_back_color[2] = b;
        m_back_color[3] = a;
    }

    void Widget::SetFontColor(float r, float g, float b, float a)
    {
        m_font_color[0] = r;
        m_font_color[1] = g;
        m_font_color[2] = b;
        m_font_color[3] = a;
    }

    void Widget::AddWidget(Widget* value)
    {
        auto it = std::find(m_children.begin(), m_children.end(), value);
        if (it != m_children.end())
            return;
        m_children.push_back(value);
        value->SetManager(GetManager());
    }

    void Widget::RemoveWidget(Widget* value)
    {
        auto it = std::find(m_children.begin(), m_children.end(), value);
        if (it == m_children.end())
            return;
        m_children.erase(it);
    }
}

