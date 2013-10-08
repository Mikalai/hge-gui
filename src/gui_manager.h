#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include <list>
#include "desktop_adapter.h"

class HGE;

namespace Gui
{
    class Widget;
    class HgeRender;

    class Manager : public DesktopAdapter
    {
    public:
        Manager(HGE* hge);
        virtual ~Manager();

        virtual void OnMouseMove(const Event& e) override;
        virtual void OnMousePress(const Event& e) override;
        virtual void OnMouseRelease(const Event& e) override;
        virtual void OnMouseWheel(const Event& e) override;
        virtual void OnKeyDown(const Event& e) override;
        virtual void OnKeyUp(const Event& e) override;
        bool GetKeyState(int key) override;
        bool GetMouseState(int key) override;
        int GetWindowWidth() override;
        int GetWindowHeight() override;

        void Add(Widget* value);
        void Remove(Widget* value);
        void Repaint();

    private:
        Widget* GetWidget(int x, int y);
        void MoveToFront(Widget* widget);

    private:
        int m_prev_x = 0;
        int m_prev_y = 0;
        int m_x = 0;
        int m_y = 0;
        bool m_left_down = false;
        bool m_right_down = false;
        bool m_middle_down = false;
        HGE* m_hge = nullptr;
        HgeRender* m_render = nullptr;
        Widget* m_focus = nullptr;
        /// Widget on wich mouse cursor is currently located
        Widget* m_cursor_widget = nullptr;
        std::list<Widget*> m_children;
    };
}

#endif // GUI_MANAGER_H
