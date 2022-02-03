#include <vector>

namespace gquery
{
    template <typename T, typename F>
    std::vector<T> filter(std::vector<T> &source, F pred)
    {
        std::vector<T> v;
        auto q = std::copy_if(std::begin(source), std::end(source), std::back_inserter(v), pred);
        return v;
    }

} // namespace gquery
