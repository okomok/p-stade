#ifndef PSTADE_OVEN_COUNTING_HPP
#define PSTADE_OVEN_COUNTING_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// '__w64 int'(msvc) and 'ptrdiff_t'(gcc) behavior seems undefined.
// Through metafunctions, they are occasionally turned into 'int'.


#include "./detail/prelude.hpp"
#include <limits> // numeric_limits
#include <boost/assert.hpp>
#include <boost/iterator/counting_iterator.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/type.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/copy_construct.hpp>
#include <pstade/function.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/unused.hpp>
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace counting_detail {


    namespace here = counting_detail;


    template< class Incrementable1, class Incrementable2 > inline
    bool is_valid(Incrementable1 i, Incrementable2 j, boost::single_pass_traversal_tag)
    {
        unused(i, j);
        return true;
    }

    template< class Incrementable1, class Incrementable2 > inline
    bool is_valid(Incrementable1 i, Incrementable2 j, boost::random_access_traversal_tag)
    {
        return pstade::copy_construct<Incrementable2>(i) <= j;
    }


    template< class Traversal, class Difference, class Incrementable1, class Incrementable2 >
    struct baby
    {
        // Prefer 'Incrementable2'; [0:int, size():uint) often happens.
        typedef typename
            pass_by_value<Incrementable2>::type
        inc_t;

        typedef
            boost::counting_iterator<inc_t, Traversal, Difference>
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(Incrementable1& i, Incrementable2& j) const
        {
            BOOST_ASSERT(here::is_valid(i, j, typename boost::iterator_traversal<iter_t>::type()));

            return result_type(
                iter_t(pstade::copy_construct<inc_t>(i)),
                iter_t(j)
            );
        }
    };


    struct max_count_tag { };
    struct min_count_tag { };


} // namespace counting_detail


template<
    class Traversal  = boost::use_default,
    class Difference = boost::use_default
>
struct op_counting :
    callable< op_counting<Traversal, Difference> >
{
    template< class Incrementable1, class Incrementable2 >
    struct apply_aux
    {
        typedef typename
            counting_detail::baby<Traversal, Difference, Incrementable1, Incrementable2>::result_type
        type;
    };

    template< class Result, class Incrementable1, class Incrementable2 >
    Result call_aux(Incrementable1 i, Incrementable2 j, boost::type<Result>) const
    {
        return
            counting_detail::baby<Traversal, Difference, Incrementable1, Incrementable2>()(i, j);
    }

    template< class Incrementable >
    struct apply_aux<Incrementable, counting_detail::max_count_tag>
    {
        typedef typename
            counting_detail::baby<Traversal, Difference, Incrementable, Incrementable const>::result_type
        type;
    };

    template< class Result, class Incrementable >
    Result call_aux(Incrementable i, counting_detail::max_count_tag, boost::type<Result>) const
    {
        return
            counting_detail::baby<Traversal, Difference, Incrementable, Incrementable const>()(i, (std::numeric_limits<Incrementable>::max)());
    }

    template< class Incrementable >
    struct apply_aux<counting_detail::min_count_tag, Incrementable>
    {
        typedef typename
            counting_detail::baby<Traversal, Difference, Incrementable const, Incrementable>::result_type
        type;
    };

    template< class Result, class Incrementable >
    Result call_aux(counting_detail::min_count_tag, Incrementable j, boost::type<Result>) const
    {
        return
            counting_detail::baby<Traversal, Difference, Incrementable const, Incrementable>()((std::numeric_limits<Incrementable>::min)(), j);
    }

    template< class Myself, class Incrementable1, class Incrementable2 >
    struct apply :
        apply_aux<
            typename pass_by_value<Incrementable1>::type,
            typename pass_by_value<Incrementable2>::type
        >
    { };

    template< class Result, class Incrementable1, class Incrementable2 >
    Result call(Incrementable1& i, Incrementable2& j) const
    {
        // Use type2type for GCC; see <pstade/const_overloaded.hpp>.
        return call_aux(i, j, boost::type<Result>());
    }
};


PSTADE_CONSTANT(counting, (op_counting<>))
PSTADE_CONSTANT(max_count, (counting_detail::max_count_tag))
PSTADE_CONSTANT(min_count, (counting_detail::min_count_tag))


} } // namespace pstade::oven


#endif
