#pragma once

#include "Uncopyable.h"


namespace elephantlogger {


/**
 * Singleton template interface.
 * Singleton can not be copied or instanciated (e.g. new).
 * You should use the static getter method instead.
 *
 * \code{.cpp}
 * class A : private Singleton<A> {
 *     private:
 *         friend Singleton<A>;
 *         A() = default;
 *
 *      public:
 *          using Singleton<A>::getInstance;
 *          void initialize() override;
 *          void destroy() override;
 * };
 * \endcode
 */
template <class T>
class Singleton : private Uncopyable<Singleton<T>> {
    private:
        friend T;
        Singleton() = default;
        virtual ~Singleton() = default;

    public:
        static T& get() {
            static T m_instance;
            return m_instance;
        }
};


#define ELEPHANTLOGGER_MAKE_SINGLETON(ClassName) \
    public: \
        using Singleton<ClassName>::get; \
    private: \
        friend Singleton<ClassName>; \
        ClassName(); \
        ~ClassName()


} // End namespace

