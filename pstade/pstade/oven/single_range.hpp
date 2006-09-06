#ifndef PSTADE_OVEN_SINGLE_RANGE_HPP
#define PSTADE_OVEN_SINGLE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/iterator_range.hpp>
#include <boost/utility/addressof.hpp>
#include <pstade/egg/function.hpp>
#include "./as_lightweight_proxy.hpp"


namespace pstade { namespace oven {


template< class Value >
struct single_range :
    boost::iterator_range<Value *>,
    private as_lightweight_proxy< single_range<Value> >
{
private:
    typedef boost::iterator_range<Value *> super_t;

public:
    explicit single_range(Value& v) :
        super_t(boost::addressof(v), boost::addressof(v) + 1)
    { }
};


namespace single_range_detail {


    struct baby_generator
    {
        template< class Unused, class Value >
        struct result
        {
            typedef single_range<Value> const type;
        };

        template< class Result, class Value >
        Result call(Value& v)
        {
            return Result(v);
        }
    };


} // namespace single_range_detail


PSTADE_EGG_FUNCTION(make_single_range, single_range_detail::baby_generator)


} } // namespace pstade::oven


#endif
