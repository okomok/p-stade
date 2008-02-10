#ifndef PSTADE_EGG_DETAIL_TUPLE_LENGTH_HPP
#define PSTADE_EGG_DETAIL_TUPLE_LENGTH_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/int.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/remove_const.hpp>


namespace pstade { namespace egg { namespace detail {


    // It is guaranteed to return `int_`.
    template<class Tuple>
    struct tuple_length :
        boost::mpl::int_<
            boost::tuples::length<typename boost::remove_const<Tuple>::type>::value
        >
    { };


} } } // namespace pstade::egg::detail


#endif
