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
#include <boost/tuple/tuple.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./elements.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


namespace unzipped_detail {


    namespace here = unzipped_detail;


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
                op_make_elements<N>(TupleRange&)
            >
        { };

        template< class N >
        typename apply<N>::type
        operator()(N) const
        {
            return op_make_elements<N>()(m_rng);
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
        result_type;

        result_type operator()(TupleRange& rng) const
        {
            return here::tuple_transform(
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
