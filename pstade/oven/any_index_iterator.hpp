#ifndef PSTADE_OVEN_ANY_INDEX_ITERATOR_HPP
#define PSTADE_OVEN_ANY_INDEX_ITERATOR_HPP
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
#include <boost/mpl/if.hpp>
#include <boost/noncopyable.hpp>
#include <boost/none.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/static_warning.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/egg/do_swap.hpp>
#include <pstade/egg/static_downcast.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/is_convertible.hpp>
#include <pstade/is_returnable.hpp>
#include <pstade/make_bool.hpp>
#include <pstade/remove_cvr.hpp>
#include <pstade/use_default.hpp>
#include "./any_iterator_fwd.hpp"
#include "./detail/check_nonnegative.hpp"


namespace pstade { namespace oven {


namespace any_index_iterator_detail {


    template< class Reference, class Difference >
    struct placeholder :
        private boost::noncopyable
    {
        virtual ~placeholder() { }
        virtual std::type_info const& typeid_() const = 0;

        virtual Reference at(Difference n) const = 0;
    };


    template< class Iterator, class Reference, class Difference >
    struct holder :
        placeholder<Reference, Difference>
    {
    private:
        typedef holder self_t;
        typedef placeholder<Reference, Difference> placeholder_t;

    public:
        explicit holder(Iterator held) :
            m_held(held)
        {
            // These are in function-scope for typeid. 
            BOOST_MPL_ASSERT((is_convertible<typename boost::iterator_reference<Iterator>::type, Reference>));
            BOOST_MPL_ASSERT((is_convertible<typename boost::iterator_difference<Iterator>::type, Difference>));
            BOOST_STATIC_WARNING((is_returnable<typename boost::iterator_reference<Iterator>::type, Reference>::value));
        }

        Iterator held() const
        {
            return m_held;
        }

        std::type_info const& typeid_() const // override
        {
            return typeid(Iterator);
        }

        Reference at(Difference n) const // override
        {
            return *(m_held + n);
        }

    private:
        Iterator m_held;
    };


    template< class Reference, class Value, class Difference >
    struct super_
    {
        typedef typename
            eval_if_use_default< Value, remove_cvr<Reference> >::type
        val_t;

        typedef typename
            if_use_default<Difference, std::ptrdiff_t>::type
        index_t;

        typedef
            boost::iterator_adaptor<
                any_index_iterator<Reference, Value, Difference>,
                index_t, // Base
                val_t,
                boost::random_access_traversal_tag,
                Reference,
                index_t
            >
        type;
    };


} // namespace any_index_iterator_detail


template< class Iterator, class AnyIndexIterator >
struct is_convertible_to_any_index_iterator :
    boost::mpl::and_<
        is_convertible<
            typename boost::iterator_reference<Iterator>::type,
            typename AnyIndexIterator::reference
        >,
        is_convertible<
            typename boost::iterator_traversal<Iterator>::type,
            boost::random_access_traversal_tag
        >,
        is_convertible<
            typename boost::iterator_difference<Iterator>::type,
            typename AnyIndexIterator::difference_type
        >
    >
{ };


template< class Reference, class Value, class Difference >
struct any_index_iterator :
    any_index_iterator_detail::super_<Reference, Value, Difference>::type
{
private:
    typedef any_index_iterator self_t;
    typedef typename any_index_iterator_detail::super_<Reference, Value, Difference>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef typename super_t::difference_type diff_t;
    typedef boost::shared_ptr< any_index_iterator_detail::placeholder<ref_t, diff_t> > content_t;

    template< class Iterator >
    struct holder_of
    {
        typedef any_index_iterator_detail::holder<Iterator, ref_t, diff_t> type;
    };

public:
    typedef typename super_t::base_type index_type;

    index_type index() const
    {
        return this->base();
    }

// structors
    any_index_iterator(boost::none_t = boost::none)
    { }

    template< class Iterator >
    explicit any_index_iterator(index_type index, Iterator it) :
        super_t(detail::check_nonnegative(index)),
        m_content(new typename holder_of<Iterator>::type(it))
    { }

    template< class R, class V, class D >
    any_index_iterator(any_index_iterator<R, V, D> const& other,
        typename enable_if< is_convertible_to_any_index_iterator<any_index_iterator<R, V, D>, self_t> >::type = 0
    ) :
        super_t(other.base()),
        m_content(new typename holder_of< any_index_iterator<R, V, D> >::type(other))
    { }

// assignments
    template< class Iterator >
    void reset(index_type index, Iterator it)
    {
        BOOST_ASSERT(0 <= index);
        self_t(index, it).swap(*this);
    }

    void reset(boost::none_t = boost::none)
    {
        self_t().swap(*this);
    }

    void reset(self_t const &other)
    {
        m_content.reset(other.index(), new typename holder_of<self_t>::type(other));
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

// content access
    template< class Iterator >
    bool contains() const
    {
        return make_bool(type() == typeid(Iterator));
    }

    template< class Iterator >
    Iterator content() const
    {
        BOOST_ASSERT(contains<Iterator>());
        return egg::static_downcast<typename holder_of<Iterator>::type>(*m_content).held();
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
void swap(any_index_iterator<R, V, D>& x, any_index_iterator<R, V, D>& y)
{
    x.swap(y);
}


} } // namespace pstade::oven


#endif
