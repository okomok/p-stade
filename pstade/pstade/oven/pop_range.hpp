#ifndef PSTADE_OVEN_POP_RANGE_HPP
#define PSTADE_OVEN_POP_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Question:
//
// 'rng|applied(pop);' is better?
// But Haskell provides one named 'init' as primitive.


#include <boost/range/begin.hpp>
#include <pstade/callable.hpp>
#include <pstade/pipable.hpp>
#include <pstade/singleton.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./detail/range_prior.hpp"
#include "./concepts.hpp"
#include "./sub_range_base.hpp"


namespace pstade { namespace oven {


template< class Range >
struct pop_range :
    sub_range_base<Range>::type,
    private as_lightweight_proxy< pop_range<Range> >
{
    PSTADE_CONCEPT_ASSERT((Forward<Range>));

private:
    typedef typename sub_range_base<Range>::type super_t;

public:
    explicit pop_range(Range& rng) :
        super_t(boost::begin(rng), detail::range_prior(rng))
    { }

    typedef Range pstade_oven_range_base_type;
};


struct op_make_pop_range :
    callable<op_make_pop_range>
{
    template< class Myself, class Range >
    struct apply
    {
        typedef pop_range<Range> const type;
    };

    template< class Result, class Range >
    Result call(Range& rng) const
    {
        return Result(rng);
    }
};


PSTADE_SINGLETON_CONST(make_pop_range, op_make_pop_range)
PSTADE_PIPABLE(popped, op_make_pop_range)


} } // namespace pstade::oven


#endif
