#ifndef PSTADE_OVEN_ANY_INDEXED_ITERATOR_HPP
#define PSTADE_OVEN_ANY_INDEXED_ITERATOR_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // ptrdiff_t
#include <typeinfo>
#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/noncopyable.hpp>
#include <boost/none.hpp>
#include <boost/shared_ptr.hpp>
#include <pstade/egg/do_swap.hpp>
#include <pstade/egg/static_downcast.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/is_convertible.hpp>
#include <pstade/remove_cvr.hpp>
#include <pstade/type_equal_to.hpp>
#include <pstade/use_default.hpp>
#include "./any_fwd.hpp"
#include "./detail/check_nonnegative.hpp"


namespace pstade { namespace oven {


namespace any_indexed_iterator_detail {


    template< class Reference, class Difference >
    struct placeholder :
        private boost::noncopyable
    {
        virtual ~placeholder() { }
        virtual std::type_info const& typeid_() const = 0;

        virtual Reference at(Difference n) const = 0;
    };


    template< class RandIter, class Reference, class Difference >
    struct holder :
        placeholder<Reference, Difference>
    {
    private:
        typedef holder self_t;
        typedef placeholder<Reference, Difference> placeholder_t;

    public:
        explicit holder(RandIter held) :
            m_held(held)
        {
            // These are in function-scope for typeid. 
            BOOST_MPL_ASSERT((is_convertible<typename boost::iterator_reference<RandIter>::type, Reference>));
            BOOST_MPL_ASSERT((is_convertible<typename boost::iterator_difference<RandIter>::type, Difference>));
        }

        RandIter held() const
        {
            return m_held;
        }

        std::type_info const& typeid_() const // override
        {
            return typeid(RandIter);
        }

        Reference at(Difference n) const // override
        {
            return *(m_held + n);
        }

    private:
        RandIter m_held;
    };


    template< class Reference, class Value, class Difference >
    struct super_
    {
        typedef typename
            if_use_default<Difference, std::ptrdiff_t>::type
        base_t;

        typedef typename
            eval_if_use_default< Value, remove_cvr<Reference> >::type
        val_t;

        typedef
            boost::iterator_adaptor<
                any_indexed_iterator<Reference, Value, Difference>,
                base_t,
                val_t,
                boost::random_access_traversal_tag,
                Reference,
                base_t
            >
        type;
    };


} // namespace any_indexed_iterator_detail


template< class Iterator, class AnyIndexedIterator >
struct is_convertible_to_any_indexed_iterator :
    boost::mpl::and_<
        is_convertible<
            typename boost::iterator_reference<Iterator>::type,
            typename AnyIndexedIterator::reference
        >,
        is_convertible<
            typename boost::iterator_traversal<Iterator>::type,
            boost::random_access_traversal_tag
        >,
        is_convertible<
            typename boost::iterator_difference<Iterator>::type,
            typename AnyIndexedIterator::difference_type
        >
    >
{ };


template< class Reference, class Value, class Difference >
struct any_indexed_iterator :
    any_indexed_iterator_detail::super_<Reference, Value, Difference>::type
{
private:
    typedef any_indexed_iterator self_t;
    typedef typename any_indexed_iterator_detail::super_<Reference, Value, Difference>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef typename super_t::difference_type diff_t;
    typedef boost::shared_ptr< any_indexed_iterator_detail::placeholder<ref_t, diff_t> > content_t;

    template< class RandIter >
    struct holder_of
    {
        typedef any_indexed_iterator_detail::holder<RandIter, ref_t, diff_t> type;
    };

public:
// structors
    any_indexed_iterator(boost::none_t = boost::none)
    { }

    template< class RandIter >
    any_indexed_iterator(diff_t index, RandIter it) :
        super_t(detail::check_nonnegative(index)),
        m_content(new typename holder_of<RandIter>::type(it))
    { }

    template< class R, class V, class D >
    any_indexed_iterator(any_indexed_iterator<R, V, D> const& other,
        typename enable_if< is_convertible_to_any_indexed_iterator<any_indexed_iterator<R, V, D>, self_t> >::type = 0
    ) :
        super_t(other.base()),
        m_content(new typename holder_of< any_indexed_iterator<R, V, D> >::type(other))
    { }

// assignments
    void reset(boost::none_t = boost::none)
    {
        self_t().swap(*this);
    }

    template< class RandIter >
    void reset(diff_t index, RandIter it)
    {
        BOOST_ASSERT(0 <= index);
        self_t(index, it).swap(*this);
    }

    self_t& operator=(boost::none_t)
    {
        reset();
        return *this;
    }

// swappable
    void swap(self_t& other)
    {
        egg::do_swap(this->base_reference(), other.base_reference());
        egg::do_swap(m_content, other.m_content);
    }

// boost::any compatibles
    bool empty() const
    {
        return !m_content;
    }

    std::type_info const& type() const
    {
        return m_content ? m_content->typeid_() : typeid(void);
    }

// index access
    typedef diff_t index_type;

    index_type index() const
    {
        return this->base();
    }

// content access
    template< class RandIter >
    bool contains() const
    {
        return type_equal_to(type(), typeid(RandIter));
    }

    template< class RandIter >
    RandIter content() const
    {
        BOOST_ASSERT(contains<RandIter>());
        return egg::static_downcast<typename holder_of<RandIter>::type>(*m_content).held();
    }

private:
    content_t m_content;

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        BOOST_ASSERT(0 <= this->base());
        return m_content->at(this->base());
    }
};


template< class R, class V, class D > inline
void swap(any_indexed_iterator<R, V, D>& x, any_indexed_iterator<R, V, D>& y)
{
    x.swap(y);
}


} } // namespace pstade::oven


#endif
