#ifndef PSTADE_OVEN_MEMOIZED_HPP
#define PSTADE_OVEN_MEMOIZED_HPP


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
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./memoize_iterator.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace memo_table_detail {


    // 'boost::any' takes argument as const-reference,
    // which makes 'auto_ptr' unmovable. So we define...

    struct value_placeholder
    {
        virtual ~value_placeholder()
        { }
    };

    template< class Value >
    struct value_holder :
        value_placeholder
    {
        explicit value_holder(Value value) :
            m_value(value)
        { }

    private:
        Value m_value;
    };

    struct any_value
    {
        template< class Value >
        void reset(Value value)
        {
            m_pcontent.reset(new value_holder<Value>(value));
        }

    private:
        std::auto_ptr<value_placeholder> m_pcontent;
    };
    

} // namespace memo_table_detail


struct memo_table :
    private boost::noncopyable
{
    memo_table()
    { }

    template< class V, class W >
    void detail_reset(V v, W w)
    {
        m_v.reset(v);
        m_w.reset(w);
    }

private:
    memo_table_detail::any_value m_v;
    memo_table_detail::any_value m_w;
};


struct op_make_memoized :
    callable<op_make_memoized>
{
    template< class Myself, class Range, class MemoTable = void >
    struct apply
    {
        typedef
            memoize_iterator<
                typename range_iterator<Range>::type,
                boost::mpl::true_ // recursive
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
            memoize_iterator<
                typename range_iterator<Range>::type
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


PSTADE_CONSTANT(make_memoized, (op_make_memoized))
PSTADE_PIPABLE(memoized, (op_make_memoized))


} } // namespace pstade::oven


#endif
