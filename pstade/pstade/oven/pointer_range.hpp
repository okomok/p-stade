#ifndef PSTADE_OVEN_POINTER_RANGE_HPP
#define PSTADE_OVEN_POINTER_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/assert.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/utility/addressof.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/nullptr.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./distance.hpp"
#include "./range_pointer.hpp"


namespace pstade { namespace oven {


namespace pointer_range_detail {


    template< class ContiguousRange >
    struct super_
    {
        typedef boost::iterator_range<
            typename range_pointer<ContiguousRange>::type
        > type;
    };


    template< class Super, class ContiguousRange >
    Super make(ContiguousRange& vec)
    {
        typedef typename Super::iterator iter_t;
        BOOST_MPL_ASSERT((boost::is_pointer<iter_t>));

        if (boost::empty(vec))
            return Super(iter_t(PSTADE_NULLPTR), iter_t(PSTADE_NULLPTR));

        return Super(
            boost::addressof( *boost::begin(vec) ),
            boost::addressof( *boost::begin(vec) ) + oven::distance(vec)
        );
    }


} // namespace pointer_range_detail


template< class ContiguousRange >
struct pointer_range :
    pointer_range_detail::super_<ContiguousRange>::type,
    private as_lightweight_proxy< pointer_range<ContiguousRange> >
{
    PSTADE_CONCEPT_ASSERT((RandomAccess<ContiguousRange>));

private:
    typedef typename pointer_range_detail::super_<ContiguousRange>::type super_t;

public:
    explicit pointer_range(ContiguousRange& vec) :
        super_t(pointer_range_detail::make<super_t>(vec))
    { }

    typedef ContiguousRange pstade_oven_range_base_type;
};


namespace pointer_range_detail {


    struct baby_make
    {
        template< class Myself, class ContiguousRange >
        struct apply
        {
            typedef pointer_range<ContiguousRange> const type;
        };

        template< class Result, class ContiguousRange >
        Result call(ContiguousRange& rng)
        {
            return Result(rng);
        }
    };


} // namespace pointer_range_detail



PSTADE_EGG_FUNCTION(make_pointer_range, pointer_range_detail::baby_make)
PSTADE_EGG_PIPABLE(pointers, pointer_range_detail::baby_make)


} } // namespace pstade::oven


#endif
