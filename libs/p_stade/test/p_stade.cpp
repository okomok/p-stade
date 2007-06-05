
#include <algorithm>
#include <pstade/oven/ptr_container.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/noncopyable.hpp>

struct ncint :
    boost::noncopyable
{
    friend bool operator<(ncint const&, ncint const&) { return true; }
};


int main()
{
    boost::ptr_vector< ::ncint > v;
    std::sort(boost::begin(v), boost::end(v));
}
