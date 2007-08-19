#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/minimal_test.hpp>

#include <pstade/egg/curry.hpp>
using namespace pstade::egg;


//[code_second_argument

bool less(int i, int j)
{
    return i < j;
}

int plus3(int a1, int a2, int a3)
{
    return a1+a2+a3;
}

//]


template<class F>
void look_into(F f)
{
    BOOST_MPL_ASSERT((boost::is_same<F, int>));
}

#if 0
pstade::egg::function<
    pstade::egg::detail::baby_bind1_result<
        pstade::egg::function<
            pstade::egg::detail::baby_bind1
        >,
        bool (*)(int, int)
    >
>
template<class Base>
struct result_of_curry2
{
    typedef
        function<
            detail::baby_bind1_result<
                function<detail::baby_bind1>,
                Base
            >
        >
    type;
};


typedef result_of_curry2<bool (*)(int, int)>::type op_curried_less;
op_curried_less const curried_less = { { {{}}, &::less } };


template<class Base>
struct result_of_curry3
{
    typedef
        result_of_curry2<
//        function<
//            detail::baby_bind1_result<
 //               function<baby_bind1>,
                function<
                    detail::baby_bind1_result<
                        function<detail::baby_bind2>,
                        Base
                    >
  //              >
  //          >
        >
    type;
};

typedef result_of_curry3<int (*)(int, int, int)>::type op_curried_plus;
op_curried_plus const curried_plus = {

template<class Base>
{
    typedef
        function<
            detail::baby_bind0_result<
                function<
                    detail::baby_bind1_result<
                        function<detail::baby_bind1>,
                        bool (*)(int, int)
                    >
                >
            >
        >
    type;
};



#endif


template<class Base>
struct result_of_curry2
{
    typedef
        function<
            detail::baby_bind0_result<
                function<
                    detail::baby_bind1_result<
                        function<detail::baby_bind1>,
                        Base
                    >
                >
            >
        >
    type;
};
                function<
                    detail::baby_bind1_result<
                        function<detail::baby_bind1>,
                        bool (*)(int, int)
                    >
                > const ppp = { { {{}}, &::less } };

            detail::baby_bind0_result<
                function<
                    detail::baby_bind1_result<
                        function<detail::baby_bind1>,
                        bool (*)(int, int)
                    >
                >
            > const qqqq = {  { { {{}}, &::less } }     };

typedef ::result_of_curry2<bool (*)(int, int)>::type op_curried_less;
op_curried_less const curried_less = { { { { {{}}, &::less } } } };


pstade::egg::function<
    pstade::egg::detail::baby_bind0_result<
        pstade::egg::function<
            pstade::egg::detail::baby_bind1_result<
                pstade::egg::function<pstade::egg::detail::baby_bind1>,
                pstade::egg::function<
                    pstade::egg::detail::baby_bind1_result<
                        pstade::egg::function<pstade::egg::detail::baby_bind2>,
                        int (*)(int, int, int)
                    >
                >
            >
        >
    >
>


void test()
{
    (void)ppp;
    (void)qqq;

    BOOST_CHECK( curry2(&::less)(3)(4) );
    ::look_into(curry3(&::plus3));
    //BOOST_CHECK( curried_less(3)(4) );
}


void pstade_minimal_test()
{
    test();
}
