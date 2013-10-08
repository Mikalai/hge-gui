#ifndef HGE_RENDER_H
#define HGE_RENDER_H

#include <stack>
#include "render_adapter.h"

class HGE;
class hgeFont;

namespace Gui
{
    struct RenderState
    {
        float x = 0;
        float y = 0;
        float r = 1;
        float g = 1;
        float b = 1;
        float a = 1;
        float angle = 0;
    };

    class HgeRender : public RenderAdapter
    {
    public:
        HgeRender(HGE* hge);
        virtual ~HgeRender();
        virtual void Translate(float dx, float dy);
        virtual void SetPosition(float x, float y);
        virtual void Rotate(float da);
        virtual void SetRotation(float a);
        virtual void DrawPoint(float x, float y);
        virtual void DrawQuad(float x, float y, float width, float height);
        virtual void DrawText(float x, float y, const std::string& s);
        virtual void SetColor(float r, float g, float b);
        virtual void SetAlpha(float a);
        virtual void PushSate();
        virtual void PopState();
        virtual void SetFont(const std::string& name);


    private:
        HGE* m_hge = nullptr;
        hgeFont* m_font = nullptr;
        float m_x = 0;
        float m_y = 0;
        std::stack<RenderState*> m_state;
        /// Current state.
        RenderState* cs = nullptr;
    };
}

#endif // HGE_RENDER_H
