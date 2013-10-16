#ifndef LIST_BOX_H
#define LIST_BOX_H

#include "widget.h"
#include "item.h"

namespace Gui
{
    class ScrollBar;

    class ListBox : public Widget
    {
    public:
        ListBox(float x = 0, float y = 0, float width = 128, float height = 128, Widget* parent = nullptr);
        virtual ~ListBox();

        void AddItem(Item* item);
        void RemoveItem(Item* item);
        void AddItem(const std::string& name, void* data = nullptr);
        void AddItems(const std::vector<std::string>& value);
        void SetStartItem(int index);        

        Item* CurrentItem();
        const Item* CurrentItem() const;

        void SetCurrentItem(int index);

        void ResetSelection();

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
        std::vector<Item*> m_items;
    };
}

#endif // LIST_BOX_H
