#ifndef PSTADE_OVEN_MATCH_RESULTS_RANGE_HPP
#define PSTADE_OVEN_MATCH_RESULTS_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/iterator_range.hpp>
#include <boost/regex.hpp>
#include <pstade/egg/function.hpp>
#include "./detail/concept_check.hpp"
#include "./lightweight_proxy.hpp"
#include "./range_adaptor.hpp"
#include "./range_iterator.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


namespace match_results_range_detail {


    template<
        class BidiRange,
        class CharT,
        class Traits
    >
    struct super_
    {
        typedef boost::iterator_range<
            boost::regex_iterator<
                typename range_iterator<BidiRange>::type,
                CharT,
                Traits
            >
        > type;
    };


    using boost::regex_constants::match_flag_type;
    using boost::regex_constants::match_default;


} // namespace match_results_range_detail


template<
    class BidiRange,
    class CharT = typename range_value<BidiRange>::type,
    class Traits = boost::regex_traits<CharT>
>
struct match_results_range :
    match_results_range_detail::super_<BidiRange, CharT, Traits>::type,
    private lightweight_proxy< match_results_range<BidiRange, CharT, Traits> >
{
    typedef BidiRange pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(BidiRange, BidirectionalRangeConcept);
    typedef typename match_results_range_detail::super_<BidiRange, CharT, Traits>::type super_t;
    typedef typename super_t::iterator iter_t;
    typedef typename iter_t::regex_type regex_t;

public:
    match_results_range(
        BidiRange& rng,
        regex_t const& re,
        match_results_range_detail::match_flag_type flag = match_results_range_detail::match_default
    ) :
        super_t(
            iter_t(boost::begin(rng), boost::end(rng), re, flag),
            iter_t()
        )
    { }
};


namespace match_results_range_detail {


    struct baby_generator
    {
        template< class Unused, class BidiRange, class RegexT, class FlagT = void >
        struct result
        {
            typedef match_results_range<BidiRange> const type;
        };

        template< class Result, class BidiRange, class RegexT >
        Result call(BidiRange& rng, RegexT const& re, match_flag_type flag = match_default)
        {
            return Result(rng, re, flag);
        }
    };


} // namespace match_results_range_detail


PSTADE_EGG_FUNCTION(make_match_results_range, match_results_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(match_results, match_results_range_detail::baby_generator)


} } // namespace pstade::oven


#endif
