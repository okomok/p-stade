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
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./memoize_iterator.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace memo_table_detail {


    struct auto_ptr_placeholder
    {
        virtual ~auto_ptr_placeholder()
        { }
    };

    template< class X >
    struct auto_ptr_holder :
        auto_ptr_placeholder
    {
        auto_ptr_holder(std::auto_ptr<X> px) :
            m_px(px)
        { }

    private:
        std::auto_ptr<X> m_px;
    };


    struct any_auto_ptr
    {
        template< class X >
        void reset(std::auto_ptr<X> px)
        {
            m_pimpl.reset(new auto_ptr_holder<X>(px));
        }

    private:
        std::auto_ptr<auto_ptr_placeholder> m_pimpl;
    };
    

} // namespace memo_table_detail


struct memo_table :
    private boost::noncopyable
{
    memo_table()
    { }

    template< class Iterator >
    void detail_reset(std::auto_ptr<Iterator> pfirst, std::auto_ptr<Iterator> plast)
    {
        m_pfirst.reset(pfirst);
        m_plast.reset(plast);
    }

private:
    memo_table_detail::any_auto_ptr m_pfirst;
    memo_table_detail::any_auto_ptr m_plast;
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
        typedef typename iter_t::base_type base_iter_t;

        // They live outside of recursive cycles.
        std::auto_ptr<base_iter_t>
            pfirst( new base_iter_t(boost::begin(rng)) ),
            plast ( new base_iter_t(boost::end(rng)) );

        Result ret(iter_t(pfirst.get()), iter_t(plast.get()));
        tb.detail_reset(pfirst, plast);
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
        return Result(rng);
    }
};


PSTADE_CONSTANT(make_memoized, (op_make_memoized))
PSTADE_PIPABLE(memoized, (op_make_memoized))


} } // namespace pstade::oven


#endif
