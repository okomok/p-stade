#ifndef PSTADE_OVEN_MATCH_RANGE_HPP
#define PSTADE_OVEN_MATCH_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/regex.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


namespace match_range_detail {


    template<
        class Range,
        class CharT,
        class Traits
    >
    struct super_ :
        iter_range<
            boost::regex_iterator<
                typename range_iterator<Range>::type,
                CharT,
                Traits
            >
        >
    { };


    using boost::regex_constants::match_flag_type;
    using boost::regex_constants::match_default;


} // namespace match_range_detail


template<
    class Range,
    class CharT  = typename range_value<Range>::type,
    class Traits = boost::regex_traits<CharT>
>
struct match_range :
    match_range_detail::super_<Range, CharT, Traits>::type,
    private as_lightweight_proxy< match_range<Range, CharT, Traits> >
{
    PSTADE_CONCEPT_ASSERT((Bidirectional<Range>));
    // PSTADE_CONCEPT_ASSERT((Readable<Range>));
    typedef CharT char_type;
    typedef Traits traits_type;

private:
    typedef typename match_range_detail::super_<Range, CharT, Traits>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    template< class Regex >
    match_range(
        Range& rng, Regex const& re,
        match_range_detail::match_flag_type flag = match_range_detail::match_default
    ) :
        super_t(
            iter_t(boost::begin(rng), boost::end(rng), re, flag),
            iter_t()
        )
    { }

    typedef Range pstade_oven_range_base_type;
};


namespace match_range_detail {


    struct baby_make
    {
        template< class Myself, class Range, class Regex, class Flag = void >
        struct apply
        {
            typedef match_range<Range> const type;
        };

        template< class Result, class Range, class Regex >
        Result call(Range& rng, Regex const& re, match_flag_type flag = match_default) const
        {
            return Result(rng, re, flag);
        }
    };


} // namespace match_range_detail


PSTADE_EGG_FUNCTION(make_match_range, match_range_detail::baby_make)
PSTADE_PIPABLE(matches, op_make_match_range)


} } // namespace pstade::oven


#endif
