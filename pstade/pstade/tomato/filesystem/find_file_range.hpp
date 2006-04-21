#ifndef PSTADE_TOMATO_FILESYSTEM_FIND_FILE_RANGE_HPP
#define PSTADE_TOMATO_FILESYSTEM_FIND_FILE_RANGE_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Model of:
//
// Readable and Single Pass (Input) Range of WIN32_FIND_DATA


// Port of:
//
// boost::directory_iterator to non-shared_ptr version


#include <boost/assert.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/noncopyable.hpp>
#include <boost/range/iterator_range.hpp>
#include <pstade/check.hpp>
#include "../diet/valid.hpp"
#include "../require.hpp"
#include "./find_file_iterator.hpp"


namespace pstade { namespace tomato {


namespace find_file_range_detail {


    // See: Boost.BaseFromMember
    //
    struct initializer
    {
    protected:
        HANDLE m_hFind;
        WIN32_FIND_DATA m_data;

        explicit initializer(const TCHAR *pszName)
        {
            BOOST_ASSERT(diet::valid(pszName));

            m_hFind = ::FindFirstFile(pszName, &m_data);
        }

        ~initializer()
        {
            if (m_hFind != INVALID_HANDLE_VALUE)
                PSTADE_CHECK(::FindClose(m_hFind)); // cannot throw
        }
    };


} // namespace find_file_range_detail


struct find_file_range  :
    private boost::noncopyable,
    private find_file_range_detail::initializer,
    boost::iterator_range<find_file_iterator>
{
private:
    typedef boost::iterator_range<find_file_iterator> super_t;

public:
    explicit find_file_range(const TCHAR *pszName) :
        find_file_range_detail::initializer(pszName),
        super_t(
            find_file_iterator(m_hFind, m_data),
            find_file_iterator()
        )
    { }
};


} } // namespace pstade::tomato


#endif
