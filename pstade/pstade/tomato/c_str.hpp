#ifndef PSTADE_TOMATO_C_STR_HPP
#define PSTADE_TOMATO_C_STR_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/atl/config.hpp> // CSIMPLESTRINGT_TEMPLATE_PARAMS/ARGS
#include <boost/microsoft/atl/simpstr_fwd.hpp> // CSimpleStringT
#include <boost/microsoft/sdk/tchar.hpp>
#include <boost/microsoft/wtl/misc.hpp> // CString
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <pstade/apple/basic_string_fwd.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/has_xxx.hpp>
#include <pstade/oven/range_adaptor.hpp>
#include <pstade/overload.hpp>


namespace pstade { namespace tomato {


class c_str_access
{
public:
    template< class T > static
    const TCHAR *detail_call(const T& str)
    {
        return str.pstade_tomato_c_str();
    }
};


namespace c_str_detail {


    PSTADE_HAS_TYPE(pstade_tomato_cstringizable)


    struct member_function
    {
        template< class T > static
        const TCHAR *call(const T& str)
        {
            return c_str_access::detail_call(str);
        }
    };


    template< class T > inline
    const TCHAR *
    pstade_tomato_c_str(const T& str)
    {
        return pstade_tomato_c_str(str, overload());
    }


    struct adl_customization
    {
        template< class T > static
        const TCHAR *call(const T& str)
        {
            return pstade_tomato_c_str(str);
        }
    };


    template< class CStringizable > inline
    const TCHAR *aux(const CStringizable& str)
    {
        typedef typename
        boost::mpl::if_< has_pstade_tomato_cstringizable<CStringizable>,
            member_function,
            adl_customization
        >::type impl_t;

        return impl_t::call(str);
    }


    struct baby
    {
        template< class CStringizable >
        struct apply : boost::mpl::identity<
            const TCHAR *
        >
        { };

        template< class Result, class CStringizable >
        Result call(const CStringizable& str)
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
const TCHAR *
pstade_tomato_c_str(const TCHAR *psz, pstade::overload)
{
    return psz;
}


template< class T > inline
const TCHAR *
pstade_tomato_c_str(const WTL::CString& str, pstade::overload)
{
    return str;
}


template< BOOST_MICROSOFT_ATL_CSIMPLESTRINGT_TEMPLATE_PARAMS > inline
const BaseType *
pstade_tomato_c_str(const ATL::CSimpleStringT< BOOST_MICROSOFT_ATL_CSIMPLESTRINGT_TEMPLATE_ARGS >& str, pstade::overload)
{
    return str;
}


template< class Traits, class Alloc > inline
const TCHAR *
pstade_tomato_c_str(const std::basic_string<TCHAR, Traits, Alloc>& str, pstade::overload)
{
    return str.c_str();
}


#endif
