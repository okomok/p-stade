#ifndef PSTADE_EGG_LEXICAL_CAST_HPP
#define PSTADE_EGG_LEXICAL_CAST_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/preprocessor/facilities/identity.hpp>
#include <pstade/adl_barrier.hpp>
#include "./automatic.hpp"
#include "./auxiliary.hpp"
#include "./object.hpp"
#include "./specified.hpp"


namespace pstade { namespace egg {


    template<class To>
    struct xp_lexical_cast
    {
        typedef To result_type;

        template<class From>
        To operator()(From const& from) const
        {
            return boost::lexical_cast<To>(from);
        }
    };


    PSTADE_ADL_BARRIER(lexical_cast) { // for 'boost'
        PSTADE_EGG_SPECIFIED1(lexical_cast, xp_lexical_cast, (class))
    }


    typedef result_of_auxiliary0< xp_lexical_cast<std::string> >::type  op_to_string;
    typedef result_of_auxiliary0< xp_lexical_cast<std::wstring> >::type op_to_wstring;
    PSTADE_EGG_OBJECT((op_to_string),  to_string)  = PSTADE_EGG_AUXILIARY_RESULT_INITIALIZER(BOOST_PP_IDENTITY({}));
    PSTADE_EGG_OBJECT((op_to_wstring), to_wstring) = PSTADE_EGG_AUXILIARY_RESULT_INITIALIZER(BOOST_PP_IDENTITY({}));


    namespace lexicalize_detail {
        typedef automatic< xp_lexical_cast<boost::mpl::_1> >::type op;
    }

    typedef result_of_auxiliary0<lexicalize_detail::op>::type op_lexicalize;
    PSTADE_EGG_OBJECT((op_lexicalize), lexicalize) = PSTADE_EGG_AUXILIARY_RESULT_INITIALIZER(PSTADE_EGG_AUTOMATIC_INITIALIZER);


} } // namespace pstade::egg


#endif
