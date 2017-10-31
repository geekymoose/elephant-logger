#pragma once

template <class T>
class Uncopyable {
    public:
        Uncopyable() = default;

    private:
        Uncopyable(Uncopyable<T> const& other) = delete;
        Uncopyable<T>& operator=(Uncopyable<T> const& other) = delete;
};