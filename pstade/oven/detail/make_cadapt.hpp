#ifndef PSTADE_OVEN_DETAIL_MAKE_CADAPT_HPP
#define PSTADE_OVEN_DETAIL_MAKE_CADAPT_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/function.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/tomato/atl/comcli_fwd.hpp> // CAdapt


namespace pstade { namespace oven {


namespace make_CAdapt_detail {


    struct little
    {
        template< class Myself, class T >
        struct apply
        {
            typedef ATL::CAdapt<typename pass_by_value<T>::type> type;
        };

        template< class Result, class T >
        Result call(T& src) const
        {
            return Result(src);
        }
    };


} // namespace make_CAdapt_detail


typedef egg::function<make_CAdapt_detail::little> T_make_CAdapt;
PSTADE_POD_CONSTANT((T_make_CAdapt), make_CAdapt) = {{}};


} } // namespae pstade::oven


#endif
