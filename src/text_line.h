#ifndef TEXT_LINE_H
#define TEXT_LINE_H

#include <string>
#include "widget.h"

namespace Gui
{
    class RenderAdapter;
    class TextLine : public Widget
    {
    public:
        TextLine(float x, float y, float width, float height, const std::string& text, Widget* parent);
        virtual ~TextLine();

        void Text(const std::string& value);
        const std::string& Text() const;

    protected:

        void OnRepaint(RenderAdapter *r) override;
        void OnKeyDown(const Event &e) override;
        void OnMousePress(const Event &e) override;

    private:
        int m_cursor_position = -1;
        int m_visible_offset = 0;
        std::string m_text;
        RenderAdapter* m_r = nullptr;
    };
}

#endif // TEXT_LINE_H
