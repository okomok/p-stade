#ifndef PSTADE_OVEN_ANY_OUTPUT_ITERATOR_HPP
#define PSTADE_OVEN_ANY_OUTPUT_ITERATOR_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <typeinfo>
#include <boost/assert.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <pstade/egg/do_swap.hpp>
#include <pstade/egg/static_downcast.hpp>
#include <pstade/make_bool.hpp>
#include <pstade/reset_assignment.hpp>
#include "./any_iterator_fwd.hpp"


namespace pstade { namespace oven {


namespace any_output_iterator_detail {


    template< class What >
    struct placeholder :
        private boost::noncopyable
    {
        virtual ~placeholder() { }
        virtual std::type_info const& typeid_() const = 0;

        virtual void write(What w) = 0;
        virtual void increment() = 0;
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

    // override
        std::type_info const& typeid_() const
        {
            return typeid(Iterator);
        }

        void write(What w)
        {
            *m_held = w;
        }

        void increment()
        {
            ++m_held;
        }

    private:
        Iterator m_held;
    };


    template< class What >
    struct content_of
    {
        typedef boost::shared_ptr< placeholder<What> > type;
    };


    template< class What >
    struct proxy
    {
    private:
        typedef typename content_of<What>::type content_t;

    public:
        explicit proxy(content_t const& c) :
            m_content(c)
        { }

        proxy& operator=(What w)
        {
            m_content->write(w);
            return *this;
        }

    private:
        content_t m_content;
    };


    template< class What >
    struct super_
    {
        typedef
            boost::iterator_facade<
                any_output_iterator<What>,
                proxy<What>,
                boost::incrementable_traversal_tag,
                proxy<What>
            >
        type;
    };


} // namespace any_output_iterator_detail


template< class What >
struct any_output_iterator :
    any_output_iterator_detail::super_<What>::type
{
private:
    typedef any_output_iterator self_t;
    typedef typename any_output_iterator_detail::super_<What>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef typename any_output_iterator_detail::content_of<What>::type content_t;

    template< class Iterator >
    struct holder_of
    {
        typedef any_output_iterator_detail::holder<Iterator, What> type;
    };

public:
// structors
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
        self_t(it).swap(*this);
    }

    void reset()
    {
        self_t().swap(*this);
    }

    void reset(self_t const& other)
    {
        m_content.reset(new typename holder_of<self_t>::type(other));
    }

    PSTADE_RESET_ASSIGNMENT(self_t)

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
        BOOST_ASSERT(has_base<Iterator>());
        return egg::static_downcast<typename holder_of<Iterator>::type>(*m_content).held();
    }

private:
    content_t m_content;

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        BOOST_ASSERT(m_content);
        return ref_t(m_content);
    }

    void increment()
    {
        BOOST_ASSERT(m_content);
        m_content->increment();
    }
};


template< class What > inline
void swap(any_output_iterator<What>& x, any_output_iterator<What>& y)
{
    x.swap(y);
}


} } // namespace pstade::oven


#endif
