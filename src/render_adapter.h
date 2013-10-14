#ifndef RENDER_ADAPTER_H
#define RENDER_ADAPTER_H

#include <string>

namespace Gui
{
    class RenderAdapter
    {
    public:
        virtual ~RenderAdapter() {};
        virtual void Translate(float dx, float dy) = 0;
        virtual void SetPosition(float x, float y) = 0;
        virtual void Rotate(float da) = 0;
        virtual void SetRotation(float a) = 0;        
        virtual void DrawPoint(float x, float y) = 0;
        virtual void DrawLine(float x1, float y1, float x2, float y2) = 0;
        virtual void DrawQuad(float x, float y, float width, float height) = 0;
        virtual void DrawTextLine(float x, float y, const std::string& s) = 0;
        virtual void SetColor(float r, float g, float b) = 0;
        virtual void SetAlpha(float a) = 0;
        virtual void PushSate() = 0;
        virtual void PopState() = 0;
    };
}

#endif // RENDER_ADAPTER_H
