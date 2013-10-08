#ifndef ACTION_H
#define ACTION_H

#include <new>
#include <cstddef>

namespace Gui
{
    class ActionParameterBase
    {
    public:
        virtual ~ActionParameterBase() {}
    };

    class ActionBase
    {
    public:
        virtual ~ActionBase() {}
        virtual void operator() (const ActionParameterBase& value) = 0;
    };

    template<class T>
    class Action : public ActionBase
    {
    public:
        Action(T* o, void (T::*m)(const ActionParameterBase&))
            : m_object(o)
            , m_method(m)
        {}

        void operator() (const ActionParameterBase& value) override
        {
            if (m_object && m_method)
                (m_object->*m_method)(value);
        }

    private:
        T* m_object;
        void (T::*m_method)(const ActionParameterBase& value);
    };

    template<>
    class Action<void> : public ActionBase
    {
    public:
        Action(void (*F)(const ActionParameterBase&))
            : m_function(F)
        {}

        void operator() (const ActionParameterBase& value) override
        {
            if (m_function)
                m_function(value);
        }

    private:
        void (*m_function)(const ActionParameterBase& value);
    };

    class ActionParameter0 : public ActionParameterBase
    {};

    template<class T1>
    class ActionParameter1 : public ActionParameterBase
    {
    public:
        ActionParameter1(const T1& _p1)
            : p1(_p1)
        {}

        T1 p1;
    };

    template<class T1, class T2>
    class ActionParameter2 : public ActionParameterBase
    {
    public:
        ActionParameter2(const T1& _p1, const T2& _p2)
            : p1(_p1)
            , p2(_p2)
        {}

        T1 p1;
        T2 p2;
    };

    template<class T1, class T2, class T3>
    class ActionParameter3 : public ActionParameterBase
    {
    public:
        ActionParameter3(const T1& _p1, const T2& _p2, const T3& _p3)
            : p1(_p1)
            , p2(_p2)
            , p3(_p3)
        {}

        T1 p1;
        T2 p2;
        T3 p3;
    };

}

#endif // ACTION_H
