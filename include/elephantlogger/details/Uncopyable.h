#pragma once


namespace elephantlogger {


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


} // End namespace

