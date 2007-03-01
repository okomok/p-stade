#ifndef PSTADE_OVEN_COUNTING_HPP
#define PSTADE_OVEN_COUNTING_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <limits> // numeric_limits
#include <boost/assert.hpp>
#include <boost/iterator/counting_iterator.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/function.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/unused.hpp>
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace counting_detail {


    template< class I, class J > inline
    bool is_valid(I& i, J& j, boost::single_pass_traversal_tag)
    {
        unused(i, j);
        return true;
    }

    template< class I, class J > inline
    bool is_valid(I& i, J& j, boost::random_access_traversal_tag)
    {
        return J(i) <= j;
    }


} // namespace counting_detail


template<
    class CategoryOrTraversal = boost::use_default,
    class Difference          = boost::use_default
>
struct op_counting :
    callable< op_counting<CategoryOrTraversal, Difference> >
{
    template< class Myself, class I, class J >
    struct apply
    {
        typedef
            boost::counting_iterator<
                // prefer 'J' in order to suppress "loss of data" warning;
                // [0:int, size():uint) is so common.
                typename pass_by_value<J>::type,
                CategoryOrTraversal,
                Difference
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        type;
    };

    template< class Result, class I, class J >
    Result call(I& i, J& j) const
    {
        typedef typename Result::iterator iter_t;
        BOOST_ASSERT(counting_detail::is_valid(i, j, typename boost::iterator_traversal<iter_t>::type()));
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
        result_type;

        result_type operator()(I& i) const
        {
            return counting(i, (std::numeric_limits<typename pass_by_value<I>::type>::max)());
        }
    };


} // namespace counting_from_detail


PSTADE_FUNCTION(counting_from, (counting_from_detail::baby<_>))


} } // namespace pstade::oven


#endif
