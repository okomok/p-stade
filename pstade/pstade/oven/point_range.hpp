#ifndef PSTADE_OVEN_POINT_RANGE_HPP
#define PSTADE_OVEN_POINT_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/assert.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/utility/addressof.hpp>
#include <pstade/nullptr.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./distance.hpp"
#include "./iter_range.hpp"
#include "./range_pointer.hpp"


namespace pstade { namespace oven {


namespace point_range_detail {


    template< class ContiguousRange >
    struct super_ :
        iter_range<
            typename range_pointer<ContiguousRange>::type
        >
    { };


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


} // namespace point_range_detail


template< class ContiguousRange >
struct point_range :
    point_range_detail::super_<ContiguousRange>::type,
    private as_lightweight_proxy< point_range<ContiguousRange> >
{
    PSTADE_CONCEPT_ASSERT((RandomAccess<ContiguousRange>));
    typedef point_range type;

private:
    typedef typename point_range_detail::super_<ContiguousRange>::type super_t;

public:
    explicit point_range(ContiguousRange& vec) :
        super_t(point_range_detail::make<super_t>(vec))
    { }

    typedef ContiguousRange pstade_oven_range_base_type;
};


PSTADE_OBJECT_GENERATOR(make_point_range,
    (point_range< deduce_to_qualified<from_1> >) const)
PSTADE_PIPABLE(pointed, (op_make_point_range))


} } // namespace pstade::oven


#endif
