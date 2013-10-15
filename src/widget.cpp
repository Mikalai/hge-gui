#include <algorithm>
#include "layout.h"
#include "render_adapter.h"
#include "action.h"
#include "widget.h"
#include "desktop_adapter.h"
#include "widget_animation.h"

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
        SetAnimation(new WidgetAnimation(this));
    }

    Widget::~Widget()
    {
        delete m_animation;
        m_animation = nullptr;

        if (m_layout)
            delete m_layout;

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
        Resize(m_x, m_y, value, m_height);
    }

    void Widget::Height(int value)
    {        
        Resize(m_x, m_y, m_width, value);
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
        Resize(value, m_y, m_width, m_height);
    }

    void Widget::LocalY(int value)
    {        
        Resize(m_x, value, m_width, m_height);
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
        x = std::min(std::max((float)x, 0.0f), w);
        y = std::min(std::max((float)y, 0.0f), h);
        Resize(x, y, m_width, m_height);
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
        if (m_animation)
        {
            if (m_manager)
                m_manager->RemoveAnimation(m_animation);
            if (value)
                value->AddAnimation(m_animation);
        }
        m_manager = value;
        if (m_manager)
        {            
            for (auto child : m_children)
                child->SetManager(value);
        }
    }

    DesktopAdapter* Widget::GetManager() const
    {
        return m_manager;
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

    void Widget::OnMouseMove(const Event& e)
    {

    }

    void Widget::OnMousePress(const Event& e)
    {

    }

    void Widget::OnMouseRelease(const Event& e)
    {
    }

    void Widget::OnKeyDown(const Event& e)
    {
    }

    void Widget::OnKeyUp(const Event& e)
    {

    }

    void Widget::OnMouseWheel(const Event& e)
    {

    }

    void Widget::OnMouseHoover(const Event& e)
    {
    }

    void Widget::OnResize(float xx, float yy, float width, float height)
    {
        m_width = width;
        m_height = height;
        m_x = xx;
        m_y = yy;

        if (m_layout)
        {
            m_layout->Update(m_x, m_y, width, height);
        }
    }

    void Widget::OnMouseEnter(const Event &e)
    {

    }

    void Widget::OnMouseLeave(const Event &e)
    {

    }

    void Widget::OnFocused(const Event &e)
    {

    }

    void Widget::OnUnfocused(const Event &e)
    {

    }

    void Widget::OnRepaint(RenderAdapter *r)
    {
        if (!m_need_repaint || !Visible())
            return;

        r->PushSate();
        if (m_style.back_color[3] > 0.0f)
        {
            r->SetColor(m_style.back_color[0], m_style.back_color[1], m_style.back_color[2]);
            r->SetAlpha(m_style.back_color[3]);
            r->DrawQuad(m_x, m_y, m_width, m_height);
        }
        r->Translate(m_x, m_y);
        for (auto child : m_children)
        {
            child->Repaint(r);
        }

        if (m_layout)
        {
            for (auto child : m_layout->Children())
            {
                if (child->Visible())
                    child->Repaint(r);
            }
        }
        r->PopState();
    }

    void Widget::OnUpdate(float dt)
    {

    }

    void Widget::OnClicked(const Event &e)
    {}

    void Widget::MouseMove(const Event& e)
    {
        SigMouseMove(Event(e));
        OnMouseMove(e);
    }

    void Widget::MousePress(const Event& e)
    {
        if (m_animation)
        {
            if (e.e.key == HGEK_LBUTTON)
                m_animation->PlayMouseLeftDown(e);
        }

        SigMousePress(Event(e));
        OnMousePress(e);
    }

    void Widget::MouseRelease(const Event& e)
    {
        if (m_animation)
        {
            if (e.e.key == HGEK_LBUTTON)
                m_animation->PlayMouseLeftUp(e);
        }

        SigMouseRelease(Event(e));
        OnMouseRelease(e);
    }

    void Widget::KeyDown(const Event& e)
    {
        SigKeyDown(Event(e));
        OnKeyDown(e);
    }

    void Widget::KeyUp(const Event& e)
    {
        SigKeyUp(Event(e));
        OnKeyUp(e);
    }

    void Widget::MouseWheel(const Event& e)
    {
        SigMouseWheel(Event(e));
        OnMouseWheel(e);
    }

    void Widget::MouseHoover(const Event& e)
    {
        SigMouseHoover(Event(e));
        OnMouseHoover(e);
    }

    void Widget::MouseEnter(const Event& e)
    {
        if (m_animation)
            m_animation->PlayMouseEnter(e);
        m_mouse_over = true;
        SigMouseEnter(Event(e));
        OnMouseEnter(e);
    }

    void Widget::MouseLeave(const Event& e)
    {
        if (m_animation)
            m_animation->PlayMouseLeave(e);
        m_mouse_over = false;        
        SigMouseLeave(Event(e));
        OnMouseLeave(e);
    }

    void Widget::Focused(const Event& e)
    {
        if (m_animation)
            m_animation->PlayFocused();
        SigFocused(Event(e));
        m_focused = true;
        OnFocused(e);
    }

    void Widget::Repaint(RenderAdapter *r)
    {
        OnRepaint(r);
    }

    void Widget::Update(float dt)
    {
        OnUpdate(dt);
    }

    void Widget::Unfocused(const Event &e)
    {
        if (m_animation)
            m_animation->PlayUnfocused();
        m_focused = false;
        SigUnfocused(Event(e));
        OnUnfocused(e);
    }

    void Widget::Resize(float x, float y, float width, float height)
    {
        if (x == m_x && y == m_y && m_width == width && m_height == height)
            return;

        SigResize(ResizeEvent(x, y, width, height));
        OnResize(x, y, width, height);
    }

    bool Widget::IsFocused() const
    {        
        return m_focused;
    }

    bool Widget::IsMouseOver() const
    {
        return m_mouse_over;
    }

    void Widget::MouseClicked(const Event& e)
    {        
        SigToggle(Event(e));
        OnClicked(e);
    }

    void Widget::SetAnimation(WidgetAnimation* animation)
    {
        if (m_animation)
        {
            if (m_manager)
                m_manager->RemoveAnimation(m_animation);
            delete m_animation;
        }
        m_animation = animation;
        if (m_manager)
            m_manager->AddAnimation(m_animation);
    }

    WidgetAnimation* Widget::GetAnimation() const
    {
        return m_animation;
    }

    void Widget::SetLayout(Layout* value)
    {
        if (m_layout)
            delete m_layout;
        m_layout = value;
        if (m_layout)
            m_layout->Update(m_x, m_y, m_width, m_height);
    }

    Layout* Widget::GetLayout() const
    {
        return m_layout;
    }
}
