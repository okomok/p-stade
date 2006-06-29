#ifndef PSTADE_BISCUIT_PARSER_LOCALE_PREDICATE_CATION_DETAIL_DEFINE_LOCALE_PREDICATE_ACTION_HPP
#define PSTADE_BISCUIT_PARSER_LOCALE_PREDICATE_CATION_DETAIL_DEFINE_LOCALE_PREDICATE_ACTION_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if !defined(PSTADE_CFG_NO_STD_LOCALE)


    #include <locale>
    #include <boost/foreach.hpp>
    #include <boost/range/reference.hpp>
    #include <pstade/unused.hpp>


    #define PSTADE_BISCUIT_DEFINE_LOCALE_PREDICATE_ACTION(name, pred) \
        namespace pstade { namespace biscuit { \
            \
            struct name \
            { \
                template< class ParsingSubRange, class UserState > \
                bool operator()(ParsingSubRange& rng, UserState& us) const \
                { \
                    std::locale loc; \
                    typedef typename boost::range_reference<ParsingSubRange>::type ref_t; \
                    BOOST_FOREACH (ref_t v, rng) { \
                        if (!pred(v, loc)) \
                            return false; \
                    } \
                    \
                    pstade::unused(us); \
                    return true; \
                } \
            }; \
            \
        } } \
    /**/


#else


    #define PSTADE_BISCUIT_DEFINE_LOCALE_PREDICATE_ACTION(name, pred) \
    /**/


#endif // !defined(PSTADE_CFG_NO_STD_LOCALE)


#endif
