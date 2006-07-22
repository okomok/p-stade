#ifndef PSTADE_SAUSAGE_ENUMERATE_RANGE_HPP
#define PSTADE_SAUSAGE_ENUMERATE_RANGE_HPP


// PStade.Sausage
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/iterator_range.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/oven/is_lightweight_proxy.hpp>
#include <pstade/oven/range_adaptor.hpp>
#include "./enumerate_iterator.hpp"


namespace pstade { namespace sausage {


namespace enumerate_range_detail {


    template< class Enumerable >
    struct super_
    {
        typedef boost::iterator_range<
            enumerate_iterator<Enumerable>
        > type;
    };


} // namespace enumerate_range_detail


template< class Enumerable >
struct enumerate_range :
    enumerate_range_detail::super_<Enumerable>::type
{
private:
    typedef typename enumerate_range_detail::super_<Enumerable>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    explicit enumerate_range(Enumerable& e) :
        super_t(iter_t(e), iter_t())
    { }
};


namespace enumerate_range_detail {


    struct baby_generator
    {
        template< class Unused, class Enumerable >
        struct result
        {
            typedef enumerate_range<Enumerable> const type;
        };

        template< class Result, class Enumerable >
        Result call(Enumerable& e)
        {
            return Result(e);
        }
    };


} // namespace enumerate_range_detail


PSTADE_EGG_FUNCTION(make_enumerate_range, enumerate_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(enumerated, enumerate_range_detail::baby_generator)


} } // namespace pstade::sausage


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::sausage::enumerate_range, 1)


#endif
