#ifndef PSTADE_OVEN_ANY_OUTPUT_ITERATOR_HPP
#define PSTADE_OVEN_ANY_OUTPUT_ITERATOR_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iterator> // output_iterator_tag
#include <typeinfo>
#include <boost/assert.hpp>
#include <boost/mpl/void.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <pstade/disable_if_copy.hpp>
#include <pstade/egg/do_swap.hpp>
#include <pstade/egg/static_downcast.hpp>
#include <pstade/make_bool.hpp>
#include <pstade/radish/swappable.hpp>
#include "./any_iterator_fwd.hpp"
#include "./detail/assign_new.hpp"


namespace pstade { namespace oven {


namespace any_output_iterator_detail {


    template< class What >
    struct placeholder :
        private boost::noncopyable
    {
        virtual ~placeholder() { }
        virtual std::type_info const& typeid_() const = 0;

        virtual void write(What w) = 0;
    };


    template< class Iterator, class What >
    struct holder :
        placeholder<What>
    {
        explicit holder(Iterator held) :
            m_held(held)
        { }

        Iterator held() const
        {
            return m_held;
        }

        std::type_info const& typeid_() const // override
        {
            return typeid(Iterator);
        }

        void write(What w) // override
        {
            *m_held = w;
        }

    private:
        Iterator m_held;
    };


} // namespace any_output_iterator_detail


template< class What >
struct any_output_iterator :
    radish::swappable< any_output_iterator<What> >
{
private:
    typedef any_output_iterator self_t;
    typedef boost::shared_ptr< any_output_iterator_detail::placeholder<What> > content_t;

    template< class Iterator >
    struct holder_of
    {
        typedef any_output_iterator_detail::holder<Iterator, What> type;
    };

public:
    any_output_iterator()
    { }

    template< class Iterator >
    explicit any_output_iterator(Iterator it) :
        m_content(new typename holder_of<Iterator>::type(it))
    { }

// assignments
    template< class Iterator >
    void reset(Iterator it)
    {
        m_content.reset(new typename holder_of<Iterator>::type(it));
    }

    void reset()
    {
        m_content.reset();
    }

    template< class Iterator >
    typename disable_if_copy_assign<self_t, Iterator>::type
    operator=(Iterator it)
    {
        reset(it);
        return *this;
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
        BOOST_ASSERT(has_base<Iterator>());
        return egg::static_downcast<typename holder_of<Iterator>::type>(*m_content).held();
    }

// swappable
    void swap(self_t& other)
    {
        egg::do_swap(m_content, other.m_content);
    }

private:
    content_t m_content;

public:
    typedef std::output_iterator_tag iterator_category;
    typedef boost::mpl::void_ value_type; // for 'postfix_increment_result'
    typedef boost::mpl::void_ pointer;    // for a rainy day
    typedef int difference_type;          // for 'iterator_facade::operator[]'

    struct reference                      // for adaptors
    {
        explicit reference(content_t const& content) :
            m_content(content)
        { }

        reference& operator=(What w)
        {
            m_content->write(w);
            return *this;
        }

    private:
        content_t m_content;
    };

    reference operator *() const { return reference(m_content); } // 'const' for adaptors.
    any_output_iterator& operator++() { return *this; }
    any_output_iterator& operator++(int) { return *this; } // must return reference.
};


// No make_any_iterator.


} } // namespace pstade::oven


#endif
