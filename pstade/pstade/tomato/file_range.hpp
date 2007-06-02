#ifndef PSTADE_TOMATO_FILE_RANGE_HPP
#define PSTADE_TOMATO_FILE_RANGE_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying hFile LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// <boost/spirit/iterator/impl/file_iterator.ipp>


#include <cstddef> // ptrdiff_t
#include <boost/assert.hpp>
#include <boost/cstdint.hpp> // uint8_t
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/nullptr.hpp>
#include <pstade/oven/iter_range.hpp>
#include "./scoped_file_view.hpp"
#include "./scoped_handle.hpp"
#include "./tstring.hpp"


namespace pstade { namespace tomato {


namespace file_range_detail {


    template< class Value >
    struct iview
    {
        explicit iview(tstring path) :
            m_diff(0) 
        {
            scoped_ihandle hFile(::CreateFile(
                path.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL,
                OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL));
            if (!hFile)
                return;

            scoped_nhandle hMap(::CreateFileMapping(*hFile, NULL, PAGE_READONLY, 0, 0, NULL));
            if (!hMap)
                return;

            m_view.reset(::MapViewOfFile(*hMap, FILE_MAP_READ, 0, 0, 0));
            m_diff = ::GetFileSize(*hFile, NULL) / sizeof(Value);
        }

        Value const *first() const
        {
            return m_view ? static_cast<Value const *>(*m_view) : PSTADE_NULLPTR;
        }

        Value const *last() const
        {
            return first() + m_diff;
        }

    private:
        scoped_file_view m_view;
        std::ptrdiff_t m_diff;
    };


    template< class Value >
    struct oview
    {
        explicit oview(tstring const& path, std::ptrdiff_t diff) :
            m_diff(0)
        {
            scoped_ihandle hFile(::CreateFile(
                    path.c_str(), GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ, NULL, 
                    CREATE_ALWAYS, FILE_FLAG_SEQUENTIAL_SCAN, NULL));
            if (!hFile)
                return;

            LARGE_INTEGER liOffset;
            liOffset.QuadPart = diff * sizeof(Value);
            if (::SetFilePointer(*hFile, liOffset.LowPart, &liOffset.HighPart, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
                return;

            if (!::SetEndOfFile(*hFile))
                return;

            scoped_nhandle hMap(::CreateFileMapping(*hFile, NULL, PAGE_READWRITE, 0, 0, NULL));
            if (!hMap)
                return;

            m_view.reset(::MapViewOfFile(*hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0));
            m_diff = diff;

            BOOST_ASSERT(m_diff * sizeof(Value) == ::GetFileSize(*hFile, NULL));
        }

        Value *first() const
        {
            return m_view ? static_cast<Value *>(*m_view) : PSTADE_NULLPTR;
        }

        Value *last() const
        {
            return first() + m_diff;
        }

    private:
        scoped_file_view m_view;
        std::ptrdiff_t m_diff;
    };


} // namespace file_range_detail


template< class Value = boost::uint8_t >
struct ifile_range :
    file_range_detail::iview<Value>,
    oven::iter_range<Value const *>::type
{
private:
    typedef file_range_detail::iview<Value> view_t;
    typedef typename oven::iter_range<Value const *>::type super_t;

public:
    explicit ifile_range(tstring const& path) :
        view_t(path),
        super_t(view_t::first(), view_t::last())
    { }

private:
    ifile_range(ifile_range const&);
    ifile_range& operator=(ifile_range const&);
};


template< class Value = boost::uint8_t >
struct ofile_range :
    file_range_detail::oview<Value>,
    oven::iter_range<Value *>::type
{
private:
    typedef file_range_detail::oview<Value> view_t;
    typedef typename oven::iter_range<Value *>::type super_t;

public:
    explicit ofile_range(tstring const& path, std::ptrdiff_t diff) :
        view_t(path, diff),
        super_t(view_t::first(), view_t::last())
    { }

private:
    ofile_range(ofile_range const&);
    ofile_range& operator=(ofile_range const&);
};


} } // namespace pstade::tomato


#endif
