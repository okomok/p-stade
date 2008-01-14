#ifndef PSTADE_OVEN_DETAIL_SCAN_ITERATOR_HPP
#define PSTADE_OVEN_DETAIL_SCAN_ITERATOR_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/optional/optional.hpp>
#include "../read.hpp"
#include "./minimum_pure.hpp"


namespace pstade { namespace oven { namespace detail {


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
            typename minimum_pure<
                boost::forward_traversal_tag,
                typename boost::iterator_traversal<Iterator>::type
            >::type,
            State const& // can be reference thanks to 'm_after'.
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
        super_t(it), m_before(init), m_fun(fun)
    { }

    template< class I, class S >
    scan_iterator(scan_iterator<I, S, BinaryFun> const& other,
        typename boost::enable_if_convertible<I, Iterator>::type * = 0,
        typename boost::enable_if_convertible<S, State>::type    * = 0
    ) :
        super_t(other.base()), m_before(other.state()), m_fun(other.function())
    { }

    State state() const
    {
        return m_before;
    }

    BinaryFun function() const
    {
        return m_fun;
    }

private:
    State m_before;
    BinaryFun m_fun;
    mutable boost::optional<State> m_after;

    State call_fun() const
    {
        return m_fun(m_before, read(this->base()));
    }

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        if (!m_after)
            m_after = call_fun();

        return *m_after;
    }

    void increment()
    {
        m_before = call_fun();
        ++this->base_reference();
        m_after.reset();
    }
};


} } } // namespace pstade::oven::detail


#endif
