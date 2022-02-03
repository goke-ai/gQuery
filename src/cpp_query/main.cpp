#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <tuple>
#include <algorithm>

void printContainer(std::vector<int> a, std::string label = "")
{
    std::cout << "+ " << label << "======\n";
    for (size_t i = 0; i < std::size(a); i++)
    {
        std::cout << i << ": " << a[i] << std::endl;
    }
    std::cout << "- " << label << "======\n";
}

void printContainer(std::array<int, 11> a, std::string label = "")
{
    std::cout << "+ " << label << "======\n";
    for (size_t i = 0; i < std::size(a); i++)
    {
        std::cout << i << ": " << a[i] << std::endl;
    }
    std::cout << "- " << label << "======\n";
}

void printContainer(std::unique_ptr<int[]> a, int N, std::string label = "")
{
    std::cout << "+ " << label << "======\n";
    for (size_t i = 0; i < N; i++)
    {
        std::cout << i << ": " << a[i] << std::endl;
    }
    std::cout << "- " << label << "======\n";
}

void printContainer(int *a, int N, std::string label = "")
{
    std::cout << "+ " << label << "======\n";
    for (size_t i = 0; i < N; i++)
    {
        std::cout << i << ": " << a[i] << std::endl;
    }
    std::cout << "- " << label << "======\n";
}

template <typename T, typename F>
std::vector<T> filter2(std::vector<T> &source, F pred)
{
    std::vector<T> v;
    auto q = std::copy_if(std::begin(source), std::end(source), std::back_inserter(v), pred);
    return v;
}

template <typename T, size_t N, typename F>
std::array<T, N> filter2(std::array<T, N> &source, F pred)
{
    std::array<T, N> v;
    auto q = std::copy_if(std::begin(source), std::end(source), std::begin(v), pred);

    return v;
}

template <typename T, size_t N, typename F>
auto filter2(std::array<T, N> &source, T *dest, F pred)
{
    std::array<T, N> v;
    auto q = std::copy_if(std::begin(source), std::end(source), std::begin(v), pred);

    int M = int(q - v.begin());

    std::cout << M << std::endl;

    dest = new T[M];

    for (size_t i = 0; i < M; i++)
    {
        dest[i] = v[i];
    }

    // Declaring tuple
    std::tuple<T *, int> y = std::make_tuple(dest, M);

    return y;
}

template <typename T, size_t N, typename F>
auto filter2(std::array<T, N> &source, std::unique_ptr<T[]> &dest, F pred)
{
    std::array<T, N> v;
    auto q = std::copy_if(std::begin(source), std::end(source), std::begin(v), pred);

    int M = int(q - v.begin());

    std::cout << M << std::endl;

    dest = std::make_unique<T[]>(M);

    for (size_t i = 0; i < M; i++)
    {
        dest[i] = v[i];
    }

    // Declaring tuple
    std::tuple<std::unique_ptr<T[]>, int> y = std::make_tuple(std::move(dest), M);

    return y;
}

int main(int, char **)
{

    std::cout << "Hello, world!\n";

    std::vector<int> vNum{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::array<int, 11> aNum{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    printContainer(vNum);

    // even
    std::vector<int> vrlt;
    auto i = std::copy_if(std::begin(vNum), std::end(vNum), std::back_inserter(vrlt),
                          [](auto x)
                          { return (x % 2 == 0); });
    printContainer(vrlt);

    //
    auto vVal = filter2(vNum, [](auto x)
                        { return (x % 2 == 0); });
    printContainer(vVal, "vVal");

    //
    auto aVal = filter2(aNum, [](auto x)
                        { return (x % 2 == 0); });
    printContainer(aVal, "aVal");
    std::cout << aVal.size() << std::endl;
    std::cout << aVal.max_size() << std::endl;

    //
    int *pX = 0;
    auto tuVal = filter2(aNum, pX, [](auto x)
                         { return (x % 2 == 0); });

    auto pVal = std::get<0>(tuVal);
    auto N = std::get<1>(tuVal);

    printContainer(pVal, N, "pVal");
    std::cout << N << std::endl;
    delete[] pX;

    //
    std::unique_ptr<int[]> upX = 0;
    auto tupVal = filter2(aNum, upX, [](auto x)
                         { return (x % 2 == 0); });

    // auto upVal = std::get<0>(tupVal);
    N = std::get<1>(tupVal);

    printContainer(std::move(upX), N, "upX");
    std::cout << N << std::endl;
}
