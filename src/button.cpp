#include <hge.h>
#include "render_adapter.h"
#include "action.h"
#include "widget_animation.h"
#include "button.h"

namespace Gui
{
    class ButtonAnimation : public WidgetAnimation
    {
    public:
        ButtonAnimation(Widget* w)
            : WidgetAnimation(w)
        {
        }

        void PlayMouseLeftDown(const Event& e) override
        {
            m_animation[MouseLeftDownAnimation].active = true;
            m_animation[MouseLeftDownAnimation].duration = g_anim;
            m_animation[MouseLeftDownAnimation].loop = false;
            m_animation[MouseLeftDownAnimation].start = m_widget->GetStyle().back_color;
            m_animation[MouseLeftDownAnimation].end = m_widget->GetStyle().back_color_mouse_down;
        }

        void PlayMouseLeftUp(const Event &e) override
        {
            m_animation[MouseLeftUpAnimation].active = true;
            m_animation[MouseLeftUpAnimation].duration = g_anim;
            m_animation[MouseLeftUpAnimation].loop = false;
            m_animation[MouseLeftUpAnimation].start = m_widget->GetStyle().back_color;
            if (m_widget->IsFocused())
                m_animation[MouseLeftUpAnimation].end = m_widget->GetStyle().back_color_focused;
            else if (m_widget->IsMouseOver())
                m_animation[MouseLeftUpAnimation].end = m_widget->GetStyle().back_color_moused;
            else
                m_animation[MouseLeftUpAnimation].end = m_widget->GetStyle().back_color_unfocused;
        }
    };

    Button::Button(float x, float y, float width, float height, const std::string &text, Widget *parent)
        : Widget(x, y, width, height, parent)
        , m_text(text)
    {
        SetAnimation(new ButtonAnimation(this));
    }

    void Button::OnRepaint(RenderAdapter *r)
    {
        Widget::OnRepaint(r);
        r->SetColor(GetStyle().font_color[0], GetStyle().font_color[1], GetStyle().font_color[2]);
        r->SetAlpha(GetStyle().font_color[3]);
        r->DrawTextLine(GlobalX(), GlobalY(), m_text);
    }

    void Button::OnKeyDown(const Event &e)
    {
        Widget::OnKeyDown(e);
        if (e.e.key == HGEK_ENTER || e.e.key == HGEK_SPACE)
        {
            if (GetAnimation())
                GetAnimation()->PlayMouseLeftDown(e);
        }
    }

    void Button::OnKeyUp(const Event &e)
    {
        Widget::OnKeyUp(e);
        if (e.e.key == HGEK_ENTER || e.e.key == HGEK_SPACE)
        {
            if (GetAnimation())
                GetAnimation()->PlayMouseLeftUp(e);
            SigToggle(e);
        }
    }
}
