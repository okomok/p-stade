#ifndef PSTADE_OVEN_MAP_VALUE_RANGE_HPP
#define PSTADE_OVEN_MAP_VALUE_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/transform_iterator.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <pstade/egg/function.hpp>
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"
#include "./range_iterator_type.hpp"


namespace pstade { namespace oven {


namespace map_value_range_detail {


    template< class AssocContainer >
    struct get_value
    {
        typedef typename AssocContainer::mapped_type& result_type;

        template< class PairT >
        result_type operator()(PairT& p) const
        {
            return p.second;
        }
    };


    template< class AssocContainer >
    struct super_
    {
        typedef boost::iterator_range<
            boost::transform_iterator<
                get_value<AssocContainer>,
                typename range_iterator<AssocContainer>::type
            >
        > type;
    };


} // namespace map_value_range_detail


template< class AssocContainer >
struct map_value_range :
    map_value_range_detail::super_<AssocContainer>::type
{
private:
    typedef typename map_value_range_detail::super_<AssocContainer>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    explicit map_value_range(AssocContainer& ac) :
    super_t(
        iter_t(boost::begin(ac), map_value_range_detail::get_value<AssocContainer>()),
        iter_t(boost::end(ac), map_value_range_detail::get_value<AssocContainer>())
    )
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


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::map_value_range, 1)


#endif
