#ifndef PSTADE_NAPKIN_DETAIL_OUTPUT_HPP
#define PSTADE_NAPKIN_DETAIL_OUTPUT_HPP


// PStade.Napkin
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <string> // basic_string
#include <boost/foreach.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <pstade/apple/is_sequence.hpp>
#include <pstade/oven/c_str_range.hpp>
#include <pstade/overload.hpp>
#include "./is_boost_archive.hpp"


namespace pstade { namespace napkin { namespace detail {


struct default_output
{
    template< class T, class String >
    static void call(T& out, String psz)
    {
        out << psz;
    }
};


struct std_sequence_output
{
    template< class T, class CharT >
    static void call(T& out, const CharT *psz)
    {
        BOOST_FOREACH (CharT ch, psz|oven::as_c_str) {
            out.push_back(ch);
            // out.insert(out.end(), ch);
        }
    }
};


struct boost_archive_output
{
    template< class T, class CharT >
    static void call(T& out, const CharT *psz)
    {
        std::basic_string<CharT> tmp(psz);
        out << tmp;
    }
};


} } } // namespace pstade::napkin::detail


template< class T, class String > inline
void pstade_napkin_output(T& out, String psz, pstade::overload<>)
{
    using namespace boost;
    using namespace pstade;
    using namespace pstade::napkin::detail;

    typedef typename
    mpl::eval_if< apple::is_sequence<T>,
        mpl::identity<std_sequence_output>,
        mpl::eval_if< is_boost_archive<T>,
            mpl::identity<boost_archive_output>,
            mpl::identity<default_output>
        >
    >::type impl_t;

    impl_t::call(out, psz);
}


#endif
