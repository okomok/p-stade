#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/deferred.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/test.hpp>
#include <pstade/pod_constant.hpp>
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


typedef PSTADE_EGG_DEFER((baby<boost::mpl::_>)) op_identity;
PSTADE_POD_CONSTANT((op_identity), identity) = PSTADE_EGG_DEFERRED;


PSTADE_TEST_IS_RESULT_OF((int&), op_identity(int&))
PSTADE_TEST_IS_RESULT_OF((int const&), op_identity(int))
PSTADE_TEST_IS_RESULT_OF((int const&), op_identity(int const))
PSTADE_TEST_IS_RESULT_OF((int const&), op_identity(int const&))

PSTADE_TEST_IS_RESULT_OF((int&), op_identity(int&, int))
PSTADE_TEST_IS_RESULT_OF((int const&), op_identity(int, int))
PSTADE_TEST_IS_RESULT_OF((int const&), op_identity(int const, int))
PSTADE_TEST_IS_RESULT_OF((int const&), op_identity(int const&, int))


#if 0

struct base_abc
{
    typedef std::string nullary_result_type;

    std::string operator()() const
    {
        return "abc";
    }
};

typedef pstade::egg::function< pstade::egg::baby::deferred<base_abc> > op_abc;
op_abc const abc = { { } };

PSTADE_TEST_IS_RESULT_OF((std::string), op_abc())

#endif


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
#if 0
    {
        BOOST_CHECK(abc() == "abc");
    }
#endif
}
