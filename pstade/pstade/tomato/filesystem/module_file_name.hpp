#ifndef PSTADE_TOMATO_FILESYSTEM_MODULE_FILE_NAME_HPP
#define PSTADE_TOMATO_FILESYSTEM_MODULE_FILE_NAME_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/array.hpp>
#include <boost/assert.hpp>
#include <boost/noncopyable.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/iterator_range.hpp>
#include <pstade/apple/atl/module.hpp>
#include <pstade/apple/sdk/tchar.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/const.hpp>
#include <pstade/integral_cast.hpp>
#include <pstade/oven/distance.hpp>
#include <pstade/oven/null_terminate_range.hpp>
#include <pstade/oven/sub_range_result_type.hpp>
#include <pstade/require.hpp>
#include "./max_path_value.hpp"
#include "./path_find_extension.hpp"
#include "./path_find_file_name.hpp"


namespace pstade { namespace tomato {


namespace module_file_name_detail {


    typedef boost::array<TCHAR, max_path::value>
    buffer_t;


    struct buffer_init
    {
        buffer_init(HINSTANCE hInst)
        {
            BOOST_ASSERT(diet::valid(hInst));

            PSTADE_REQUIRE(0 !=
                ::GetModuleFileName(hInst, boost::begin(m_buf), pstade::integral(oven::distance(m_buf)))
            );

            BOOST_ASSERT(oven::is_null_terminated(m_buf));
        }

    protected:
        buffer_t m_buf;
    };


} // namespace module_file_name_detail


struct module_file_name :
    private module_file_name_detail::buffer_init,
    oven::null_terminate_range<module_file_name_detail::buffer_t>,
    private boost::noncopyable
{
    typedef const TCHAR *const_iterator;
    typedef module_file_name pstade_tomato_cstringizable;

private:
    typedef module_file_name_detail::buffer_init init_t; 
    typedef oven::null_terminate_range<module_file_name_detail::buffer_t> super_t;
    typedef oven::sub_range_result_const<module_file_name>::type const_sub_range_t;

public:
    explicit module_file_name(HINSTANCE hInst = _Module.GetModuleInstance()) :
        init_t(hInst),
        super_t(m_buf)
    { }

    const TCHAR *c_str() const
    { return boost::begin(m_buf); }

    const TCHAR *pstade_tomato_c_str() const
    { return c_str(); }

    const_sub_range_t folder() const
    {
        BOOST_ASSERT(oven::is_null_terminated(m_buf));

        return boost::make_iterator_range(
            boost::begin(m_buf),
            tomato::path_find_file_name(boost::begin(m_buf))
        );
    }

    const_sub_range_t identifier() const
    {
        BOOST_ASSERT(oven::is_null_terminated(m_buf));

        return boost::make_iterator_range(
            boost::begin(m_buf),
            tomato::path_find_extension(boost::begin(m_buf))
        );
    }

    const_sub_range_t name() const
    {
        BOOST_ASSERT(oven::is_null_terminated(m_buf));

        const TCHAR *pszFile = tomato::path_find_file_name(boost::begin(m_buf));
        return boost::make_iterator_range(
            pszFile,
            tomato::path_find_extension(pszFile)
        );
    }
};


} } // namespace pstade::tomato


#endif
