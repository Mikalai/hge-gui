#include "action.h"
#include "text_line.h"
#include "button.h"
#include "list_box.h"
#include "combo_box.h"

namespace Gui
{
    ComboBox::ComboBox(float x, float y, float width, float height, Widget *parent)
        : Widget(x, y, width, height)
    {
        float delta = 20;
        //m_line_edit = new TextLine(0, 0, width - 10, GetManager())
        GetStyle().back_color_focused[3] = 0;
        GetStyle().back_color[3] = 0;
        GetStyle().back_color_mouse_down[3] = 0;
        GetStyle().back_color_unfocused[3] = 0;
        GetStyle().back_color_moused[3] = 0;

        m_line_edit = new TextLine(0, 0, width - delta, delta, "", this);
        m_button = new Button(width - delta, 0, delta, delta, "", this);
        m_button->Checkable(true);
        m_button->SigToggle.Connect(new TriggerAction<ComboBox>(this, &ComboBox::ShowList));
        m_list_box = new ListBox(0, delta, width, height - delta, this);
        m_list_box->Visible(false);
        m_list_box->SigItemSelected.Connect(new ValueChanged<ComboBox, int>(this, &ComboBox::ItemSelected));
    }

    ComboBox::~ComboBox()
    {}

    void ComboBox::OnResize(float x, float y, float width, float height)
    {
        Widget::OnResize(x, y, width, height);
        auto * m = GetManager();
        float w = 10;
        if (m)
            w = m->GetFont()->GetCharacterHeight('I');
        m_line_edit->Resize(0, 0, width - w, w);
        m_button->Resize(width - w, 0, w, w);
        m_line_edit->Resize(0, w, width, height);
    }

    void ComboBox::Update()
    {
        if (!m_need_update)
            return;
    }

    void ComboBox::ItemSelected(int)
    {
        m_list_box->Visible(false);
        Item* item = m_list_box->CurrentItem();
        if (item)
        {
            m_line_edit->Text(item->name);
            SigValueChanged(SimpleType<Item*>(item));
        }
        else
        {
            SigValueChanged(SimpleType<Item*>(nullptr));
        }
    }

    void ComboBox::AddItems(const std::vector<std::string> &value)
    {
        if (m_list_box)
            m_list_box->AddItems(value);
    }

    void ComboBox::ShowList()
    {
        m_list_box->Visible(!m_list_box->Visible());
    }
}
