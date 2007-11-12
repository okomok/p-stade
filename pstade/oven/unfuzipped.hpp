#ifndef PSTADE_OVEN_UNFUZIPPED_HPP
#define PSTADE_OVEN_UNFUZIPPED_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/version.hpp>
#if BOOST_VERSION >= 103500


#include <boost/fusion/include/as_vector.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/include/transform.hpp>
#include <boost/mpl/always.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/mpl/vector/vector20.hpp>
#include <boost/mpl/zip_view.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/remove_cvr.hpp>
#include <pstade/result_of.hpp>
#include <pstade/use_default.hpp>
#include "./concepts.hpp"
#include "./detail/baby_to_adaptor.hpp"
#include "./elements.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


namespace unfuzipped_detail {


    namespace fusion = boost::fusion;
    namespace mpl = boost::mpl;


    template< class TupleRange >
    struct make_at_range
    {
        template< class N_Ref >
        struct result_aux :
            result_of<
                X_make_elements<typename mpl::at_c<N_Ref, 0>::type, typename mpl::at_c<N_Ref, 1>::type>(TupleRange&)
            >
        { };

        template< class FunCall >
        struct result;

        template< class Fun, class N_Ref >
        struct result<Fun(N_Ref)> :
            result_aux<typename remove_cvr<N_Ref>::type>
        { };

        template< class N_Ref >
        typename result_aux<N_Ref>::type
        operator()(N_Ref) const
        {
            return X_make_elements<typename mpl::at_c<N_Ref, 0>::type, typename mpl::at_c<N_Ref, 1>::type>()(m_rng);
        }

        explicit make_at_range(TupleRange& rng) :
            m_rng(rng)
        { }

    private:
        TupleRange& m_rng;
    };


    template< class Tuple >
    struct use_default_tuple
    {
        typedef
            mpl::transform_view< Tuple, mpl::always<boost::use_default> >
        type;
    };


    template< class RefTuple >
    struct baby
    {
        template< class Myself, class TupleRange >
        struct apply
        {
            typedef typename
                range_value<TupleRange>::type
            tup_t;

            typedef
                mpl::range_c<int, 0, mpl::size<tup_t>::value>
            counting_tup_t;

            typedef typename
                eval_if_use_default< RefTuple, use_default_tuple<counting_tup_t> >::type
            ref_tup_t;

            typedef
                mpl::zip_view< mpl::vector2<counting_tup_t, ref_tup_t> >
            count_and_ref_tup_t;

            typedef typename
                fusion::result_of::as_vector<
                    typename fusion::result_of::transform<
                        count_and_ref_tup_t const,
                        make_at_range<TupleRange>
                    >::type const            
                >::type
            type;
        };

        template< class Result, class TupleRange >
        Result call(TupleRange& rng) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<TupleRange>));

            typedef apply<void, TupleRange> apply_t;
            return fusion::as_vector(
                fusion::transform(typename apply_t::count_and_ref_tup_t(), make_at_range<TupleRange>(rng))
            );
        }
    };


    template< class RefTuple >
    struct pod_
    {
        typedef egg::function< baby<RefTuple> > type;
    };


} // namespace unfuzipped_detail


template< class RefTuple = boost::use_default >
struct X_make_unfuzipped :
    unfuzipped_detail::pod_<RefTuple>::type
{
    typedef typename unfuzipped_detail::pod_<RefTuple>::type pod_type;
};


PSTADE_OVEN_BABY_TO_ADAPTOR(unfuzipped, (X_make_unfuzipped<>::pod_type::baby_type))


} } // namespace pstade::oven


#endif // BOOST_VERSION >= 103500


#endif
