#include <iostream>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/mpl/assert.hpp>


template< class F >
void foo(F&)
{
    BOOST_MPL_ASSERT_NOT((boost::is_pointer<F>));
    BOOST_MPL_ASSERT((boost::is_function<F>));
}

template< class F >
void foo(F const&)
{
    BOOST_MPL_ASSERT_NOT((boost::is_pointer<F>));
    BOOST_MPL_ASSERT((boost::is_function<F>));
}

void bar() { }

int main()
{
    foo(bar);  // ok
    // foo(&bar); // error
}
