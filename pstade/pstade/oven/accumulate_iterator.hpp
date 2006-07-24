#ifndef PSTADE_OVEN_ACCUMULATE_ITERATOR_HPP
#define PSTADE_OVEN_ACCUMULATE_ITERATOR_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp> // forward_traversal_tag
#include <boost/iterator/iterator_traits.hpp> // iterator_value
#include <boost/tuple/tuple.hpp>
#include "./detail/an_iterator.hpp"
#include "./detail/minimum_traversal.hpp"


namespace pstade { namespace oven {


template< class Iterator, class BinaryFun >
struct accumulate_iterator;


namespace accumulate_iterator_detail {


    template< class Iterator >
    struct traversal
    {
        typedef boost::tuples::tuple<
            Iterator,
            detail::an_iterator<boost::forward_traversal_tag>
        > iters_t;

        typedef typename detail::
            minimum_traversal<iters_t>::type
        type;
    };


    template< class Iterator, class BinaryFun >
    struct super_
    {
        typedef typename boost::iterator_value<Iterator>::type value_t;

        typedef boost::iterator_adaptor<
            accumulate_iterator<Iterator, BinaryFun>,
            Iterator,
            value_t,
            typename traversal<Iterator>::type,
            value_t const
        > type;
    };


} // namespace accumulate_iterator_detail


template< class Iterator, class BinaryFun >
struct accumulate_iterator :
    accumulate_iterator_detail::super_<Iterator, BinaryFun>::type
{
private:
    typedef typename accumulate_iterator_detail::super_<Iterator, BinaryFun>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef typename super_t::value_type value_t;

public:
    accumulate_iterator()
    { }

    accumulate_iterator(Iterator const& it, value_t const& init, BinaryFun fun) :
        super_t(it), m_state(init), m_fun(fun)
    { }

    template< class Iterator_, class BinaryFun_ >
    accumulate_iterator(
        accumulate_iterator<Iterator_, BinaryFun_> const& other,
        typename boost::enable_if_convertible<Iterator_, Iterator>::type * = 0
    ) :
        super_t(other.base()), m_state(other.state()), m_fun(other.functor())
    { }

    value_t const& state() const
    {
        return m_state;
    }

    BinaryFun functor() const
    {
        return m_fun;
    }

private:
    value_t m_state;
    BinaryFun m_fun;

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        return m_fun(m_state, *this->base());
    }

    void increment()
    {
        m_state = dereference();
        ++this->base_reference();
    }
};


template< class Iterator, class BinaryFun, class Value > inline
accumulate_iterator<Iterator, BinaryFun> const
make_accumulate_iterator(Iterator const& it, Value const& init, BinaryFun fun)
{
    return accumulate_iterator<Iterator, BinaryFun>(it, init, fun);
}


} } // namespace pstade::oven


#endif
