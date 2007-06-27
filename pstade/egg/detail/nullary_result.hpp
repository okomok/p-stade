#ifndef PSTADE_EGG_DETAIL_NULLARY_RESULT_HPP
#define PSTADE_EGG_DETAIL_NULLARY_RESULT_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <pstade/has_xxx.hpp>
#include <pstade/use_default.hpp>
#include "../error_non_nullary.hpp"


namespace pstade { namespace egg { namespace detail {


    PSTADE_HAS_TYPE(nullary_result_type)


    template<class Baby, class Function>
    struct get_nullary_result :
        if_use_default< typename Baby::nullary_result_type,
            error_non_nullary<Function>,
            typename Baby::nullary_result_type
        >
    { };


    template<class Baby, class Function>
    struct nullary_result :
        boost::mpl::eval_if< has_nullary_result_type<Baby>,
            get_nullary_result<Baby, Function>,
            boost::mpl::identity< error_non_nullary<Function> >
        >
    { };


} } } // namespace pstade::egg::detail


#endif
