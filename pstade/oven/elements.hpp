#ifndef PSTADE_OVEN_ELEMENTS_HPP
#define PSTADE_OVEN_ELEMENTS_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/int.hpp>
#include <pstade/affect.hpp>
#include <pstade/deduced_const.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/specified.hpp>
#include <pstade/egg/tuple_element.hpp>
#include <pstade/egg/tuple_get.hpp>
#include <pstade/result_of.hpp>
#include "./concepts.hpp"
#include "./range_iterator.hpp"
#include "./range_value.hpp"
#include "./read.hpp"
#include "./transformed.hpp"


namespace pstade { namespace oven {


template< class N >
struct tp_make_elements
{
private:
    template< class TupleRange >
    struct ref_of :
        affect<
            typename iterator_read<typename range_iterator<TupleRange>::type>::type,
            typename egg::tuple_element<N, typename range_value<TupleRange>::type>::type
        >
    { };

public:
    struct baby
    {
        template< class Myself, class TupleRange >
        struct apply :
            result_of<
                xp_make_transformed<typename ref_of<TupleRange>::type>(
                    TupleRange&, egg::xp_tuple_get<N>
                )
            >
        { };

        template< class Result, class TupleRange >
        Result call(TupleRange& rng) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<TupleRange>));

            return xp_make_transformed<typename ref_of<TupleRange>::type>()(
                rng, egg::xp_tuple_get<N>()
            );
        }
    };

    typedef egg::function<baby> type;
};


template< class N >
struct xp_make_elements :
    tp_make_elements<N>::type
{ };

template< int N >
struct xp_make_elements_c :
    tp_make_elements< boost::mpl::int_<N> >::type
{ };


PSTADE_EGG_SPECIFIED1(make_elements, xp_make_elements, (class))
PSTADE_EGG_SPECIFIED1(make_elements_c, xp_make_elements_c, (int))


namespace elements_detail_ {


    template< class N >
    struct elements
    {
    private:
        elements& operator=(elements const&);    
    };


    template< int N >
    struct elements_c :
        elements< boost::mpl::int_<N> >
    { };


    template< class TupleRange, class N > inline
    typename result_of<xp_make_elements<N>(TupleRange&)>::type
    operator|(TupleRange& rng, elements<N>)
    {
        return xp_make_elements<N>()(rng);
    }

    template< class TupleRange, class N > inline
    typename result_of<xp_make_elements<N>(PSTADE_DEDUCED_CONST(TupleRange)&)>::type
    operator|(TupleRange const& rng, elements<N>)
    {
        return xp_make_elements<N>()(rng);
    }


} // namespace elements_detail_


using elements_detail_::elements;
using elements_detail_::elements_c;


} } // namespace pstade::oven


#endif
