#ifndef PSTADE_OVEN_GET_AT_RANGE_HPP
#define PSTADE_OVEN_GET_AT_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/mpl/int.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <pstade/affect.hpp>
#include <pstade/const_overloaded.hpp>
#include <pstade/nonassignable.hpp>
#include <pstade/param.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./detail/concept_check.hpp"
#include "./range_iterator.hpp"
#include "./range_reference.hpp"


namespace pstade { namespace oven {


namespace get_at_range_detail {


    template< class FusionSeqRange, class N >
    struct get_at_fun
    {
        typedef typename range_reference<FusionSeqRange>::type seq_ref_t;
        typedef typename boost::remove_reference<seq_ref_t>::type seq_t;

        typedef typename affect_cvr<
            seq_ref_t,
            typename boost::fusion::result_of::at<seq_t, N>::type
        >::type result_type;

        result_type operator()(typename param<seq_ref_t>::type seq) const
        {
            return boost::fusion::at<N>(seq);
        }
    };


    template< class FusionSeqRange, class N >
    struct super_
    {
        typedef boost::iterator_range<
            boost::transform_iterator<
                get_at_fun<FusionSeqRange, N>,
                typename range_iterator<FusionSeqRange>::type
            >
        > type;
    };


} // namespace get_at_range_detail


template< class FusionSeqRange, class N >
struct get_at_range :
    get_at_range_detail::super_<FusionSeqRange, N>::type,
    private as_lightweight_proxy< get_at_range<FusionSeqRange, N> >
{
    typedef FusionSeqRange pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(FusionSeqRange, SinglePassRangeConcept);
    typedef typename get_at_range_detail::super_<FusionSeqRange, N>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    explicit get_at_range(FusionSeqRange& rng) :
        super_t(
            iter_t(boost::begin(rng), get_at_range_detail::get_at_fun<FusionSeqRange, N>()),
            iter_t(boost::end(rng),   get_at_range_detail::get_at_fun<FusionSeqRange, N>())
        )
    { }
};


// generators
//

template< class N, class FusionSeqRange > inline
typename const_overloaded<get_at_range<FusionSeqRange, N>, FusionSeqRange>::type const
make_get_at_range(FusionSeqRange& rng)
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
    // Note:
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
