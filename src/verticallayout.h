#ifndef VERTICALLAYOUT_H
#define VERTICALLAYOUT_H

#include "layout.h"

namespace Gui
{
    class VerticalLayout : public Layout
    {
    public:
        VerticalLayout();

        void Update(float x, float y, float width, float height) override;
    };
}

#endif // VERTICALLAYOUT_H
