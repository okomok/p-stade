#ifndef PSTADE_TOMATO_C_STR_HPP
#define PSTADE_TOMATO_C_STR_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <pstade/apple/atl/config.hpp> // ATL_VER, CSIMPLESTRINGT_TEMPLATE_PARAMS/ARGS
#include <pstade/apple/atl/core.hpp> // ::AtlIsValidString
#include <pstade/apple/atl/simpstr_fwd.hpp> // CSimpleStringT
#include <pstade/apple/sdk/tchar.hpp>
#include <pstade/apple/wtl/misc.hpp> // CString
#include <pstade/apple/basic_string_fwd.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pipable.hpp>
#include <pstade/nullptr.hpp>
#include <pstade/static_c.hpp>
#include "./boolean_cast.hpp"


// c_str extension space
//

namespace pstade_tomato_extension {


    struct c_str { };


} // namespace pstade_tomato_extension


namespace pstade { namespace tomato {


// c_str
//

namespace c_str_detail {


    inline
    bool invariant(TCHAR const *psz)
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

                    BOOST_ASSERT("null-terminated string candidate is too long to diagnose." && pch != pchEnd);
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER) {
                return false;
            }

            return true;

        #endif

    #endif // !(PSTADE_APPLE_ATL_VER < 0x0700)
    }


    template< class T > inline
    TCHAR const *pstade_tomato_c_str(T const& str)
    {
        return pstade_tomato_(pstade_tomato_extension::c_str(), str);
    }

    template< class T > inline
    TCHAR const *aux(T const& str)
    {
        return pstade_tomato_c_str(str);
    }


} // namespace c_str_detail


struct op_c_str :
    callable<op_c_str>
{
    template< class Myself, class CStringizable >
    struct apply
    {
        typedef TCHAR const *type;
    };

    // 'has_xxx' works only with "class".
    template< class Result >
    Result call(TCHAR const *psz) const
    {
        return psz;
    }

    template< class Result, class CStringizable >
    Result call(CStringizable const& str) const
    {
        Result result = c_str_detail::aux(str);
        BOOST_ASSERT(c_str_detail::invariant(result));
        return result;
    }
};


PSTADE_CONSTANT(c_str, op_c_str)
PSTADE_PIPABLE(to_c_str, op_c_str)


} } // namespace pstade::tomato


// predefined extensions
//

namespace pstade_tomato_extension {


    TCHAR const *
    pstade_tomato_(c_str, WTL::CString const& str)
    {
        return str;
    }


    // 'enable_if<is_ATL_CSimpleStringT,...>' is useless here, which ignores class hierarchy.
    template< PSTADE_APPLE_ATL_CSIMPLESTRINGT_TEMPLATE_PARAMS > inline
    BaseType const *
    pstade_tomato_(c_str, ATL::CSimpleStringT< PSTADE_APPLE_ATL_CSIMPLESTRINGT_TEMPLATE_ARGS > const& str)
    {
        return str;
    }


    template< class Traits, class Alloc > inline
    TCHAR const *
    pstade_tomato_(c_str, std::basic_string<TCHAR, Traits, Alloc> const& str)
    {
        return str.c_str();
    }


} // namespace pstade_tomato_extension


#endif
