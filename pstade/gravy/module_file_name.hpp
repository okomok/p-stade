#ifndef PSTADE_GRAVY_MODULE_FILE_NAME_HPP
#define PSTADE_GRAVY_MODULE_FILE_NAME_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// A Random Access Traversal Readable Lvalue Range
// that represents the module file name.


#include <boost/array.hpp>
#include <boost/assert.hpp>
#include <boost/range/begin.hpp>
#include <pstade/oven/as_c_str.hpp>
#include <pstade/oven/iter_range.hpp>
#include <pstade/require.hpp>
#include "./detail/path_find_extension.hpp"
#include "./detail/path_find_file_name.hpp"
#include "./main_instance.hpp"
#include "./sdk/tchar.hpp"
#include "./sdk/windows.hpp"


namespace pstade { namespace gravy {


    namespace module_file_name_detail {


        typedef
            boost::array<TCHAR, MAX_PATH>
        buffer_t;


        template<class = void>
        struct init
        {
            typedef init type;

            explicit init(HINSTANCE hInst)
            {
                BOOST_ASSERT(hInst != NULL);

                PSTADE_REQUIRE(0 !=
                    ::GetModuleFileName(hInst, boost::begin(m_buf), MAX_PATH) );

                BOOST_ASSERT(oven::contains_zero(m_buf));
            }

        protected:
            buffer_t m_buf;
        };


        template<class = void>
        struct super_
        {
            typedef
                oven::iter_range<TCHAR const *>
            type;
        };


    } // namespace module_file_name_detail


    struct module_file_name :
        private module_file_name_detail::init<>::type,
        module_file_name_detail::super_<>::type
    {
    private:
        typedef module_file_name_detail::init<>::type init_t; 
        typedef module_file_name_detail::super_<>::type super_t;
        typedef oven::iter_range_of<module_file_name const>::type const const_sub_range_t;

    public:
        explicit module_file_name(HINSTANCE hInst = main_instance) :
            init_t(hInst),
            super_t(m_buf|oven::as_c_str)
        { }

        const_sub_range_t folder() const
        {
            return oven::make_iter_range(
                boost::begin(m_buf),
                detail::path_find_file_name(boost::begin(m_buf)) );
        }

        const_sub_range_t identifier() const
        {
            return oven::make_iter_range(
                boost::begin(m_buf),
                detail::path_find_extension(boost::begin(m_buf)) );
        }

        const_sub_range_t name() const
        {
            TCHAR const *pszFile = detail::path_find_file_name(boost::begin(m_buf));
            return oven::make_iter_range(
                pszFile,
                detail::path_find_extension(pszFile) );
        }

        friend
        TCHAR const *pstade_gravy_c_str(module_file_name const& self)
        {
            return boost::begin(self.m_buf);
        }

    private:
        module_file_name(module_file_name const&);
        module_file_name& operator=(module_file_name const&);
    };


} } // namespace pstade::gravy


#endif
