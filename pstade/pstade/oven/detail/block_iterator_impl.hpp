#ifndef PSTADE_OVEN_DETAIL_BLOCK_ITERATOR_IMPL_HPP
#define PSTADE_OVEN_DETAIL_BLOCK_ITERATOR_IMPL_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <bitset>
#include <cstddef> // size_t
#include <exception>
#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/core.hpp> // _1
#include <boost/noncopyable.hpp>
#include <boost/thread/condition.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/addressof.hpp>
#include <pstade/egg/ret.hpp>
#include <pstade/nullptr.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/static_c.hpp>
#include "./ref_to_ptr.hpp"


#if defined(BOOST_MSVC)
    #pragma warning(push)
    #pragma warning(disable: 4355) // 'this' : used in base member initializer list
#endif


namespace pstade { namespace oven { namespace detail {


struct yield_break_exception :
    std::exception
{
    char const *what() const throw() // override
    {
        return "yield_break_exception";
    }
};


typedef std::bitset<3> block_status_type;

struct block_incrementing  : static_c<std::size_t, 0> { };
struct block_end           : static_c<std::size_t, 1> { };
struct block_interrupted   : static_c<std::size_t, 2> { };


template< class IteratorBlock >
struct block_iterator_impl :
    private boost::noncopyable
{
private:
    typedef block_iterator_impl self_t;
    typedef typename IteratorBlock::yield_type result_t;
    typedef typename pass_by_reference<result_t>::type result_ref_t;
    typedef typename ref_to_ptr<result_ref_t>::type result_ptr_t;

public:
    explicit block_iterator_impl(IteratorBlock block) :
        m_block(block),
        m_presult(PSTADE_NULLPTR),
        m_status(1), // block_incrementing
        m_thread(boost::lambda::bind(&block_iterator_impl::work, this))
    { }

    ~block_iterator_impl()
    {
        try {
            {
                boost::mutex::scoped_lock lock(m_mutex);
                m_status.set(block_interrupted::value);
                m_cond.notify_one();
            }
            m_thread.join();
        }
        catch (...) {
            BOOST_ASSERT(false);
        }
    }

    result_ref_t deref()
    {
        boost::mutex::scoped_lock lock(m_mutex);

        BOOST_ASSERT(m_presult != PSTADE_NULLPTR);
        BOOST_ASSERT(!m_status.test(block_incrementing::value));
        BOOST_ASSERT("out of range access" && !m_status.test(block_end::value));

        return *m_presult;
    }

    void next()
    {
        boost::mutex::scoped_lock lock(m_mutex);

        BOOST_ASSERT("out of range" && !m_status.test(block_end::value));

        m_status.set(block_incrementing::value);
        m_cond.notify_one();

        while (m_status.test(block_incrementing::value) && !m_status.test(block_end::value))
            m_cond.wait(lock);
    }

    bool done()
    {
        boost::mutex::scoped_lock lock(m_mutex);

        while (m_status.test(block_incrementing::value) && !m_status.test(block_end::value))
            m_cond.wait(lock);

        return m_status.test(block_end::value);
    }

private:
    IteratorBlock m_block;
    result_ptr_t m_presult;
    boost::mutex m_mutex;
    boost::condition m_cond;
    block_status_type m_status;
    boost::thread m_thread; // must be the last member.

    void work()
    {
        try {
            m_block(egg::ret<void>(boost::lambda::bind(&self_t::yield, this, boost::lambda::_1)));
        }
        catch (yield_break_exception const&) {
        }

        boost::mutex::scoped_lock lock(m_mutex);
#if !defined(NDEBUG)
        m_presult = PSTADE_NULLPTR;
#endif
        m_status.set(block_end::value);
        m_cond.notify_one();
    }

    void yield(result_ref_t result) // in the same thread as 'work()'.
    {
        boost::mutex::scoped_lock lock(m_mutex);

        // 'result' is alive until next increment,
        // as far as 'value' can go across thread-boundary.
        m_presult = boost::addressof(result);
        m_status.reset(block_incrementing::value);
        m_cond.notify_one();

        while (!m_status.test(block_incrementing::value) && !m_status.test(block_interrupted::value))
            m_cond.wait(lock);

        if (m_status.test(block_interrupted::value))
            throw yield_break_exception();
    }
};


} } } // namespace pstade::oven::detail


#if defined(BOOST_MSVC)
    #pragma warning(pop)
#endif


#endif
