#ifndef ITEM_H
#define ITEM_H

#include <string>

namespace Gui
{
    struct Item
    {
        Item(const std::string& _name, void* _data = nullptr)
            : name(_name)
            , data(_data)
        {}

        const std::string name;
        void* data;
    };
}
#endif // ITEM_H
