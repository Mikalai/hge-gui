#include "list_box.h"
#include "pop_menu.h"

namespace Gui
{
    PopMenu::PopMenu(float x, float y, float width, float height, Widget *parent)
        : Widget(x, y, width, height, parent)
    {
        float delta = 20;
        //m_line_edit = new TextLine(0, 0, width - 10, GetManager())
        GetStyle().back_color_focused[3] = 0;
        GetStyle().back_color[3] = 0;
        GetStyle().back_color_mouse_down[3] = 0;
        GetStyle().back_color_unfocused[3] = 0;
        GetStyle().back_color_moused[3] = 0;

        m_list_box = new ListBox(0, 0, width, height, this);
        m_list_box->Visible(false);
        m_list_box->SigItemSelected.Connect(new ValueChanged<PopMenu, int>(this, &PopMenu::ItemSelected));
    }

    PopMenu::~PopMenu()
    {}

    void PopMenu::ItemSelected(int)
    {
        Visible(false);
        m_list_box->Visible(false);
        auto item = m_list_box->CurrentItem();
        SigItemSelected(SimpleType<Item*>(item));
    }

    void PopMenu::AddItems(const std::vector<std::string> &items)
    {
        m_list_box->AddItems(items);
    }

    void PopMenu::AddItem(const std::string &value, void *data)
    {
        m_list_box->AddItem(value, data);
    }

    void PopMenu::Exec()
    {
        Visible(true);
        GetManager()->SetFocused(this);
        m_list_box->Visible(true);
        m_list_box->ResetSelection();
    }

    void PopMenu::OnResize(float x, float y, float width, float height)
    {
        Widget::OnResize(x, y, width, height);
        m_list_box->Resize(0, 0, width, height);
    }

    void PopMenu::OnUnfocused(const Event &e)
    {
        Visible(false);        
    }

    void PopMenu::OnRepaint(RenderAdapter *r)
    {
        Widget::OnRepaint(r);
    }
}
