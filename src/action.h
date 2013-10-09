#ifndef ACTION_H
#define ACTION_H

#include <tuple>
#include <new>
#include <cstddef>

namespace Gui
{
    class ActionParameterBase
    {
    public:
        virtual ~ActionParameterBase() {}
    };

    template<typename... P>
    class ActionParameter : public ActionParameterBase
    {
    public:
        ActionParameter(P... value)
            : m_parameters(value...)
        {}

        std::tuple<P...> m_parameters;
    };


    class ActionBase
    {
    public:
        virtual ~ActionBase() {}
        virtual void operator() (const ActionParameterBase& value) = 0;
    };

    template<typename T, typename Func, typename P, int N>
    struct Caller;

    template<typename T, typename Func, typename P>
    struct Caller<T, Func, P, 1>
    {
        void operator() (T* o, Func f, const P& p)
        {
            (o->*f)(std::get<0>(p));
        }
    };

    template<typename T, typename... P>
    class Action : public ActionBase
    {
    public:
        Action(T* o, void (T::*m)(P...))
            : m_object(o)
            , m_method(m)
        {}

        void operator() (const ActionParameterBase& value) override
        {
            const ActionParameter<P...>& p = dynamic_cast<const ActionParameter<P...>&>(value);
            if (m_object && m_method)
            {
                constexpr int size = std::tuple_size<std::tuple<P...>>::value;
                Caller<T, void (T::*)(P...), std::tuple<P...>, size> o;
                o(m_object, m_method, p.m_parameters);
            }
        }

    private:
        T* m_object;
        void (T::*m_method)(P...);
    };

    template<>
    class Action<void> : public ActionBase
    {
    public:
        Action(void (*F)(void))
            : m_function(F)
        {}

        void operator() (const ActionParameterBase&) override
        {
            if (m_function)
                m_function();
        }

    private:
        void (*m_function)();
    };
}

#endif // ACTION_H
