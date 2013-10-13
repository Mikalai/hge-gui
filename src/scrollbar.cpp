#include "scrollbar.h"
#include "button.h"

namespace Gui
{
    struct ScrollAction : public Action
    {
        ScrollAction(ScrollBar* scroll, int delta)
            : m_delta(delta)
            , m_scroll(scroll)
        {}

        void operator () (const ActionParameter& p)
        {
            m_scroll->Position(m_scroll->Position() + m_delta);
        }

        int m_delta;
        ScrollBar* m_scroll;
    };

    struct ScrollUpdateAction : public Action
    {
        ScrollUpdateAction(ScrollBar* scroll)
            : m_scroll(scroll)
        {}

        void operator () (const ActionParameter& p)
        {
            if (!m_scroll->GetManager()->GetMouseState(HGEK_LBUTTON))    //  TODO: Add hge abstraction
                return;
            float y = m_scroll->ScrollButton()->LocalY();
            float off = m_scroll->UpButton()->Height();
            float h = m_scroll->Height() - 2*off;
            int value = int((y - off) / (h) * (float)(m_scroll->Max() - m_scroll->Min()));
            m_scroll->Position(value);
        }

        ScrollBar* m_scroll;
    };

    ScrollBar::ScrollBar(float x, float y, float width, float height, Widget *parent)
        : Widget(x, y, width, height, parent)
        , m_position(0)
    {
        m_up_button = new Button(0, 0, width, 10, "", this);
        m_up_button->Fixed(true);
        m_up_button->Moveable(false);
        m_down_button = new Button(0, height - 10, width, 10, "", this);
        m_down_button->Fixed(true);
        m_down_button->Moveable(false);
        m_scroll = new Button(0, 10, width, 10, "", this);

        m_up_button->SigToggle.Connect(new ScrollAction(this, -1));
        m_down_button->SigToggle.Connect(new ScrollAction(this, 1));
        m_scroll->SigMouseMove.Connect(new ScrollUpdateAction(this));
    }

    void ScrollBar::SetMinMax(int min, int max)
    {
        m_min = min;
        m_max = max;
    }

    void ScrollBar::Position(int value)
    {
        int new_pos = std::min(std::max(value, m_min), m_max);
        if (new_pos == m_position)
            return;
        m_position = new_pos;

        float off = m_up_button->Height();
        float h = Height() - 2*off;
        float scroll_pos = (m_position - m_min) / (float)(m_max - m_min) * h;
        m_scroll->Resize(0, off + scroll_pos, m_scroll->Width(), m_scroll->Height());
    }

    int ScrollBar::Position() const
    {
        return m_position;
    }

    Button* ScrollBar::UpButton() const
    {
        return m_up_button;
    }

    Button* ScrollBar::DownButton() const
    {
        return m_down_button;
    }

    Button* ScrollBar::ScrollButton() const
    {
        return m_scroll;
    }
}
