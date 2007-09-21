#ifndef PSTADE_OVEN_ANY_INCREMENTABLE_HPP
#define PSTADE_OVEN_ANY_INCREMENTABLE_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// An iterator which is not SinglePass but Incrementable
// is not considered as "iterator" in the context of Range.
// any_incrementable can accept such "incomplete" iterators
// which any_iterator cannot.


#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/static_warning.hpp>
#include <pstade/egg/static_downcast.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/is_convertible.hpp>
#include <pstade/is_returnable.hpp>
#include <pstade/make_bool.hpp>
#include <pstade/remove_cvr.hpp>
#include <pstade/use_default.hpp>
#include "./any_incrementable_fwd.hpp"
#include "./applier.hpp"
#include "./detail/assign_new.hpp"


namespace pstade { namespace oven {


namespace any_incrementable_detail {


    template< class Reference >
    struct placeholder :
        private boost::noncopyable
    {
        virtual ~placeholder() { }

        virtual Reference dereference() const = 0;
        virtual void increment() = 0;
    };


    template< class Iterator, class Reference >
    struct holder :
        placeholder<Reference>
    {
        explicit holder(Iterator held) :
            m_held(held)
        {
            BOOST_MPL_ASSERT((is_convertible<typename boost::iterator_reference<Iterator>::type, Reference>));
            BOOST_STATIC_WARNING((is_returnable<typename boost::iterator_reference<Iterator>::type, Reference>::value));
        }

        Iterator held() const
        {
            return m_held;
        }

    private:
        Iterator m_held;

    public:
        Reference dereference() const
        {
            return *m_held;
        }

        void increment()
        {
            ++m_held;
        }
    };


    template< class Reference, class Value >
    struct super_
    {
        typedef
            boost::iterator_facade<
                any_incrementable<Reference, Value>,
                typename eval_if_use_default< Value, remove_cvr<Reference> >::type,
                boost::incrementable_traversal_tag,
                Reference
            >
        type;
    };


    template< class Iterator, class AnyIncrementable >
    struct is_convertible_to :
        is_convertible<
            typename boost::iterator_reference<Iterator>::type,
            typename AnyIncrementable::reference
        >
    { };


} // namespace any_incrementable_detail



template< class Reference, class Value >
struct any_incrementable :
    any_incrementable_detail::readable_super_<Reference, Value>::type
{
private:
    typedef any_incrementable self_t;
    typedef typename any_incrementable_detail::super_<Reference, Value>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef boost::shared_ptr< any_incrementable_detail::placeholder<ref_t> > content_t;

    template< class Iterator >
    struct holder_of
    {
        typedef any_incrementable_detail::holder<Iterator, ref_t> type;
    };

public:
// structors
    any_incrementable()
    { }

    template< class Iterator >
    explicit any_incrementable(Iterator it) :
        m_content(new typename holder_of<Iterator>::type(it))
    { }

    template< class R, class V >
    any_incrementable(any_incrementable<R, V> const& other,
        typename enable_if< any_incrementable_detail::is_convertible_to<any_incrementable<R, V>, self_t> >::type = 0
    ) :
        m_content(new typename holder_of< any_incrementable<R, V> >::type(other))
    { }

    template< class Iterator >
    Iterator base() const
    {
        return egg::static_downcast<typename holder_of<Iterator>::type>(*m_content).held();
    }

    template< class Iterator >
    bool has_base() const
    {
        return make_bool( typeid(*m_content) == typeid(typename holder_of<Iterator>::type) );
    }

// assignment to work around 'explicit' above
    template< class Iterator >
    typename disable_if<is_convertible<Iterator, self_t>, self_t&>::type
    operator=(Iterator it)
    {
        detail::assign_new<typename holder_of<Iterator>::type>(it, m_content);
        return *this;
    }

private:
    content_t m_content;

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        return m_content->dereference();
    }

    void increment()
    {
        m_content->increment();
    }
};


namespace any_incrementable_void_detail {


    template< class Reference >
    struct placeholder :
        private boost::noncopyable
    {
        virtual ~placeholder() { }

        virtual void deref_write() const = 0;
    };






} // namespace any_incrementable_void_detail


template< >
struct any_incrementable<void>
{
    typedef UnaryFun function_type;

    template< class Iterator >
    explicit function_output_iterator(Iterator it) :
        m_fun(fun)
    { }

    UnaryFun function() const
    {
        return m_fun;
    }

    // as "adaptor"; 'adapted_to' kicks in!
    UnaryFun base() const
    {
        return m_fun;
    }

private:
    mutable UnaryFun m_fun;

public:
    typedef std::output_iterator_tag iterator_category;
    typedef boost::mpl::void_ value_type; // for 'postfix_increment_result'
    typedef boost::mpl::void_ pointer;    // for a rainy day
    typedef int difference_type;          // for 'iterator_facade::operator[]'

    struct reference                      // for adaptors
    {
        explicit reference(UnaryFun& fun) :
            m_fun(fun)
        { }

        // can replace 'for_each'?
        template< class Value >
        reference& operator=(Value& val)
        {
            m_content->deref_write(val);
            return *this;
        }

        template< class Value >
        reference& operator=(Value const& val)
        {
            m_content->deref_write(val);
            return *this;
        }

    private:
        content_t m_content;
    };

    reference operator *() const { return reference(m_fun); } // 'const' for adaptors.
    function_output_iterator& operator++() { return *this; }
    function_output_iterator& operator++(int) { return *this; } // must return reference.
};


} } // namespace pstade::oven


#endif
