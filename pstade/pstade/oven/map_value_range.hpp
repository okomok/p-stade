#ifndef PSTADE_OVEN_MAP_VALUE_RANGE_HPP
#define PSTADE_OVEN_MAP_VALUE_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Synonym of:
//
// 'second_range'


#include <pstade/egg/function.hpp>
#include "./detail/concept_check.hpp"
#include "./lightweight_proxy.hpp"
#include "./range_adaptor.hpp"
#include "./second_range.hpp"


namespace pstade { namespace oven {


namespace map_value_range_detail {


    template< class AssocContainer >
    struct super_
    {
        typedef second_range<
            AssocContainer
        > type;
    };


} // namespace map_value_range_detail


template< class AssocContainer >
struct map_value_range :
    map_value_range_detail::super_<AssocContainer>::type,
    private lightweight_proxy< map_value_range<AssocContainer> >
{
    typedef AssocContainer pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(AssocContainer, SinglePassRangeConcept);
    typedef typename map_value_range_detail::super_<AssocContainer>::type super_t;

public:
    explicit map_value_range(AssocContainer& ac) :
        super_t(ac)
    { }
};


namespace map_value_range_detail {


    struct baby_generator
    {
        template< class Unused, class AssocContainer >
        struct result
        {
            typedef map_value_range<AssocContainer> const type;
        };

        template< class Result, class AssocContainer >
        Result call(AssocContainer& ac)
        {
            return Result(ac);
        }
    };


} // namespace map_value_range_detail


PSTADE_EGG_FUNCTION(make_map_value_range, map_value_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(map_values, map_value_range_detail::baby_generator)


} } // namespace pstade::oven


#endif
