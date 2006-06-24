#ifndef PSTADE_OVEN_POSITION_RANGE_HPP
#define PSTADE_OVEN_POSITION_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include <boost/spirit/iterator/position_iterator.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/static_c.hpp>
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"


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
                typename boost::range_result_iterator<ForwardRange>::type,
                PositionT
            >
        > type;
    };


    template< class PositionIter, class ForwardRange, class PositionT >
    PositionIter make_iter(ForwardRange& rng, const PositionT& pos, int tabchars)
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
    position_range_detail::super_<ForwardRange, PositionT>::type
{
private:
    typedef typename position_range_detail::super_<ForwardRange, PositionT>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    explicit position_range(
        ForwardRange& rng,
        const PositionT& pos = PositionT(),
        int tabchars = position_range_detail::default_tabchars::value
    ) :
        super_t(
            position_range_detail::make_iter<iter_t>(rng, pos, tabchars),
            iter_t()
        )
    { }
};


namespace position_range_detail {


    struct baby_generator
    {
        typedef boost::spirit::file_position default_pos_t;

        template< class ForwardRange, class PositionT = default_pos_t, class Int = void >
        struct result
        {
            typedef typename boost::remove_cv<PositionT>::type pos_t;
            typedef const position_range<ForwardRange, pos_t> type;
        };

        template< class Result, class ForwardRange >
        Result call(ForwardRange& rng)
        {
            return Result(rng);
        }

        template< class Result, class ForwardRange, class PositionT >
        Result call(ForwardRange& rng, const PositionT& pos, int tabchars = default_tabchars::value)
        {
            return Result(rng, pos, tabchars);
        }
    };


} // namespace position_range_detail


PSTADE_EGG_FUNCTION(make_position_range, position_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(positioned, position_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::position_range, 2)


#endif
