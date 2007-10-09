#ifndef PSTADE_GRAVY_C_STR_HPP
#define PSTADE_GRAVY_C_STR_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/basic_string_fwd.hpp>
#include <pstade/egg/auxiliary.hpp>
#include <pstade/pod_constant.hpp>
#include "./sdk/tchar.hpp"


namespace pstade_gravy_extension {


    struct c_str { };

    
    template<class Traits, class Alloc> inline
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


    typedef egg::result_of_auxiliary0<c_str_detail::op>::type T_c_str;
    PSTADE_POD_CONSTANT((T_c_str), c_str) = PSTADE_EGG_AUXILIARY_L {} PSTADE_EGG_AUXILIARY_R;


} } // namespace pstade::gravy


#endif
