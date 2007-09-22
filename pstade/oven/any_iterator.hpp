#ifndef PSTADE_OVEN_ANY_ITERATOR_HPP
#define PSTADE_OVEN_ANY_ITERATOR_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// References:
//
// [1] Thomas Becker, Type Erasure for C++ Iterators, 2007.
//     http://thbecker.net/free_software_utilities/type_erasure_for_cpp_iterators/start_page.html


#include <cstddef> // ptrdiff_t
#include <typeinfo>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/if.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/static_warning.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/clone_ptr.hpp>
#include <pstade/egg/static_downcast.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/is_convertible.hpp>
#include <pstade/is_returnable.hpp>
#include <pstade/make_bool.hpp>
#include <pstade/remove_cvr.hpp>
#include <pstade/reset_assignment.hpp>
#include <pstade/use_default.hpp>
#include "./any_iterator_fwd.hpp"
#include "./detail/pure_traversal.hpp"


namespace pstade { namespace oven {


namespace any_iterator_detail {


    template< class Reference, class Traversal, class Difference, class T = Traversal >
    struct placeholder :
        private boost::noncopyable
    {
        // In fact, 'shared_ptr' needs no virtual destructor,
        // but there is no way to suppress GCC warning.
        virtual ~placeholder() { }

        // BTW, msvc-7.1/8.0 RTTI seems randomly broken.
        virtual std::type_info const& typeid_() const = 0;

        virtual Reference dereference() const = 0;
        virtual void increment() = 0;
    };

    template< class Reference, class Difference, class T >
    struct placeholder<Reference, boost::single_pass_traversal_tag, Difference, T> :
        placeholder<Reference, boost::incrementable_traversal_tag, Difference, T>
    {
        typedef placeholder<Reference, T, Difference> most_derived_t; // Dr.Becker's way!
        virtual bool equal(most_derived_t const& other) const = 0;
    };

    template< class Reference, class Difference, class T >
    struct placeholder<Reference, boost::forward_traversal_tag, Difference, T> :
        placeholder<Reference, boost::single_pass_traversal_tag, Difference, T>
    {
        typedef placeholder<Reference, T, Difference> most_derived_t;
        virtual most_derived_t *clone() const = 0;
    };

    template< class Reference, class Difference, class T >
    struct placeholder<Reference, boost::bidirectional_traversal_tag, Difference, T> :
        placeholder<Reference, boost::forward_traversal_tag, Difference, T>
    {
        virtual void decrement() = 0;
    };

    template< class Reference, class Difference, class T >
    struct placeholder<Reference, boost::random_access_traversal_tag, Difference, T> :
        placeholder<Reference, boost::bidirectional_traversal_tag, Difference, T>
    {
        virtual void advance(Difference n) = 0;
        virtual Difference difference_to(placeholder const& other) const = 0;
    };


    // customizes Clonable for 'clone_ptr'.
    template< class Reference, class Traversal, class Difference > inline
    placeholder<Reference, Traversal, Difference> *
    new_clone(placeholder<Reference, Traversal, Difference> const& ph)
    {
        return ph.clone();
    }


    template< class From, class To, class Traversal >
    struct is_convertible_difference :
        boost::mpl::eval_if< boost::is_same<Traversal, boost::random_access_traversal_tag>,
            is_convertible<From, To>,
            boost::mpl::true_
        >
    { };


