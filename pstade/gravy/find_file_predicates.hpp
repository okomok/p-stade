#ifndef PSTADE_GRAVY_FIND_FILE_PREDICATES_HPP
#define PSTADE_GRAVY_FIND_FILE_PREDICATES_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <pstade/candy/test_any.hpp>
#include <pstade/pod_constant.hpp>
#include "./sdk/tchar.hpp"
#include "./sdk/windows.hpp"


namespace pstade { namespace gravy {


    template<DWORD attr>
    struct find_file_matches_mask
    {
        typedef bool result_type;

        bool operator()(WIN32_FIND_DATA const& data) const
        {
            return candy::test_any(data.dwFileAttributes, attr);
        }
    };


    #define PSTADE_GRAVY_define_pred(suffix, SUFFIX) \
        typedef find_file_matches_mask< BOOST_PP_CAT(FILE_ATTRIBUTE_, SUFFIX) > PSTADE_GRAVY_pred_t(suffix); \
        PSTADE_POD_CONSTANT( (PSTADE_GRAVY_pred_t(suffix)), PSTADE_GRAVY_pred(suffix) ) = {}; \
    /**/

        #define PSTADE_GRAVY_pred(suffix) \
            BOOST_PP_CAT(find_file_is_, suffix) \
        /**/

        #define PSTADE_GRAVY_pred_t(suffix) \
            BOOST_PP_CAT(op_, PSTADE_GRAVY_pred(suffix)) \
        /**/


    PSTADE_GRAVY_define_pred(readonly,   READONLY)
    PSTADE_GRAVY_define_pred(directory,  DIRECTORY)
    PSTADE_GRAVY_define_pred(compressed, COMPRESSED)
    PSTADE_GRAVY_define_pred(system,     SYSTEM)
    PSTADE_GRAVY_define_pred(hidden,     HIDDEN)
    PSTADE_GRAVY_define_pred(temporary,  TEMPORARY)
    PSTADE_GRAVY_define_pred(normal,     NORMAL)
    PSTADE_GRAVY_define_pred(archive,    ARCHIVE)


        #undef PSTADE_GRAVY_pred_t
        #undef PSTADE_GRAVY_pred
    #undef PSTADE_GRAVY_define_pred


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

    PSTADE_POD_CONSTANT((op_find_file_is_dots), find_file_is_dots) = {};


} } // namespace pstade::gravy


#endif
