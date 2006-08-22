#ifndef PSTADE_SAUSAGE_GENERATE_RANGE_HPP
#define PSTADE_SAUSAGE_GENERATE_RANGE_HPP


// PStade.Sausage
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/iterator_range.hpp>
#include <pstade/egg/by_value.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/oven/as_lightweight_proxy.hpp>
#include "./generate_iterator.hpp"


namespace pstade { namespace sausage {


namespace generate_range_detail {


    template< class Generator >
    struct super_
    {
        typedef boost::iterator_range<
            generate_iterator<Generator>
        > type;
    };


} // namespace generate_range_detail


template< class Generator >
struct generate_range :
    generate_range_detail::super_<Generator>::type,
    private oven::as_lightweight_proxy< generate_range<Generator> >
{
private:
    typedef typename generate_range_detail::super_<Generator>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    explicit generate_range(Generator gen) :
        super_t(iter_t(gen), iter_t())
    { }
};


namespace generate_range_detail {


    struct baby_generator
    {
        template< class Unused, class Generator >
        struct result
        {
            typedef typename egg::by_value<Generator>::type gen_t;
            typedef generate_range<gen_t> const type;
        };

        template< class Result, class Generator >
        Result call(Generator gen)
        {
            return Result(gen);
        }
    };


} // namespace generate_range_detail


PSTADE_EGG_FUNCTION(make_generate_range, generate_range_detail::baby_generator)
PSTADE_EGG_PIPABLE(generated, generate_range_detail::baby_generator)


} } // namespace pstade::sausage


#endif
