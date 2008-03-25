#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_DETAIL_CHAR_CLASSIFICATION_HPP
#define BOOST_EGG_DETAIL_CHAR_CLASSIFICATION_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <locale>
#include <boost/preprocessor/cat.hpp>
#include <boost/egg/const.hpp>
#include <boost/egg/preprocessor/array_iterate.hpp>
#include <boost/egg/preprocessor/cat3.hpp>
#include <boost/egg/detail/adl_barrier.hpp>


namespace boost { namespace egg {


    struct T_is_classified_as
    {
        typedef bool result_type;

        template<class CharT>
        bool operator()(CharT ch, std::ctype_base::mask m, std::locale const &loc) const
        {
            return std::use_facet< std::ctype<CharT> >(loc).is(m, ch);
        }

        template<class CharT>
        bool operator()(CharT ch, std::ctype_base::mask m) const
        {
            return (*this)(ch, m, std::locale());
        }
    };

    BOOST_EGG_CONST((T_is_classified_as), is_classified_as) = {};


#define entries (11, (space, print, cntrl, upper, lower, alpha, digit, punct, xdigit, alnum, graph))
    #define  BOOST_EGG_PP_ARRAY_ITERATION_PARAMS (entries, <boost/egg/detail/char_classification.hpp>)
    #include BOOST_EGG_PP_ARRAY_ITERATE()
#undef  entries


} } // namespace boost::egg


#endif
#else
#define name BOOST_EGG_PP_ARRAY_ITERATION()


    struct BOOST_EGG_PP_CAT3(T_, is_, name)
    {
        typedef bool result_type;

        template<class CharT>
        bool operator()(CharT ch, std::locale const &loc) const
        {
            return std::use_facet< std::ctype<CharT> >(loc).is(std::ctype_base::name, ch);
        }

        template<class CharT>
        bool operator()(CharT ch) const
        {
            return (*this)(ch, std::locale());
        }
    };

BOOST_EGG_ADL_BARRIER(char_classification) {
    BOOST_EGG_CONST((BOOST_EGG_PP_CAT3(T_, is_, name)), BOOST_PP_CAT(is_, name)) = {};
}


#undef  name
#endif
