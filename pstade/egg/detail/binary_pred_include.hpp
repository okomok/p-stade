

// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if !defined(PSTADE_EGG_BINARY_PRED_PARAMS)
    #error Please define PSTADE_EGG_BINARY_PRED_PARAMS.
#endif
#define PSTADE_name BOOST_PP_TUPLE_ELEM(2, 0, PSTADE_EGG_BINARY_PRED_PARAMS)
#define PSTADE_op   BOOST_PP_TUPLE_ELEM(2, 1, PSTADE_EGG_BINARY_PRED_PARAMS)


    struct BOOST_PP_CAT(T_, PSTADE_name)
    {
        typedef bool result_type;

        template<class X, class Y>
        bool operator()(X const& x, Y const& y) const
        {
            return x PSTADE_op y;
        }
    };

    PSTADE_ADL_BARRIER(PSTADE_name) {
        PSTADE_POD_CONSTANT((BOOST_PP_CAT(T_, PSTADE_name)), PSTADE_name) = {};
    }


#undef  PSTADE_op
#undef  PSTADE_name
#undef  PSTADE_EGG_BINARY_PRED_PARAMS
