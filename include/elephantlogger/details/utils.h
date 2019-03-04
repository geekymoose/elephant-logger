#pragma once


namespace elephantlogger {


// Assertions
#ifdef ELEPHANTLOGGER_ASSERT_ENABLED
#include <cassert>
#define ELEPHANTLOGGER_ASSERT(condition) assert(condition)
#else
#define ELEPHANTLOGGER_ASSERT(condition)
#endif // ELEPHANTLOGGER_ASSERT_DISABLED


/**
 * Uncopyable interface.
 * Disables the copy constructor and the copy operator.
 *
 * \code{.cpp}
 * class A : private Uncopyable<A> {
 *     // Your code
 * };
 * \endcode
 */
template <class T>
class Uncopyable {
    public:
        Uncopyable() = default;
        virtual ~Uncopyable() = default;

    private:
        Uncopyable(Uncopyable<T> const& other) = delete;
        Uncopyable<T>& operator=(Uncopyable<T> const& other) = delete;
};


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


#define ELEPHANTLOGGER_ADD_SINGLETON_UTILS(ClassName) \
    public: \
        using Singleton<ClassName>::get; \
    private: \
        friend Singleton<ClassName>


} // End namespace

