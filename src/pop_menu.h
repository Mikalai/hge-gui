#ifndef POP_MENU_H
#define POP_MENU_H

#include "item.h"
#include "widget.h"

namespace Gui
{
    class ListBox;

    class PopMenu : public Widget
    {
    public:
        PopMenu(float x, float y, float width, float height, Widget* parent);
        virtual ~PopMenu();

        void AddItems(const std::vector<std::string>& items);
        void AddItem(const std::string& value, void* data = nullptr);
        void AddItem(Item* value);
        Item* GetItem(int index);
        Signal SigItemSelected;

        void Exec();

    protected:
        void OnResize(float x, float y, float width, float height) override;
        void OnUnfocused(const Event &e);
        void OnRepaint(RenderAdapter *r) override;

    private:
        void ItemSelected(int index);
        void Update();

    private:
        ListBox* m_list_box;
    };
}

#endif // POP_MENU_H
