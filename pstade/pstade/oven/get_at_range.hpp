#ifndef PSTADE_OVEN_GET_AT_RANGE_HPP
#define PSTADE_OVEN_GET_AT_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/mpl/int.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <pstade/affect.hpp>
#include <pstade/const_overloaded.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/nonassignable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./detail/concept_check.hpp"
#include "./range_reference.hpp"
#include "./transform_range.hpp"


namespace pstade { namespace oven {


namespace get_at_range_detail {


    template< class N >
    struct baby_at
    {
        template< class Unused, class FusionSeq >
        struct apply :
            boost::fusion::result_of::at<FusionSeq, N>
        { };

        template< class Result, class FusionSeq >
        Result call(FusionSeq& seq)
        {
            return boost::fusion::at<N>(seq);
        }
    };


    template< class N >
    struct function
    {
        typedef egg::function< baby_at<N> > type;
    };


    template< class FusionSeqRange, class N >
    struct reference
    {
        typedef typename range_reference<FusionSeqRange>::type seq_ref_t;
        typedef typename boost::remove_reference<seq_ref_t>::type seq_t;

        typedef typename affect_cvr<
            seq_ref_t,
            typename boost::fusion::result_of::at<seq_t, N>::type
        >::type type;
    };


    template< class FusionSeqRange, class N >
    struct super_
    {
        typedef transform_range<
            FusionSeqRange,
            typename function<N>::type,
            typename reference<FusionSeqRange, N>::type
        > type;
    };


} // namespace get_at_range_detail


template< class FusionSeqRange, class N >
struct get_at_range :
    get_at_range_detail::super_<FusionSeqRange, N>::type,
    private as_lightweight_proxy< get_at_range<FusionSeqRange, N> >
{
    typedef FusionSeqRange pstade_oven_range_base_type;
    typedef N index_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(FusionSeqRange, SinglePassRangeConcept);
    typedef typename get_at_range_detail::super_<FusionSeqRange, N>::type super_t;
    typedef typename super_t::function_type fun_t;

public:
    explicit get_at_range(FusionSeqRange& rng) :
        super_t(rng, fun_t())
    { }
};


// generators
//

template< class N, class FusionSeqRange > inline
get_at_range<FusionSeqRange, N> const
make_get_at_range(FusionSeqRange& rng, typename const_overloaded<FusionSeqRange>::type = 0)
{
    return get_at_range<FusionSeqRange, N>(rng);
}


template< class N, class FusionSeqRange > inline
get_at_range<typename boost::add_const<FusionSeqRange>::type, N> const
make_get_at_range(FusionSeqRange const& rng)
{
    return get_at_range<typename boost::add_const<FusionSeqRange>::type, N>(rng);
}


template< class N >
struct got_at;


namespace get_at_range_detail {


    struct adl_marker
    { };


    template< class FusionSeqRange, class N > inline
    get_at_range<FusionSeqRange, N> const
    operator|(FusionSeqRange& rng, got_at<N> const&)
    {
        return get_at_range<FusionSeqRange, N>(rng);
    }


    template< class FusionSeqRange, class N > inline
    get_at_range<typename boost::add_const<FusionSeqRange>::type, N> const
    operator|(FusionSeqRange const& rng, got_at<N> const&)
    {
        return get_at_range<typename boost::add_const<FusionSeqRange>::type, N>(rng);
    }


} // namespace get_at_range_detail


template< class N >
struct got_at :
    get_at_range_detail::adl_marker,
    private nonassignable
    // Topic:
    // 'noncopyable' is allowed here by the latest standard draft,
    // but GCC doesn't follow it.
    // http://www.codecomments.com/archive324-2006-4-888159.html
{ };


template< int N >
struct got_at_c :
    got_at< boost::mpl::int_<N> >
{ };


} } // namespace pstade::oven


#endif
