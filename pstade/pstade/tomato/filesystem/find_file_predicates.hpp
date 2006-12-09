#ifndef PSTADE_TOMATO_FILESYSTEM_FIND_FILE_PREDICATES_HPP
#define PSTADE_TOMATO_FILESYSTEM_FIND_FILE_PREDICATES_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <pstade/apple/sdk/tchar.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/candy/test_any.hpp>
#include <pstade/constant.hpp>


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
    PSTADE_CONSTANT(PSTADE_TOMATO_pred(suffix), PSTADE_TOMATO_pred_t(suffix)) \
/**/

    #define PSTADE_TOMATO_pred(suffix) \
        BOOST_PP_CAT(find_file_is_, suffix) \
    /**/

    #define PSTADE_TOMATO_pred_t(suffix) \
        BOOST_PP_CAT(op_, PSTADE_TOMATO_pred(suffix)) \
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


struct op_find_file_is_dots
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

PSTADE_CONSTANT(find_file_is_dots, op_find_file_is_dots)


} } // namespace pstade::tomato


#endif
