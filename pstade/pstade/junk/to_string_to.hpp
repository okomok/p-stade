#ifndef PSTADE_TO_STRING_TO_HPP
#define PSTADE_TO_STRING_TO_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n1973.html


#include <boost/lexical_cast.hpp>
#include <pstade/apple/basic_string_fwd.hpp>
#include <pstade/egg/baby_auto.hpp>
#include <pstade/egg/pipable.hpp>


namespace pstade {


// string_to
//

template< class To, class CharT, class Traits, class Alloc > inline
To string_to(std::basic_string<CharT, Traits, Alloc> const& str)
{
    return boost::lexical_cast<To>(str);
}


template< class To, class CharT > inline
To string_to(CharT const *str)
{
    return boost::lexical_cast<To>(str);
}


struct string_to_class
{
    template< class To, class From >
    static To call(From const& from)
    {
        return pstade::string_to<To>(from);
    }
};

PSTADE_EGG_PIPABLE(unstrung, egg::baby_auto<string_to_class>)


// to_string
//

template< class CharT, class T > inline
std::basic_string<CharT> to_basic_string(const T& x)
{
    return boost::lexical_cast< std::basic_string<CharT> >(x);
}


template< class CharT >
struct baby_to_string
{
    template< class Unused, class T >
    struct result
    {
        typedef std::basic_string<CharT> const type;
    };

    template< class Result, class T >
    Result call(T const& x)
    {
        return boost::lexical_cast< std::basic_string<CharT> >(x);
    };
};

PSTADE_EGG_PIPABLE(to_string,  baby_to_string<char>)
PSTADE_EGG_PIPABLE(to_wstring, baby_to_string<wchar_t>)


} // namespace pstade


#endif
