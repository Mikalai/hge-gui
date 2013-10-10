#ifndef TEXT_LINE_H
#define TEXT_LINE_H

#include <string>
#include "widget.h"

namespace Gui
{
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

    private:
        int m_cursor_position = -1;
        std::string m_text;
    };
}

#endif // TEXT_LINE_H
