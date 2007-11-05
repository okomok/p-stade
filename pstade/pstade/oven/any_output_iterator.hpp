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
#include <pstade/nonvirtual.hpp>
#include <pstade/reset_assignment.hpp>
#include <pstade/type_equal_to.hpp>
#include <pstade/type_erasure.hpp>
#include "./any_fwd.hpp"


namespace pstade { namespace oven {


namespace any_output_iterator_detail {


    template< class Reference >
    struct placeholder :
        private boost::noncopyable
    {
        virtual std::type_info const& typeid_() const = 0;
        virtual void write_increment(Reference x) = 0;

    protected:
        PSTADE_NONVIRTUAL ~placeholder() { }
    };


    template< class OutIter, class Reference >
    struct holder :
        placeholder<Reference>
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

        void write_increment(Reference x)
        {
            *m_held++ = x;
        }

    private:
        OutIter m_held;
    };


} // namespace any_output_iterator_detail


template< class Reference >
struct any_output_iterator :
    std::iterator<std::output_iterator_tag, void, void, void, void>
{
private:
    typedef any_output_iterator self_t;
    typedef boost::shared_ptr< any_output_iterator_detail::placeholder<Reference> > content_t;

    template< class OutIter >
    struct holder_of
    {
        typedef any_output_iterator_detail::holder<OutIter, Reference> type;
    };

public:
// structors
    any_output_iterator(boost::none_t = boost::none)
    { }

    template< class OutIter >
    explicit any_output_iterator(OutIter it) :
        m_content(new typename holder_of<OutIter>::type(it))
    { }

    any_output_iterator(T_type_erasure, self_t it) :
        m_content(new typename holder_of<self_t>::type(it))
    { }

// assignments
    void reset(boost::none_t = boost::none)
    {
        self_t().swap(*this);
    }

    template< class OutIter >
    void reset(OutIter it)
    {
        self_t(it).swap(*this);
    }

    void reset(self_t it)
    {
        self_t(type_erasure, it).swap(*this);
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
        return type_equal_to(type(), typeid(OutIter));
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

        void operator=(Reference x)
        {
            m_content->write_increment(x);
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


template< class Reference > inline
void swap(any_output_iterator<Reference>& x, any_output_iterator<Reference>& y)
{
    x.swap(y);
}


} } // namespace pstade::oven


#endif
