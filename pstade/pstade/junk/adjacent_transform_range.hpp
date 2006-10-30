#ifndef PSTADE_OVEN_ADJACENT_TRANSFORM_RANGE_HPP
#define PSTADE_OVEN_ADJACENT_TRANSFORM_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/pass_by.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./clear_range.hpp"
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"
#include "./range_reference.hpp"
#include "./range_traversal.hpp"
#include "./sub_range_base.hpp"
#include "./transform_range.hpp"
#include "./zip_range.hpp"


namespace pstade { namespace oven {


namespace adjacent_transform_range_detail {


    template< class BinaryFun, class Reference >
    struct unzip_fun
    {
        typedef Reference result_type;

        template< class Tuple >
        result_type operator()(Tuple const& t) const
        {
            return m_fun(boost::tuples::get<0>(t), boost::tuples::get<1>(t));
        }

        explicit unzip_fun()
        { }

        explicit unzip_fun(BinaryFun const& fun) :
            m_fun(fun)
        { }

    private:
        BinaryFun m_fun;
    };


    template< class Range, class BinaryFun >
    struct default_reference
    {
        typedef typename range_reference<Range>::type ref_t;
        typedef typename boost::result_of<BinaryFun(ref_t, ref_t)>::type type;
    };


    template< class Range, class BinaryFun, class Reference, class Value >
    struct super_
    {
        typedef typename
            boost::mpl::eval_if< boost::is_same<Reference, boost::use_default>,
                default_reference<Range, BinaryFun>,
                boost::mpl::identity<Reference>
            >::type
        ref_t;

        typedef typename
            oven::sub_range_base<Range>::type
        rng_t;

        typedef
            transform_range<
                zip_range<rng_t, rng_t>,
                unzip_fun<BinaryFun, ref_t>,
                ref_t,
                Value
            >
        type;
    };


    template< class ForwardIter > inline
    ForwardIter prior(ForwardIter first, ForwardIter const& last, boost::bidirectional_traversal_tag)
    {
        pstade::unused(first);
        return boost::prior(last);
    }

    template< class ForwardIter > inline
    ForwardIter prior(ForwardIter first, ForwardIter const& last, boost::forward_traversal_tag)
    {
        ForwardIter prev(first);
        for (; ++first != last; prev = first)
            ;

        return prev;
    }


    template< class Super, class Range, class UnzipFun >
    Super make(Range& rng, UnzipFun const& fun)
    {
        if (boost::empty(rng))
            return Super(
                oven::make_iter_range(boost::begin(rng), boost::begin(rng)),
                oven::make_iter_range(boost::begin(rng), boost::begin(rng)),
                fun
            );

        typename typedef range_iterator<Range>::type iter_t;
        iter_t first(boost::begin(rng));
        iter_t last(boost::end(rng));

        return Super(
            oven::make_iter_range(first, (prior)(first, last, typename range_traversal<Range>::type())),
            oven::make_iter_range(boost::next(first), last),
            fun
        );
    }


} // namespace adjacent_transform_range_detail


template<
    class Range,
    class BinaryFun,
    class Reference = boost::use_default,
    class Value     = boost::use_default
>
struct adjacent_transform_range :
    adjacent_transform_range_detail::super_<Range, BinaryFun, Reference, Value>::type,
    private as_lightweight_proxy< adjacent_transform_range<Range, BinaryFun, Reference, Value> >
{
    PSTADE_CONCEPT_ASSERT((Forward<Range>));
    // PSTADE_CONCEPT_ASSERT((Readable<Range>));
    typedef BinaryFun function_type;

private:
    typedef typename adjacent_transform_range_detail::super_<Range, BinaryFun, Reference, Value>::type super_t;
    typedef typename super_t::function_type unzip_fun_t;

public:
    adjacent_transform_range(Range& rng, BinaryFun const& fun) :
        super_t(adjacent_transform_range_detail::make<super_t>(rng, unzip_fun_t(fun)))
    { }

    typedef Range pstade_oven_range_base_type;
};


namespace adjacent_transform_range_detail {


    struct baby_make
    {
        template< class Myself, class Range, class BinaryFun >
        struct apply
        {
            typedef typename pass_by_value<BinaryFun>::type fun_t;
            typedef adjacent_transform_range<Range, fun_t> const type;
        };

        template< class Result, class Range, class BinaryFun >
        Result call(Range& rng, BinaryFun& fun)
        {
            return Result(rng, fun);
        }
    };


} // namespace adjacent_transform_range_detail


PSTADE_EGG_FUNCTION(make_adjacent_transform_range, adjacent_transform_range_detail::baby_make)
PSTADE_EGG_PIPABLE(adjacent_transformed, adjacent_transform_range_detail::baby_make)


} } // namespace pstade::oven


#endif
