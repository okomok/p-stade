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
#include <pstade/value_cast.hpp>
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace counting_detail {


    template< class Incrementable1, class Incrementable2 > inline
    bool is_valid(Incrementable1 i, Incrementable2 j, boost::single_pass_traversal_tag)
    {
        unused(i, j);
        return true;
    }

    template< class Incrementable1, class Incrementable2 > inline
    bool is_valid(Incrementable1 i, Incrementable2 j, boost::random_access_traversal_tag)
    {
        return pstade::value_cast<Incrementable2>(i) <= j;
    }


} // namespace counting_detail


template<
    class CategoryOrTraversal = boost::use_default,
    class Difference          = boost::use_default
>
struct op_counting :
    callable< op_counting<CategoryOrTraversal, Difference> >
{
    template< class Myself, class Incrementable1, class Incrementable2 >
    struct apply
    {
        typedef
            boost::counting_iterator<
                // Prefer 'Incrementable2'; [0:int, size():uint) often happens.
                typename pass_by_value<Incrementable2>::type,
                CategoryOrTraversal,
                Difference
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        type;
    };

    template< class Result, class Incrementable1, class Incrementable2 >
    Result call(Incrementable1& i, Incrementable2& j) const
    {
        typedef typename Result::iterator iter_t;
        typedef typename iter_t::base_type inc2_t;

        BOOST_ASSERT(counting_detail::is_valid(
            i, j, typename boost::iterator_traversal<iter_t>::type()
        ));

        return Result(
            iter_t(pstade::value_cast<inc2_t>(i)),
            iter_t(j)
        );
    }
};


PSTADE_CONSTANT(counting, (op_counting<>))


namespace counting_from_detail {


    template< class Incrementable >
    struct baby
    {
        typedef typename
            pass_by_value<Incrementable>::type
        inc_t;

        typedef typename
            boost::result_of<
                op_counting<>(Incrementable&, inc_t)
            >::type
        result_type;

        result_type operator()(Incrementable& i) const
        {
            return counting(i, (std::numeric_limits<inc_t>::max)());
        }
    };


} // namespace counting_from_detail


PSTADE_FUNCTION(counting_from, (counting_from_detail::baby<_>))


} } // namespace pstade::oven


#endif
