#ifndef PSTADE_OVEN_MATCH_RANGE_HPP
#define PSTADE_OVEN_MATCH_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <string>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/regex.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/pipable.hpp>
#include <pstade/use_default.hpp>
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
    struct super_
    {
        typedef typename defaultable_eval_to< CharT, range_value<Range> >::type char_t;
        typedef typename defaultable_to< Traits, boost::regex_traits<char_t> >::type traits_t;

        typedef typename
            iter_range<
                boost::regex_iterator<
                    typename range_iterator<Range>::type,
                    char_t,
                    traits_t
                >
            >
        type;
    };


} // namespace match_range_detail


template<
    class Range,
    class CharT  = boost::use_default,
    class Traits = boost::use_default
>
struct match_range :
    match_range_detail::super_<Range, CharT, Traits>::type,
    private as_lightweight_proxy< match_range<Range, CharT, Traits> >
{
    PSTADE_CONCEPT_ASSERT((Bidirectional<Range>));
    // PSTADE_CONCEPT_ASSERT((Readable<Range>));

private:
    typedef typename match_range_detail::super_<Range, CharT, Traits>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    template< class Regex >
    match_range(
        Range& rng, Regex const& re,
        boost::regex_constants::match_flag_type flag = boost::regex_constants::match_default
    ) :
        super_t(
            iter_t(boost::begin(rng), boost::end(rng), re, flag),
            iter_t()
        )
    { }

    typedef Range pstade_oven_range_base_type;
};


PSTADE_OBJECT_GENERATOR(make_match_range, const match_range, (by_qualified))
PSTADE_PIPABLE(matches, op_make_match_range)


} } // namespace pstade::oven


#endif
