#include "widget.h"
#include "verticallayout.h"

namespace Gui
{
    VerticalLayout::VerticalLayout()
    {
    }

    void VerticalLayout::Update(float x, float y, float width, float height)
    {
        size_t count = m_children.size();
        float new_height = height / count;
        for (int i = 0; i < count; ++i)
        {
            m_children[i]->Resize(5, i*new_height + 5, width-10, new_height-10);
        }
    }
}
