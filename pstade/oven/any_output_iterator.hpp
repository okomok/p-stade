#ifndef PSTADE_OVEN_ANY_OUTPUT_ITERATOR_HPP
#define PSTADE_OVEN_ANY_OUTPUT_ITERATOR_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iterator>
#include <typeinfo>
#include <boost/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <pstade/egg/do_swap.hpp>
#include <pstade/egg/static_downcast.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/make_bool.hpp>
#include <pstade/remove_cvr.hpp>
#include <pstade/reset_assignment.hpp>
#include "./any_iterator_fwd.hpp"
#include "./write.hpp"


namespace pstade { namespace oven {


namespace any_output_iterator_detail {


    template< class What >
    struct placeholder :
        private boost::noncopyable
    {
        virtual ~placeholder() { }
        virtual std::type_info const& typeid_() const = 0;

        virtual void write_(What w) = 0;
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

        void write_(What w)
        {
            write(m_held, w);
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
    struct output_proxy
    {
    private:
        typedef typename content_of<What>::type content_t;

    public:
        explicit output_proxy(content_t const& c) :
            m_content(c)
        { }

        output_proxy& operator=(What w)
        {
            m_content->write_(w);
            return *this;
        }
    private:
        content_t m_content;
    };


    // See writable_postfix_increment_proxy in Boost.Iterator.
    template< class What >
    struct postfix_increment_proxy
    {
    private:
        typedef postfix_increment_proxy self_t;
        typedef any_output_iterator<What> iter_t;
        typedef typename content_of<What>::type content_t;

    public:
        postfix_increment_proxy(iter_t& it, content_t& c, bool& written) :
            m_it(it), m_content(c), m_written(written)
        { }

        self_t& operator *()
        {
            return *this;
        }

        // Provides writability of *r++
        What operator=(What w)
        {
            m_content->write_(w);
            m_content->increment();
            m_written = true;
            return w;
        }

        // Provides X(r++)
        operator iter_t const&() const
        {
            return m_it;
        }

        // Provides r++
        ~postfix_increment_proxy()
        {
            if (!m_written)
                m_content->increment();
        }

    private:
        iter_t& m_it;
        content_t& m_content;
        bool& m_written;
    };

    template<class X>
    struct is_postfix_increment_proxy :
        boost::mpl::false_
    { };

    template<class What>
    struct is_postfix_increment_proxy< postfix_increment_proxy<What> > :
        boost::mpl::true_
    { };


} // namespace any_output_iterator_detail


template< class What >
struct any_output_iterator :
    std::iterator<std::output_iterator_tag, void, void, void, void>
{
private:
    typedef any_output_iterator self_t;
    typedef any_output_iterator_detail::output_proxy<What> output_proxy_t;
    typedef any_output_iterator_detail::postfix_increment_proxy<What> postfix_increment_proxy_t;
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
    explicit any_output_iterator(Iterator it,
        typename disable_if< any_output_iterator_detail::is_postfix_increment_proxy<Iterator> >::type = 0
    ) :
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

// iterator implementation
    output_proxy_t operator *() const
    {
        BOOST_ASSERT(m_content);
        return output_proxy_t(m_content);
    }

    self_t& operator++()
    {
        BOOST_ASSERT(m_content);
        m_content->increment();
        return *this;
    }

#if 0
    // OutputIterator has SinglePass semantics,
    // but it++ is a MultiPass algorithm. Doh!
    self_t  operator++(int)
    {
        BOOST_ASSERT(m_content);
        self_t tmp(*this);
        ++*this;
        return tmp; // This is no longer a valid iterator.
    }
#endif

    postfix_increment_proxy_t operator++(int)
    {
        BOOST_ASSERT(m_content);
        m_postfix_written = false;
        return postfix_increment_proxy_t(*this, m_content, m_postfix_written);
    }

private:
    content_t m_content;
    bool m_postfix_written;
};


template< class What > inline
void swap(any_output_iterator<What>& x, any_output_iterator<What>& y)
{
    x.swap(y);
}


} } // namespace pstade::oven


#endif
