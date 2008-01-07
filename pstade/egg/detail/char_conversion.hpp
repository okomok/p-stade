#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_CHAR_CONVERSION_HPP
#define PSTADE_EGG_DETAIL_CHAR_CONVERSION_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <locale>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/array/elem.hpp>
#include <boost/preprocessor/array/size.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/pod_constant.hpp>
#include "../by_cref.hpp"


namespace pstade { namespace egg {


#define entries \
    (2,( \
        (std::toupper,  to_upper), \
        (std::tolower,  to_lower) \
    ) ) \
/**/
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC(BOOST_PP_ARRAY_SIZE(entries)), <pstade/egg/detail/char_conversion.hpp>))
    #include BOOST_PP_ITERATE()
#undef  entries


} } // namespace pstade::egg


#endif
#else
#define entry BOOST_PP_ARRAY_ELEM(BOOST_PP_ITERATION(), entries)
#define op   BOOST_PP_TUPLE_ELEM(2, 0, entry)
#define name BOOST_PP_TUPLE_ELEM(2, 1, entry)


    struct BOOST_PP_CAT(little_, name)
    {
        template<class Myself, class CharT, class Locale = void>
        struct apply :
            boost::remove_cv<CharT>
        { };

        template<class Result, class CharT>
        Result call(CharT& ch, std::locale const& loc) const
        {
            return op(ch, loc);
        }

        template<class Result, class CharT>
        Result call(CharT& ch) const
        {
            return op(ch, std::locale());
        }
    };

    typedef function<BOOST_PP_CAT(little_, name), by_cref> BOOST_PP_CAT(T_, name);

    PSTADE_ADL_BARRIER(char_conversion) {
        PSTADE_POD_CONSTANT((BOOST_PP_CAT(T_, name)), name) = {{}};
    }


#undef  name
#undef  op
#undef  entry
#endif
