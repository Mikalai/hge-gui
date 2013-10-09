#ifndef DESKTOP_ADAPTER_H
#define DESKTOP_ADAPTER_H

#include <hge.h>

namespace Gui
{
    typedef hgeInputEvent Event;
    class Animation;

    class DesktopAdapter
    {
    public:
        virtual ~DesktopAdapter() {}

        virtual void OnMouseMove(const Event& e) = 0;
        virtual void OnMousePress(const Event& e) = 0;
        virtual void OnMouseRelease(const Event& e) = 0;
        virtual void OnMouseWheel(const Event& e) = 0;
        virtual void OnKeyDown(const Event& e) = 0;
        virtual void OnKeyUp(const Event& e) = 0;
        virtual bool GetKeyState(int key) = 0;
        virtual bool GetMouseState(int key) = 0;
        virtual int GetWindowWidth() = 0;
        virtual int GetWindowHeight() = 0;
        virtual void AddAnimation(Animation* value) = 0;
        virtual void RemoveAnimation(Animation* value) = 0;
    };
}

#endif // DESKTOP_ADAPTER_H
