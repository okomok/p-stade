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
#include <boost/noncopyable.hpp>
#include <boost/none.hpp>
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

        virtual void write_increment(What w) = 0;
    };


    template< class OutIter, class What >
    struct holder :
        placeholder<What>
    {
        explicit holder(OutIter held) :
            m_held(held)
        { }

        OutIter held() const
        {
            return m_held;
        }

    // override
        std::type_info const& typeid_() const
        {
            return typeid(OutIter);
        }

        void write_increment(What w)
        {
            *m_held++ = w;
        }

    private:
        OutIter m_held;
    };


} // namespace any_output_iterator_detail


template< class What >
struct any_output_iterator :
    std::iterator<std::output_iterator_tag, void, void, void, void>
{
private:
    typedef any_output_iterator self_t;
    typedef boost::shared_ptr< any_output_iterator_detail::placeholder<What> > content_t;

    template< class OutIter >
    struct holder_of
    {
        typedef any_output_iterator_detail::holder<OutIter, What> type;
    };

public:
// structors
    any_output_iterator(boost::none_t = boost::none)
    { }

    template< class OutIter >
    explicit any_output_iterator(OutIter it) :
        m_content(new typename holder_of<OutIter>::type(it))
    { }

// assignments
    template< class OutIter >
    void reset(OutIter it)
    {
        self_t(it).swap(*this);
    }

    void reset(boost::none_t = boost::none)
    {
        self_t().swap(*this);
    }

    void reset(self_t const& other)
    {
        m_content.reset(new typename holder_of<self_t>::type(other));
    }

    PSTADE_RESET_ASSIGNMENT(any_output_iterator)

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

// content access
    template< class OutIter >
    bool contains() const
    {
        return make_bool(type() == typeid(OutIter));
    }

    template< class OutIter >
    OutIter content() const
    {
        BOOST_ASSERT(contains<OutIter>());
        return egg::static_downcast<typename holder_of<OutIter>::type>(*m_content).held();
    }

private:
    content_t m_content;

// iterator implementation
    struct output_proxy
    {
        content_t const& m_content;

        void operator=(What w)
        {
            m_content->write_increment(w);
        }
    };

public:
    output_proxy operator *() const
    {
        BOOST_ASSERT(m_content);
        output_proxy r = {m_content};
        return r;
    }

    self_t& operator++() { return *this; }
    self_t& operator++(int) { return *this; }
};


template< class What > inline
void swap(any_output_iterator<What>& x, any_output_iterator<What>& y)
{
    x.swap(y);
}


} } // namespace pstade::oven


#endif
