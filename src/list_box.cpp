#include "render_adapter.h"
#include "scrollbar.h"
#include "desktop_adapter.h"
#include "list_box.h"
#include "widget_animation.h"

namespace Gui
{
    float delta = 0.0f;

    struct ListItemScroll : public Action
    {
        ListItemScroll(ListBox* box)
            : m_box(box)
        {}

        void operator () (const ActionParameter& pp)
        {
            const ScrollBarValueChanged& p = dynamic_cast<const ScrollBarValueChanged&>(pp);
            m_box->SetStartItem(p.value);
        }

        ListBox* m_box;
    };

    ListBox::ListBox(float x, float y, float width, float height, Widget *parent)
        : Widget(x, y, width, height, parent)
    {
        m_scroll = new ScrollBar(width - 5, 0, 5, height, this);
        m_scroll->Visible(false);
        m_scroll->SigValueChanged.Connect(new ListItemScroll(this));
        m_scroll->Fixed(true);
        m_scroll->Moveable(false);
        m_scroll->GetAnimation()->PlayFocused();
    }

    ListBox::~ListBox()
    {
        while (!m_items.empty())
        {
            delete m_items.back();
            m_items.pop_back();
        }
    }

    void ListBox::OnRepaint(RenderAdapter *r)
    {
        Widget::OnRepaint(r);
        if (m_need_update)
            Update();

        float x = GlobalX();
        float y = GlobalY();

        if (m_current_item != -1 && m_current_item >= m_start_item && m_current_item < m_start_item + m_visible_count)
        {
            float h = GetManager()->GetFont()->GetCharacterHeight('I') + delta;
            int qx = x;
            int qy = y + float(m_current_item - m_start_item) * h;
            r->PushSate();
            r->SetColor(0, 0.1, 0.4);
            r->SetAlpha(0.7);
            r->DrawQuad(qx, qy, Width() - 5, h);
            r->PopState();
        }

        for (int i = m_start_item; i <= m_start_item + m_visible_count && i != m_items.size(); ++i)
        {
            float h = GetManager()->GetFont()->GetCharacterHeight('I') + delta;
            r->SetColor(0, 0, 0);
            int size = m_items[i]->name.size();
            int count = 0;
            float width = 0;
            for (int j = 0; j != size; ++j)
            {
                float delta = GetManager()->GetFont()->GetCharacterWidth(m_items[i]->name[j]);
                if (delta + width > Width() - 5)
                    break;
                count++;
                width += delta;
            }
            r->DrawTextLine(x, y, m_items[i]->name.substr(0, count));
            y += GetManager()->GetFont()->GetCharacterHeight('I') + delta;
        }
    }

    void ListBox::OnMousePress(const Event &e)
    {
        Widget::OnMousePress(e);
        float h = GetManager()->GetFont()->GetCharacterHeight('I') + delta;
        int item = m_start_item + (e.e.y - GlobalY()) / h;
        if (item == m_current_item)
            return;
        m_current_item = item;
        SigItemSelected(ListItemSelected(m_current_item));
        Update();
    }

    void ListBox::Update()
    {
        m_visible_count = Height() / (GetManager()->GetFont()->GetCharacterHeight('I') + delta);
        int count = m_items.size();
        if (count < m_visible_count)
        {
            m_scroll->Visible(false);
        }
        else
        {
            m_scroll->Visible(true);
            m_scroll->SetMinMax(0, count - m_visible_count);
        }
        m_need_update = false;
    }

    void ListBox::AddItems(const std::vector<std::string> &value)
    {
        for (auto name : value)
        {
            ListItem* b(new ListItem(name));
            m_items.push_back(b);
        }
        m_need_update = true;
    }

    void ListBox::SetStartItem(int index)
    {
        m_start_item = index;
        m_need_update = true;
    }

    void ListBox::OnMouseWheel(const Event &e)
    {
        int count = m_items.size();
        m_start_item -= e.e.wheel;
        m_start_item = std::max(std::min(m_start_item, count - m_visible_count), 0);
        m_scroll->Position(m_start_item);
        //Update();
    }
}
