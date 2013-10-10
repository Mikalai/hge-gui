#include "render_adapter.h"
#include "text_line.h"

namespace Gui
{
    TextLine::TextLine(float x, float y, float width, float height, const std::string &text, Widget *parent)
        : Widget(x, y, width, height, parent)
        , m_text(text)
    {
        m_cursor_position = m_text.empty() ? -1 : 0;
    }

    TextLine::~TextLine()
    {}


    void TextLine::Text(const std::string &value)
    {
        m_text = value;
        m_cursor_position = m_text.empty() ? -1 : 0;
    }

    const std::string& TextLine::Text() const
    {
        return m_text;
    }


    void TextLine::OnRepaint(RenderAdapter *r)
    {
        Widget::OnRepaint(r);
        r->SetColor(GetStyle().font_color[0], GetStyle().font_color[1], GetStyle().font_color[2]);
        r->SetAlpha(GetStyle().font_color[3]);
        r->DrawText(GlobalX(), GlobalY(), m_text);
    }

    void TextLine::OnKeyDown(const Event &e)
    {
        if (e.e.key == HGEK_BACKSPACE)
        {
            if (m_cursor_position != 0)
            {
                m_cursor_position--;
                m_text.erase(m_text.begin() + m_cursor_position, m_text.begin() + m_cursor_position+1);
            }
        }
        else if (e.e.key == HGEK_DELETE)
        {
            if (m_cursor_position < m_text.size())
            {
                m_text.erase(m_text.begin() + m_cursor_position, m_text.begin() + m_cursor_position + 1);
            }
        }
        else if (e.e.key == HGEK_LEFT)
        {
            if (m_cursor_position != 0)
                m_cursor_position--;
        }
        else if (e.e.key == HGEK_RIGHT)
        {
            if (m_cursor_position != m_text.size())
                m_cursor_position++;
        }
        else
        {
            if (e.e.chr)
            {
                m_text.insert(m_text.begin()+m_cursor_position, e.e.chr);
                m_cursor_position++;
            }
        }
    }
}
