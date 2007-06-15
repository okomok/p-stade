#ifndef PSTADE_GRAVY_C_STR_HPP
#define PSTADE_GRAVY_C_STR_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/basic_string_fwd.hpp>
#include <pstade/auxiliary.hpp>
#include "./sdk/tchar.hpp"


namespace pstade_gravy_extension {


    struct c_str { };

    
    template< class Traits, class Alloc > inline
    TCHAR const *pstade_gravy_(c_str, std::basic_string<TCHAR, Traits, Alloc> const& str)
    {
        return str.c_str();
    }


    inline
    TCHAR const *pstade_gravy_(c_str, TCHAR const *psz)
    {
        return psz;
    }


} // namespace pstade_gravy_extension


namespace pstade { namespace gravy {


    namespace c_str_detail {


        template<class X> inline
        TCHAR const *pstade_gravy_c_str(X const& x)
        {
            return pstade_gravy_(pstade_gravy_extension::c_str(), x);
        }


        struct op
        {
            typedef  TCHAR const *result_type;

            template<class CStringizable>
            TCHAR const *operator()(CStringizable const& str) const
            {
                return pstade_gravy_c_str(str);
            }
        };


    } // namespace c_str_detail


    PSTADE_AUXILIARY(0, c_str, (c_str_detail::op))


} } // namespace pstade::gravy


#endif
