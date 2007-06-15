#ifndef PSTADE_GRAVY_FIND_FILE_FUNCTORS_HPP
#define PSTADE_GRAVY_FIND_FILE_FUNCTORS_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/as_c_str.hpp>
#include <pstade/oven/copy_range.hpp>
#include "./sdk/windows.hpp"


namespace pstade { namespace gravy {


    template<class Sequence>
    struct find_file_construct
    {
        typedef Sequence result_type;

        Sequence operator()(WIN32_FIND_DATA const& data) const
        {
            return data.cFileName|oven::as_c_str|oven::copied;
        }
    };


    template<class StringT>
    struct find_file_stringize
    {
        typedef StringT result_type;

        StringT operator()(WIN32_FIND_DATA const& data) const
        {
            return StringT(data.cFileName);
        }
    };


} } // namespace pstade::gravy


#endif
