#ifndef PSTADE_OVEN_APPLY_RANGE_HPP
#define PSTADE_OVEN_APPLY_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Will be cute with the upcoming Boost.Phoenix-v2.


// Question:
//
// Should be defined 'rng1' or something that is the same as '_1' or 'arg1'?


#include <boost/type_traits/remove_cv.hpp>
#include <pstade/egg/function.hpp>
#include "./begin_end.hpp"
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"
#include "./sub_range_base_type.hpp"


namespace pstade { namespace oven {


template<
    class Range,
    class BeginFun,
    class EndFun = end_fun
>
struct apply_range :
    sub_range_base<Range>::type
{
private:
    typedef typename sub_range_base<Range>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    apply_range(Range& rng, BeginFun bfun, EndFun efun = oven::end) :
        super_t(bfun(rng), efun(rng))
    { }
};


namespace apply_range_detail {


    struct baby_generator
    {
        template< class Range, class BeginFun, class EndFun = oven::end_fun >
        struct result
        {
            typedef typename boost::remove_cv<BeginFun>::type bfun_t;
            typedef typename boost::remove_cv<EndFun>::type efun_t;
            typedef const apply_range<Range, bfun_t, efun_t> type;
        };

        template< class Result, class Range, class BeginFun, class EndFun >
        Result call(Range& rng, BeginFun bfun, EndFun efun)
        {
            return Result(rng, bfun, efun);
        }

        template< class Result, class Range, class BeginFun >
        Result call(Range& rng, BeginFun bfun)
        {
            return Result(rng, bfun);
        }
    };


} // namespace apply_range_detail


PSTADE_EGG_FUNCTION(make_apply_range, apply_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(applied, apply_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::apply_range, 3)


#endif
