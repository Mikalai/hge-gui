#ifndef ANIMATION_H
#define ANIMATION_H

#include <array>
#include "desktop_adapter.h"

namespace Gui
{
    class Widget;

    static const float g_anim = 0.1f;

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
    static const int MouseLeftDownAnimation = 4;
    static const int MouseLeftUpAnimation = 5;

    class WidgetAnimation : public Animation
    {
    public:
        WidgetAnimation(Widget* w);
        virtual ~WidgetAnimation() {}

        void Update(float dt) override;
        bool Active() const override;
        virtual void PlayFocused();
        virtual void PlayMouseEnter(const Event& e);
        virtual void PlayMouseLeave(const Event& e);
        virtual void PlayUnfocused();
        virtual void PlayMouseLeftDown(const Event& e) {}
        virtual void PlayMouseLeftUp(const Event& e) {}
    protected:

        AnimationState m_animation[6];
        Widget* m_widget;
    };
}

#endif // ANIMATION_H
