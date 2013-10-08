#ifndef WIDGET_H
#define WIDGET_H

#include <vector>
#include "signal.h"
#include "desktop_adapter.h"

namespace Gui
{
    class RenderAdapter;
    class DesktopAdapter;

    class Widget
    {
    public:
        Widget(float x = 0, float y = 0, float width = 128, float height = 128, Widget* parent = nullptr);
        virtual ~Widget();

        Signal MousePress;
        Signal MouseRelease;
        Signal MouseMove;
        Signal KeyDown;
        Signal KeyUp;
        Signal MouseHoover;
        Signal Resize;
        Signal MouseWheel;

        int Width() const;
        int Height() const;
        void Width(int value);
        void Height(int value);

        int LocalX() const;
        int LocalY() const;
        int GlobalX() const;
        int GlobalY() const;
        void LocalX(int value);
        void LocalY(int value);

        /// Set position relative to parent.
        void SetLocalPosition(int x, int y);

        virtual void Repaint(RenderAdapter* r);
        void Invalidate();

        /// x and y in the current widget coordinate system
        Widget* GetWidget(int x, int y);

        void Fixed(bool value) { m_fixed = value; }
        bool Fixed() const { return m_fixed; }

        void SetManager(DesktopAdapter* value);
        DesktopAdapter* GetManager() const;

        void SetBackgroundColor(float r, float g, float b, float a);
        void SetFontColor(float r, float g, float b, float a);

        void AddWidget(Widget* w);
        void RemoveWidget(Widget* w);

        Widget* Parent() const { return m_parent; }

    private:
        DesktopAdapter* m_manager;
        float m_x = 0;
        float m_y = 0;
        float m_width = 128;
        float m_height = 128;
        float m_back_color[4] = {1, 1, 1, 1};
        float m_font_color[4] = {0, 0, 0, 1};
        bool m_fixed = false;
        Widget* m_parent = nullptr;
        bool m_need_repaint = true;
        std::vector<Widget*> m_children;
    };
}

#endif // WIDGET_H
