#ifndef PSTADE_OVEN_SCANNED_HPP
#define PSTADE_OVEN_SCANNED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/optional/optional.hpp>
#include <boost/range/empty.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./detail/minimum_pure.hpp"
#include "./dropped.hpp"
#include "./front.hpp"
#include "./iter_range.hpp"
#include "./jointed.hpp"
#include "./range_iterator.hpp"
#include "./shared_single.hpp"


namespace pstade { namespace oven {


namespace scanned_detail {


    template< class Iterator, class State, class BinaryFun >
    struct scan_iterator;


    template< class Iterator, class State, class BinaryFun >
    struct scan_iterator_super
    {
        typedef
            boost::iterator_adaptor<
                scan_iterator<Iterator, State, BinaryFun>,
                Iterator,
                State,
                typename detail::minimum_pure<
                    boost::forward_traversal_tag,
                    typename boost::iterator_traversal<Iterator>::type
                >::type,
                State const& // can be reference thanks to 'm_cache'.
            >
        type;
    };


    template< class Iterator, class State, class BinaryFun >
    struct scan_iterator :
        scan_iterator_super<Iterator, State, BinaryFun>::type
    {
    private:
        typedef typename scan_iterator_super<Iterator, State, BinaryFun>::type super_t;
        typedef typename super_t::reference ref_t;

    public:
        scan_iterator()
        { }

        scan_iterator(Iterator it, State const& init, BinaryFun fun) :
            super_t(it), m_state(init), m_fun(fun)
        { }

        template< class I, class S >
        scan_iterator(scan_iterator<I, S, BinaryFun> const& other,
            typename boost::enable_if_convertible<I, Iterator>::type * = 0,
            typename boost::enable_if_convertible<S, State>::type    * = 0
        ) :
            super_t(other.base()), m_state(other.state()), m_fun(other.function())
        { }

        State state() const
        {
            return m_state;
        }

        BinaryFun function() const
        {
            return m_fun;
        }

    private:
        State m_state;
        BinaryFun m_fun;
        mutable boost::optional<State> m_cache;

        State call_fun() const
        {
            return m_fun(m_state, *this->base());
        }

    friend class boost::iterator_core_access;
        ref_t dereference() const
        {
            if (!m_cache)
                m_cache = call_fun();

            return *m_cache;
        }

        void increment()
        {
            m_state = call_fun();
            ++this->base_reference();
            m_cache.reset();
        }
    };


    template< class Range, class State, class BinaryFun >
    struct baby
    {
        typedef
            scan_iterator<
                typename range_iterator<Range>::type,
                typename pass_by_value<State>::type,
                typename pass_by_value<BinaryFun>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(Range& rng, State& init, BinaryFun& fun) const
        {
            return result_type(
                iter_t(boost::begin(rng), init, fun),
                iter_t(boost::end(rng),   init, fun)
            );
        }
    };


} // namespace scanned_detail


struct op_make_scanned :
    callable<op_make_scanned>
{
    template< class Myself, class Range, class State, class BinaryFun = void >
    struct apply :
        boost::result_of<
            op_make_jointed(
                typename boost::result_of<op_shared_single(State const *)>::type,
                typename scanned_detail::baby<Range, State, BinaryFun>::result_type
            )
        >
    { };

    template< class Result, class Range, class State, class BinaryFun >
    Result call(Range& rng, State& init, BinaryFun& fun) const
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

        // Prefer const-qualified 'State';
        // It's common that 'rng' is constant but 'init' isn't 'const'.
        // As 'scan_iterator' is constant, 'make_jointed' won't work in such case.
        return make_jointed(
            shared_single(new State const(init)),
            scanned_detail::baby<Range, State, BinaryFun>()(rng, init, fun)
        );
    }

    template< class Myself, class Range, class BinaryFun >
    struct apply<Myself, Range, BinaryFun> :
        boost::result_of<
            op_make_scanned(
                typename boost::result_of<op_make_dropped(Range&, int)>::type,
                typename boost::result_of<op_value_front(Range&)>::type,
                BinaryFun&
            )
        >
    { };

    template< class Result, class Range, class BinaryFun >
    Result call(Range& rng, BinaryFun& fun) const
    {
        BOOST_ASSERT(!boost::empty(rng));
        return (*this)(make_dropped(rng, 1), value_front(rng), fun);
    }
};


PSTADE_CONSTANT(make_scanned, (op_make_scanned))
PSTADE_PIPABLE(scanned, (op_make_scanned))


} } // namespace pstade::oven


#endif
