
#include <boost/utility/result_of.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>


typedef int (*my_ptr)(int);
struct A { int print(int) const; };
typedef int (A::*mem_ptr)(int) const;

BOOST_MPL_ASSERT((boost::is_same<
                 int,
                 boost::result_of<my_ptr()>::type
>));

BOOST_MPL_ASSERT((boost::is_same<
                 int,
                 boost::result_of<mem_ptr()>::type
>));


int main() {}
