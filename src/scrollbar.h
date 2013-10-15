#ifndef SCROLLBAR_H
#define SCROLLBAR_H

#include "widget.h"

namespace Gui
{
    class Button;


    class ScrollBar : public Widget
    {
    public:
        ScrollBar(float x, float y, float width, float height, Widget* parent);
        virtual ~ScrollBar();

        void Position(int value);
        int Position() const;
        void SetMinMax(int min, int max);
        int Min() { return m_min; }
        int Max() { return m_max; }

        Button* UpButton() const;
        Button* DownButton() const;
        Button* ScrollButton() const;

        Signal SigValueChanged;

    public:
        void OnMouseWheel(const Event &e) override;

    private:
        int m_min = 0;
        int m_max = 100;
        int m_position;
        Button* m_up_button;
        Button* m_down_button;
        Button* m_scroll;
    };
}

#endif // SCROLLBAR_H
