#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


#include <boost/type_traits/decay.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <pstade/result_of.hpp>
#include <string>


// my.hpp
//

namespace my {


// ポリモーフィックでない場合

    namespace op {

        struct less
        {
            typedef bool result_type;

            template< class A0, class A1 >
            bool operator()(A0 a0, A1 a1) const
            {
                return a0 < a1;
            }
        };

    }

    // 厳密にはODR違反になり得るが、実際に問題を起こすことはない(らしい)
    op::less const less = { };

    // シングルトンでODR違反を回避する
    template< class T >
    struct singleton
    {
        static T instance;
    };

    template< class T >
    T singleton<T>::instance;

    namespace {
        op::less const& less2 = singleton<op::less>::instance;
    }


// ポリモーフィックな場合

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


// ポリモーフィックかつ引数の数がゼロになり得る場合

    namespace op {

        struct zero
        {
            int operator()() const
            {
                return 0;
            }

            template< class FunCall >
            struct result;

            template< class Fun >
            struct result<Fun(std::string&)>
            {
                typedef std::string& type;
            };

            std::string& operator()(std::string& str) const
            {
                str += "0";
                return str;
            }
        };

    }

    op::zero const zero = { };

} // namespace my

namespace boost {

    template< >
    struct result_of<my::op::zero()>
    {
        typedef int type;
    };

    template< >
    struct result_of<my::op::zero const()>
    {
        typedef int type;
    };

} // namespace boost


namespace my {


// VC++7.1/8のバグについて

    namespace op {

        template< class T >
        struct foo_error
        {
            template< class FunCall >
            struct result;

            template< class Fun, class A >
            struct result<Fun(A)>
            {
                typedef int type;
            };

            int operator()(int a) const
            {
                return a;
            }
        };

        template< class T >
        struct foo_ok
        {
            template< class FunCall >
            struct result;

            template< class Fun, class A >
            struct result<Fun(A)>
            {
                typedef int type;
            };

            int operator()(int a) const
            {
                return a;
            }

#if defined(BOOST_MSVC)
            // ユーザ定義のコンストラクタが一個必要
            foo_ok() { }
#endif
        };

        struct dummy { };

        template< class T >
        struct foo_ok2
#if defined(BOOST_MSVC)
            // 基底クラスも持つのもよい
            : dummy
#endif
        {
            template< class FunCall >
            struct result;

            template< class Fun, class A >
            struct result<Fun(A)>
            {
                typedef int type;
            };

            int operator()(int a) const
            {
                return a;
            }
        };

    } // namespace op


} // namespace my



// my_test.cpp
//

void test()
{
    {
        pstade::result_of<my::op::less(int, int)>::type a = my::less(10, 12);
        BOOST_CHECK(a == true);
    }
    {
        pstade::result_of<my::op::less(int, int)>::type a = my::less2(12, 10);
        BOOST_CHECK(a == false);
    }
    {
        pstade::result_of<my::op::zero()>::type a = my::zero();
        BOOST_CHECK(a == 0);
        std::string str("zero is ");
        pstade::result_of<my::op::zero(std::string&)>::type b = my::zero(str);
        BOOST_CHECK(b == "zero is 0");
    }
    {
        //pstade::result_of<my::op::foo_error<int>(int)>::type error;
        pstade::result_of<my::op::foo_ok<int>(int)>::type ok;
        pstade::result_of<my::op::foo_ok2<int>(int)>::type ok2;
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
