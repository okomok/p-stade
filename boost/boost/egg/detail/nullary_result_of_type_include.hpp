

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if !defined(BOOST_EGG_NULLARY_RESULT_OF_TYPE_PARAMS)
    #error Please define BOOST_EGG_NULLARY_RESULT_OF_TYPE_PARAMS.
#endif
#define PSTADE_name BOOST_PP_TUPLE_ELEM(1, 0, BOOST_EGG_NULLARY_RESULT_OF_TYPE_PARAMS)


    namespace boost {

        template< >
        struct result_of< PSTADE_name(void) >
        {
            typedef PSTADE_name::nullary_result_type type;
        };

        template< >
        struct result_of< PSTADE_name const(void) > :
               result_of< PSTADE_name() >
        { };

    }


#undef  PSTADE_name
#undef  BOOST_EGG_NULLARY_RESULT_OF_TYPE_PARAMS
