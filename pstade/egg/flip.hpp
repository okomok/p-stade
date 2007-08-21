#ifndef PSTADE_EGG_FLIP_HPP
#define PSTADE_EGG_FLIP_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "./function.hpp"
#include "./generator.hpp"
#include "./use_brace_level1.hpp"


namespace pstade { namespace egg {


#if BOOST_WORKAROUND(__GNUC__, == 3)
    template<class Base>
    struct baby_flip_result
    {
        Base m_base;

        template<class Myself, class A0, class A1>
        struct apply :
            result_of<Base const(A1&, A0&)>
        { };

        template<class Result, class A0, class A1>
        Result call(A0& a0, A1& a1) const
        {
            return m_base(a1, a0);
        }
    };
#endif


    template<class BinaryBase>
    struct result_of_flip
    {
#if !BOOST_WORKAROUND(__GNUC__, == 3)
        // Keep 'baby' a template for 'generator'.
        template<class Base>
        struct baby
        {            
            Base m_base;

            template<class Myself, class A0, class A1>
            struct apply :
                result_of<Base const(A1&, A0&)>
            { };

            template<class Result, class A0, class A1>
            Result call(A0& a0, A1& a1) const
            {
                return m_base(a1, a0);
            }
        };

        typedef function< baby<BinaryBase> > type;
#else
        typedef function< baby_flip_result<BinaryBase> > type;
#endif
    };


    #define PSTADE_EGG_FLIP_L { {
    #define PSTADE_EGG_FLIP_R } }


    typedef
        generator<
            result_of_flip< deduce<boost::mpl::_1, as_value> >::type,
            use_brace_level1
        >::type
    op_flip;


    PSTADE_POD_CONSTANT((op_flip), flip) = PSTADE_EGG_GENERATOR;


} } // namespace pstade::egg


#endif
