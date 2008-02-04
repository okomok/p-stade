#ifndef PSTADE_OVEN_COUNTING_HPP
#define PSTADE_OVEN_COUNTING_HPP
#include "./detail/prefix.hpp"


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


#include <limits> // numeric_limits
#include <boost/assert.hpp>
#include <boost/iterator/counting_iterator.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <pstade/derived_from.hpp>
#include <pstade/egg/by_value.hpp>
#include <pstade/egg/copy.hpp>
#include <pstade/egg/use_deduced_form.hpp>
#include <pstade/pod_constant.hpp>
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
        return egg::copy<Incrementable2>(i) <= j;
    }


    template< class Traversal, class Difference, class Incrementable1, class Incrementable2 >
    struct simple_base
    {
        // Prefer 'Incrementable2'; [0:int, size():uint) often happens.
        typedef
            boost::counting_iterator<Incrementable2, Traversal, Difference>
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(Incrementable1 i, Incrementable2 j) const
        {
            BOOST_ASSERT(here::is_valid(i, j, typename boost::iterator_traversal<iter_t>::type()));
            return result_type(iter_t(egg::copy<Incrementable2>(i)), iter_t(j));
        }
    };


    struct max_count_tag { };
    struct min_count_tag { };


    template< class Traversal, class Difference >
    struct little
    {
        typedef little use_deduced_form;

        template< class Myself, class Incrementable1, class Incrementable2 >
        struct apply
        {
            typedef typename
                simple_base<Traversal, Difference, Incrementable1, Incrementable2>::result_type
            type;
        };

        template< class Result, class Incrementable1, class Incrementable2 >
        Result call(boost::type<Result>, Incrementable1 i, Incrementable2 j) const
        {
            return
                simple_base<Traversal, Difference, Incrementable1, Incrementable2>()(i, j);
        }

        template< class Myself, class Incrementable >
        struct apply<Myself, Incrementable, max_count_tag>
        {
            typedef typename
                simple_base<Traversal, Difference, Incrementable, Incrementable>::result_type
            type;
        };

        template< class Result, class Incrementable >
        Result call(boost::type<Result>, Incrementable i, max_count_tag) const
        {
            return
                simple_base<Traversal, Difference, Incrementable, Incrementable>()(i, (std::numeric_limits<Incrementable>::max)());
        }

        template< class Myself, class Incrementable >
        struct apply<Myself, min_count_tag, Incrementable>
        {
            typedef typename
                simple_base<Traversal, Difference, Incrementable, Incrementable>::result_type
            type;
        };

        template< class Result, class Incrementable >
        Result call(boost::type<Result>, min_count_tag, Incrementable j) const
        {
            return
                simple_base<Traversal, Difference, Incrementable, Incrementable>()((std::numeric_limits<Incrementable>::min)(), j);
        }
    };


} // namespace counting_detail


template<
    class Traversal  = boost::use_default,
    class Difference = boost::use_default
>
struct X_counting : derived_from<
    egg::function<counting_detail::little<Traversal, Difference>, egg::by_value>
>
{ };


typedef X_counting<>::base_class T_counting;
PSTADE_POD_CONSTANT((T_counting), counting) = {{}};


PSTADE_POD_CONSTANT((counting_detail::max_count_tag), max_count) = {};
PSTADE_POD_CONSTANT((counting_detail::min_count_tag), min_count) = {};


} } // namespace pstade::oven


#endif
