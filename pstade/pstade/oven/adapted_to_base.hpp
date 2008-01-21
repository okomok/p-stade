#ifndef PSTADE_OVEN_ADAPTED_TO_BASE_HPP
#define PSTADE_OVEN_ADAPTED_TO_BASE_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Question:
//
// 'is_convertible' is over-optimistic?
// Meanwhile, 'iterator_cast' uses 'is_same'.
//
// Can this function be used for more generic usage?
// If it can, give it a better name?
//
// This implementation is slightly complicated than
// 'iterator_cast' in order to support a reference
// type as 'Base'. Any pitfalls?


// References:
//
// [1] Eric Niebler, iterator_cast, Boost.RangeEx, 2004.
//     http://www.boost-consulting.com/vault/index.php?directory=Algorithms


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/egg/adapted_to_base.hpp>
#include <pstade/egg/ambi.hpp>
#include <pstade/egg/automatic.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/specified.hpp>
#include <pstade/pod_constant.hpp>
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


using egg::X_adapted_to;
using egg::adapted_to;
using egg::to_base;


namespace adapted_range_to_detail {


    template< class Base >
    struct little
    {
        template< class Myself, class Adapted >
        struct apply
        {
            typedef Base type;
        };

        template< class Result, class Adapted >
        Result call(Adapted& ad) const
        {
            typedef typename range_iterator<Result>::type iter_t;
            return Result(
                X_adapted_to<iter_t>()(boost::begin(ad)),
                X_adapted_to<iter_t>()(boost::end(ad))
            );
        }
    };


} // namespace adapted_range_to_detail


template< class Base >
struct X_adapted_range_to :
    egg::function< adapted_range_to_detail::little<Base> >
{ };


#define  PSTADE_EGG_SPECIFIED_PARAMS (adapted_range_to, X_adapted_range_to, (class), (1))
#include PSTADE_EGG_SPECIFIED()


namespace to_base_range_detail {
    typedef egg::automatic< X_adapted_range_to<boost::mpl::_> >::type op;
}

typedef egg::result_of_ambi0<to_base_range_detail::op>::type T_to_base_range;
PSTADE_POD_CONSTANT((T_to_base_range), to_base_range) = PSTADE_EGG_AMBI_L PSTADE_EGG_AUTOMATIC() PSTADE_EGG_AMBI_R;


} } // namespace pstade::oven


#endif
