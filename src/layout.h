#ifndef LAYOUT_H
#define LAYOUT_H

#include <vector>

namespace Gui
{
    class Widget;

    class Layout
    {
    public:
        Layout();
        virtual ~Layout();
        virtual void Update(float x, float y, float width, float height) = 0;

        void AddWidget(Widget* value);
        void RemoveWidget(Widget* value);

        std::vector<Widget*> Children() { return m_children; }

    protected:
        std::vector<Widget*> m_children;
        float m_x, m_y, m_width, m_height;
    };
}

#endif // LAYOUT_H
