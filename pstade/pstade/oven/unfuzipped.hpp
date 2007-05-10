#ifndef PSTADE_OVEN_UNFUZIPPED_HPP
#define PSTADE_OVEN_UNFUZIPPED_HPP


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
#include <boost/utility/result_of.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./elements_at.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


namespace unfuzipped_detail {


    namespace fusion = boost::fusion;
    namespace mpl = boost::mpl;


    template< class TupleRange >
    struct make_at_range
    {
        template< class N >
        struct result :
            boost::result_of<
                op_make_elements_at<N>(TupleRange&)
            >
        { };

        template< class N >
        typename result<N>::type
        operator()(N) const
        {
            return op_make_elements_at<N>()(m_rng);
        }

        explicit make_at_range(TupleRange& rng) :
            m_rng(rng)
        { }

    private:
        TupleRange& m_rng;
    };


    template< class TupleRange >
    struct baby
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


PSTADE_FUNCTION(make_unfuzipped, (unfuzipped_detail::baby<_>))
PSTADE_PIPABLE(unfuzipped, (op_make_unfuzipped))


} } // namespace pstade::oven


#endif // BOOST_VERSION >= 103500


#endif
