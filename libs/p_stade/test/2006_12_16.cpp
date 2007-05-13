#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


#include <boost/mpl/apply.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/add_reference.hpp>


template< class T, class U >
struct klass
{ };

template< class T, class U >
struct has_type_self
{
    typedef has_type_self type;
};

template< class T, class U >
struct has_type_int
{
    typedef int type;
};

template< class T, int U = 1 >
struct non_type_parameter
{ };

template< class T, class U = typename T::hello >
struct hello
{ };

template< class T0, class T1, class T2=int, class T3=int, class T4=int, class T5=int >
struct too_many_parameters
{ };

template< class T, class U >
struct non_default_constructible
{
    typedef non_default_constructible type;

    explicit non_default_constructible(int)
    { }
};

namespace mpl = boost::mpl;


void test()
{
    {
        ::klass<int&, double> x =
            mpl::apply<
                ::klass<
                    boost::add_reference<mpl::_1>, mpl::_2
                >,
                int, double
            >::type();
    }
    {
        ::has_type_self<int&, double> x =
            mpl::apply<
                ::has_type_self<
                    boost::add_reference<mpl::_1>, mpl::_2
                >,
                int, double
            >::type();
    }
    {
        int x =
            mpl::apply<
                ::has_type_int<
                    boost::add_reference<mpl::_1>, mpl::_2
                >,
                int, double
            >::type();
    }
    {/*
        ::non_type_parameter<int&> error =
            mpl::apply<
                ::non_type_parameter<
                    boost::add_reference<mpl::_1>
                >,
                int
            >::type();
    */}
    {/*
        typedef ::hello<mpl::_1> error;
    */}
    {/*
        ::too_many_parameters<int&, double> error =
            mpl::apply<
                ::too_many_parameters<
                    boost::add_reference<mpl::_1>, mpl::_2
                >,
                int, double
            >::type();
    */}
    {
        ::non_default_constructible<int&, double> error_under_Boost_1_33 =
            mpl::apply<
                ::non_default_constructible<
                    boost::add_reference<mpl::_1>, mpl::_2
                >,
                int, double
            >::type(1);
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
