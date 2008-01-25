#ifndef PSTADE_EGG_DETAIL_NULLARY_RESULT_OF_LITTLE_HPP
#define PSTADE_EGG_DETAIL_NULLARY_RESULT_OF_LITTLE_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <pstade/has_xxx.hpp>
#include <pstade/use_default.hpp>
#include "../function_fwd.hpp"
#include "./unspecified.hpp"


template<class Function>
struct PSTADE_EGG_ERROR_NON_NULLARY;


namespace pstade { namespace egg { namespace detail {


    PSTADE_HAS_TYPE(nullary_result_type)


    template<class Little, class Function>
    struct get_nullary_result_of_little :
        if_use_default< typename Little::nullary_result_type,
            PSTADE_EGG_ERROR_NON_NULLARY<Function>,
            typename Little::nullary_result_type
        >
    { };


    template<class Little, class Function = function<Little, PSTADE_EGG_UNSPECIFIED> >
    struct nullary_result_of_little :
        boost::mpl::eval_if< has_nullary_result_type<Little>,
            get_nullary_result_of_little<Little, Function>,
            boost::mpl::identity< PSTADE_EGG_ERROR_NON_NULLARY<Function> >
        >
    { };


} } }// namespace pstade::egg::detail


#endif
