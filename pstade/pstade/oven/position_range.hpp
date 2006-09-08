#ifndef PSTADE_OVEN_POSITION_RANGE_HPP
#define PSTADE_OVEN_POSITION_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/iterator_range.hpp>
#include <boost/spirit/iterator/position_iterator.hpp>
#include <pstade/egg/by_value.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/static_c.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./detail/concept_check.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace position_range_detail {


    struct default_tabchars :
        static_c<int, 4>
    { };


    template<
        class ForwardRange,
        class PositionT
    >
    struct super_
    {
        typedef boost::iterator_range<
            boost::spirit::position_iterator2< // 2!
                typename range_iterator<ForwardRange>::type,
                PositionT
            >
        > type;
    };


    template< class PositionIter, class ForwardRange, class PositionT >
    PositionIter make_first(ForwardRange& rng, PositionT const& pos, int tabchars)
    {
        PositionIter pit(boost::begin(rng), boost::end(rng), pos);
        pit.set_tabchars(tabchars);
        return pit;
    }


} // namespace position_range_detail


template<
    class ForwardRange,
    class PositionT = boost::spirit::file_position
>
struct position_range :
    position_range_detail::super_<ForwardRange, PositionT>::type,
    private as_lightweight_proxy< position_range<ForwardRange, PositionT> >
{
    typedef ForwardRange pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(ForwardRange, ForwardRangeConcept);
    typedef typename position_range_detail::super_<ForwardRange, PositionT>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    explicit position_range(
        ForwardRange& rng,
        PositionT const& pos = PositionT(),
        int tabchars = position_range_detail::default_tabchars::value
    ) :
        super_t(
            position_range_detail::make_first<iter_t>(rng, pos, tabchars),
            iter_t()
        )
    { }
};


namespace position_range_detail {


    struct baby_make
    {
        typedef boost::spirit::file_position default_pos_t;

        template< class Unused, class ForwardRange, class PositionT = default_pos_t, class Int = void >
        struct result
        {
            typedef typename egg::by_value<PositionT>::type pos_t;
            typedef position_range<ForwardRange, pos_t> const type;
        };

        template< class Result, class ForwardRange >
        Result call(ForwardRange& rng)
        {
            return Result(rng);
        }

        template< class Result, class ForwardRange, class PositionT >
        Result call(ForwardRange& rng, PositionT const& pos, int tabchars = default_tabchars::value)
        {
            return Result(rng, pos, tabchars);
        }
    };


} // namespace position_range_detail


PSTADE_EGG_FUNCTION(make_position_range, position_range_detail::baby_make)
PSTADE_EGG_PIPABLE(positioned, position_range_detail::baby_make)


} } // namespace pstade::oven


#endif
