#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_DETAIL_CHAR_CONVERSION_HPP
#define BOOST_EGG_DETAIL_CHAR_CONVERSION_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <locale>
#include <boost/preprocessor/cat.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/egg/by_cref.hpp>
#include <boost/egg/const.hpp>
#include <boost/egg/preprocessor/array_iterate.hpp>
#include <boost/egg/preprocessor/cat3.hpp>
#include <boost/egg/detail/adl_barrier.hpp>


namespace boost { namespace egg {


#define entries (2, (upper, lower))
    #define  BOOST_EGG_PP_ARRAY_ITERATION_PARAMS (entries, <boost/egg/detail/char_conversion.hpp>)
    #include BOOST_EGG_PP_ARRAY_ITERATE()
#undef  entries


} } // namespace boost::egg


#endif
#else
#define name BOOST_EGG_PP_ARRAY_ITERATION()


    namespace BOOST_EGG_PP_CAT3(to_, name, _detail) {


        struct little
        {
            template<class Me, class CharT, class Locale = void>
            struct apply :
                remove_cv<CharT>
            { };

            template<class Re, class CharT>
            Re call(CharT &ch, std::locale const &loc) const
            {
                return std::use_facet< std::ctype<Re> >(loc).BOOST_PP_CAT(to, name)(ch);
            }

            template<class Re, class CharT>
            Re call(CharT &ch) const
            {
                return call<Re>(ch, std::locale());
            }
        };


    } // namespace to_NAME_detail


    typedef function<BOOST_EGG_PP_CAT3(to_, name, _detail)::little, by_cref> BOOST_EGG_PP_CAT3(T_, to_, name);
BOOST_EGG_ADL_BARRIER(char_conversion) {
    BOOST_EGG_CONST((BOOST_EGG_PP_CAT3(T_, to_, name)), BOOST_PP_CAT(to_, name)) = {{}};
}


#undef  name
#endif
