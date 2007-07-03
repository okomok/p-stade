#ifndef PSTADE_EGG_NOT_HPP
#define PSTADE_EGG_NOT_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/facilities/identity.hpp>
#include "./function_by_value.hpp"
#include "./fuse.hpp"
#include "./object.hpp"
#include "./unfuse.hpp"


namespace pstade { namespace egg {


    namespace not_detail {


        template<class BasePred>
        struct fused_result
        {
            BasePred m_base;

            typedef bool result_type;

            template<class Tuple>
            result_type operator()(Tuple const& tup) const
            {
                return !fuse(m_base)(tup);
            }
        };


        template<class BasePred>
        struct result_of_not_ :
            result_of_unfuse<
                fused_result<BasePred>
            >
        { };


        struct baby
        {
            template<class Myself, class BasePred>
            struct apply :
                result_of_not_<BasePred>
            { };

            template<class Result, class BasePred>
            Result call(BasePred base) const
            {
                Result r = PSTADE_EGG_UNFUSE_RESULT_INITIALIZER(BOOST_PP_IDENTITY({base}), BOOST_PP_IDENTITY({}));
                return r;
            }
        };


    } // namespace not_detail



    using not_detail::result_of_not_;


    #define PSTADE_EGG_NOT_RESULT_INITIALIZER(B) \
        { { { B() }, {} } } \
    /**/


    typedef function_by_value<not_detail::baby> op_not_;
    PSTADE_EGG_OBJECT((op_not_), not_) = { {} };


} } // namespace pstade::egg


#endif
