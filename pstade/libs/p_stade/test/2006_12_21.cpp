#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


#include <boost/type_traits/decay.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/result_of.hpp>
#include <boost/lambda/bind.hpp>


// my.hpp
//

namespace my {


    namespace op {

        struct logical_not
        {
            typedef bool result_type;

            template< class A >
            bool operator()(A const& a) const
            {
                return !a;
            }
        };

    }

    op::logical_not const logical_not = { }; // see 8.5.1/8


    template< class T >
    struct singleton
    {
        static T instance;
    };

    template< class T >
    T singleton<T>::instance;

    namespace {
        static // <- for weird stdafx.h.
        op::logical_not const& logical_not2 = singleton<op::logical_not>::instance;
    }


    namespace op {

        struct identity
        {
            template< class FunCall >
            struct result;

            template< class Fun, class A >
            struct result<Fun(A)> :
                boost::remove_cv<typename boost::decay<A>::type>
            { };

            template< class A >
            A operator()(A a) const
            {
                return a;
            }
        };

    }

    op::identity const identity = { };


} // namespace my


// my_test.cpp
//

void test()
{
    {
        pstade::result_of<my::op::logical_not(bool)>::type a = my::logical_not(true);
        BOOST_CHECK(a == false);
    }
    {
        pstade::result_of<my::op::logical_not(bool)>::type a = my::logical_not2(false);
        BOOST_CHECK(a == true);
    }
    {
        pstade::result_of<my::op::identity(int)>::type a = my::identity(5);
        BOOST_CHECK(a == 5);
    }
    {
        namespace lambda = boost::lambda;
        BOOST_CHECK( lambda::bind(my::logical_not, true)() == false );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
