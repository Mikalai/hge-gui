#ifndef FONTADAPTER_H
#define FONTADAPTER_H

#include <string>

namespace Gui
{
    class FontAdapter
    {
    public:
        virtual ~FontAdapter() {}
        virtual void SetFont(const std::string& name) = 0;
        virtual float GetCharacterWidth(char value) = 0;
        virtual float GetCharacterHeight(char value) = 0;
    };
}
#endif // FONTADAPTER_H
