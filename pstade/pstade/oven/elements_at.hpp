#ifndef PSTADE_OVEN_ELEMENTS_AT_HPP
#define PSTADE_OVEN_ELEMENTS_AT_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/version.hpp>
#if BOOST_VERSION >= 103500


#include <boost/mpl/int.hpp>
#include <boost/mpl/placeholders.hpp> // _1
#include <boost/utility/result_of.hpp>
#include <pstade/at.hpp>
#include <pstade/callable.hpp>
#include <pstade/deduced_const.hpp>
#include <pstade/nonassignable.hpp>
#include <pstade/specified.hpp>
#include "./concepts.hpp"
#include "./detail/reference_affect.hpp"
#include "./transformed.hpp"


namespace pstade { namespace oven {


template< class N >
struct op_make_elements_at :
    callable< op_make_elements_at<N> >
{
    template< class Myself, class TupleRange >
    struct apply
    {
        typedef typename
            detail::reference_affect<
                TupleRange,
                fusion_element_at<boost::mpl::_1, N>
            >::type
        ref_t;

        typedef typename
            boost::result_of<
                op_make_transformed<ref_t>(TupleRange&, op_fusion_at<N>)
            >::type
        type;
    };

    template< class Result, class TupleRange >
    Result call(TupleRange& rng) const
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<TupleRange>));

        typedef typename apply<void, TupleRange>::ref_t ref_t;
        return op_make_transformed<ref_t>()(rng, op_fusion_at<N>());
    }
};


template< int N >
struct op_make_elements_at_c :
    op_make_elements_at< boost::mpl::int_<N> >
{ };


PSTADE_SPECIFIED1(make_elements_at, op_make_elements_at, 1)
PSTADE_SPECIFIED1(make_elements_at_c, op_make_elements_at_c, (int))


namespace elements_at_detail_ {


    template< class N >
    struct elements_at :
        private nonassignable
    { };


    template< int N >
    struct elements_at_c :
        elements_at< boost::mpl::int_<N> >
    { };


    template< class TupleRange, class N > inline
    typename boost::result_of<op_make_elements_at<N>(TupleRange&)>::type
    operator|(TupleRange& rng, elements_at<N>)
    {
        return op_make_elements_at<N>()(rng);
    }

    template< class TupleRange, class N > inline
    typename boost::result_of<op_make_elements_at<N>(PSTADE_DEDUCED_CONST(TupleRange)&)>::type
    operator|(TupleRange const& rng, elements_at<N>)
    {
        return op_make_elements_at<N>()(rng);
    }


} // namespace elements_at_detail_


using elements_at_detail_::elements_at;
using elements_at_detail_::elements_at_c;


} } // namespace pstade::oven


#endif // BOOST_VERSION >= 103500


#endif
