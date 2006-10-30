#ifndef PSTADE_OVEN_ADJACENT_TRANSFORM_ITERATOR_HPP
#define PSTADE_OVEN_ADJACENT_TRANSFORM_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iterator> // distance
#include <boost/assert.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/iterator/detail/minimum_category.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_traits.hpp> // iterator_reference/traversal
#include <boost/next_prior.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/unused.hpp>


namespace pstade { namespace oven {


template<
    class ForwardIter,
    class BinaryFun,
    class Reference,
    class Value
>
struct adjacent_transform_iterator;


namespace adjacent_transform_iterator_detail {


    template< class ForwardIter >
    struct traversal :
        boost::detail::minimum_category<
            typename boost::iterator_traversal<ForwardIter>::type,
            boost::bidirectional_traversal_tag
        >
    { };


    template< class ForwardIter, class BinaryFun >
    struct reference
    {
        typedef typename boost::iterator_reference<ForwardIter>::type ref_t;
        typedef typename boost::result_of<BinaryFun(ref_t, ref_t)>::type type;
    };


    template< class ForwardIter, class BinaryFun, class Reference, class Value >
    struct super_
    {
        typedef typename
            boost::mpl::eval_if< boost::is_same<Reference, boost::use_default>,
                reference<ForwardIter, BinaryFun>,
                boost::mpl::identity<Reference>
            >::type
        ref_t;

        typedef typename
            boost::mpl::eval_if< boost::is_same<Value, boost::use_default>,
                remove_cvr<ref_t>,
                boost::mpl::identity<Value>
            >::type
        val_t;

        typedef boost::iterator_adaptor<
            adjacent_transform_iterator<ForwardIter, BinaryFun, Reference, Value>,
            ForwardIter,
            val_t,
            typename traversal<ForwardIter>::type,
            ref_t
        > type;
    };


} // namespace adjacent_transform_iterator_detail


template<
    class ForwardIter,
    class BinaryFun,
    class Reference = boost::use_default,
    class Value     = boost::use_default
>
struct adjacent_transform_iterator :
    adjacent_transform_iterator_detail::super_<ForwardIter, BinaryFun, Reference, Value>::type
{
private:
    typedef typename adjacent_transform_iterator_detail::super_<ForwardIter, BinaryFun, Reference, Value>::type super_t;
    typedef typename super_t::reference ref_t;

public:
    adjacent_transform_iterator()
    { }

    adjacent_transform_iterator(ForwardIter const& it, ForwardIter const& next, BinaryFun const& fun) :
        super_t(it), m_next(next), m_fun(fun)
    { }

    template< class ForwardIter_, class Reference_, class Value_ >
    adjacent_transform_iterator(
        adjacent_transform_iterator<ForwardIter_, BinaryFun, Reference_, Value_> const& other,
        typename boost::enable_if_convertible<ForwardIter_, ForwardIter>::type * = 0
    ) :
        super_t(other.base()), m_next(other.next()), m_fun(other.function())
    { }

    ForwardIter const& next() const
    {
        return m_next;
    }

    BinaryFun const& function() const
    {
        return m_fun;
    }

private:
    ForwardIter m_next;
    BinaryFun   m_fun;

    bool is_dot() const
    {
        return this->base() == m_next;
    }

    bool line_invariant() const
    {
        return !is_dot() &&
            boost::next(this->base()) == m_next;
    }

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        BOOST_ASSERT(line_invariant());
        return m_fun(*this->base(), *m_next);
    }

    template< class Other >
    bool equal(Other const& other) const
    {
        BOOST_ASSERT(!is_dot() ? line_invariant() : true);
        return this->base() == other.base();
    }

    void increment()
    {
        BOOST_ASSERT(line_invariant());
        ++this->base_reference();
        ++m_next;
    }

    void decrement()
    {
        BOOST_ASSERT(line_invariant());
        --this->base_reference();
        --m_next;
    }
};


namespace adjacent_transform_iterator_detail {


    template< class ForwardIter > inline
    ForwardIter back(ForwardIter first, ForwardIter const& last, boost::bidirectional_traversal_tag)
    {
        pstade::unused(first);
        return boost::prior(last);
    }

    template< class ForwardIter > inline
    ForwardIter back(ForwardIter first, ForwardIter const& last, boost::forward_traversal_tag)
    {
        ForwardIter prev(first);
        for (; ++first != last; prev = first)
            ;

        return prev;

    /*
        while (boost::next(first) != last)
            ++first;

        return first;
    */
    }


} // namespace adjacent_transform_iterator_detail



template< class Reference, class Value, class ForwardIter, class BinaryFun >
adjacent_transform_iterator<ForwardIter, BinaryFun, Reference, Value> const
make_adjacent_transform_begin_iterator(ForwardIter const& first, ForwardIter const& last, BinaryFun fun)
{
    typedef adjacent_transform_iterator<ForwardIter, BinaryFun, Reference, Value> result_t;

    if (std::distance(first, last) == 0)
        return result_t(first, first, fun); // dot

    return result_t(first, boost::next(first), fun);
}


template< class Reference, class Value, class ForwardIter, class BinaryFun >
adjacent_transform_iterator<ForwardIter, BinaryFun, Reference, Value> const
make_adjacent_transform_end_iterator(ForwardIter const& first, ForwardIter const& last, BinaryFun fun)
{
    typedef adjacent_transform_iterator<ForwardIter, BinaryFun, Reference, Value> result_t;

    if (std::distance(first, last) == 0)
        return result_t(first, first, fun); // dot

    typedef typename boost::iterator_traversal<ForwardIter>::type trv_t;
    return result_t(adjacent_transform_iterator_detail::back(first, last, trv_t()), last, fun);
}


} } // namespace pstade::oven


#endif
