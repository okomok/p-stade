#ifndef PSTADE_OVEN_ELEMENTS_HPP
#define PSTADE_OVEN_ELEMENTS_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/int.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/affect.hpp>
#include <pstade/callable.hpp>
#include <pstade/deduced_const.hpp>
#include <pstade/nonassignable.hpp>
#include <pstade/specified.hpp>
#include <pstade/tuple.hpp>
#include "./concepts.hpp"
#include "./deref.hpp"
#include "./range_iterator.hpp"
#include "./range_value.hpp"
#include "./transformed.hpp"


namespace pstade { namespace oven {


template< class N >
struct op_make_elements :
    callable< op_make_elements<N> >
{
private:
    template< class TupleRange >
    struct ref_of :
        affect<
            typename deref_of<typename range_iterator<TupleRange>::type>::type,
            typename tuple_element<N, typename range_value<TupleRange>::type>::type
        >
    { };

public:
    template< class Myself, class TupleRange >
    struct apply
    {
        typedef typename
            boost::result_of<
                op_make_transformed<typename ref_of<TupleRange>::type>(
                    TupleRange&, op_tuple_get<N>
                )
            >::type
        type;
    };

    template< class Result, class TupleRange >
    Result call(TupleRange& rng) const
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<TupleRange>));

        return op_make_transformed<typename ref_of<TupleRange>::type>()(
            rng, op_tuple_get<N>()
        );
    }
};


template< int N >
struct op_make_elements_c :
    op_make_elements< boost::mpl::int_<N> >
{ };


PSTADE_SPECIFIED1(make_elements, op_make_elements, 1)
PSTADE_SPECIFIED1(make_elements_c, op_make_elements_c, (int))


namespace elements_detail_ {


    template< class N >
    struct elements :
        private nonassignable
    { };


    template< int N >
    struct elements_c :
        elements< boost::mpl::int_<N> >
    { };


    template< class TupleRange, class N > inline
    typename boost::result_of<op_make_elements<N>(TupleRange&)>::type
    operator|(TupleRange& rng, elements<N>)
    {
        return op_make_elements<N>()(rng);
    }

    template< class TupleRange, class N > inline
    typename boost::result_of<op_make_elements<N>(PSTADE_DEDUCED_CONST(TupleRange)&)>::type
    operator|(TupleRange const& rng, elements<N>)
    {
        return op_make_elements<N>()(rng);
    }


} // namespace elements_detail_


using elements_detail_::elements;
using elements_detail_::elements_c;


} } // namespace pstade::oven


#endif
