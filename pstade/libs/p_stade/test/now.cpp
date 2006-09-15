#if 1

#include <pstade/../libs/oven/test/to_counter.cpp>
//#include <pstade/../libs/oven/test/to_stream.cpp>
//#include <pstade/../libs/biscuit/test/capture.cpp>

#else




#include <iostream>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/mpl/assert.hpp>


template< class F >
void foo(F&)
{
    BOOST_MPL_ASSERT_NOT((boost::is_pointer<F>));
    BOOST_MPL_ASSERT((boost::is_function<F>));
    std::cout << "non-const";
}

template< class F >
void foo(F const&)
{
    BOOST_MPL_ASSERT_NOT((boost::is_pointer<F>));
    BOOST_MPL_ASSERT((boost::is_function<F>));
    std::cout << "const";
}

void bar() { }

int main()
{
     //foo(bar);
     foo(&bar); //error
}


#endif
