#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_UNFUSE_RESULT_HPP
#define PSTADE_EGG_UNFUSE_RESULT_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// This could be implementedy by 'compose' with 'tuples::pack',
// but this is the basis together with 'fuse'.


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/deferred.hpp>
#include <pstade/preprocessor.hpp>
#include "./detail/config.hpp" // PSTADE_EGG_MAX_ARITY
#include "./tuple/pack.hpp"


namespace pstade { namespace egg {


    template<class Function, class Pack = tuples::op_pack>
    struct unfuse_result
    {
        Function m_function;
        Pack m_pack;

        typedef Function base_type;

        Function base() const
        {
            return m_function;
        }

        template<class Myself, PSTADE_EGG_APPLY_PARAMS(A)>
        struct apply
        { };

        // 0ary
        template<class Result>
        Result call() const
        {
            return m_function(m_pack());
        }

        // 1ary-
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_ARITY, <pstade/egg/unfuse_result.hpp>))
        #include BOOST_PP_ITERATE()
    };


} // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)> :
        boost::result_of<
            PSTADE_DEFERRED(Function const)(
                typename boost::result_of<
                    PSTADE_DEFERRED(Pack const)(PSTADE_PP_ENUM_PARAMS_WITH(n, A, &))
                >::type
            )
        >
    { };

    template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
    Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        return m_function(m_pack(BOOST_PP_ENUM_PARAMS(n, a)));
    }


#undef n
#endif
