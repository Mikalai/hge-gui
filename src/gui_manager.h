#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include <list>
#include "desktop_adapter.h"

class HGE;
class hgeFont;

namespace Gui
{
    class Animation;
    class Widget;
    class HgeRender;    

    class HgeFont : public FontAdapter
    {
    public:
        HgeFont();
        virtual ~HgeFont();
        void SetFont(const std::string& name) override;
        float GetCharacterWidth(char value) override;
        float GetCharacterHeight(char value) override;

        hgeFont* m_font = nullptr;
    };

    class Manager : public DesktopAdapter
    {
    public:
        Manager(HGE* hge);
        virtual ~Manager();

        void OnMouseMove(const Event& e) override;
        void OnMousePress(const Event& e) override;
        void OnMouseRelease(const Event& e) override;
        void OnMouseWheel(const Event& e) override;
        void OnKeyDown(const Event& e) override;
        void OnKeyUp(const Event& e) override;
        bool GetKeyState(int key) override;
        bool GetMouseState(int key) override;
        int GetWindowWidth() override;
        int GetWindowHeight() override;
        void AddAnimation(Animation* value) override;
        void RemoveAnimation(Animation* value) override;
        void SetFocused(Widget *w) override;

        void Add(Widget* value);
        void Remove(Widget* value);
        void Add(Animation* value);
        void Remove(Animation* value);
        void Repaint();
        void Update(float dt);

        FontAdapter* GetFont() override;
        hgeFont* GetHgeFont();
        HGE* GetHge() { return m_hge; }

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
        HgeFont* m_font = nullptr;
        HgeRender* m_render = nullptr;
        Widget* m_focus = nullptr;
        /// Widget on wich mouse cursor is currently located
        Widget* m_cursor_widget = nullptr;
        std::list<Widget*> m_children;
        std::list<Animation*> m_animation;
    };
}

#endif // GUI_MANAGER_H
