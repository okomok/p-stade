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


#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/fusion/sequence/adapted/mpl.hpp>
#include <boost/fusion/sequence/conversion/as_vector.hpp>
#include <boost/fusion/sequence/intrinsic/mpl.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/size.hpp>
#include <pstade/remove_cvr.hpp>
#include <pstade/result_of.hpp>
#include "./concepts.hpp"
#include "./detail/base_to_adaptor.hpp"
#include "./elements.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


namespace unfuzipped_detail {


    namespace fusion = boost::fusion;
    namespace mpl = boost::mpl;


    template< class TupleRange >
    struct make_at_range
    {
        template< class N >
        struct result_aux :
            result_of<
                xp_make_elements<N>(TupleRange&)
            >
        { };

        template< class FunCall >
        struct result;

        template< class Fun, class N >
        struct result<Fun(N)> :
            result_aux<typename remove_cvr<N>::type>
        { };

        template< class N >
        typename result_aux<N>::type
        operator()(N) const
        {
            return xp_make_elements<N>()(m_rng);
        }

        explicit make_at_range(TupleRange& rng) :
            m_rng(rng)
        { }

    private:
        TupleRange& m_rng;
    };


    template< class TupleRange >
    struct base
    {
        typedef typename
            range_value<TupleRange>::type
        tup_t;

        typedef
            mpl::range_c<int, 0, mpl::size<tup_t>::value>
        counting_tup_t;

        typedef typename
            fusion::result_of::as_vector<
                typename fusion::result_of::transform<
                    counting_tup_t const,
                    make_at_range<TupleRange>
                >::type const            
            >::type
        result_type;

        result_type operator()(TupleRange& rng) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<TupleRange>));

            return fusion::as_vector(
                fusion::transform(counting_tup_t(), make_at_range<TupleRange>(rng))
            );
        }
    };


} // namespace unfuzipped_detail


PSTADE_OVEN_BASE_TO_ADAPTOR(unfuzipped, (unfuzipped_detail::base<_>))


} } // namespace pstade::oven


#endif // BOOST_VERSION >= 103500


#endif
