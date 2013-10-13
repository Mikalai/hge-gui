#include <hge.h>
#include <hgefont.h>
#include "hge_render.h"

namespace Gui
{

    DWORD FloatToDword(float r, float g, float b, float a)
    {
        DWORD rr = (DWORD)(r * 255.0f);
        DWORD gg = (DWORD)(g * 255.0f);
        DWORD bb = (DWORD)(b * 255.0f);
        DWORD aa = (DWORD)(a * 255.0f);
        DWORD c = aa << 24 | rr << 16 | gg << 8 | bb;
        return c;
    }

    HgeRender::HgeRender(HGE *hge)
        : m_hge(hge)
    {
        cs = new RenderState;
        m_font = new hgeFont("../data/font1.fnt");
    }

    HgeRender::~HgeRender()
    {
        if (m_font)
        {
            delete m_font;
            m_font = nullptr;
        }
    }

    void HgeRender::DrawQuad(float x, float y, float width, float height)
    {
        hgeQuad quad;
        quad.v[0].x = x + cs->x;
        quad.v[0].y = y + cs->y;
        quad.v[1].x = x + width + cs->x;
        quad.v[1].y = y + cs->y;
        quad.v[2].x = x + width + cs->x;
        quad.v[2].y = y + height + cs->y;
        quad.v[3].x = x + cs->x;
        quad.v[3].y = y + height + cs->y;

        for( int i = 0; i < 4; i++ )
        {
            quad.v[i].z = 0.5f;
            quad.v[i].col = FloatToDword(cs->r, cs->g, cs->b, cs->a);
        }

        quad.tex = 0;
        quad.blend = BLEND_DEFAULT;
        m_hge->Gfx_RenderQuad(&quad);
    }

    void HgeRender::PushSate()
    {
        m_state.push(cs);
        cs = new RenderState(*cs);
    }

    void HgeRender::PopState()
    {
        if (m_state.empty())
            return;
        delete cs;
        cs = m_state.top();
        m_state.pop();
    }

    void HgeRender::Translate(float dx, float dy)
    {
        cs->x += dx;
        cs->y += dy;
    }

    void HgeRender::SetPosition(float x, float y)
    {
        cs->x = x;
        cs->y = y;
    }

    void HgeRender::Rotate(float da)
    {
        cs->angle += da;
    }

    void HgeRender::SetRotation(float a)
    {
        cs->angle = a;
    }

    void HgeRender::DrawPoint(float x, float y)
    {
        //  TODO: Lock texture for more efficiency
        DrawQuad(x, y, 1, 1);
    }

    void HgeRender::DrawLine(float x1, float y1, float x2, float y2)
    {
        m_hge->Gfx_RenderLine(x1, y1, x2, y2, FloatToDword(cs->r, cs->g, cs->b, cs->a));
    }

    void HgeRender::DrawTextLine(float x, float y, const std::string& s)
    {
        if (m_font)
        {
            m_font->SetColor(FloatToDword(cs->r, cs->g, cs->b, cs->a));
            m_font->SetScale(0.8);
            m_font->Render(x, y, HGETEXT_LEFT, s.c_str());            
        }
    }

    void HgeRender::SetColor(float r, float g, float b)
    {
        cs->r = r; cs->g = g; cs->b = b;
    }

    void HgeRender::SetAlpha(float a)
    {
        cs->a = a;
    }

    void HgeRender::SetFont(const std::string &name)
    {
        if (m_font)
            delete m_font;
        m_font = new hgeFont(name.c_str());
    }

    float HgeRender::GetCharacterWidth(char value)
    {
        if (!m_font)
            return 0;
        char chr[] = {value, 0};
        return m_font->GetStringWidth(chr);
    }

    float HgeRender::GetCharacterHeight(char)
    {
        if (!m_font)
            return 0;
        return m_font->GetHeight() * m_font->GetScale();
    }
}
