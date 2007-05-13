#ifndef PSTADE_OVEN_POSITION_RANGE_HPP
#define PSTADE_OVEN_POSITION_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/spirit/iterator/position_iterator.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
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
        class Range,
        class PositionT
    >
    struct super_
    {
        typedef boost::iterator_range<
            boost::spirit::position_iterator<
                typename boost::range_result_iterator<Range>::type,
                PositionT
            >
        > type;
    };


    template<
        class Range,
        class PositionT
    >
    struct super2
    {
        typedef boost::iterator_range<
            boost::spirit::position_iterator2<
                typename boost::range_result_iterator<Range>::type,
                PositionT
            >
        > type;
    };


    template< class PositionIter, class Range >
    PositionIter make_iter(Range& rng, int tabchars)
    {
        PositionIter pit(boost::begin(rng), boost::end(rng));
        pit.set_tabchars(tabchars);
        return pit;
    }


    template< class PositionIter, class Range, class PositionT >
    PositionIter make_iter(Range& rng, const PositionT& pos, int tabchars)
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
    position_range_detail::super_<Range, PositionT>::type
{
private:
    typedef typename position_range_detail::super_<Range, PositionT>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    explicit position_range(Range& rng, int tabchars = position_range_detail::default_tabchars::value) :
        super_t(
            position_range_detail::make_iter<iter_t>(rng, tabchars),
            iter_t()
        )
    { }

    explicit position_range(Range& rng, const PositionT& pos, int tabchars = position_range_detail::default_tabchars::value) :
        super_t(
            position_range_detail::make_iter<iter_t>(rng, pos, tabchars),
            iter_t()
        )
    { }
};


template<
    class Range,
    class PositionT = boost::spirit::file_position
>
struct position_range2 :
    position_range_detail::super2<Range, PositionT>::type
{
private:
    typedef typename position_range_detail::super2<Range, PositionT>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    explicit position_range2(Range& rng, int tabchars = position_range_detail::default_tabchars::value) :
        super_t(
            position_range_detail::make_iter<iter_t>(rng, tabchars),
            iter_t()
        )
    { }

    explicit position_range2(Range& rng, const PositionT& pos, int tabchars = position_range_detail::default_tabchars::value) :
        super_t(
            position_range_detail::make_iter<iter_t>(rng, pos, tabchars),
            iter_t()
        )
    { }
};


namespace position_range_detail {


    struct baby_generator
    {
        template< class Range, class PositionT = void, class Int = void >
        struct result
        {
            typedef typename boost::remove_cv<PositionT>::type pos_t;
            typedef const position_range<Range, pos_t> type;
        };

        template< class Range >
        struct result<Range>
        {
            typedef const position_range<Range> type;
        };

        template< class Range >
        struct result<Range, int>
        {
            typedef const position_range<Range> type;
        };

        template< class Range >
        struct result<Range, const int> : result<Range, int>
        { };

        template< class Result, class Range >
        Result call(Range& rng, int tabchars = position_range_detail::default_tabchars::value)
        {
            return Result(rng, tabchars);
        }

        template< class Result, class Range, class PositionT >
        Result call(Range& rng, const PositionT& pos, int tabchars = position_range_detail::default_tabchars::value)
        {
            return Result(rng, pos, tabchars);
        }
    };


    struct baby_generator2 : baby_generator
    {
        template< class Range, class PositionT = void, class Int = void >
        struct result
        {
            typedef typename boost::remove_cv<PositionT>::type pos_t;
            typedef const position_range2<Range, pos_t> type;
        };

        template< class Range >
        struct result<Range>
        {
            typedef const position_range2<Range> type;
        };

        template< class Range >
        struct result<Range, int>
        {
            typedef const position_range2<Range> type;
        };

        template< class Range >
        struct result<Range, const int> : result<Range, int>
        { };
    };


} // namespace position_range_detail


PSTADE_EGG_FUNCTION(make_position_range, position_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(positioned, position_range_detail::baby_generator)

PSTADE_EGG_FUNCTION(make_position_range2, position_range_detail::baby_generator2)
PSTADE_OVEN_RANGE_ADAPTOR(positioned2, position_range_detail::baby_generator2)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::position_range, 2)
PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::position_range2, 2)


#endif
