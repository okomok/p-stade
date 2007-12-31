

// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if !defined(PSTADE_EGG_CHAR_CONVERSION_PARAMS)
    #error Please define PSTADE_EGG_CHAR_CONVERSION_PARAMS.
#endif
#define PSTADE_name BOOST_PP_TUPLE_ELEM(2, 0, PSTADE_EGG_CHAR_CONVERSION_PARAMS)
#define PSTADE_func BOOST_PP_TUPLE_ELEM(2, 1, PSTADE_EGG_CHAR_CONVERSION_PARAMS)


    struct BOOST_PP_CAT(baby_, PSTADE_name)
    {
        template<class Myself, class CharT, class Locale = void>
        struct apply :
            boost::remove_cv<CharT>
        { };

        template<class Result, class CharT>
        Result call(CharT& ch, std::locale const& loc) const
        {
            return PSTADE_func(ch, loc);
        }

        template<class Result, class CharT>
        Result call(CharT& ch) const
        {
            return PSTADE_func(ch, std::locale());
        }
    };

    typedef pstade::egg::function<BOOST_PP_CAT(baby_, PSTADE_name), by_cref> BOOST_PP_CAT(T_, PSTADE_name);

    PSTADE_ADL_BARRIER(char_conversion) {
        PSTADE_POD_CONSTANT((BOOST_PP_CAT(T_, PSTADE_name)), PSTADE_name) = {{}};
    }


#undef  PSTADE_func
#undef  PSTADE_name
#undef  PSTADE_EGG_CHAR_CONVERSION_PARAMS
