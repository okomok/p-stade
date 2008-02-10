#ifndef PSTADE_EGG_DETAIL_RESULT_OF_TUPLE_GET_HPP
#define PSTADE_EGG_DETAIL_RESULT_OF_TUPLE_GET_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/affect.hpp>
#include "./tuple_element.hpp"


namespace pstade { namespace egg { namespace detail {


    template<int N, class Tuple>
    struct result_of_tuple_get :
        affect<
            Tuple&,
            typename tuple_element<N, Tuple>::type
        >
    { };


} } } // namespace pstade::egg::detail


#endif
