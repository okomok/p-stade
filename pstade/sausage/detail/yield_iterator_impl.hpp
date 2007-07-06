#ifndef PSTADE_SAUSAGE_DETAIL_YIELD_ITERATOR_IMPL_HPP
#define PSTADE_SAUSAGE_DETAIL_YIELD_ITERATOR_IMPL_HPP


// PStade.Sausage
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://d.hatena.ne.jp/y-hamigaki/20060409#1144593955


#include <bitset>
#include <cstddef> // size_t
#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/core.hpp> // _1
#include <boost/noncopyable.hpp>
#include <boost/thread/condition.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <boost/throw_exception.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/addressof.hpp>
#include <pstade/egg/perfect.hpp>
#include <pstade/nullptr.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/static_c.hpp>
#include "../exception.hpp" // exit_exception
#include "./ref_to_ptr.hpp"
#include "./routine_result.hpp"


#if defined(BOOST_MSVC)
    #pragma warning(push)
    #pragma warning(disable: 4355) // 'this' : used in base member initializer list
#endif


namespace pstade { namespace sausage { namespace detail {


typedef std::bitset<3>
status_t;

struct is_incrementing  : pstade::static_c<std::size_t, 0> { };
struct is_end           : pstade::static_c<std::size_t, 1> { };
struct is_interrupted   : pstade::static_c<std::size_t, 2> { };


template< class Routine >
struct yield_iterator_impl :
    private boost::noncopyable
{
private:
    typedef yield_iterator_impl self_t;
    typedef typename detail::routine_result<Routine>::type result_t;
    typedef typename pass_by_reference<result_t>::type result_ref_t;
    typedef typename detail::ref_to_ptr<result_ref_t>::type result_ptr_t;

public:
    explicit yield_iterator_impl(Routine const& rou) :
        m_rou(rou),
        m_presult(PSTADE_NULLPTR),
        m_status(1), // is_incrementing
        m_thread(boost::lambda::bind(&yield_iterator_impl::work, this))
    { }

    ~yield_iterator_impl()
    {
        try {
            {
                boost::mutex::scoped_lock lock(m_mutex);
                m_status.set(is_interrupted::value);
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
        BOOST_ASSERT(!m_status.test(is_incrementing::value));
        BOOST_ASSERT("out of range access" && !m_status.test(is_end::value));

        return *m_presult;
    }

    void next()
    {
        boost::mutex::scoped_lock lock(m_mutex);

        BOOST_ASSERT("out of range" && !m_status.test(is_end::value));

        m_status.set(is_incrementing::value);
        m_cond.notify_one();

        while (m_status.test(is_incrementing::value) && !m_status.test(is_end::value))
            m_cond.wait(lock);
    }

    bool done()
    {
        boost::mutex::scoped_lock lock(m_mutex);

        while (m_status.test(is_incrementing::value) && !m_status.test(is_end::value))
            m_cond.wait(lock);

        return m_status.test(is_end::value);
    }

private:
    Routine m_rou;
    result_ptr_t m_presult;
    boost::mutex m_mutex;
    boost::condition m_cond;
    status_t m_status;
    boost::thread m_thread; // must be the last member.

    void work()
    {
        try {
            m_rou(egg::perfect<void>(
                boost::lambda::bind(&self_t::yield, this, boost::lambda::_1)
            ));
        }
        catch (exit_exception const&)
        { }

        boost::mutex::scoped_lock lock(m_mutex);
        m_status.set(is_end::value);
        m_cond.notify_one();
    }

    void yield(result_ref_t result) // in the same thread as 'work()'.
    {
        boost::mutex::scoped_lock lock(m_mutex);

        // 'result' is alive until next increment,
        // as far as 'value' can go across thread-boundary.
        m_presult = boost::addressof(result);
        m_status.reset(is_incrementing::value);
        m_cond.notify_one();

        while (!m_status.test(is_incrementing::value) && !m_status.test(is_interrupted::value))
            m_cond.wait(lock);

        if (m_status.test(is_interrupted::value)) {
            exit_exception ex;
            boost::throw_exception(ex);
        }
    }
};


} } } // namespace pstade::sausage::detail


#if defined(BOOST_MSVC)
    #pragma warning(pop)
#endif


#endif
