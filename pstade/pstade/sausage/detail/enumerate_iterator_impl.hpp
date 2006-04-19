#ifndef PSTADE_SAUSAGE_DETAIL_ENUMERATE_ITERATOR_IMPL_HPP
#define PSTADE_SAUSAGE_DETAIL_ENUMERATE_ITERATOR_IMPL_HPP


// PStade.Sausage
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://d.hatena.ne.jp/y-hamigaki/20060409#1144593955


// Todo:
//
// Exception-safe


#include <bitset>
#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/core.hpp> // _1
#include <boost/mpl/size_t.hpp>
#include <boost/noncopyable.hpp>
#include <boost/thread/condition.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <pstade/nullptr.hpp>
#include "../enumerate.hpp"
#include "../enumerate_argument_type.hpp"


#if defined(BOOST_MSVC)
    #pragma warning(push)
    #pragma warning(disable: 4355) // 'this' : used in base member initializer list
#endif


namespace pstade { namespace sausage { namespace detail {


typedef std::bitset<3>
status_t;

struct is_incrementing  : boost::mpl::size_t<0> { };
struct is_end           : boost::mpl::size_t<1> { };
struct is_interrupted   : boost::mpl::size_t<2> { };


template< class Enumerable >
struct enumerate_iterator_impl :
    private boost::noncopyable
{
private:
    typedef enumerate_iterator_impl self_t;
    typedef typename enumerate_argument<Enumerable>::type arg_t;
    typedef typename boost::remove_reference<arg_t>::type val_t;

public:
    explicit enumerate_iterator_impl(Enumerable& enm) :
        m_enm(enm),
        m_parg(PSTADE_NULLPTR),
        m_status(1), // is_incrementing
        m_thread(boost::lambda::bind(&enumerate_iterator_impl::work, this))
    { }

    ~enumerate_iterator_impl()
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
            // cannot throw
        }
    }

    arg_t deref()
    {
        boost::mutex::scoped_lock lock(m_mutex);

        BOOST_ASSERT(m_parg != PSTADE_NULLPTR);
        BOOST_ASSERT(!m_status.test(is_incrementing::value));
        BOOST_ASSERT(!m_status.test(is_end::value) && "pstade::sausage::enumerate_iterator - out of range access");

        return *m_parg;
    }

    void next()
    {
        boost::mutex::scoped_lock lock(m_mutex);

        BOOST_ASSERT(!m_status.test(is_end::value) && "pstade::sausage::enumerate_iterator - out of range");

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
    Enumerable& m_enm;
    val_t *m_parg;
    boost::mutex m_mutex;
    boost::condition m_cond;
    status_t m_status;
    boost::thread m_thread; // must be last

    void work()
    {
        sausage::enumerate(m_enm, boost::lambda::bind(&self_t::enum_fun, this, boost::lambda::_1));

        boost::mutex::scoped_lock lock(m_mutex);
        m_status.set(is_end::value);
        m_cond.notify_one();
    }

    bool enum_fun(arg_t arg)
    {
        boost::mutex::scoped_lock lock(m_mutex);

        // 'arg' is alive until next increment,
        // as far as 'arg' can go across thread-boundary.
        m_parg = &arg;
        m_status.reset(is_incrementing::value);
        m_cond.notify_one();

        while (!m_status.test(is_incrementing::value) && !m_status.test(is_interrupted::value))
            m_cond.wait(lock);

        if (m_status.test(is_interrupted::value))
            return false;

        return true; // continue
    }
};


} } } // namespace pstade::sausage::detail


#if defined(BOOST_MSVC)
    #pragma warning(pop)
#endif


#endif
