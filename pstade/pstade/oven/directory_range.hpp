#ifndef PSTADE_OVEN_DIRECTORY_RANGE_HPP
#define PSTADE_OVEN_DIRECTORY_RANGE_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// This range could be just a function.
// But this is "conceptually" a noncopyable range.


#include <boost/filesystem/convenience.hpp> // basic_recursive_directory_iterator
#include <boost/filesystem/operations.hpp> // basic_directory_iterator
#include <boost/filesystem/path.hpp>
#include <pstade/implicitly_defined.hpp>
#include "./iter_range.hpp"
#include "./lightweight_copyable.hpp"


namespace pstade { namespace oven {


template< class Path >
struct basic_directory_range;


template< class Path >
struct basic_recursive_directory_range;


namespace directory_range_detail {


    template< class Path >
    struct super_
    {
        typedef
            iter_range<boost::filesystem::basic_directory_iterator<Path>,
                lightweight_copyable< basic_directory_range<Path> >
            >
        type;
    };


    template< class Path >
    struct recursive_super
    {
        typedef
            iter_range<boost::filesystem::basic_recursive_directory_iterator<Path>,
                lightweight_copyable< basic_recursive_directory_range<Path> >
            >
        type;
    };


} // namespace directory_range_detail


template< class Path >
struct basic_directory_range :
    directory_range_detail::super_<Path>::type
{
private:
    typedef typename directory_range_detail::super_<Path>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    explicit basic_directory_range(Path const& dir) :
        super_t(iter_t(dir), iter_t())
    { }

    template< class ErrorCode >
    explicit basic_directory_range(Path const& dir, ErrorCode& ec) :
        super_t(iter_t(dir, ec), iter_t())
    { }

    PSTADE_IMPLICITLY_DEFINED_COPY_TO_BASE(basic_directory_range, super_t)
};


typedef basic_directory_range<boost::filesystem::path> directory_range;
#if !defined(BOOST_FILESYSTEM_NARROW_ONLY)
typedef basic_directory_range<boost::filesystem::wpath> wdirectory_range;
#endif


template< class Path >
struct basic_recursive_directory_range :
    directory_range_detail::recursive_super<Path>::type
{
private:
    typedef typename directory_range_detail::recursive_super<Path>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    explicit basic_recursive_directory_range(Path const& dir) :
        super_t(iter_t(dir), iter_t())
    { }

    template< class ErrorCode >
    explicit basic_recursive_directory_range(Path const& dir, ErrorCode& ec) :
        super_t(iter_t(dir, ec), iter_t())
    { }

    PSTADE_IMPLICITLY_DEFINED_COPY_TO_BASE(basic_recursive_directory_range, super_t)
};


typedef basic_recursive_directory_range<boost::filesystem::path> recursive_directory_range;
#if !defined(BOOST_FILESYSTEM_NARROW_ONLY)
typedef basic_recursive_directory_range<boost::filesystem::wpath> wrecursive_directory_range;
#endif


} } // namespace pstade::oven


#endif
