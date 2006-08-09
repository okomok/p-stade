#ifndef PSTADE_SARRAY_HPP
#define PSTADE_SARRAY_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // size_t
#include <boost/checked_delete.hpp>
#include <boost/noncopyable.hpp>


#if !defined(PSTADE_SARRAY_THRESHOLD_SIZE)
    #define PSTADE_SARRAY_THRESHOLD_SIZE 256
#endif


namespace pstade {


template<
    class T,
    std::size_t N = PSTADE_SARRAY_THRESHOLD_SIZE
>
struct sarray :
    private boost::noncopyable
{
    explicit sarray(std::size_t sz) :
        m_ptr(m_arr)
    {
        if (N < sz)
            m_ptr = new T[sz];
    }

    ~sarray()
    {
        if (m_ptr != m_arr)
            boost::checked_array_delete(m_ptr);
    }

    T *get() const
    {
        return m_ptr;
    }

    T& operator[](std::size_t i) const
    {
        return m_ptr[i]; 
    }

    typedef T element_type;

private:
    T m_arr[N];
    T *m_ptr;
};


} // namespace pstade


#endif
