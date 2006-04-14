#ifndef BOOST_MICROSOFT_WTL_REGEX_HPP
#define BOOST_MICROSOFT_WTL_REGEX_HPP


// Boost.Microsoft
//
// Copyright 2006 Shunsuke Sogame.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


/*
 *
 * Copyright (c) 2004
 * John Maddock
 *
 * Use, modification and distribution are subject to the 
 * Boost Software License, Version 1.0. (See accompanying file 
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */


#include <boost/microsoft/wtl/misc.h> // WTL::CString
#include <boost/microsoft/wtl/range/string.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/regex.hpp>
#include <boost/regex/mfc.hpp>


namespace boost {


// regex creation functions
inline
basic_regex<TCHAR> make_regex(
    const WTL::CString& s,
    regex_constants::syntax_option_type f = regex_constants::normal
)
{
    basic_regex<TCHAR> result(boost::begin(s), boost::end(s), f);
    return result;
}

// regex_match overloads
template< class A, class T > inline
bool regex_match(
    const WTL::CString& s,
    match_results<const TCHAR *, A>& what,
    const basic_regex<TCHAR, T>& e,
    regex_constants::match_flag_type f = regex_constants::match_default
)
{
    return boost::regex_match(boost::begin(s), boost::end(s), what, e, f);
}

template< class T > inline
bool regex_match(
    const WTL::CString& s,
    const basic_regex<TCHAR, T>& e,
    regex_constants::match_flag_type f = regex_constants::match_default
)
{
    return boost::regex_match(boost::begin(s), boost::end(s), e, f);
}


// regex_search overloads
template< class A, class T > inline
bool regex_search(
    const WTL::CString& s,
    match_results<const TCHAR *, A>& what,
    const basic_regex<TCHAR, T>& e,
    regex_constants::match_flag_type f = regex_constants::match_default
)
{
    return boost::regex_search(boost::begin(s), boost::end(s), what, e, f);
}

template< class T > inline
bool regex_search(
    const WTL::CString& s,
    const basic_regex<TCHAR, T>& e,
    regex_constants::match_flag_type f = regex_constants::match_default
)
{
    return boost::regex_search(boost::begin(s), boost::end(s), e, f);
}

// regex_iterator creation
inline
regex_iterator<const TCHAR *> make_regex_iterator(
    const WTL::CString& s,
    const basic_regex<TCHAR>& e,
    regex_constants::match_flag_type f = regex_constants::match_default
)
{
    regex_iterator<const TCHAR *> result(boost::begin(s), boost::end(s), e, f);
    return result;
}

inline
regex_token_iterator<const TCHAR *> make_regex_token_iterator(
    const WTL::CString& s,
    const basic_regex<TCHAR>& e, int sub = 0,
    regex_constants::match_flag_type f = regex_constants::match_default
)
{
    regex_token_iterator<const TCHAR *> result(boost::begin(s), boost::end(s), e, sub, f);
    return result;
}

inline
regex_token_iterator<const TCHAR *> make_regex_token_iterator(
    const WTL::CString& s,
    const basic_regex<TCHAR>& e,
    const std::vector<int>& subs,
    regex_constants::match_flag_type f = regex_constants::match_default
)
{
    regex_token_iterator<const TCHAR *> result(boost::begin(s), boost::end(s), e, subs, f);
    return result;
}

template< std::size_t N > inline
regex_token_iterator<const TCHAR *> make_regex_token_iterator(
    const WTL::CString& s,
    const basic_regex<TCHAR>& e,
    const int (& subs)[N],
    regex_constants::match_flag_type f = regex_constants::match_default
)
{
    regex_token_iterator<const TCHAR *> result(boost::begin(s), boost::end(s), e, subs, f);
    return result;
}

template< class OutputIter, class BidiIter, class Traits > inline
OutputIter regex_replace(
    OutputIter out,
    BidiIter first,
    BidiIter last,
    const basic_regex<TCHAR, Traits>& e,
    const WTL::CString& fmt,
    match_flag_type flags = match_default)
{
    return boost::regex_replace(out, first, last, e, begin(fmt), flags);
}

/* TODO
template< class Traits > inline
WTL::CString regex_replace(
    const WTL::CString& s,
    const basic_regex<TCHAR, Traits>& e,
    const WTL::CString& fmt,
    match_flag_type flags = match_default)
{
    WTL::CString result;
    boost::regex_replace(pstade::stove::back_inserter(result), boost::begin(s), boost::end(s), e, begin(fmt), flags);
    return result;
}
*/

} // namespace boost


#endif
