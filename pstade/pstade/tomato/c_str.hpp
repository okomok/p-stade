#ifndef PSTADE_TOMATO_C_STR_HPP
#define PSTADE_TOMATO_C_STR_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/utility/enable_if.hpp>
#include <pstade/apple/atl/config.hpp> // ATL_vER, CSIMPLESTRINGT_TEMPLATE_PARAMS/ARGS
#include <pstade/apple/atl/core.hpp> // ::AtlIsValidString
#include <pstade/apple/atl/simpstr_fwd.hpp> // CSimpleStringT
#include <pstade/apple/sdk/tchar.hpp>
#include <pstade/apple/wtl/misc.hpp> // CString
#include <pstade/apple/basic_string_fwd.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/has_xxx.hpp>
#include <pstade/nullptr.hpp>
#include <pstade/overload.hpp>
#include <pstade/static_c.hpp>
#include "./access.hpp"
#include "./boolean_cast.hpp"


namespace pstade { namespace tomato {


namespace c_str_detail {


    inline
    bool is_valid(TCHAR const *psz)
    {
    #if !(PSTADE_APPLE_ATL_VER < 0x0700)

        return ATL::AtlIsValidString(psz)|booleanized;

    #else

        // See:
        // ATL7::AtlIsValidString

        #if defined(NDEBUG)

            return (psz != PSTADE_NULLPTR);

        #else

            if (psz == PSTADE_NULLPTR)
                return false;

            typedef static_c<std::ptrdiff_t, 1398269> faraway;

            __try {
                TCHAR const *pch = psz;
                TCHAR const *pchEnd = psz + faraway::value - 1;
                TCHAR ch = *(volatile TCHAR *)pch;
                while ((ch != _T('\0')) && (pch != pchEnd)) {
                    ++pch;
                    ch = *(volatile TCHAR *)pch;

                    if (pch == pchEnd) {
                        BOOST_ASSERT("null-terminated string candidate is too long to diagnose." && false);
                    }
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER) {
                return false;
            }

            return true;

        #endif

    #endif // !(PSTADE_APPLE_ATL_VER < 0x0700)
    }


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

        // Note:
        // 'has_xxx' works only with "class".
        template< class Result >
        Result call(TCHAR const *psz)
        {
            return psz;
        }

        template< class Result, class CStringizable >
        Result call(CStringizable const& str)
        {
            Result result = c_str_detail::aux(str);
            BOOST_ASSERT(c_str_detail::is_valid(result));
            return result;
        }
    };


} // namespace c_str_detail


PSTADE_EGG_FUNCTION(c_str, c_str_detail::baby)
PSTADE_EGG_PIPABLE(c_stringized, c_str_detail::baby)


} } // namespace pstade::tomato


// predefined customizations
//


TCHAR const *
pstade_tomato_c_str(WTL::CString const& str, pstade::overload<>)
{
    return str;
}


// Note:
// 'enable_if<is_ATL_CSimpleStringT,...>' is useless here, which ignores class hierarchy.
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
