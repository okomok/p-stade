#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_CHAR_CLASSIFICATION_HPP
#define PSTADE_EGG_DETAIL_CHAR_CLASSIFICATION_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <locale>
#include <boost/preprocessor/cat.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/pp_array_iterate.hpp>
#include <pstade/preprocessor.hpp>


namespace pstade { namespace egg {


    struct T_is_classified_as
    {
        typedef bool result_type;

        template<class CharT>
        bool operator()(CharT ch, std::ctype_base::mask m, std::locale const& loc) const
        {
            return std::use_facet< std::ctype<CharT> >(loc).is(m, ch);
        }

        template<class CharT>
        bool operator()(CharT ch, std::ctype_base::mask m) const
        {
            return (*this)(ch, m, std::locale());
        }
    };

    PSTADE_POD_CONSTANT((T_is_classified_as), is_classified_as) = {};


#define entries (11, (space, print, cntrl, upper, lower, alpha, digit, punct, xdigit, alnum, graph))
    #define  PSTADE_PP_ARRAY_ITERATION_PARAMS (entries, <pstade/egg/detail/char_classification.hpp>)
    #include PSTADE_PP_ARRAY_ITERATE()
#undef  entries


} } // namespace pstade::egg


#endif
#else
#define name PSTADE_PP_ARRAY_ITERATION()


    struct PSTADE_PP_CAT3(T_, is_, name)
    {
        typedef bool result_type;

        template<class CharT>
        bool operator()(CharT ch, std::locale const& loc) const
        {
            return std::use_facet< std::ctype<CharT> >(loc).is(std::ctype_base::name, ch);
        }

        template<class CharT>
        bool operator()(CharT ch) const
        {
            return (*this)(ch, std::locale());
        }
    };

PSTADE_ADL_BARRIER(char_classification) {
    PSTADE_POD_CONSTANT((PSTADE_PP_CAT3(T_, is_, name)), BOOST_PP_CAT(is_, name)) = {};
}


#undef  name
#endif
