#ifndef PSTADE_OVEN_DIRECTORY_RANGE_HPP
#define PSTADE_OVEN_DIRECTORY_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/filesystem/operations.hpp> // basic_directory_iterator
#include <boost/range/iterator_range.hpp>
#include <boost/version.hpp>
#include "./is_lightweight_proxy.hpp"


#if (BOOST_VERSION < 103400)
    #define PSTADE_OVEN_NO_BASIC_DIRECTORY_RANGE
#endif


#if !defined(PSTADE_OVEN_NO_BASIC_DIRECTORY_RANGE)


    namespace pstade { namespace oven {


        namespace directory_range_detail {


            template< class Path >
            struct super_
            {
                typedef boost::iterator_range<
                    boost::filesystem::basic_directory_iterator<Path>
                > type;
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
            explicit basic_directory_range(const Path& dir) :
                super_t(iter_t(dir), iter_t())
            { }

            explicit basic_directory_range(const Path& dir, boost::filesystem::system_error_type& ec) :
                super_t(iter_t(dir, ec), iter_t())
            { }
        };


        typedef basic_directory_range<boost::filesystem::path>
        directory_range;


        typedef basic_directory_range<boost::filesystem::wpath>
        wdirectory_range;


    } } // namespace pstade::oven


    PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::basic_directory_range, 1)


#else


    namespace pstade { namespace oven {


        namespace directory_range_detail {


            template< class = void >
            struct super_
            {
                typedef boost::iterator_range<
                    boost::filesystem::directory_iterator
                > type;
            };


        } // namespace directory_range_detail


        struct directory_range :
            directory_range_detail::super_<>::type
        {
        private:
            typedef directory_range_detail::super_<>::type super_t;
            typedef super_t::iterator iter_t;

        public:
            explicit directory_range(const boost::filesystem::path& dir) :
                super_t(iter_t(dir), iter_t())
            { }
        };


    } } // namespace pstade::oven


    PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY(pstade::oven::directory_range)


#endif // !defined(PSTADE_OVEN_NO_BASIC_DIRECTORY_RANGE)


#endif
