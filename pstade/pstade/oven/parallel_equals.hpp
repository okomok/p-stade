#ifndef PSTADE_OVEN_PARALLEL_EQUALS_HPP
#define PSTADE_OVEN_PARALLEL_EQUALS_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/detail/atomic_count.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/noncopyable.hpp>
#include <boost/range/empty.hpp>
#include <boost/ref.hpp>
#include <boost/thread/thread.hpp>
#include <pstade/egg/equal_to.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/make_function_of.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "./concepts.hpp"
#include "./detail/default_grainsize.hpp"
#include "./detail/minimum_pure.hpp"
#include "./distance.hpp"
#include "./equals.hpp"
#include "./iter_range.hpp"
#include "./range_difference.hpp"
#include "./range_traversal.hpp"
#include "./split_at.hpp"


namespace pstade { namespace oven {


namespace parallel_equals_detail {


    typedef boost::detail::atomic_count atomic_bool;


    template< class Predicate >
    struct breakable
    {
        template< class X, class Y >
        bool operator()(X const& x, Y const& y) const
        {
            if (*m_pbreak)
                return false;
            else
                return m_pred(x, y);
        }

        void break_()
        {
            BOOST_ASSERT(*m_pbreak == 0);
            ++*m_pbreak;
        }

        breakable(Predicate pred, atomic_bool *pbreak) :
            m_pred(pred), m_pbreak(pbreak)
        { }

        Predicate base() const
        {
            return m_pred;
        }

    private:
        Predicate m_pred;
        atomic_bool *m_pbreak;
    };


    template< class IterRange1, class IterRange2, class Predicate >
    struct aux :
        private boost::noncopyable
    {
    private:
        typedef typename range_difference<IterRange1>::type diff_t;

    public:
        void operator()()
        {
            typename result_of<op_make_split_at(IterRange1&, diff_t&)>::type xs_ys1 = make_split_at(m_rng1, m_grain);
            if (boost::empty(xs_ys1.second)) {
                m_equal = algo(xs_ys1.first, m_rng2);
                return;
            }

            typename result_of<op_make_split_at(IterRange2&, diff_t&)>::type xs_ys2 = make_split_at(m_rng2, m_grain);
            if (boost::empty(xs_ys2.second)) {
                m_equal = false;
                return;
            }

            aux auxR(m_grain, xs_ys1.second, xs_ys2.second, m_breakable_pred.base());
            boost::thread thrd(boost::ref(auxR));

            m_equal = algo(xs_ys1.first, xs_ys2.first);
            if (!m_equal)
                auxR.m_breakable_pred.break_();

            thrd.join();
            m_equal = m_equal && auxR.equal();
        }

        template< class Range1, class Range2 >
        bool algo(Range1& rng1, Range2& rng2) const
        {
            return equals(rng1, rng2, m_breakable_pred);
        }

        template< class Range1, class Range2 >
        aux(diff_t grainsize, Range1& rng1, Range2& rng2, Predicate pred) :
            m_grain(grainsize), m_rng1(rng1), m_rng2(rng2),
            m_bool(0), m_breakable_pred(pred, &m_bool), m_equal(false)
        { }

        bool equal() const
        {
            return m_equal;
        }

    private:
        diff_t m_grain;
        IterRange1 m_rng1;
        IterRange2 m_rng2;
        atomic_bool m_bool;
        breakable<Predicate> m_breakable_pred;
        bool m_equal;
    };


    struct baby
    {
        template< class Difference, class IterRange1, class IterRange2, class Predicate >
        bool call_aux(Difference grainsize, IterRange1 rng1, IterRange2 rng2, Predicate pred, boost::random_access_traversal_tag) const
        {
            if (distance(rng1) != distance(rng2))
                return false;

            return call_aux(grainsize, rng1, rng2, pred, boost::forward_traversal_tag()); 
        }

        template< class Difference, class IterRange1, class IterRange2, class Predicate >
        bool call_aux(Difference grainsize, IterRange1 rng1, IterRange2 rng2, Predicate pred, boost::forward_traversal_tag) const
        {
            aux<IterRange1, IterRange2, Predicate> auxRoot(detail::default_grainsize(grainsize, rng1), rng1, rng2, pred);
            auxRoot();
            return auxRoot.equal();
        }

        template< class Myself, class Difference, class Range1, class Range2, class Predicate = egg::op_equal_to const >
        struct apply
        {
            typedef bool type;
        };

        template< class Result, class Difference, class Range1, class Range2, class Predicate >
        Result call(Difference& grainsize, Range1& rng1, Range2& rng2, Predicate& pred) const
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range1>));
            PSTADE_CONCEPT_ASSERT((Forward<Range2>));

            typedef typename detail::minimum_pure<
                typename range_traversal<Range1>::type,
                typename range_traversal<Range2>::type
            >::type trv_t;

            return call_aux(grainsize, make_iter_range(rng1), make_iter_range(rng2), pred, trv_t());
        }

        template< class Result, class Difference, class Range1, class Range2 >
        Result call(Difference& grainsize, Range1& rng1, Range2& rng2) const
        {
            return egg::make_function_of(*this)(grainsize, rng1, rng2, egg::equal_to);
        }
    };


} // namespace parallel_equals_detail


typedef egg::function<parallel_equals_detail::baby> op_parallel_equals;
PSTADE_POD_CONSTANT((op_parallel_equals), parallel_equals) = {{}};


} } // namespace pstade::oven


#endif
