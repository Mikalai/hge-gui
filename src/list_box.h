#ifndef LIST_BOX_H
#define LIST_BOX_H

#include "widget.h"

namespace Gui
{
    class ScrollBar;

    struct ListItem
    {
        ListItem(const std::string& _name, void* _data = nullptr)
            : name(_name)
            , data(_data)
        {}

        const std::string name;
        void* data;
    };

    struct ListItemSelected : public ActionParameter
    {
        ListItemSelected(int value)
            : item(value) {}

        int item = -1;
    };

    class ListBox : public Widget
    {
    public:
        ListBox(float x = 0, float y = 0, float width = 128, float height = 128, Widget* parent = nullptr);
        virtual ~ListBox();

        void AddItem(ListItem* item);
        void RemoveItem(ListItem* item);
        void AddItem(const std::string& name, void* data = nullptr);
        void AddItems(const std::vector<std::string>& value);
        void SetStartItem(int index);

        Signal SigItemSelected;

    protected:
        void OnRepaint(RenderAdapter *r) override;
        void OnMousePress(const Event &e) override;
        void OnMouseWheel(const Event &e) override;


        void Update();
    private:
        ScrollBar* m_scroll = nullptr;
        bool m_need_update = true;
        int m_start_item = 0;
        int m_current_item = -1;
        int m_visible_count = 0;
        std::vector<ListItem*> m_items;
    };
}

#endif // LIST_BOX_H