    template< class Iterator, class Reference, class Traversal, class Difference >
    struct holder :
        placeholder<Reference, Traversal, Difference>
    {
    private:
        typedef holder self_t;
        typedef placeholder<Reference, Traversal, Difference> placeholder_t;

    public:
        explicit holder(Iterator held) :
            m_held(held)
        {
            // These are in function-scope for typeid. 
            BOOST_MPL_ASSERT((is_convertible<typename boost::iterator_reference<Iterator>::type, Reference>));
            BOOST_MPL_ASSERT((is_convertible<typename boost::iterator_traversal<Iterator>::type, Traversal>));
            BOOST_MPL_ASSERT((is_convertible_difference<typename boost::iterator_difference<Iterator>::type, Difference, Traversal>));
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

    private:
        Iterator m_held;

    // These may be 'virtual', depending on the base 'placeholder'.

        placeholder_t *clone() const
        {
            return new self_t(m_held);
        }

    public:
        Reference dereference() const
        {
            return *m_held;
        }

        bool equal(placeholder_t const& other) const
        {
            return m_held == egg::static_downcast<self_t>(other).m_held;
        }

        void increment()
        {
            ++m_held;
        }

        void decrement()
        {
            --m_held;
        }

        void advance(Difference n)
        {
            m_held += n;
        }

        Difference difference_to(placeholder_t const& other) const
        {
            return egg::static_downcast<self_t>(other).m_held - m_held;
        }
    };


    template< class Reference, class Traversal, class Value, class Difference >
    struct super_
    {
        typedef
            boost::iterator_facade<
                any_iterator<Reference, Traversal, Value, Difference>,
                typename eval_if_use_default< Value, remove_cvr<Reference> >::type,
                Traversal,
                Reference,
                typename if_use_default<Difference, std::ptrdiff_t>::type
            >
        type;
    };


    template< class Reference, class Traversal, class Difference >
    struct content_of
    {
        typedef
            placeholder<Reference, Traversal, Difference>
        placeholder_t;

        // A recursive range must be Forward.
        // Hence there is no reference-cycles by 'shared_ptr'.
        typedef typename
            boost::mpl::if_< is_convertible<Traversal, boost::forward_traversal_tag>,
                clone_ptr<placeholder_t>,
                boost::shared_ptr<placeholder_t>
            >::type
        type;
    };


    template< class Category >
    struct category_to_pure_traversal :
        boost::detail::pure_traversal_tag<
            typename boost::iterator_category_to_traversal<Category>::type
        >
    { };


} // namespace any_iterator_detail


template< class Iterator, class AnyIterator >
struct is_convertible_to_any_iterator :
    boost::mpl::and_<
        is_convertible<
            typename boost::iterator_reference<Iterator>::type,
            typename AnyIterator::reference
        >,
        is_convertible<
            typename boost::iterator_traversal<Iterator>::type,
            typename detail::pure_traversal<AnyIterator>::type
        >,
        any_iterator_detail::is_convertible_difference<
            typename boost::iterator_difference<Iterator>::type,
            typename AnyIterator::difference_type, typename detail::pure_traversal<AnyIterator>::type
        >
    >
{ };


template< class Reference, class Traversal, class Value, class Difference >
struct any_iterator :
    any_iterator_detail::super_<Reference, Traversal, Value, Difference>::type
{
private:
    typedef any_iterator self_t;
    typedef typename any_iterator_detail::super_<Reference, Traversal, Value, Difference>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef typename any_iterator_detail::category_to_pure_traversal<typename super_t::iterator_category>::type trv_t;
    typedef typename super_t::difference_type diff_t;
    typedef typename any_iterator_detail::content_of<ref_t, trv_t, diff_t>::type content_t;

    template< class Iterator >
    struct holder_of
    {
        typedef any_iterator_detail::holder<Iterator, ref_t, trv_t, diff_t> type;
    };

public:
// structors
    any_iterator()
    { }

    // This constructor can't be implicit.
    // Use 'is_convertible_to_any_iterator' instead.
    // "UglyIssue.txt" of References[1] tells in detail.
    template< class Iterator >
    explicit any_iterator(Iterator it) :
        m_content(new typename holder_of<Iterator>::type(it))
    { }

    template< class R, class T, class V, class D >
    any_iterator(any_iterator<R, T, V, D> const& other,
        typename enable_if< is_convertible_to_any_iterator<any_iterator<R, T, V, D>, self_t> >::type = 0
    ) :
        m_content(new typename holder_of< any_iterator<R, T, V, D> >::type(other))
    { }

// assignments
    template< class Iterator >
    void reset(Iterator it)
    {
        self_t(it).swap(*this);
    }

    void reset()
    {
        self_t().swap(*this);
    }

    PSTADE_RESET_ASSIGNMENT(self_t)

    void reset(self_t const &other)
    {
        m_content.reset(new typename holder_of<self_t>::type(other));
    }

// swappable
    void swap(self_t& other)
    {
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

// base access
    template< class Iterator >
    bool has_base() const
    {
        return make_bool(type() == typeid(Iterator));
    }

    template< class Iterator >
    Iterator base() const
    {
        return egg::static_downcast<typename holder_of<Iterator>::type>(*m_content).held();
    }

private:
    content_t m_content;

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        return m_content->dereference();
    }

    // can't be a template; 'placeholder' type is different.
    bool equal(self_t const& other) const
    {
        return m_content->equal(*other.m_content);
    }

    void increment()
    {
        m_content->increment();
    }

    void decrement()
    {
        m_content->decrement();
    }

    void advance(diff_t n)
    {
        m_content->advance(n);
    }

    diff_t distance_to(self_t const& other) const
    {
        return m_content->difference_to(*other.m_content);
    }
};


template< class R, class T, class V, class D > inline
void swap(any_iterator<R, T, V, D>& x, any_iterator<R, T, V, D>& y)
{
    x.swap(y);
}


} } // namespace pstade::oven


#endif
