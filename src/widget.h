#ifndef WIDGET_H
#define WIDGET_H

#include <vector>
#include "signal.h"
#include "desktop_adapter.h"
#include "style.h"

namespace Gui
{
    class WidgetAnimation;
    class RenderAdapter;
    class DesktopAdapter;

    class Widget
    {
    public:
        Widget(float x = 0, float y = 0, float width = 128, float height = 128, Widget* parent = nullptr);
        virtual ~Widget();

        Signal SigMousePress;
        Signal SigMouseRelease;
        Signal SigMouseMove;
        Signal SigKeyDown;
        Signal SigKeyUp;
        Signal SigMouseHoover;
        Signal SigResize;
        Signal SigMouseWheel;
        Signal SigMouseEnter;
        Signal SigMouseLeave;
        Signal SigFocused;
        Signal SigUnfocused;
        Signal SigToggle;

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

        void Invalidate();

        /// x and y in the current widget coordinate system
        Widget* GetWidget(int x, int y);

        void Fixed(bool value) { m_fixed = value; }
        bool Fixed() const { return m_fixed; }

        void Moveable(bool value) { m_moveable = value; }
        bool Moveable() const { return m_moveable; }

        void SetManager(DesktopAdapter* value);
        DesktopAdapter* GetManager() const;

        void AddWidget(Widget* w);
        void RemoveWidget(Widget* w);

        void SetStyle(const Style& value) { m_style = value; }
        Style& GetStyle() { return m_style; }

        Widget* Parent() const { return m_parent; }

        void MouseMove(const Event& e);
        void MousePress(const Event& e);
        void MouseRelease(const Event& e);
        void KeyDown(const Event& e);
        void KeyUp(const Event& e);
        void MouseWheel(const Event& e);
        void MouseHoover(const Event& e);
        void MouseEnter(const Event& e);
        void MouseLeave(const Event& e);
        void MouseClicked(const Event& e);
        void Focused(const Event& e);
        void Unfocused(const Event& e);
        void Repaint(RenderAdapter* r);
        void Update(float dt);
        bool IsFocused() const;
        bool IsMouseOver() const;

        void SetAnimation(WidgetAnimation* animation);
        WidgetAnimation* GetAnimation() const;

    protected:

        virtual void OnMouseMove(const Event& e);
        virtual void OnMousePress(const Event& e);
        virtual void OnMouseRelease(const Event& e);
        virtual void OnClicked(const Event& e);
        virtual void OnKeyDown(const Event& e);
        virtual void OnKeyUp(const Event& e);
        virtual void OnMouseWheel(const Event& e);
        virtual void OnMouseHoover(const Event& e);
        virtual void OnResize(const Event& e);
        virtual void OnMouseEnter(const Event& e);
        virtual void OnMouseLeave(const Event& e);
        virtual void OnFocused(const Event& e);
        virtual void OnUnfocused(const Event& e);
        virtual void OnRepaint(RenderAdapter* r);
        virtual void OnUpdate(float dt);

    private:
        DesktopAdapter* m_manager = nullptr;
        WidgetAnimation* m_animation = nullptr;
        Style m_style;
        float m_x = 0;
        float m_y = 0;
        float m_width = 128;
        float m_height = 128;
        bool m_fixed = false;
        Widget* m_parent = nullptr;
        bool m_need_repaint = true;
        bool m_focused = false;
        bool m_mouse_over = false;
        bool m_moveable = false;
        std::vector<Widget*> m_children;        
    };
}

#endif // WIDGET_H
