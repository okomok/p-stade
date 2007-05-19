#include <pstade/vodka/drink.hpp>

#include <pstade/oven/identities.hpp>
#include <boost/ptr_container/ptr_vector.hpp>


using namespace pstade::oven;


struct x : boost::noncopyable
{ };


int main()
{
    boost::ptr_vector<x> rng;
    rng|identities;
    rng|identities(in_single_pass);
}
