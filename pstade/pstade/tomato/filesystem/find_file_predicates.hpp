#ifndef PSTADE_TOMATO_FILESYSTEM_FIND_FILE_PREDICATES_HPP
#define PSTADE_TOMATO_FILESYSTEM_FIND_FILE_PREDICATES_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <pstade/apple/sdk/tchar.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/candy/test_any.hpp>
#include <pstade/instance.hpp>


namespace pstade { namespace tomato {


template< DWORD attr >
struct find_file_matches_mask
{
    typedef bool result_type;

    bool operator()(WIN32_FIND_DATA const& data) const
    {
        return candy::test_any(data.dwFileAttributes, attr);
    }
};


#define PSTADE_TOMATO_define_pred(suffix, SUFFIX) \
    typedef find_file_matches_mask< BOOST_PP_CAT(FILE_ATTRIBUTE_, SUFFIX) > \
    PSTADE_TOMATO_pred_t(suffix); \
    PSTADE_INSTANCE(PSTADE_TOMATO_pred_t(suffix) const, PSTADE_TOMATO_pred(suffix), value) \
/**/

    #define PSTADE_TOMATO_pred(suffix) \
        BOOST_PP_CAT(find_file_is_, suffix) \
    /**/

    #define PSTADE_TOMATO_pred_t(suffix) \
        BOOST_PP_CAT(PSTADE_TOMATO_pred(suffix), _fun) \
    /**/


PSTADE_TOMATO_define_pred(readonly,   READONLY)
PSTADE_TOMATO_define_pred(directory,  DIRECTORY)
PSTADE_TOMATO_define_pred(compressed, COMPRESSED)
PSTADE_TOMATO_define_pred(system,     SYSTEM)
PSTADE_TOMATO_define_pred(hidden,     HIDDEN)
PSTADE_TOMATO_define_pred(temporary,  TEMPORARY)
PSTADE_TOMATO_define_pred(normal,     NORMAL)
PSTADE_TOMATO_define_pred(archive,    ARCHIVE)


    #undef PSTADE_TOMATO_pred_t
    #undef PSTADE_TOMATO_pred
#undef PSTADE_TOMATO_define_pred


struct find_file_is_dots_fun
{
    typedef bool result_type;

    bool operator()(WIN32_FIND_DATA const& data) const
    {
        return
            find_file_is_directory(data) &&
            data.cFileName[0] == _T('.') &&
            (
                data.cFileName[1] == _T('\0') ||
                (
                    data.cFileName[1] == _T('.') && 
                    data.cFileName[2] == _T('\0')
                )
            )
        ;
    }
};

PSTADE_INSTANCE(find_file_is_dots_fun const, find_file_is_dots, value)


} } // namespace pstade::tomato


#endif
