#ifndef PSTADE_ARRAYA_HPP
#define PSTADE_ARRAYA_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // size_t, ptrdiff_t
#include <boost/checked_delete.hpp>
#include <boost/mpl/divides.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/noncopyable.hpp>


#if !defined(PSTADE_ARRAYA_THRESHOLD_BYTES)
    #define PSTADE_ARRAYA_THRESHOLD_BYTES 256
#endif


namespace pstade {


namespace arraya_detail {


    template< class T >
    struct default_threshold :
        boost::mpl::divides<
            boost::mpl::size_t<PSTADE_ARRAYA_THRESHOLD_BYTES>,
            boost::mpl::sizeof_<T>
        >
    { };


} // namespace arraya_detail


template<
    class T,
    std::size_t N = arraya_detail::default_threshold<T>::value
>
struct arraya :
    private boost::noncopyable
{
    explicit arraya(std::size_t sz) :
        m_ptr(m_arr)
    {
        if (N < sz)
            m_ptr = new T[sz];
    }

    ~arraya()
    {
        if (m_ptr != m_arr)
            boost::checked_array_delete(m_ptr);
    }

    T *get() const
    {
        return m_ptr;
    }

    T& operator[](std::ptrdiff_t i) const
    {
        return m_ptr[i]; 
    }

    typedef T element_type;

private:
    T m_arr[N];
    T *m_ptr;
};


template<
    class T
>
struct arraya<T, 0> :
    private boost::noncopyable
{
    explicit arraya(std::size_t sz) :
        m_ptr(new T[sz])
    { }

    ~arraya()
    {
        boost::checked_array_delete(m_ptr);
    }

    T *get() const
    {
        return m_ptr;
    }

    T& operator[](std::ptrdiff_t i) const
    {
        return m_ptr[i]; 
    }

    typedef T element_type;

private:
    T *m_ptr;
};


} // namespace pstade


#endif
