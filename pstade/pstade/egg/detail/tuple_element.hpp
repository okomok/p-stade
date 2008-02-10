#ifndef PSTADE_EGG_DETAIL_TUPLE_ELEMENT_HPP
#define PSTADE_EGG_DETAIL_TUPLE_ELEMENT_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/remove_const.hpp>


namespace pstade { namespace egg { namespace detail {


    template<int N, class Tuple>
    struct tuple_element :
        boost::tuples::element<N, typename boost::remove_const<Tuple>::type>
    { };


} } } // namespace pstade::egg::detail


#endif
