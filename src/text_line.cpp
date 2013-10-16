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
        Moveable(false);
        Fixed(true);
    }

    TextLine::~TextLine()
    {}


    void TextLine::Text(const std::string &value)
    {
        m_text = value;
        m_cursor_position = m_text.empty() ? -1 : 0;
        Update();
    }

    const std::string& TextLine::Text() const
    {
        return m_text;
    }


    void TextLine::Update()
    {
        //  determine neccessary width
        m_width_cache.resize(m_text.size());
        //  fill width array
        for (int index = 0, max_i = m_text.size(); index != max_i; ++index)
        {
            m_width_cache[index] = GetManager()->GetFont()->GetCharacterWidth(m_text[index]);
        }

        //  find visible characters count
        float width = 0;
        m_visible_count = 0;  // visible count
        int max_i = m_text.size();
        for (int index = m_visible_offset; index != max_i; ++index)
        {
            if (width + m_width_cache[index] > Width())
                break;
            width += m_width_cache[index];
            m_visible_count++;
        }

        //  setup visible offset to make cursor always visible
        if (m_visible_offset > m_cursor_position)
        {
            m_visible_offset = m_cursor_position;
        }

        if (m_visible_offset + m_visible_count < m_cursor_position)
        {
            m_visible_offset = m_cursor_position - m_visible_count;
        }

        //  clip offset
        m_visible_offset = std::max(std::min(m_visible_offset, (int)m_text.size()-m_visible_count), 0);

        m_need_update = false;
    }

    void TextLine::OnRepaint(RenderAdapter *r)
    {        
        Widget::OnRepaint(r);

        r->PushSate();
        r->Translate(LocalX(), LocalY());
        r->SetColor(GetStyle().font_color[0], GetStyle().font_color[1], GetStyle().font_color[2]);
        r->SetAlpha(GetStyle().font_color[3]);

        if (m_need_update)
            Update();

        r->DrawTextLine(0, 0, m_text.substr(m_visible_offset, m_visible_count));

        //  find cursor geometry
        if (m_editable && IsFocused())
        {
            float x = 0;
            for (int index = m_visible_offset; index < m_cursor_position; ++index)
            {
                x += m_width_cache[index];
            }
            r->DrawLine(x, 1, x, GetManager()->GetFont()->GetCharacterHeight('I') - 1);
        }
        r->PopState();
    }

    void TextLine::OnKeyDown(const Event &e)
    {
        if (!m_editable)
            return;

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
        Update();
    }

    void TextLine::OnMousePress(const Event &e)
    {
        int x = e.e.x - GlobalX();
        for (int i = m_visible_offset, max_i = m_text.size(); i < max_i; ++i)
        {
            x -= GetManager()->GetFont()->GetCharacterWidth(m_text[i]);
            if (x < 0)
            {
                m_cursor_position = i;
                break;
            }
        }
        if (x > 0)
            m_cursor_position = m_text.size();

        Update();
    }

    bool TextLine::Editable() const
    {
        return m_editable;
    }

    void TextLine::Editable(bool value)
    {
        m_editable = value;
    }
}
