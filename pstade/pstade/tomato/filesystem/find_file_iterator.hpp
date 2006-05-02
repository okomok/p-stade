#ifndef PSTADE_TOMATO_FILESYSTEM_FIND_FILE_ITERATOR_HPP
#define PSTADE_TOMATO_FILESYSTEM_FIND_FILE_ITERATOR_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include "../boolean_cast.hpp"


namespace pstade { namespace tomato {


struct find_file_iterator :
    boost::iterator_facade<
        find_file_iterator,
        WIN32_FIND_DATA,
        boost::single_pass_traversal_tag
    >
{
    // See: sgi.STL::istream_iterator

    find_file_iterator() : // the end iterator
        m_found(false)
    { }

    find_file_iterator(HANDLE hFind, WIN32_FIND_DATA& data) :
        m_hFind(hFind), m_pdata(&data), m_found(hFind != INVALID_HANDLE_VALUE)
    { }

private:
    HANDLE m_hFind;
    WIN32_FIND_DATA *m_pdata;
    bool m_found;

    void find_next_file()
    {
        m_found = tomato::boolean(::FindNextFile(m_hFind, m_pdata));

        if (!m_found)
            BOOST_ASSERT(::GetLastError() == ERROR_NO_MORE_FILES);
    }

    bool equal_aux(const find_file_iterator& other) const
    {
        return m_hFind == other.m_hFind && m_pdata == other.m_pdata;
    }

friend class boost::iterator_core_access;
    void increment()
    {
        BOOST_ASSERT(m_found && "out of range");

        find_next_file();
    }

    bool equal(const find_file_iterator& other) const
    {
        return (m_found == other.m_found) && (!m_found || equal_aux(other));
    }

    WIN32_FIND_DATA& dereference() const
    {
        BOOST_ASSERT(m_found && "out of range access");

        return *m_pdata;
    }
};


} } // namespace pstade::tomato


#endif
