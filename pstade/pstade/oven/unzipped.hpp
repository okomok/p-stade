#ifndef PSTADE_OVEN_UNZIPPED_HPP
#define PSTADE_OVEN_UNZIPPED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
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
#include <pstade/const_overloaded.hpp>
#include <pstade/deduced_const.hpp>
#include <pstade/nonassignable.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./detail/reference_affect.hpp"
#include "./range_reference.hpp"
#include "./transformed.hpp"


namespace pstade { namespace oven {


template< class N >
struct op_unzipped_at :
    callable< op_unzipped_at<N> >
{
    template< class Myself, class TupleRange >
    struct apply
    {
        typedef typename
            detail::reference_affect<
                TupleRange,
                value_at<boost::mpl::_1, N>
            >::type
        ref_t;

        typedef typename
            boost::result_of<
                op_make_transformed<ref_t>(TupleRange&, op_at<N>)
            >::type
        type;
    };

    template< class Result, class TupleRange >
    Result call(TupleRange& rng) const
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<TupleRange>));

        typedef typename apply<void, TupleRange>::ref_t ref_t;
        return op_make_transformed<ref_t>()(rng, op_at<N>());
    };
};


template< class N >
struct unzipped_at;


namespace unzipped_at_detail {


    struct adl_marker
    { };


    template< class TupleRange, class N > inline
    typename boost::result_of<op_unzipped_at<N>(TupleRange&)>::type
    operator|(TupleRange& rng, unzipped_at<N> const&)
    {
        return op_unzipped_at<N>()(rng);
    }


    template< class TupleRange, class N > inline
    typename boost::result_of<op_unzipped_at<N>(PSTADE_DEDUCED_CONST(TupleRange)&)>::type
    operator|(TupleRange const& rng, unzipped_at<N> const&)
    {
        return op_unzipped_at<N>()(rng);
    }


} // namespace unzipped_at_detail


template< class N >
struct unzipped_at :
    unzipped_at_detail::adl_marker,
    private nonassignable
{ };


template< int N >
struct unzipped_at_c :
    unzipped_at< boost::mpl::int_<N> >
{ };


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
    struct make_at_range
    {
        template< class N >
        struct apply :
            boost::result_of<op_unzipped_at<N>(TupleRange&)>
        { };

        template< class N >
        typename apply<N>::type
        operator()(N const&) const
        {
            return op_unzipped_at<N>()(m_rng);
        }

        explicit make_at_range(TupleRange& rng) :
            m_rng(rng)
        { }

    private:
        TupleRange& m_rng;
    };


    namespace impl = boost::detail::tuple_impl_specific;


    template< class TupleRange >
    struct to_counting_tuple
    {
        typedef typename range_value<TupleRange>::type tup_t;
        typedef typename counting_tuple<0, boost::tuples::length<tup_t>::value>::type type;
    };


} // namespace unzipped_detail


struct op_unzipped :
    callable<op_unzipped>
{
    template< class Myself, class TupleRange >
    struct apply
    {
        typedef typename unzipped_detail::to_counting_tuple<TupleRange>::type counting_tup_t;
        typedef typename unzipped_detail::impl::tuple_meta_transform<counting_tup_t, unzipped_detail::make_at_range<TupleRange> >::type type;
    };

    template< class Result, class TupleRange >
    Result call(TupleRange& rng) const
    {
        typedef typename unzipped_detail::to_counting_tuple<TupleRange>::type counting_tup_t;
        return unzipped_detail::impl::tuple_transform(counting_tup_t(), unzipped_detail::make_at_range<TupleRange>(rng));
    }
};


PSTADE_PIPABLE(unzipped, (op_unzipped))


} } // namespace pstade::oven


#endif
