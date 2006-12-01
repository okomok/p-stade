#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/ret.hpp>


#include <boost/lambda/core.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/reference.hpp>


struct my_fun_t
{
	template< class T >
	T operator()(T x, T y) const
	{
		return x + y;
	}
};


struct my_fun0_t
{
	int operator()() const
	{
		return 10;
	}
};


template< class FunctorWithResult >
int foo(FunctorWithResult fun)
{
	typename boost::result_of<FunctorWithResult(int)>::type x = fun(1, 2);
	return x;
}


void test()
{
    using namespace pstade;
	namespace lambda = boost::lambda;

	::my_fun_t my_fun;
	{
		BOOST_CHECK( 3 ==
			::foo( pstade::ret<int>(my_fun) )
		);
    }
	{
		BOOST_CHECK( 3 ==
			::foo( my_fun|with_ret<int>() )
		);
    }
	{
		BOOST_CHECK( 3 ==
			lambda::bind( pstade::ret<int>(my_fun), lambda::_1, lambda::_2 )(1|to_reference, 2|to_reference)
		);
	}

	::my_fun0_t my_fun0;
	{
		boost::result_of<
			result_of_ret<int, my_fun0_t>::type()
		>::type result = pstade::ret<int>(my_fun0)();
		BOOST_CHECK( result == 10 );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
