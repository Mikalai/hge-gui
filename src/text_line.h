#ifndef TEXT_LINE_H
#define TEXT_LINE_H

#include <string>
#include <vector>
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

        bool Editable() const;
        void Editable(bool value);

    protected:

        void OnRepaint(RenderAdapter *r) override;
        void OnKeyDown(const Event &e) override;
        void OnMousePress(const Event &e) override;

        void Update();
    private:
        bool m_editable = true;
        bool m_need_update = true;
        std::vector<float> m_width_cache;
        int m_cursor_position = -1;
        int m_visible_offset = 0;
        int m_visible_count = 0;
        std::string m_text;
    };
}

#endif // TEXT_LINE_H
