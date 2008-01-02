

// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if !defined(PSTADE_EGG_BINARY_ARITHMETIC_PARAMS)
    #error Please define PSTADE_EGG_BINARY_ARITHMETIC_PARAMS.
#endif
#define PSTADE_name BOOST_PP_TUPLE_ELEM(2, 0, PSTADE_EGG_BINARY_ARITHMETIC_PARAMS)
#define PSTADE_op   BOOST_PP_TUPLE_ELEM(2, 1, PSTADE_EGG_BINARY_ARITHMETIC_PARAMS)


    template<class X, class Y>
    struct BOOST_PP_CAT(result_of_, PSTADE_name)
    {
    private:
        static X x;
        static Y y;

        static bool const is_x =
            sizeof( pstade::egg::detail::are_you_x<X, Y>(x PSTADE_op y) ) == sizeof(boost::type_traits::yes_type);

    public:
        typedef typename
            boost::mpl::if_c< is_x,
                X, Y
            >::type
        type;
    };

    struct BOOST_PP_CAT(little_, PSTADE_name)
    {
        template<class Myself, class X, class Y>
        struct apply :
            BOOST_PP_CAT(result_of_, PSTADE_name)<
                typename boost::remove_cv<X>::type, typename boost::remove_cv<Y>::type
            >
        { };

        template<class Result, class X, class Y>
        Result call(X& x, Y& y) const
        {
            return x PSTADE_op y;
        }
    };

    typedef pstade::egg::function<BOOST_PP_CAT(little_, PSTADE_name), by_cref> BOOST_PP_CAT(T_, PSTADE_name);
    PSTADE_ADL_BARRIER(PSTADE_name) {
        PSTADE_POD_CONSTANT((BOOST_PP_CAT(T_, PSTADE_name)), PSTADE_name) = {{}};
    }


#undef  PSTADE_op
#undef  PSTADE_name
#undef  PSTADE_EGG_BINARY_ARITHMETIC_PARAMS
