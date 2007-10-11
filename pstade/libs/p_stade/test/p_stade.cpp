#include <pstade/oven/foreach.hpp>
#include <pstade/used.hpp>

#include <vector>

void f(float x) { pstade::used(x); }

void g(std::vector<float> const & v)
{
   PSTADE_OVEN_FOREACH(i, v)
      f(i);
}

void g_(std::vector<float> const & v)
{
    for (std::vector<float>::const_iterator first = boost::begin(v), last = boost::end(v); first != last; ++first)
      f(*first);
}



int main()
{
    {
        std::vector<float> v;
        v.push_back(3.2);
        g(v);
    }

    {
        std::vector<float> v;
        v.push_back(3.2);
        g_(v);
    }
}
