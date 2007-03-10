#ifndef PSTADE_OVEN_DIRECTORY_RANGE_HPP
#define PSTADE_OVEN_DIRECTORY_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/filesystem/operations.hpp> // basic_directory_iterator
#include <boost/version.hpp>
#include <pstade/implicitly_defined.hpp>
#include "./iter_range.hpp"
#include "./lightweight_copyable.hpp"


#if (BOOST_VERSION < 103400)
    #define PSTADE_OVEN_NO_BASIC_DIRECTORY_RANGE
#endif


namespace pstade { namespace oven {


#if !defined(PSTADE_OVEN_NO_BASIC_DIRECTORY_RANGE)


    template< class Path >
    struct basic_directory_range;


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

        explicit basic_directory_range(Path const& dir, boost::filesystem::system_error_type& ec) :
            super_t(iter_t(dir, ec), iter_t())
        { }

        PSTADE_IMPLICITLY_DEFINED_COPY_TO_BASE(basic_directory_range, super_t)
    };


    typedef basic_directory_range<boost::filesystem::path>
    directory_range;


    typedef basic_directory_range<boost::filesystem::wpath>
    wdirectory_range;


#else


    namespace directory_range_detail {


        struct directory_range;


        template< class = void >
        struct super_
        {
            typedef
                iter_range<boost::filesystem::directory_iterator,
                    lightweight_copyable<directory_range>
                >
            type;
        };


    } // namespace directory_range_detail


    struct directory_range :
        directory_range_detail::super_<>::type
    {
    private:
        typedef directory_range_detail::super_<>::type super_t;
        typedef super_t::iterator iter_t;

    public:
        explicit directory_range(boost::filesystem::path const& dir) :
            super_t(iter_t(dir), iter_t())
        { }

        PSTADE_IMPLICITLY_DEFINED_COPY_TO_BASE(directory_range, super_t)
    };


#endif // !defined(PSTADE_OVEN_NO_BASIC_DIRECTORY_RANGE)


} } // namespace pstade::oven


#endif
