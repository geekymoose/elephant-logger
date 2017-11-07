#pragma once

#include "Uncopyable.h"

namespace ElephantLogger {


/**
 * Singleton interface.
 *
 * \note
 * Example to implement a singleton class A:
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
        static T& getInstance() {
            static T m_instance;
            return m_instance;
        }

    public:
        virtual void startup() = 0;
        virtual void shutdown() = 0;
};


} // End namespace
