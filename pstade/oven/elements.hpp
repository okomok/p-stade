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
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/egg/specified.hpp>
#include <pstade/egg/tuple/element.hpp>
#include <pstade/egg/tuple/get.hpp>
#include <pstade/result_of.hpp>
#include <pstade/use_default.hpp>
#include "./concepts.hpp"
#include "./range_iterator.hpp"
#include "./range_value.hpp"
#include "./read.hpp"
#include "./transformed.hpp"


namespace pstade { namespace oven {


namespace elements_detail {


    template< class N, class Reference >
    struct little
    {
    private:
        template< class TupleRange >
        struct ref_of :
            eval_if_use_default<Reference,
                affect<
                    typename iterator_read<typename range_iterator<TupleRange>::type>::type,
                    typename egg::tuple_element<N, typename range_value<TupleRange>::type>::type
                >
            >
        { };

    public:
        template< class Myself, class TupleRange >
        struct apply :
            result_of<
                X_make_transformed<typename ref_of<TupleRange>::type>(
                    TupleRange&, egg::X_tuple_get<N>
                )
            >
        { };

        template< class Result, class TupleRange >
        Result call(TupleRange& rng) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<TupleRange>));

            return X_make_transformed<typename ref_of<TupleRange>::type>()(
                rng, egg::X_tuple_get<N>()
            );
        }
    };


} // namespace elements_detail


template< class N, class Reference = boost::use_default >
struct X_make_elements :
    egg::function< elements_detail::little<N, Reference> >
{ };

template< int N, class Reference = boost::use_default >
struct X_make_elements_c :
    X_make_elements<boost::mpl::int_<N>, Reference>
{ };


#define  PSTADE_EGG_SPECIFIED_PARAMS (make_elements, X_make_elements, (class), (1))
#include PSTADE_EGG_SPECIFIED()

#define  PSTADE_EGG_SPECIFIED_PARAMS (make_elements_c, X_make_elements_c, (int), (1))
#include PSTADE_EGG_SPECIFIED()


template< class N, class Reference = boost::use_default >
struct elements :
    egg::result_of_pipable< X_make_elements<N, Reference> >::type,
    egg::lookup_pipable_operator
{ };

template< int N, class Reference = boost::use_default >
struct elements_c :
    elements<boost::mpl::int_<N>, Reference>
{ };


} } // namespace pstade::oven


#endif
