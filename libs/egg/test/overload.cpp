

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/version.hpp>
#if BOOST_VERSION >= 103500


#include <boost/egg/overload.hpp>
#include "./egg_test.hpp"


#include <boost/mpl/vector.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <string>
#include <boost/egg/const.hpp>
#include "./using_egg.hpp"


struct T_fun1
{
    typedef int result_type;

    result_type operator()(int const &i , int j) const
    {
        return i + j;
    }
};

struct T_fun2
{
    typedef std::string &result_type;

    result_type operator()(std::string &s , std::string t) const
    {
        return s += t;
    }
};

struct T_fun3
{
    typedef int &result_type;

    result_type operator()(int *p) const
    {
        return *p;
    }
};

struct T_fun4
{
    typedef char result_type;

    template<class T>
    result_type operator()(T) const
    {
        return 'a';
    }
};


typedef
    boost::mpl::vector<
        T_fun1(int const &, int),
        T_fun2(std::string &, std::string const &),
        T_fun3(boost::is_pointer< boost::remove_reference<boost::mpl::_> >),
        T_fun4(boost::mpl::_)
    >
overload_set;

typedef result_of_overload<overload_set>::type T_fun;
BOOST_EGG_CONST((T_fun), fun) = BOOST_EGG_OVERLOAD_L {}, {}, {}, {} BOOST_EGG_OVERLOAD_R;


BOOST_MPL_ASSERT((details::is_matched::apply<int &, int &>));
BOOST_MPL_ASSERT((details::is_matched::apply<long *, boost::is_pointer<boost::mpl::_> >));
BOOST_MPL_ASSERT((details::is_matched::apply<double, boost::mpl::_>));

BOOST_MPL_ASSERT((details::has_matched_params<T_fun1(int const &, int), boost::tuple<int &, int &> >));
BOOST_MPL_ASSERT((details::has_matched_params<T_fun2(std::string &, std::string const &), boost::tuple<std::string &, std::string &> >));

BOOST_MPL_ASSERT_NOT((details::has_matched_params<T_fun4(boost::mpl::_), const boost::tuple<const std::string&, const std::string&> >));


BOOST_MPL_ASSERT((boost::is_same<
                 details::overload_resolution<overload_set, boost::tuple<int &, int &> >::type,
                 T_fun1
>));

BOOST_MPL_ASSERT((boost::is_same<
                 details::overload_resolution<overload_set, boost::tuple<std::string &, std::string const &> >::type,
                 T_fun2
>));


struct T_fun5
{
    typedef int result_type;

    result_type operator()() const
    {
        return 999;
    }
};

typedef
    boost::mpl::vector<
        T_fun1(int const &, int),
        T_fun2(std::string &, std::string const &),
        T_fun3(boost::is_pointer< boost::remove_reference<boost::mpl::_> >),
        T_fun4(boost::mpl::_),
        T_fun5()
    >
overload_set_nullary;

typedef result_of_overload<overload_set_nullary>::type T_fun_nullary;
T_fun_nullary const fun_nullary  = BOOST_EGG_OVERLOAD_L {}, {}, {}, {}, {} BOOST_EGG_OVERLOAD_R;


BOOST_MPL_ASSERT((boost::mpl::equal<
                 boost::function_types::parameter_types<int()>::type,
                 boost::mpl::empty_sequence
>));

BOOST_MPL_ASSERT((boost::is_same<
                 details::nullary_result_of_overload_resolution<overload_set_nullary>::type,
                 int
>));


void egg_test()
{
    {
        BOOST_CHECK( fun(1, 2) == 3 );
        std::string s("abc"), t("de");
        BOOST_CHECK( fun(s, t) == "abcde" );
        int i = 12;
        int *p = &i;
        BOOST_CHECK( &(fun(p)) == &i );
        BOOST_CHECK( fun(s) == 'a' );
    }
    {
        BOOST_CHECK( fun_nullary(1, 2) == 3 );
        std::string s("abc"), t("de");
        BOOST_CHECK( fun_nullary(s, t) == "abcde" );
        int i = 12;
        int *p = &i;
        BOOST_CHECK( &(fun_nullary(p)) == &i );
        BOOST_CHECK( fun_nullary(s) == 'a' );
        BOOST_CHECK( fun_nullary() == 999 );
    }
}


#else
int main() {}
#endif
