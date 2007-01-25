#ifndef PSTADE_OVEN_GOT_AT_HPP
#define PSTADE_OVEN_GOT_AT_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/const_overloaded.hpp>
#include <pstade/deduced_const.hpp>
#include <pstade/nonassignable.hpp>
#include "./concepts.hpp"
#include "./detail/reference_affect.hpp"
#include "./transformed.hpp"


namespace pstade { namespace oven {


namespace got_at_detail {


    template< class N >
    struct op_at :
        callable< op_at<N> >
    {
        template< class Myself, class FusionSeq >
        struct apply :
            boost::fusion::result_of::at<FusionSeq, N>
        { };

        template< class Result, class FusionSeq >
        Result call(FusionSeq& seq) const
        {
            return boost::fusion::at<N>(seq);
        }
    };


} // namespace got_at_detail


template< class N >
struct op_make_got_at :
    callable< op_make_got_at<N> >
{
    template< class Myself, class FusionSeqRange >
    struct apply
    {
        typedef typename
            detail::reference_affect<
                FusionSeqRange,
                boost::fusion::result_of::value_at<boost::mpl::_1, N>
            >::type
        ref_t;

        typedef typename
            boost::result_of<
                op_make_transformed<ref_t>(FusionSeqRange&, got_at_detail::op_at<N>)
            >::type
        type;
    };

    template< class Result, class FusionSeqRange >
    Result call(FusionSeqRange& rng) const
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<FusionSeqRange>));

        typedef typename apply<void, FusionSeqRange>::type ref_t;
        return op_make_transformed<ref_t>()(rng, got_at_detail::op_at<N>());
    }
};


template< class N >
struct got_at;


namespace got_at_detail {


    struct adl_marker
    { };


    template< class FusionSeqRange, class N > inline
    typename boost::result_of<op_make_got_at<N>(FusionSeqRange&)>::type
    operator|(FusionSeqRange& rng, got_at<N> const&)
    {
        return op_make_got_at<N>()(rng);
    }


    template< class FusionSeqRange, class N > inline
    typename boost::result_of<op_make_got_at<N>(PSTADE_DEDUCED_CONST(FusionSeqRange)&)>::type
    operator|(FusionSeqRange const& rng, got_at<N> const&)
    {
        return op_make_got_at<N>()(rng);
    }


} // namespace got_at_detail


template< class N >
struct got_at :
    got_at_detail::adl_marker,
    private nonassignable
    // Topic:
    // 'noncopyable' is allowed here by the latest standard draft,
    // but GCC doesn't follow it yet.
    // http://www.codecomments.com/archive324-2006-4-888159.html
{ };


template< int N >
struct got_at_c :
    got_at< boost::mpl::int_<N> >
{ };


} } // namespace pstade::oven


#endif
