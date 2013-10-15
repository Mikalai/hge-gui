#ifndef BUTTON_H
#define BUTTON_H

#include "widget.h"

namespace Gui
{
    class Button : public Widget
    {
    public:
        Button(float x, float y, float width, float height, const std::string& text, Widget* parent);

        void Checkable(bool value);
        bool Checkable() const;

        void Checked(bool value);
        bool Checked() const;

    protected:
        void OnRepaint(RenderAdapter *r) override;
        void OnKeyDown(const Event &e) override;
        void OnKeyUp(const Event &e) override;
    private:
        bool m_checkable = false;
        bool m_checked = false;
        std::string m_text;
    };
}

#endif // BUTTON_H
