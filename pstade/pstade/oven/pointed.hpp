#ifndef PSTADE_OVEN_POINTED_HPP
#define PSTADE_OVEN_POINTED_HPP
#include "./detail/prefix.hpp"


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
#include <pstade/egg/copy.hpp>
#include <pstade/nullptr.hpp>
#include "./concepts.hpp"
#include "./detail/base_to_adaptor.hpp"
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
    struct base
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

            return aux_(boost::addressof(*first), egg::copy<std::ptrdiff_t>(last - first));
        }

        result_type aux_(ptr_t p, std::ptrdiff_t d) const
        {
            return result_type(p, p + d);
        }
    };


} // namespace pointed_detail


PSTADE_OVEN_BASE_TO_ADAPTOR(pointed, (pointed_detail::base<_>))


} } // namespace pstade::oven


#endif
