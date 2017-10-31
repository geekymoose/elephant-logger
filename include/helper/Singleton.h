#pragma once

#include "Uncopyable.h"

template <class T>
class Singleton : private Uncopyable<Singleton<T>> {
    private:
        final T;
        Singleton() = default;
        virtual ~Singleton() = default;

    public:
        static T& getInstance() {
            static T m_instance;
            return m_instance;
        }

    public:
        virtual void initialize() = 0;
        virtual void destroy() = 0;
};