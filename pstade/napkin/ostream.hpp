#ifndef PSTADE_NAPKIN_OSTREAM_HPP
#define PSTADE_NAPKIN_OSTREAM_HPP


// PStade.Napkin
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/none.hpp>
#include <boost/shared_ptr.hpp>
#include <pstade/disable_if_copy.hpp>
#include <pstade/egg/static_downcast.hpp>
#include <pstade/radish/bool_testable.hpp>
#include <pstade/radish/swappable.hpp>
#include <pstade/reset_assignment.hpp>
#include <pstade/type_equal_to.hpp>
#include <pstade/type_erasure.hpp>
#include "./config.hpp"
#include "./detail/basic_holder.hpp"
#include "./detail/basic_placeholder.hpp"
#include "./nout.hpp"


namespace pstade { namespace napkin {


template< class CharT >
struct basic_ostream :
    radish::bool_testable< basic_ostream<CharT>,
    radish::swappable    < basic_ostream<CharT> > >
{
private:
    typedef basic_ostream self_t;

public:
    typedef CharT char_type;

// structors
    basic_ostream(boost::none_t = boost::none)
    { }

    template< class StringOutputable >
    explicit basic_ostream(StringOutputable& out, typename disable_if_copy<self_t, StringOutputable>::type = 0) :
        m_content(new detail::basic_holder<CharT, StringOutputable>(out))
    { }

    basic_ostream(T_type_erasure, self_t& out) :
        m_content(new detail::basic_holder<CharT, self_t>(out))
    { }

// assignments
    void reset(boost::none_t = boost::none)
    {
        self_t().swap(*this);
    }

    template< class StringOutputable >
    void reset(StringOutputable& out, typename disable_if_copy<self_t, StringOutputable>::type = 0)
    {
        self_t(out).swap(*this);
    }

    void reset(self_t& out)
    {
        self_t(type_erasure, out).swap(*this);
    }

    PSTADE_RESET_ASSIGNMENT(basic_ostream)

// output
    template< class OutputStreamable >
    basic_ostream& operator<<(const OutputStreamable& x)
    {
        m_content->output(x);
        return *this;
    }

// bool_testable
    operator radish::safe_bool() const
    {
        return radish::make_safe_bool(m_content);
    }

// swappable
    void swap(self_t& other)
    {
        m_content.swap(other.m_content);
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
    template< class StringOutputable >
    bool contains() const
    {
        return type_equal_to(type(), typeid(StringOutputable));
    }

    template< class StringOutputable >
    StringOutputable& content() const
    {
        BOOST_ASSERT(contains<StringOutputable>());
        return egg::static_downcast< detail::basic_holder<CharT, StringOutputable> >(*m_content).held();
    }

private:
    boost::shared_ptr< detail::basic_placeholder<CharT> > m_content;
};


typedef basic_ostream<char>
ostream;


#if !defined(PSTADE_NAPKIN_NO_WIDESTRING)

typedef basic_ostream<wchar_t>
wostream;

#endif


} } // namespace pstade::napkin


#endif
