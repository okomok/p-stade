

#include <boost/optional_poly.hpp>

struct my_base {};
struct my_derived : my_base {};

int main()
{
    boost::optional_poly<my_derived> from;
    boost::optional_poly<my_base> to(from);
}
