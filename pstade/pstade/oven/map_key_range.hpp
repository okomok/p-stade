#ifndef PSTADE_OVEN_MAP_KEY_RANGE_HPP
#define PSTADE_OVEN_MAP_KEY_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Synonym of:
//
// 'first_range'


#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./detail/concept_check.hpp"
#include "./first_range.hpp"


namespace pstade { namespace oven {


namespace map_key_range_detail {


    template< class AssocContainer >
    struct super_
    {
        typedef first_range<
            AssocContainer
        > type;
    };


} // namespace map_key_range_detail


template< class AssocContainer >
struct map_key_range :
    map_key_range_detail::super_<AssocContainer>::type,
    private as_lightweight_proxy< map_key_range<AssocContainer> >
{
    typedef AssocContainer pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(AssocContainer, SinglePassRangeConcept);
    typedef typename map_key_range_detail::super_<AssocContainer>::type super_t;

public:
    explicit map_key_range(AssocContainer& ac) :
        super_t(ac)
    { }
};


namespace map_key_range_detail {


    struct baby_generator
    {
        template< class Unused, class AssocContainer >
        struct result
        {
            typedef map_key_range<AssocContainer> const type;
        };

        template< class Result, class AssocContainer >
        Result call(AssocContainer& ac)
        {
            return Result(ac);
        }
    };


} // namespace map_key_range_detail


PSTADE_EGG_FUNCTION(make_map_key_range, map_key_range_detail::baby_generator)
PSTADE_EGG_PIPABLE(map_keys, map_key_range_detail::baby_generator)


} } // namespace pstade::oven


#endif
