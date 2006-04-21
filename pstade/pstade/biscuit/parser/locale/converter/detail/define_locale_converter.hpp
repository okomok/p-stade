#ifndef PSTADE_BISCUIT_PARSER_LOCALE_CONVERTER_DETAIL_DEFINE_LOCALE_CONVERTER_HPP
#define PSTADE_BISCUIT_PARSER_LOCALE_CONVERTER_DETAIL_DEFINE_LOCALE_CONVERTER_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if !defined(PSTADE_CFG_NO_STD_LOCALE)

    #include <locale>
    #include <functional> // unary_function

    #define PSTADE_BISCUIT_DEFINE_LOCALE_CONVERTER(name, fun) \
        namespace pstade { namespace biscuit { \
            \
            template< class CharT > \
            struct name : \
                std::unary_function<CharT, CharT> \
            { \
                CharT operator()(CharT ch) const \
                { \
                    return fun(ch, std::locale()); \
                } \
            }; \
            \
        } } \
    /**/

#else

    #define PSTADE_BISCUIT_DEFINE_LOCALE_CONVERTER(name, fun) \
    /**/

#endif // !defined(PSTADE_CFG_NO_STD_LOCALE)


#endif
