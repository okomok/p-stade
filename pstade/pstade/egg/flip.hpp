#ifndef PSTADE_EGG_FLIP_HPP
#define PSTADE_EGG_FLIP_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "./by_perfect.hpp"
#include "./by_value.hpp"
#include "./forward.hpp"
#include "./generator.hpp"
#include "./use_brace2.hpp"


namespace pstade { namespace egg {


    namespace flip_detail {


        template<class Base, class Strategy>
        struct little_result
        {
            Base m_base;

            template<class Myself, class A0, class A1>
            struct apply :
                result_of<Base const(A1&, A0&)>
            { };

            template<class Result, class A0, class A1>
            Result call(A0& a0, A1& a1) const
            {
                return m_base(egg::forwarding<Strategy, 2, 1>(a1), egg::forwarding<Strategy, 2, 0>(a0));
            }
        };


    } // namespace flip_detail


    template<class BinaryBase, class Strategy = by_perfect>
    struct result_of_flip
    {
        typedef function<flip_detail::little_result<BinaryBase, Strategy>, Strategy> type;
    };


    #define PSTADE_EGG_FLIP_L { {
    #define PSTADE_EGG_FLIP_R } }
    #define PSTADE_EGG_FLIP(F) PSTADE_EGG_FLIP_L F PSTADE_EGG_FLIP_R


    template<class Strategy = by_perfect>
    struct X_flip :
        generator<
            typename result_of_flip<deduce<boost::mpl::_1, as_value>, Strategy>::type,
            by_value,
            use_brace2
        >::type
    { };

    typedef X_flip<>::function_type T_flip;
    PSTADE_POD_CONSTANT((T_flip), flip) = PSTADE_EGG_GENERATOR();


} } // namespace pstade::egg


#endif
