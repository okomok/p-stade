

// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if !defined(PSTADE_EGG_FUNCTION_PREAMBLE_PARAMS)
    #error Please define PSTADE_EGG_FUNCTION_PREAMBLE_PARAMS.
#endif
#define PSTADE_Little   BOOST_PP_TUPLE_ELEM(2, 0, PSTADE_EGG_FUNCTION_PREAMBLE_PARAMS)
#define PSTADE_m_little BOOST_PP_TUPLE_ELEM(2, 1, PSTADE_EGG_FUNCTION_PREAMBLE_PARAMS)


    typedef function function_type;
    typedef PSTADE_Little little_type;

    PSTADE_Little PSTADE_m_little;

    little_type little() const
    {
        return PSTADE_m_little;
    }

    typedef typename
        pstade::egg::detail::nullary_result<little_type, function>::type
    nullary_result_type;

    #include PSTADE_EGG_BLL_BINDABLE()


#undef  PSTADE_m_little
#undef  PSTADE_Little
#undef  PSTADE_EGG_FUNCTION_PREAMBLE_PARAMS
