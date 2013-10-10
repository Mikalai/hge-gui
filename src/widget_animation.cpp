#include "action.h"
#include "widget.h"
#include "widget_animation.h"

namespace Gui
{    
    void LinearInterpolate(const std::array<float, 4>& a, const std::array<float, 4>&b, float t, std::array<float, 4>& out)
    {
        float p1 = b[0] * t + a[0] * (1 - t);
        float p2 = b[1] * t + a[1] * (1 - t);
        float p3 = b[2] * t + a[2] * (1 - t);
        float p4 = b[3] * t + a[3] * (1 - t);
        out[0] = p1;
        out[1] = p2;
        out[2] = p3;
        out[3] = p4;
    }

    WidgetAnimation::WidgetAnimation(Widget *w)
        : m_widget(w)
    {    
    }

    void WidgetAnimation::Update(float dt)
    {
        if (!Active())
            return;
        for (int i = 0; i != sizeof(m_animation)/sizeof(m_animation[0]); ++i)
        {
            if (m_animation[i].active)
            {
                Style& style = m_widget->GetStyle();
                style.back_color = m_animation[i].current;
                m_animation[i].Update(dt);
            }
        }
    }

    void WidgetAnimation::PlayMouseEnter(const Event& e)
    {
        if (m_widget->IsFocused())
            return;
        m_animation[MouseEnterAnimation].active = true;
        m_animation[MouseEnterAnimation].duration = g_anim;
        m_animation[MouseEnterAnimation].loop = false;
        m_animation[MouseEnterAnimation].start = m_widget->GetStyle().back_color;
        m_animation[MouseEnterAnimation].end = m_widget->GetStyle().back_color_moused;
    }

    void WidgetAnimation::PlayMouseLeave(const Event& e)
    {        
        m_animation[MouseLeaveAnimation].active = true;
        m_animation[MouseLeaveAnimation].duration = g_anim;
        m_animation[MouseLeaveAnimation].loop = false;
        m_animation[MouseLeaveAnimation].start = m_widget->GetStyle().back_color;
        if (m_widget->IsFocused())
            m_animation[MouseLeaveAnimation].end = m_widget->GetStyle().back_color_focused;
        else
            m_animation[MouseLeaveAnimation].end = m_widget->GetStyle().back_color_unfocused;
    }

    void WidgetAnimation::PlayFocused()
    {
        m_animation[FocusedAnimation].active = true;
        m_animation[FocusedAnimation].duration = g_anim;
        m_animation[FocusedAnimation].loop = false;
        m_animation[FocusedAnimation].start = m_widget->GetStyle().back_color;
        m_animation[FocusedAnimation].end = m_widget->GetStyle().back_color_focused;
    }

    void WidgetAnimation::PlayUnfocused()
    {
        m_animation[UnfocusedAnimation].active = true;
        m_animation[UnfocusedAnimation].duration = g_anim;
        m_animation[UnfocusedAnimation].loop = false;
        m_animation[UnfocusedAnimation].start = m_widget->GetStyle().back_color;
        if (m_widget->IsMouseOver())
            m_animation[UnfocusedAnimation].end = m_widget->GetStyle().back_color_moused;
        else
            m_animation[UnfocusedAnimation].end = m_widget->GetStyle().back_color_unfocused;
    }

    bool WidgetAnimation::Active() const
    {
        bool flag = false;
        for (int i = 0; i != sizeof(m_animation)/sizeof(m_animation[0]); ++i)
        {
            flag |= m_animation[i].active;
        }
        return flag;
    }

    void AnimationState::Update(float dt)
    {
        if (!active)
            return;

        time += dt;
        if (time > duration)
        {
            if (loop)
                time = 0;
            else
            {
                time = 0;
                active = false;
            }
        }

        LinearInterpolate(start, end, Value(), current);
    }
}
