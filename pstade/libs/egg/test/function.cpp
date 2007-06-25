#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/function.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/test.hpp>
#include <boost/noncopyable.hpp>


template<class X>
struct baby
{
    typedef X& result_type;

    result_type operator()(X& x) const
    {
        return x;
    }

    result_type operator()(X& x, int ) const
    {
        return x;
    }
};


PSTADE_EGG_FUNCTION(identity, (baby<_>))

//typedef pstade::egg::function< baby<boost::mpl::_> > op_identity;
//const op_identity identity = op_identity();


PSTADE_TEST_IS_RESULT_OF((int&), op_identity(int&))
PSTADE_TEST_IS_RESULT_OF((int const&), op_identity(int))
PSTADE_TEST_IS_RESULT_OF((int const&), op_identity(int const))
PSTADE_TEST_IS_RESULT_OF((int const&), op_identity(int const&))

PSTADE_TEST_IS_RESULT_OF((int&), op_identity(int&, int))
PSTADE_TEST_IS_RESULT_OF((int const&), op_identity(int, int))
PSTADE_TEST_IS_RESULT_OF((int const&), op_identity(int const, int))
PSTADE_TEST_IS_RESULT_OF((int const&), op_identity(int const&, int))


struct base_abc
{
    std::string operator()() const
    {
        return "abc";
    }
};

typedef pstade::egg::function<base_abc, std::string> op_abc;
op_abc const abc = op_abc();

PSTADE_TEST_IS_RESULT_OF((std::string), op_abc())


struct nc_t : boost::noncopyable
{ };


void pstade_minimal_test()
{
    {
        int i = 10;
        BOOST_CHECK(&(identity(i)) == &i);
        BOOST_CHECK(identity(10) == 10);
        BOOST_CHECK(&(identity(i, 0)) == &i);
        BOOST_CHECK(identity(10, 0) == 10);
    }
    {
        ::nc_t x;
        BOOST_CHECK(&(identity(x)) == &x);
    }
    {
        int a[] = { 1,2,3 };
        BOOST_CHECK(identity(a)[0] == 1);
    }
    {
        char const s[] = "abc";
        BOOST_CHECK(identity(s)[0] == 'a');
    }
    {
        BOOST_CHECK(abc() == "abc");
    }
}
