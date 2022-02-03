#pragma once

#include <algorithm>
#include <iterator>
#include <functional>
#include <iostream>

namespace query
{
    template <typename T, template <typename U, class A = std::allocator<U>> class Arr>
    void printContainer(Arr<T> &source)
    {
        for (auto &&i : source)
        {
            std::cout << i << ", ";
        }
        std::cout << std::endl;
    }

    template <typename T, template <typename U, class A = std::allocator<U>> class Arr, typename F>
    bool all(Arr<T> &source, F pred)
    {
        return std::all_of(std::begin(source), std::end(source), pred);
    }

    template <typename T, template <typename U, class A = std::allocator<U>> class Arr, typename F>
    bool any(Arr<T> &source, F pred)
    {
        return std::any_of(std::begin(source), std::end(source), pred);
    }
    template <typename T, template <typename U, class A = std::allocator<U>> class Arr>
    Arr<T> append(Arr<T> &source, T v)
    {
        std::inserter(source, std::end(source)) = v;
        return source;
    }

    template <template <typename U, class A = std::allocator<U>> class Arr>
    double average(Arr<int> source)
    {
        double n = std::size(source);
        if (n == 0)
        {
            n = 1.0;
        }

        auto s = sum(source);

        return s / n;
    }

    template <template <typename U, class A = std::allocator<U>> class Arr>
    double average(Arr<float> source)
    {
        double n = std::size(source);
        if (n == 0)
        {
            n = 1.0;
        }

        auto s = sum(source);
        return s / n;
    }

    template <template <typename U, class A = std::allocator<U>> class Arr>
    double average(Arr<double> source)
    {
        double n = std::size(source);
        if (n == 0)
        {
            n = 1.0;
        }

        auto s = sum(source);
        return s / n;
    }

    template <typename T, template <typename U, class A = std::allocator<U>> class Arr, typename F>
    double average(Arr<T> &source, F pred)
    {

        Arr<double> v;
        std::transform(std::begin(source), std::end(source), std::back_inserter(v), pred);
        double n = std::size(v);
        if (n == 0)
        {
            n = 1.0;
        }

        auto s = sum(v);

        return s / n;
    }

    template <typename T, template <typename U, class A = std::allocator<U>> class Arr>
    bool contains(Arr<T> &source, T v)
    {
        auto p = std::find(std::begin(source), std::end(source), v);
        return !(p == std::end(source));
    }

    template <typename T, template <typename U, class A = std::allocator<U>> class Arr>
    int count(Arr<T> &source)
    {
        return std::size(source);
    }

    template <typename T, template <typename U, class A = std::allocator<U>> class Arr, typename F>
    int count(Arr<T> &source, F pred)
    {
        auto n = std::count_if(std::begin(source), std::end(source), pred);
        return n;
    }

    template <typename T, template <typename U, class A = std::allocator<U>> class Arr>
    Arr<T> distinct(Arr<T> &source)
    {
        Arr<T> v;
        std::sort(std::begin(source), std::end(source));
        // auto it = std::unique(std::begin(source), std::end(source));
        // // auto n = distance(source.std::begin(), it);
        // copy(std::begin(source), it, std::back_inserter(v));
        std::unique_copy(std::begin(source), std::end(source), std::back_inserter(v));
        return v;
    }

    template <typename T, template <typename U, class A = std::allocator<U>> class Arr>
    T elementAt(Arr<T> &source, int index)
    {
        auto p = std::begin(source);
        std::advance(p, index);
        if (p == std::end(source))
        {
            throw std::out_of_range("end of source");
        }
        return *p;
    }

    template <typename T, template <typename U, class A = std::allocator<U>> class Arr, typename F>
    Arr<T> filter(Arr<T> &source, F pred)
    {
        Arr<T> v;
        auto q = std::copy_if(std::begin(source), std::end(source), std::back_inserter(v), pred);
        return v;
    }

    template <typename T, template <typename U, class A = std::allocator<U>> class Arr, typename F>
    T first(Arr<T> &source, F pred)
    {
        auto p = std::find_if(std::begin(source), std::end(source), pred);

        if (p == std::end(source))
        {
            throw std::out_of_range("end of source");
        }
        return *p;
    }

    template <typename T, template <typename U, class A = std::allocator<U>> class Arr>
    T first(Arr<T> &source)
    {
        auto p = std::begin(source);

        if (p == std::end(source))
        {
            throw std::out_of_range("end of source");
        }
        return *p;
    }

    template <typename T, template <typename U, class A = std::allocator<U>> class Arr>
    T last(Arr<T> &source)
    {
        if (std::size(source) == 0)
        {
            throw std::out_of_range("end of source");
        }
        return source[source.size() - 1];
    }

    template <typename T, template <typename U, class A = std::allocator<U>> class Arr, typename F>
    T last(Arr<T> &source, F pred)
    {
        auto p = std::find_if(rbegin(source), rend(source), pred);

        if (p == std::rend(source))
        {
            throw std::out_of_range("end of source");
        }
        return *p;
    }

    template <typename T, template <typename U, class A = std::allocator<U>> class Arr>
    T max(Arr<T> &source)
    {
        auto p = std::max(std::begin(source), std::end(source));
        return *p;
    }

    template <typename T, template <typename U, class A = std::allocator<U>> class Arr, typename F>
    T max(Arr<T> &source, F pred)
    {
        auto p = std::max_element(std::begin(source), std::end(source), pred);
        return *p;
    }

    template <typename T, template <typename U, class A = std::allocator<U>> class Arr>
    T min(Arr<T> &source)
    {
        auto p = std::min(std::begin(source), std::end(source));
        return *p;
    }

