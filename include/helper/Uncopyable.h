#pragma once


namespace ElephantLogger {


/**
 * Uncopyable interface.
 * Disable copy constructor and copy operator.
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

    private:
        Uncopyable(Uncopyable<T> const& other) = delete;
        Uncopyable<T>& operator=(Uncopyable<T> const& other) = delete;
};


} // End namespace