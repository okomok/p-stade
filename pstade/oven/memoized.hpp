#ifndef PSTADE_OVEN_MEMOIZED_HPP
#define PSTADE_OVEN_MEMOIZED_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <memory> // auto_ptr
#include <boost/mpl/bool.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/shared_ptr.hpp>
#include <pstade/any_movable.hpp>
#include "./concepts.hpp"
#include "./detail/baby_to_adaptor.hpp"
#include "./detail/memoize_iterator.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


struct memo_table :
    private boost::noncopyable
{
    template< class V, class W >
    void detail_reset(V v, W w)
    {
        m_v = v; m_w = w;
    }

private:
    any_movable m_v, m_w;
};


namespace memoized_detail {


    struct baby
    {
        template< class Myself, class Range, class MemoTable = void >
        struct apply
        {
            typedef
                detail::memoize_iterator<
                    typename range_iterator<Range>::type,
                    boost::mpl::true_
                >
            iter_t;

            typedef
                iter_range<iter_t> const
            type;
        };

        template< class Result, class Range >
        Result call(Range& rng, memo_table& tb) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

            typedef typename Result::iterator iter_t;
            typedef typename iter_t::memo_type memo_t;

            // They live outside of recursive cycles.
            std::auto_ptr<memo_t>
                pfirstData( new memo_t(boost::begin(rng)) ),
                plastData ( new memo_t(boost::end(rng))   );

            Result ret(iter_t(pfirstData.get()), iter_t(plastData.get()));
            tb.detail_reset(pfirstData, plastData);
            return ret;
        }

        template< class Myself, class Range >
        struct apply<Myself, Range>
        {
            typedef
                detail::memoize_iterator<
                    typename range_iterator<Range>::type,
                    boost::mpl::false_
                >
            iter_t;

            typedef
                iter_range<iter_t> const
            type;
        };

        template< class Result, class Range >
        Result call(Range& rng) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

            typedef typename Result::iterator iter_t;
            typedef typename iter_t::memo_type memo_t;

            boost::shared_ptr<memo_t>
                pfirstData( new memo_t(boost::begin(rng)) ),
                plastData ( new memo_t(boost::end(rng))   );

            return Result(iter_t(pfirstData), iter_t(plastData));
        }
    };


} // namespace memoized_detail


PSTADE_OVEN_BABY_TO_ADAPTOR(memoized, (memoized_detail::baby))


} } // namespace pstade::oven


#endif