    template <typename T, template <typename U, class A = std::allocator<U>> class Arr, typename F>
    T min(Arr<T> &source, F pred)
    {
        auto p = std::min(std::begin(source), std::end(source), pred);
        return *p;
    }

    template <typename T, template <typename U, class A = std::allocator<U>> class Arr>
    Arr<T> orderBy(Arr<T> &source)
    {
        std::sort(std::begin(source), std::end(source));
        return source;
    }

    template <typename T, template <typename U, class A = std::allocator<U>> class Arr, typename F>
    Arr<T> orderBy(Arr<T> &source, F pred)
    {
        std::sort(std::begin(source), std::end(source), pred);
        return source;
    }

    template <typename T, template <typename U, class A = std::allocator<U>> class Arr>
    Arr<T> orderByDescending(Arr<T> &source)
    {
        std::sort(std::begin(source), std::end(source));
        reverse(source);
        return source;
    }

    template <typename T, template <typename U, class A = std::allocator<U>> class Arr, typename F>
    Arr<T> orderByDescending(Arr<T> &source, F pred)
    {
        std::sort(std::begin(source), std::end(source), pred);
        reverse(source);
        return source;
    }

    template <typename T, template <typename U, class A = std::allocator<U>> class Arr>
    Arr<T> prepend(Arr<T> &source, T v)
    {
        std::inserter(source, std::begin(source)) = v;
        return source;
    }

    template <typename T, template <typename U, class A = std::allocator<U>> class Arr>
    Arr<T> range(int start, int count)
    {
        Arr<T> v(count);
        std::generate(std::begin(v), std::begin(v) + count,
                      [&]()
                      {
                          return start++;
                      });
        return v;
    }

    template <typename T, template <typename U, class A = std::allocator<U>> class Arr>
    Arr<T> reverse(Arr<T> &source)
    {
        std::reverse(std::begin(source), std::end(source));
        return source;
    }

    template <typename T, template <typename U, class A = std::allocator<U>> class Arr, typename F>
    void remove(Arr<T> &source, F pred)
    {
        auto it = std::remove_if(std::begin(source), std::end(source), pred);
        source.erase(it, std::end(source));
    }

    template <typename T, template <typename U, class A = std::allocator<U>> class Arr, typename F>
    void replace(Arr<T> &source, T v, F pred)
    {
        std::replace_if(std::begin(source), std::end(source), pred, v);
    }

    template <typename T, template <typename U, class A = std::allocator<U>> class Arr, typename F>
    Arr<T> select(Arr<T> &source, F pred)
    {
        Arr<T> v;
        std::transform(std::begin(source), std::end(source), std::back_inserter(v), pred);
        return v;
    }

    template <typename R, typename T, template <typename U, class A = std::allocator<U>> class Arr, typename F>
    Arr<R> select(Arr<T> &source, F pred)
    {
        Arr<R> v;
        std::transform(std::begin(source), std::end(source), std::back_inserter(v), pred);
        return v;
    }

    template <typename T, template <typename U, class A = std::allocator<U>> class Arr>
    Arr<T> skip(Arr<T> &source, int n)
    {
        Arr<T> v;
        std::copy(std::begin(source) + n, std::end(source), std::back_inserter(v));
        return v;
    }

    template <typename T, template <typename U, class A = std::allocator<U>> class Arr, typename F>
    Arr<T> skip(Arr<T> &source, int n, F pred)
    {
        Arr<T> v;
        std::copy_if(std::begin(source), std::end(source), std::back_inserter(v), pred);
        return skip(v, n);
    }

    template <typename T, template <typename U, class A = std::allocator<U>> class Arr>
    Arr<T> skipLast(Arr<T> &source, int n)
    {
        Arr<T> v;
        std::copy(rbegin(source) + n, rend(source), std::back_inserter(v));
        reverse(v);
        return v;
    }

    template <template <typename U, class A = std::allocator<U>> class Arr>
    int sum(Arr<int> source)
    {
        int s = 0;
        std::for_each(std::begin(source), std::end(source),
                      [&](int a)
                      {
                          s += a;
                      });
        return s;
    }

    template <template <typename U, class A = std::allocator<U>> class Arr>
    float sum(Arr<float> source)
    {
        float s = 0.0;
        std::for_each(std::begin(source), std::end(source),
                      [&](float a)
                      {
                          s += a;
                      });
        return s;
    }

    template <template <typename U, class A = std::allocator<U>> class Arr>
    double sum(Arr<double> source)
    {
        double s = 0.0;
        std::for_each(std::begin(source), std::end(source),
                      [&](double a)
                      {
                          s += a;
                      });
        return s;
    }

    template <typename T, template <typename U, class A = std::allocator<U>> class Arr>
    Arr<T> take(Arr<T> &source, int n)
    {
        if (std::size(source) < n)
        {
            n = std::size(source);
        }
        Arr<T> v;
        std::copy_n(std::begin(source), n, std::back_inserter(v));
        return v;
    }

    template <typename T, template <typename U, class A = std::allocator<U>> class Arr, typename F>
    Arr<T> take(Arr<T> &source, int n, F pred)
    {
        Arr<T> v;
        std::copy_if(std::begin(source), std::end(source), std::back_inserter(v), pred);
        return take(v, n);
    }

    template <typename T, template <typename U, class A = std::allocator<U>> class Arr>
    Arr<T> takeLast(Arr<T> &source, int n)
    {
        if (std::size(source) < n)
        {
            n = std::size(source);
        }
        Arr<T> v;
        std::copy_n(rbegin(source), n, std::back_inserter(v));
        reverse(v);
        return v;
    }
} // namespace query
