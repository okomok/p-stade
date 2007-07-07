#ifndef PSTADE_EGG_IS_CLASSIFIED_AS_HPP
#define PSTADE_EGG_IS_CLASSIFIED_AS_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <locale>
#include <pstade/pod_constant.hpp>


namespace pstade { namespace egg {


    struct op_is_classified_as
    {
        typedef bool result_type;

        template<class CharT>
        bool operator()(CharT ch, std::ctype_base::mask m, std::locale const& loc) const
        {
            return std::use_facet< std::ctype<CharT> >(loc).is(m, ch);
        }

        template<class CharT>
        bool operator()(CharT ch, std::ctype_base::mask m) const
        {
            return (*this)(ch, m, std::locale());
        }
    };


    PSTADE_POD_CONSTANT((op_is_classified_as), is_classified_as) = {};


} } // namespace pstade::egg


#endif
