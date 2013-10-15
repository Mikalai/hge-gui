#ifndef ACTION_H
#define ACTION_H

#include <tuple>
#include <new>
#include <cstddef>

namespace Gui
{
    class ActionParameter
    {
    public:
        virtual ~ActionParameter() {}
    };

    class Action
    {
    public:
        virtual ~Action() {}
        virtual void operator() (const ActionParameter& value) = 0;
    };

    template<typename T>
    class SimpleType : public ActionParameter
    {
    public:
        SimpleType(const T& v)
            : m_value(v)
        {}

        T m_value;
    };

    template<>
    class SimpleType<void> : public ActionParameter
    {};

    template<typename T>
    class ToggleAction : public Action
    {
    public:

        ToggleAction(T* o, void(T::*m)(bool))
            : m_object(o)
            , m_method(m)
        {}

        void operator () (const ActionParameter& p) override
        {
            const SimpleType<bool>& v = dynamic_cast<const SimpleType<bool>&>(p);
            (m_object->*m_method)(v.m_value);
        }

    private:
        T* m_object;
        void (T::*m_method)(bool);
    };

    template<typename T>
    class TriggerAction : public Action
    {
    public:
        TriggerAction(T* o, void(T::*m)(void))
            : m_object(o)
            , m_method(m)
        {}

        void operator () (const ActionParameter& p) override
        {
            (m_object->*m_method)();
        }

        T* m_object;
        void (T::*m_method)(void);
    };

    template<typename T, typename V>
    class ValueChanged : public Action
    {
    public:
        ValueChanged(T* o, void (T::*m)(V))
            : m_object(o)
            , m_method(m)
        {}

        void operator () (const ActionParameter& p) override
        {
            const SimpleType<V>& v = dynamic_cast<const SimpleType<V>&>(p);
            if (m_object && m_method)
                (m_object->*m_method)(v.m_value);
        }

    private:
        T* m_object;
        void (T::*m_method)(V);
    };
}

#endif // ACTION_H
