#ifndef PSTADE_OVEN_POINTED_HPP
#define PSTADE_OVEN_POINTED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/assert.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/utility/addressof.hpp>
#include <pstade/function.hpp>
#include <pstade/nullptr.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./distance.hpp"
#include "./iter_range.hpp"
#include "./range_pointer.hpp"


namespace pstade { namespace oven {


namespace pointed_detail {


    template< class ContiguousRange >
    struct baby
    {
        PSTADE_CONCEPT_ASSERT((RandomAccess<ContiguousRange>));

        typedef
            typename range_pointer<ContiguousRange>::type
        ptr_t;

        typedef
            iter_range<ptr_t> const
        result;

        result call(ContiguousRange& rng)
        {
            if (boost::empty(rng))
                return result(ptr_t(PSTADE_NULLPTR), ptr_t(PSTADE_NULLPTR));

            return result(
                boost::addressof( *boost::begin(rng) ),
                boost::addressof( *boost::begin(rng) ) + oven::distance(rng)
            );
        }
    };


} // namespace pointed_detail


PSTADE_FUNCTION(make_pointed, (pointed_detail::baby<_>))
PSTADE_PIPABLE(pointed, (op_make_pointed))


} } // namespace pstade::oven


#endif
