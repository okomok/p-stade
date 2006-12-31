#ifndef PSTADE_OVEN_UNZIP_RANGE_HPP
#define PSTADE_OVEN_UNZIP_RANGE_HPP


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
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./detail/reference_affect.hpp"
#include "./range_reference.hpp"
#include "./transform_range.hpp"


namespace pstade { namespace oven {


namespace unzip_at_range_detail {


    template< class TupleRange, class N >
    struct super_ // avoid inheritance; GCC3.4 is broken by MPL.
    {
        typedef
            transform_range<
                TupleRange,
                op_at<N>,
                typename detail::reference_affect<
                    TupleRange,
                    value_at<boost::mpl::_1, N>
                >::type
            >
        type;
    };


} // namespace unzip_at_range_detail


template< class TupleRange, class N >
struct unzip_at_range :
    unzip_at_range_detail::super_<TupleRange, N>::type,
    private as_lightweight_proxy< unzip_at_range<TupleRange, N> >
{
    PSTADE_CONCEPT_ASSERT((SinglePass<TupleRange>));
    typedef N index_type;

private:
    typedef typename unzip_at_range_detail::super_<TupleRange, N>::type super_t;
    typedef typename super_t::function_type fun_t;

public:
    explicit unzip_at_range(TupleRange& rng) :
        super_t(rng, fun_t())
    { }
};


template< class N, class TupleRange > inline
unzip_at_range<TupleRange, N> const
make_unzip_at_range(TupleRange& rng,
    typename const_overloaded<TupleRange>::type = 0)
{
    return unzip_at_range<TupleRange, N>(rng);
}


template< class N, class TupleRange > inline
unzip_at_range<PSTADE_DEDUCED_CONST(TupleRange), N> const
make_unzip_at_range(TupleRange const& rng)
{
    return unzip_at_range<PSTADE_DEDUCED_CONST(TupleRange), N>(rng);
}


template< class N >
struct unzipped_at;


namespace unzip_at_range_detail {


    struct adl_marker
    { };


    template< class TupleRange, class N > inline
    unzip_at_range<TupleRange, N> const
    operator|(TupleRange& rng, unzipped_at<N> const&)
    {
        return unzip_at_range<TupleRange, N>(rng);
    }


    template< class TupleRange, class N > inline
    unzip_at_range<PSTADE_DEDUCED_CONST(TupleRange), N> const
    operator|(TupleRange const& rng, unzipped_at<N> const&)
    {
        return unzip_at_range<PSTADE_DEDUCED_CONST(TupleRange), N>(rng);
    }


} // namespace unzip_at_range_detail


template< class N >
struct unzipped_at :
    unzip_at_range_detail::adl_marker,
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
        struct apply
        {
            typedef unzip_at_range<TupleRange, N> type;
        };

        template< class N >
        typename apply<N>::type
        operator()(N const&) const
        {
            typedef typename apply<N>::type result_t;
            return result_t(m_rng);
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
