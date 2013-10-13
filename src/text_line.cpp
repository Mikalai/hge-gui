#include <algorithm>
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
        m_r = r;
        r->SetColor(GetStyle().font_color[0], GetStyle().font_color[1], GetStyle().font_color[2]);
        r->SetAlpha(GetStyle().font_color[3]);
        //  determine neccessary width
        std::vector<float> chr_width(m_text.size());
        //  fill width array
        for (int index = 0, max_i = m_text.size(); index != max_i; ++index)
        {
            chr_width[index] = r->GetCharacterWidth(m_text[index]);
        }

        //  find visible characters count
        float width = 0;
        int count = 0;  // visible count
        int max_i = m_text.size();
        for (int index = m_visible_offset; index != max_i; ++index)
        {
            if (width + chr_width[index] > Width())
                break;
            width += chr_width[index];
            count++;
        }

        //  setup visible offset to make cursor always visible
        if (m_visible_offset > m_cursor_position)
        {
            m_visible_offset = m_cursor_position;
        }

        if (m_visible_offset + count < m_cursor_position)
        {
            m_visible_offset = m_cursor_position - count;
        }

        //  clip offset
        m_visible_offset = std::max(std::min(m_visible_offset, (int)m_text.size()-count), 0);

        r->DrawTextLine(GlobalX(), GlobalY(), m_text.substr(m_visible_offset, count));

        //  find cursor geometry
        float x = 0;
        for (int index = m_visible_offset; index < m_cursor_position; ++index)
        {
            x += chr_width[index];
        }
        r->DrawLine(GlobalX() + x, GlobalY() + 1, GlobalX() + x, GlobalY() + r->GetCharacterHeight('I') - 1);
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

    void TextLine::OnMousePress(const Event &e)
    {
        if (!m_r)
            return;

        int x = e.e.x - GlobalX();
        for (int i = m_visible_offset, max_i = m_text.size(); i < max_i; ++i)
        {
            x -= m_r->GetCharacterWidth(m_text[i]);
            if (x < 0)
            {
                m_cursor_position = i;
                break;
            }
        }
        if (x > 0)
            m_cursor_position = m_text.size();
    }
}
