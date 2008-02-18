#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/poly.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/test.hpp>
#include <pstade/pod_constant.hpp>
#include <boost/noncopyable.hpp>
#include <boost/type_traits/remove_cv.hpp>


template<class X>
struct foo
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
struct foo<char>
{
    typedef std::string result_type;

    result_type operator()(char ch) const
    {
        return std::string("char");
    }
};

template<>
struct foo<char const> :
    foo<char>
{};


struct nested_plus
{
    template<class A1, class A2, class A3 = void>
    struct apply
    {
        typedef apply type;

        typedef typename boost::remove_cv<A1>::type result_type;

        result_type operator()(A1& a1, A2& a2, A3& a3) const
        {
            return a1 + a2 + a3;
        }
    };

    template<class A1, class A2>
    struct apply<A1, A2>
    {
        typedef apply type;

        typedef typename boost::remove_cv<A1>::type result_type;

        result_type operator()(A1& a1, A2& a2) const
        {
            return a1 + a2;
        }
    };
};


// total specialization must be outside.
template<class A1>
struct neg_impl // needed cuz instantiated in overload resolution.
{
    typedef neg_impl type;
    typedef void result_type;
};

template<>
struct neg_impl<int>
{
    typedef neg_impl type;

    typedef int result_type;

    result_type operator()(int& a1) const
    {
        return -a1;
    }
};

template<>
struct neg_impl< void >
{
    typedef neg_impl type;

    typedef char result_type;

    result_type operator()() const
    {
        return 'c';
    }
};

struct base_neg
{
    template<class A1 = void> // nullary
    struct apply :
        neg_impl<A1>
    { };
};


typedef pstade::egg::poly< foo<boost::mpl::_> >::type T_identity;
PSTADE_POD_CONSTANT((T_identity), identity) = PSTADE_EGG_POLY();

typedef pstade::egg::poly<foo<boost::mpl::_>, boost::use_default>::type T_identity_;
PSTADE_POD_CONSTANT((T_identity_), identity_) = PSTADE_EGG_POLY();

typedef pstade::egg::poly< nested_plus >::type T_nplus;
PSTADE_POD_CONSTANT((T_nplus), nplus) = PSTADE_EGG_POLY();


typedef pstade::egg::poly< base_neg, boost::use_default, pstade::egg::use_nullary_result >::type T_neg;
PSTADE_POD_CONSTANT((T_neg), neg) = PSTADE_EGG_POLY();


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


PSTADE_TEST_IS_RESULT_OF((int), T_nplus(int&, int))
PSTADE_TEST_IS_RESULT_OF((int const), T_nplus(int, int, int))

PSTADE_TEST_IS_RESULT_OF((int), T_neg(int&))
PSTADE_TEST_IS_RESULT_OF((char), T_neg())


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
    {
        BOOST_CHECK( nplus(1, 2) == 1+2 );
        BOOST_CHECK( nplus(1,2,3) == 1+2+3 );
    }
    {
        int i = 10;
        BOOST_CHECK( neg(i) == -10 );
        BOOST_CHECK( neg() == 'c' );
    }
}
