#ifndef STYLE_H
#define STYLE_H

#include <array>

namespace Gui
{
    class Style
    {
    public:
        std::array<float, 4> back_color_unfocused = {{0.6f, 0.6f, 0.6f, 0.8f}};
        std::array<float, 4> font_color_unfocused = {{0, 0, 0, 1}};
        std::array<float, 4> back_color_focused = {{0.9f, 0.9f, 0.9f, 1.0f}};
        std::array<float, 4> font_color_focused = {{0, 0, 0, 1}};
        std::array<float, 4> back_color_moused = {{0.7f, 0.7f, 0.7f, 1.0f}};
        std::array<float, 4> font_color_moused = {{0, 0, 0, 1}};
        std::array<float, 4> font_color = {{0, 0, 0, 1}};
        std::array<float, 4> back_color = {{0.6f, 0.6f, 0.6f, 0.8f}};
        std::array<float, 4> back_color_mouse_down = {{0.3f, 0.4f, 0.5f, 1.0f}};
    };
}

#endif // STYLE_H
