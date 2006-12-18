#ifndef PSTADE_OVEN_POSITION_RANGE_HPP
#define PSTADE_OVEN_POSITION_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/spirit/iterator/position_iterator.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/pipable.hpp>
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
    // PSTADE_CONCEPT_ASSERT((Readable<Range>));
    typedef position_range type;

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


PSTADE_OBJECT_GENERATOR(make_position_range,
    (position_range< deduce<_1, to_qualified>, deduce<_2, to_value, boost::spirit::file_position> >) const)
PSTADE_PIPABLE(with_position, (op_make_position_range))


} } // namespace pstade::oven


#endif
