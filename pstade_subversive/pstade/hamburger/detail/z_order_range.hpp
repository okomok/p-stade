#ifndef PSTADE_HAMBURGER_DETAIL_Z_ORDER_RANGE_HPP
#define PSTADE_HAMBURGER_DETAIL_Z_ORDER_RANGE_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Copyable for BOOST_FOREACH.
// Yet another oven range candidate?


#include <algorithm> //sort
#include <vector>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/shared_ptr.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/garlic/back_inserter.hpp>
#include <pstade/lexical_cast.hpp>
#include <pstade/oven/copy.hpp>
#include <pstade/oven/direct_range.hpp>
#include <pstade/oven/indirect_range.hpp>
#include <pstade/oven/is_lightweight_proxy.hpp>
#include <pstade/oven/range_adaptor.hpp>
#include <pstade/oven/share_range.hpp>
#include "../element.hpp"


namespace pstade { namespace hamburger { namespace detail {


namespace z_order_range_detail {


    struct order
    {
        template< class Iterator >
        bool operator()(Iterator it1, Iterator it2) const
        {
            int zIndex1 = pstade::lexical(it1->att(Name_zIndex));
            int zIndex2 = pstade::lexical(it2->att(Name_zIndex));
            return zIndex1 < zIndex2;
        }
    };


    template< class NodeRange >
    struct storage_box
    {
        typedef typename boost::range_result_iterator<NodeRange>::type iter_t;
        typedef std::vector<iter_t> storage_type;

        explicit storage_box(NodeRange& rng) :
           m_its(new storage_type())
        {
            oven::copy(rng|oven::directed, garlic::back_inserter(*m_its));
            std::sort(boost::begin(*m_its), boost::end(*m_its), order());
        }

    protected:
         oven::share_range<storage_type> m_its;
    };


    template< class NodeRange >
    struct super_
    {
        typedef oven::indirect_range<
            oven::share_range<
                typename storage_box<NodeRange>::storage_type
            >
        > type;
    };


} // namespace z_order_range_detail


template< class NodeRange >
struct z_order_range :
    z_order_range_detail::storage_box<NodeRange>,
    z_order_range_detail::super_<NodeRange>::type
{
private:
    typedef z_order_range_detail::storage_box<NodeRange> box_t;
    typedef typename z_order_range_detail::super_<NodeRange>::type super_t;

public:
    explicit z_order_range(NodeRange& rng) :
        box_t(rng),
        super_t(box_t::m_its)
    { }
};


namespace z_order_range_detail {


    struct baby_generator
    {
        template< class NodeRange >
        struct result
        {
            typedef z_order_range<NodeRange> type;
        };

        template< class Result, class NodeRange >
        Result call(NodeRange& rng)
        {
            return Result(rng);
        }
    };


} // namespace z_order_range_detail


PSTADE_EGG_FUNCTION(make_z_order_range, z_order_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(z_ordered, z_order_range_detail::baby_generator)


} } } // namespace pstade::hamburger::detail


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::hamburger::detail::z_order_range, 1)


#endif
