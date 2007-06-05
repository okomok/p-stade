#ifndef PSTADE_OVEN_POINTED_HPP
#define PSTADE_OVEN_POINTED_HPP
#include "./prelude.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // ptrdiff_t
#include <boost/mpl/assert.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/addressof.hpp>
#include <pstade/copy_construct.hpp>
#include <pstade/function.hpp>
#include <pstade/nullptr.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_reference.hpp"


namespace pstade { namespace oven {


namespace pointed_detail {


    // 'range_pointer' seems useless.
    template< class Reference >
    struct to_pointer :
        boost::add_pointer<
            typename boost::remove_reference<Reference>::type
        >
    { };


    template< class ContiguousRange >
    struct baby
    {
        typedef typename
            to_pointer<
                typename range_reference<ContiguousRange>::type
            >::type
        ptr_t;

        typedef
            iter_range<ptr_t> const
        result_type;

        result_type operator()(ContiguousRange& rng) const
        {
            PSTADE_CONCEPT_ASSERT((RandomAccess<ContiguousRange>));
            return aux(boost::begin(rng), boost::end(rng));    
        }

        template< class Iterator >
        result_type aux(Iterator first, Iterator last) const
        {
            if (first == last)
                return result_type(null_<ptr_t>(), null_<ptr_t>());

            return aux_(boost::addressof(*first), pstade::copy_construct<std::ptrdiff_t>(last - first));
        }

        result_type aux_(ptr_t p, std::ptrdiff_t d) const
        {
            return result_type(p, p + d);
        }
    };


} // namespace pointed_detail


PSTADE_FUNCTION(make_pointed, (pointed_detail::baby<_>))
PSTADE_PIPABLE(pointed, (op_make_pointed))


} } // namespace pstade::oven


#endif
