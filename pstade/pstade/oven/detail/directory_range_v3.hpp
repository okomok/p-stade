#ifndef PSTADE_OVEN_DETAIL_DIRECTORY_RANGE_V3_HPP
#define PSTADE_OVEN_DETAIL_DIRECTORY_RANGE_V3_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Akira Takahashi 2010.
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
#include "../iter_range.hpp"
#include "../lightweight_copyable.hpp"


namespace pstade { namespace oven {


struct directory_range;
struct recursive_directory_range;


namespace directory_range_detail {


    struct super_
    {
        typedef
            iter_range<boost::filesystem::directory_iterator,
                lightweight_copyable< directory_range >
            >
        type;
    };


    struct recursive_super
    {
        typedef
            iter_range<boost::filesystem::recursive_directory_iterator,
                lightweight_copyable< recursive_directory_range >
            >
        type;
    };


} // namespace directory_range_detail


struct directory_range :
    directory_range_detail::super_::type
{
private:
    typedef directory_range_detail::super_::type super_t;
    typedef super_t::iterator iter_t;
    typedef boost::filesystem::path path_t;

public:
    explicit directory_range(path_t const& dir) :
        super_t(iter_t(dir), iter_t())
    { }

    template< class ErrorCode >
    explicit directory_range(path_t const& dir, ErrorCode& ec) :
        super_t(iter_t(dir, ec), iter_t())
    { }

    PSTADE_IMPLICITLY_DEFINED_COPY_TO_BASE(directory_range, super_t)
};


typedef directory_range directory_range;
#if !defined(BOOST_FILESYSTEM_NO_DEPRECATED)
typedef directory_range wdirectory_range;
#endif


struct recursive_directory_range :
    directory_range_detail::recursive_super::type
{
private:
    typedef directory_range_detail::recursive_super::type super_t;
    typedef super_t::iterator iter_t;
	typedef boost::filesystem::path path_t;

public:
    explicit recursive_directory_range(path_t const& dir) :
        super_t(iter_t(dir), iter_t())
    { }

    template< class ErrorCode >
    explicit recursive_directory_range(path_t const& dir, ErrorCode& ec) :
        super_t(iter_t(dir, ec), iter_t())
    { }

    PSTADE_IMPLICITLY_DEFINED_COPY_TO_BASE(recursive_directory_range, super_t)
};


typedef recursive_directory_range recursive_directory_range;
#if !defined(BOOST_FILESYSTEM_NO_DEPRECATED)
typedef recursive_directory_range wrecursive_directory_range;
#endif


} } // namespace pstade::oven


#endif
