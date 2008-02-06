#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_CHAR_CONVERSION_HPP
#define PSTADE_EGG_DETAIL_CHAR_CONVERSION_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <locale>
#include <boost/preprocessor/cat.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/pp_array_iterate.hpp>
#include <pstade/preprocessor.hpp>
#include "../by_cref.hpp"


namespace pstade { namespace egg {


#define entries (2, (upper, lower))
    #define  PSTADE_PP_ARRAY_ITERATION_PARAMS (entries, <pstade/egg/detail/char_conversion.hpp>)
    #include PSTADE_PP_ARRAY_ITERATE()
#undef  entries


} } // namespace pstade::egg


#endif
#else
#define name PSTADE_PP_ARRAY_ITERATION()


    namespace PSTADE_PP_CAT3(to_, name, _detail) {


        struct little
        {
            template<class Me, class CharT, class Locale = void>
            struct apply :
                boost::remove_cv<CharT>
            { };

            template<class Re, class CharT>
            Re call(CharT& ch, std::locale const& loc) const
            {
                return std::use_facet< std::ctype<Re> >(loc).BOOST_PP_CAT(to, name)(ch);
            }

            template<class Re, class CharT>
            Re call(CharT& ch) const
            {
                return call<Re>(ch, std::locale());
            }
        };


    } // namespace PSTADE_PP_CAT3(to_, name, _detail)


    typedef function<PSTADE_PP_CAT3(to_, name, _detail)::little, by_cref> PSTADE_PP_CAT3(T_, to_, name);
PSTADE_ADL_BARRIER(char_conversion) {
    PSTADE_POD_CONSTANT((PSTADE_PP_CAT3(T_, to_, name)), BOOST_PP_CAT(to_, name)) = {{}};
}


#undef  name
#endif
