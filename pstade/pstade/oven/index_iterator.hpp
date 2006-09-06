#ifndef PSTADE_OVEN_INDEX_ITERATOR_HPP
#define PSTADE_OVEN_INDEX_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // ptrdiff_t, size_t
#include <boost/iterator/iterator_categories.hpp> // random_access_traversal_tag
#include <boost/iterator/iterator_facade.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/remove_cvr.hpp>


namespace pstade { namespace oven {


template<
    class UnaryFun,  class Index,
    class Reference, class Value, class Difference
>
struct index_iterator;


namespace index_iterator_detail {


    template< class UnaryFun, class Index >
    struct default_reference :
        boost::result_of<UnaryFun(Index)>
    { };


    template<
        class UnaryFun,  class Index,
        class Reference, class Value, class Difference
    >
    struct super_
    {
        typedef typename boost::mpl::eval_if<
            boost::is_same<Reference, boost::use_default>,
            default_reference<UnaryFun, Index>,
            boost::mpl::identity<Reference>
        >::type ref_t;

        typedef typename boost::mpl::eval_if<
            boost::is_same<Value, boost::use_default>,
            remove_cvr<ref_t>,
            boost::mpl::identity<Value>
        >::type val_t;

        typedef boost::iterator_facade<
            index_iterator<UnaryFun, Index, Reference, Value, Difference>,
            val_t,
            boost::random_access_traversal_tag,
            ref_t,
            Difference
        > type;
    };


} // namespace index_iterator_detail


template<
    class UnaryFun,
    class Index      = std::size_t,
    class Reference  = boost::use_default,
    class Value      = boost::use_default,
    class Difference = std::ptrdiff_t
>
struct index_iterator :
    index_iterator_detail::super_<UnaryFun, Index, Reference, Value, Difference>::type
{
private:
    typedef index_iterator self_t;
    typedef typename index_iterator_detail::super_<UnaryFun, Index, Reference, Value, Difference>::type super_t;
    typedef typename super_t::difference_type diff_t;
    typedef typename super_t::reference ref_t;

public:
    index_iterator()
    { }

    index_iterator(UnaryFun fun, Index i) :
        m_fun(fun), m_i(i)
    { }

    UnaryFun functor() const
    {
        return m_fun;
    }

    Index index() const
    {
        return m_i;
    }

private:
    UnaryFun m_fun;
    Index m_i;

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        return m_fun(m_i);
    }

    bool equal(self_t const& other) const
    {
        return m_i == other.m_i;
    }

    void increment()
    {
        ++m_i;
    }

    void decrement()
    {
        --m_i;
    }

    void advance(diff_t d)
    {
        m_i += d;
    }

    diff_t distance_to(self_t const& other) const
    {
        return diff_t(other.m_i) - diff_t(m_i);
    }
};


template< class Index, class UnaryFun > inline
index_iterator<UnaryFun, Index> const
make_index_iterator(UnaryFun fun, Index i)
{
    return index_iterator<UnaryFun, Index>(fun, i);
}


} } // namespace pstade::oven


#endif
