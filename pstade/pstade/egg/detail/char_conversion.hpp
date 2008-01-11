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
#include <pstade/preprocessor.hpp>
#include "../by_cref.hpp"


namespace pstade { namespace egg {


#define entries (2, (upper, lower))
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC(BOOST_PP_ARRAY_SIZE(entries)), <pstade/egg/detail/char_conversion.hpp>))
    #include BOOST_PP_ITERATE()
#undef  entries


} } // namespace pstade::egg


#endif
#else
#define name BOOST_PP_ARRAY_ELEM(BOOST_PP_ITERATION(), entries)


    struct PSTADE_PP_CAT3(little_, to_, name)
    {
        template<class Myself, class CharT, class Locale = void>
        struct apply :
            boost::remove_cv<CharT>
        { };

        template<class Result, class CharT>
        Result call(CharT& ch, std::locale const& loc) const
        {
            return std::use_facet< std::ctype<Result> >(loc).BOOST_PP_CAT(to, name)(ch);
        }

        template<class Result, class CharT>
        Result call(CharT& ch) const
        {
            return call<Result>(ch, std::locale());
        }
    };

    typedef function<PSTADE_PP_CAT3(little_, to_, name), by_cref> PSTADE_PP_CAT3(T_, to_, name);

PSTADE_ADL_BARRIER(char_conversion) {
    PSTADE_POD_CONSTANT((PSTADE_PP_CAT3(T_, to_, name)), BOOST_PP_CAT(to_, name)) = {{}};
}


#undef  name
#endif
