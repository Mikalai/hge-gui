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

    class Manager;

    class HgeRender : public RenderAdapter
    {
    public:
        HgeRender(Manager* hge);
        virtual ~HgeRender();
        void Translate(float dx, float dy) override;
        void SetPosition(float x, float y) override;
        void Rotate(float da) override;
        void SetRotation(float a) override;
        void DrawPoint(float x, float y) override;
        void DrawLine(float x1, float y1, float x2, float y2) override;
        void DrawQuad(float x, float y, float width, float height) override;
        void DrawTextLine(float x, float y, const std::string& s) override;
        void SetColor(float r, float g, float b) override;
        void SetAlpha(float a) override;
        void PushSate() override;
        void PopState() override;        

    private:
        Manager* m_manager;
        float m_x = 0;
        float m_y = 0;
        std::stack<RenderState*> m_state;
        /// Current state.
        RenderState* cs = nullptr;
    };
}

#endif // HGE_RENDER_H
