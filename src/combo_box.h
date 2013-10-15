#ifndef COMBO_BOX_H
#define COMBO_BOX_H

#include <vector>
#include <string>
#include "widget.h"

namespace Gui
{
    class TextLine;
    class ListBox;
    class Button;

    class ComboBox : public Widget
    {
    public:
        ComboBox(float x, float y, float width, float height, Widget* parent);
        virtual ~ComboBox();
        void AddItems(const std::vector<std::string>& value);

        Signal SigValueChanged;

    protected:
        void OnResize(float x, float y, float width, float height) override;
        void Update();

        void ItemSelected(int value);
        void ShowList();

    private:
        bool m_need_update = true;
        Button* m_button;
        ListBox* m_list_box;
        TextLine* m_line_edit;
    };
}

#endif // COMBO_BOX_H
