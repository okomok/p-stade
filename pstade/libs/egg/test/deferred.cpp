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
struct little
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

template<>
struct little<char>
{
    typedef std::string result_type;

    result_type operator()(char ch) const
    {
        return std::string("char");
    }
};

template<>
struct little<char const> :
    little<char>
{};


typedef PSTADE_EGG_DEFER((little<boost::mpl::_>)) T_identity;
PSTADE_POD_CONSTANT((T_identity), identity) = PSTADE_EGG_DEFERRED();

typedef PSTADE_EGG_DEFER_BY((little<boost::mpl::_>), boost::use_default) T_identity_;
PSTADE_POD_CONSTANT((T_identity_), identity_) = PSTADE_EGG_DEFERRED();


PSTADE_TEST_IS_RESULT_OF((int&), T_identity(int&))
PSTADE_TEST_IS_RESULT_OF((int const&), T_identity(int))
PSTADE_TEST_IS_RESULT_OF((int const&), T_identity(int const))
PSTADE_TEST_IS_RESULT_OF((int const&), T_identity(int const&))

PSTADE_TEST_IS_RESULT_OF((int&), T_identity(int&, int))
PSTADE_TEST_IS_RESULT_OF((int const&), T_identity(int, int))
PSTADE_TEST_IS_RESULT_OF((int const&), T_identity(int const, int))
PSTADE_TEST_IS_RESULT_OF((int const&), T_identity(int const&, int))


PSTADE_TEST_IS_RESULT_OF((std::string), T_identity(char))
PSTADE_TEST_IS_RESULT_OF((std::string), T_identity(char &))
PSTADE_TEST_IS_RESULT_OF((std::string), T_identity(char const&))


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

        BOOST_CHECK(identity_(10, 0) == 10);
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
    {
        char ch = 'a';
        BOOST_CHECK( identity(ch) == "char" );
        BOOST_CHECK( identity('a') == "char" );
    }
}
