#ifndef ANIMATION_H
#define ANIMATION_H

#include <array>
#include "desktop_adapter.h"

namespace Gui
{
    class Widget;

    struct AnimationState
    {
        bool active = false;
        bool loop = false;
        float duration = 0.1f;
        float time = 0.0f;
        std::array<float, 4> start;
        std::array<float, 4> end;
        std::array<float, 4> current;

        void Update(float dt);
        float Value() { return time / duration; }
    };

    class Animation
    {
    public:
        virtual ~Animation() {}
        virtual void Update(float dt) = 0;
        virtual bool Active() const = 0;
    };

    static const int FocusedAnimation = 0;
    static const int MouseEnterAnimation = 1;
    static const int MouseLeaveAnimation = 2;
    static const int UnfocusedAnimation = 3;

    class WidgetAnimation : public Animation
    {
    public:
        WidgetAnimation(Widget* w);
        virtual ~WidgetAnimation() {}

        virtual void Update(float dt);
        virtual bool Active() const;
        void PlayFocused(Event e);
        void PlayMouseEnter(Event e);
        void PlayMouseLeave(Event e);
        void PlayUnfocused(Event e);
    private:

        AnimationState m_animation[4];

        Widget* m_widget;
    };
}

#endif // ANIMATION_H
