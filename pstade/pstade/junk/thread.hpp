#ifndef PSTADE_TOMATO_THREAD_HPP
#define PSTADE_TOMATO_THREAD_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <vector>
#include <process.h>
#include <boost/config.hpp>
#include <boost/config/requires_threads.hpp>
#include <boost/noncopyable.hpp>
#include <boost/utility/addressof.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/instance.hpp>
#include <pstade/oven/copy.hpp>
#include <pstade/check.hpp>
#include <pstade/require.hpp>


namespace pstade { namespace tomato {


namespace thead_detail {


    template< class Functor >
    unsigned int __stdcall proc(void *pData)
    {
        Functor *pfun = reinterpret_cast<Functor *>(pData);
        (*pfun)();
        return 0;
    }


    PSTADE_INSTANCE(std::vector<HANDLE>, handles, value)


} // namespace thead_detail


struct thread :
    private boost::noncopyable
{
    template< class Funtor >
    explicit thread(Functor fun)
    {
        unsigned int id;
        m_hThread = static_cast<HANDLE>(
        ::_beginthreadex(
            NULL,
            0,
            &thread_detail::proc<Functor>,
            reinterpret_cast<void *>(boost::addressof(fun)),
            0,
            &id
        );

        pstade::require(m_hThread != NULL, "valid thread handle");
    }

    HANDLE handle() const
    {
        return m_hThread;
    }

    ~thread()
    {
        PSTADE_CHECK(::CloseHandle(m_hThread));
    }

private:
    explicit thread();
};


inline
void wait_for_thread()
{
    DWORD dwCount = boost::size(thread_detail::threads);
    oven::array_range<HANDLE> arr(dwCount);
    oven::copies(thread_detail::handles, arr);
 
    dwRet = ::MsgWaitForMultipleObjects(m_dwCount, m_arrThreadHandles, FALSE, INFINITE, QS_ALLINPUT);
}


} } // namespace pstade::tomato


#endif
