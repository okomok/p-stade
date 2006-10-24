#ifndef PSTADE_OVEN_POSITION_RANGE_HPP
#define PSTADE_OVEN_POSITION_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/spirit/iterator/position_iterator.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/static_c.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace position_range_detail {


    struct default_tabchars :
        static_c<int, 4>
    { };


    template<
        class Range,
        class PositionT
    >
    struct super_ :
        iter_range<
            boost::spirit::position_iterator2< // 2!
                typename range_iterator<Range>::type,
                PositionT
            >
        >
    { };


    template< class PositionIter, class Range, class PositionT >
    PositionIter make_first(Range& rng, PositionT const& pos, int tabchars)
    {
        PositionIter pit(boost::begin(rng), boost::end(rng), pos);
        pit.set_tabchars(tabchars);
        return pit;
    }


} // namespace position_range_detail


template<
    class Range,
    class PositionT = boost::spirit::file_position
>
struct position_range :
    position_range_detail::super_<Range, PositionT>::type,
    private as_lightweight_proxy< position_range<Range, PositionT> >
{
    PSTADE_CONCEPT_ASSERT((Forward<Range>));
    PSTADE_CONCEPT_ASSERT((Readable<Range>));

private:
    typedef typename position_range_detail::super_<Range, PositionT>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    explicit position_range(
        Range& rng,
        PositionT const& pos = PositionT(),
        int tabchars = position_range_detail::default_tabchars::value
    ) :
        super_t(
            position_range_detail::make_first<iter_t>(rng, pos, tabchars),
            iter_t()
        )
    { }

    typedef Range pstade_oven_range_base_type;
};


namespace position_range_detail {


    struct baby_make
    {
        typedef boost::spirit::file_position default_pos_t;

        template< class Myself, class Range, class PositionT = default_pos_t, class Int = void >
        struct apply
        {
            typedef typename pass_by_value<PositionT>::type pos_t;
            typedef position_range<Range, pos_t> const type;
        };

        template< class Result, class Range >
        Result call(Range& rng)
        {
            return Result(rng);
        }

        template< class Result, class Range, class PositionT >
        Result call(Range& rng, PositionT const& pos, int tabchars = default_tabchars::value)
        {
            return Result(rng, pos, tabchars);
        }
    };


} // namespace position_range_detail


PSTADE_EGG_FUNCTION(make_position_range, position_range_detail::baby_make)
PSTADE_EGG_PIPABLE(with_position, position_range_detail::baby_make)


} } // namespace pstade::oven


#endif
