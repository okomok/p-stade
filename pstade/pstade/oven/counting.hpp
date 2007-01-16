#ifndef PSTADE_OVEN_COUNTING_HPP
#define PSTADE_OVEN_COUNTING_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <limits> // numeric_limits
#include <boost/iterator/counting_iterator.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/function.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/use_default.hpp>
#include "./iter_range.hpp"


namespace pstade { namespace oven {


template<
    class Incrementable       = boost::use_default,
    class CategoryOrTraversal = boost::use_default,
    class Difference          = boost::use_default
>
struct op_counting :
    callable< op_counting<Incrementable, CategoryOrTraversal, Difference> >
{
    template< class Myself, class I, class J >
    struct apply
    {
        typedef typename
            // prefer 'J' in order to suppress "loss of data" warning;
            // [0:int, size():uint) is so common.
            use_default_eval_to< Incrementable, pass_by_value<J> >::type
        inc_t;

        typedef
            iter_range<
                boost::counting_iterator<
                    inc_t,
                    CategoryOrTraversal,
                    Difference
                >
            > const
        type;
    };

    template< class Result, class I, class J >
    Result call(I& i, J& j) const
    {
        typedef typename Result::iterator iter_t;
        return Result(iter_t(i), iter_t(j));
    }
};


PSTADE_CONSTANT(counting, (op_counting<>))


namespace counting_from_detail {


    template< class I >
    struct baby
    {
        typedef typename
            boost::result_of<
                op_counting<>(I&, I)
            >::type
        result;

        result call(I& i)
        {
            return counting(i, (std::numeric_limits<typename pass_by_value<I>::type>::max)());
        }
    };


} // namespace counting_from_detail


PSTADE_FUNCTION(counting_from, (counting_from_detail::baby<_>))


} } // namespace pstade::oven


#endif
