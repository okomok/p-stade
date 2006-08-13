#ifndef PSTADE_TOMATO_C_STR_HPP
#define PSTADE_TOMATO_C_STR_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/utility/enable_if.hpp>
#include <pstade/apple/atl/config.hpp> // CSIMPLESTRINGT_TEMPLATE_PARAMS/ARGS
#include <pstade/apple/atl/simpstr_fwd.hpp> // CSimpleStringT
#include <pstade/apple/sdk/tchar.hpp>
#include <pstade/apple/wtl/misc.hpp> // CString
#include <pstade/apple/basic_string_fwd.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/has_xxx.hpp>
#include <pstade/oven/range_adaptor.hpp>
#include <pstade/overload.hpp>
#include "./access.hpp"


namespace pstade { namespace tomato {


namespace c_str_detail {


    PSTADE_HAS_TYPE(pstade_tomato_cstringizable)


    // member function
    //
    template< class T > inline
    typename boost::enable_if<has_pstade_tomato_cstringizable<T>,
    TCHAR const *>::type aux(T const& str)
    {
        return access::detail_c_str(str);
    }


    // ADL
    //
    template< class T > inline
    TCHAR const *pstade_tomato_c_str(T const& str)
    {
        return pstade_tomato_c_str(str, overload<>());
    }

    template< class T > inline
    typename boost::disable_if<has_pstade_tomato_cstringizable<T>,
    TCHAR const *>::type aux(T const& str)
    {
        return pstade_tomato_c_str(str);
    }


    struct baby
    {
        template< class Unused, class CStringizable >
        struct result
        {
            typedef TCHAR const *type;
        };

        template< class Result, class CStringizable >
        Result call(CStringizable const& str)
        {
            return c_str_detail::aux(str);
        }
    };


} // namespace c_str_detail


PSTADE_EGG_FUNCTION(c_str, c_str_detail::baby)
PSTADE_OVEN_RANGE_ADAPTOR(c_stringized, c_str_detail::baby)


} } // namespace pstade::tomato


// predefined customizations
//

inline
TCHAR const *
pstade_tomato_c_str(TCHAR const *psz, pstade::overload<>)
{
    return psz;
}


template< class T > inline
TCHAR const *
pstade_tomato_c_str(WTL::CString const& str, pstade::overload<>)
{
    return str;
}


template< PSTADE_APPLE_ATL_CSIMPLESTRINGT_TEMPLATE_PARAMS > inline
BaseType const *
pstade_tomato_c_str(ATL::CSimpleStringT< PSTADE_APPLE_ATL_CSIMPLESTRINGT_TEMPLATE_ARGS > const& str, pstade::overload<>)
{
    return str;
}


template< class Traits, class Alloc > inline
TCHAR const *
pstade_tomato_c_str(std::basic_string<TCHAR, Traits, Alloc> const& str, pstade::overload<>)
{
    return str.c_str();
}


#endif
