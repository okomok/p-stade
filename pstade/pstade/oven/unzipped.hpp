#ifndef PSTADE_OVEN_UNZIPPED_HPP
#define PSTADE_OVEN_UNZIPPED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/zip_iterator.hpp> // tuple_impl_specific
#include <boost/mpl/int.hpp>
#include <boost/mpl/placeholders.hpp> // _1
#include <boost/tuple/tuple.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/at.hpp>
#include <pstade/callable.hpp>
#include <pstade/deduced_const.hpp>
#include <pstade/function.hpp>
#include <pstade/nonassignable.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./detail/reference_affect.hpp"
#include "./range_value.hpp"
#include "./transformed.hpp"


namespace pstade { namespace oven {


template< class N >
struct op_make_unzipped_at :
    callable< op_make_unzipped_at<N> >
{
    template< class Myself, class TupleRange >
    struct apply
    {
        typedef typename
            detail::reference_affect<
                TupleRange,
                tuple_value_at<boost::mpl::_1, N>
            >::type
        ref_t;

        typedef typename
            boost::result_of<
                op_make_transformed<ref_t>(TupleRange&, op_tuple_at<N>)
            >::type
        type;
    };

    template< class Result, class TupleRange >
    Result call(TupleRange& rng) const
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<TupleRange>));

        typedef typename apply<void, TupleRange>::ref_t ref_t;
        return op_make_transformed<ref_t>()(rng, op_tuple_at<N>());
    };
};


namespace unzipped_at_detail {


    template< class N >
    struct unzipped_at :
        private nonassignable
    { };


    template< int N >
    struct unzipped_at_c :
        unzipped_at< boost::mpl::int_<N> >
    { };


    template< class TupleRange, class N > inline
    typename boost::result_of<op_make_unzipped_at<N>(TupleRange&)>::type
    operator|(TupleRange& rng, unzipped_at<N> const&)
    {
        return op_make_unzipped_at<N>()(rng);
    }

    template< class TupleRange, class N > inline
    typename boost::result_of<op_make_unzipped_at<N>(PSTADE_DEDUCED_CONST(TupleRange)&)>::type
    operator|(TupleRange const& rng, unzipped_at<N> const&)
    {
        return op_make_unzipped_at<N>()(rng);
    }


} // namespace unzipped_at_detail


using unzipped_at_detail::unzipped_at;
using unzipped_at_detail::unzipped_at_c;


// unzipped
//

namespace unzipped_detail {


    template< int From, int To >
    struct counting_tuple
    {
        typedef
            boost::tuples::cons<
                boost::mpl::int_<From>,
                typename counting_tuple<From + 1, To>::type
            >
        type;
    };

    template< int To >
    struct counting_tuple<To, To>
    {
        typedef boost::tuples::null_type type;
    };


    template< class TupleRange >
    struct to_counting_tuple
    {
        typedef typename
            range_value<TupleRange>::type
        tup_t;

        typedef typename
            counting_tuple<
                0, boost::tuples::length<tup_t>::value
            >::type
        type;
    };


    template< class TupleRange >
    struct make_at_range
    {
        template< class N >
        struct apply :
            boost::result_of<
                op_make_unzipped_at<N>(TupleRange&)
            >
        { };

        template< class N >
        typename apply<N>::type
        operator()(N const&) const
        {
            return op_make_unzipped_at<N>()(m_rng);
        }

        explicit make_at_range(TupleRange& rng) :
            m_rng(rng)
        { }

    private:
        TupleRange& m_rng;
    };


    using boost::detail::tuple_impl_specific::tuple_meta_transform;
    using boost::detail::tuple_impl_specific::tuple_transform;


    template< class TupleRange >
    struct baby
    { 
        typedef typename
            to_counting_tuple<TupleRange>::type
        counting_tup_t;

        typedef typename
            tuple_meta_transform<
                counting_tup_t,
                make_at_range<TupleRange>
            >::type
        result;

        result call(TupleRange& rng)
        {
            return (tuple_transform)(
                counting_tup_t(),
                make_at_range<TupleRange>(rng)
            );
        }
    };


} // namespace unzipped_detail


PSTADE_FUNCTION(make_unzipped, (unzipped_detail::baby<_>))
PSTADE_PIPABLE(unzipped, (op_make_unzipped))


} } // namespace pstade::oven


#endif
