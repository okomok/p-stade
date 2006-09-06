#ifndef PSTADE_SAUSAGE_GENERATE_RANGE_HPP
#define PSTADE_SAUSAGE_GENERATE_RANGE_HPP


// PStade.Sausage
//
// Copyright Shunsuke Sogame 2005-2006.
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


    template< class Routine >
    struct super_
    {
        typedef boost::iterator_range<
            generate_iterator<Routine>
        > type;
    };


} // namespace generate_range_detail


template< class Routine >
struct generate_range :
    generate_range_detail::super_<Routine>::type,
    private oven::as_lightweight_proxy< generate_range<Routine> >
{
private:
    typedef typename generate_range_detail::super_<Routine>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    explicit generate_range(Routine gen) :
        super_t(iter_t(gen), iter_t())
    { }
};


namespace generate_range_detail {


    struct baby_generator
    {
        template< class Unused, class Routine >
        struct result
        {
            typedef typename egg::by_value<Routine>::type gen_t;
            typedef generate_range<gen_t> const type;
        };

        template< class Result, class Routine >
        Result call(Routine gen)
        {
            return Result(gen);
        }
    };


} // namespace generate_range_detail


PSTADE_EGG_FUNCTION(make_generate_range, generate_range_detail::baby_generator)
PSTADE_EGG_PIPABLE(generated, generate_range_detail::baby_generator)


} } // namespace pstade::sausage


#endif
