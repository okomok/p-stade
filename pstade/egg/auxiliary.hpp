#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_AUXILIARY1_TO_HPP
#define PSTADE_EGG_AUXILIARY1_TO_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2004/n1742.pdf


#include <boost/mpl/int.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <pstade/deduced_const.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/result_of.hpp>
#include "./apply_params.hpp"
#include "./deduce.hpp"
#include "./detail/config.hpp" // PSTADE_EGG_MAX_ARITY
#include "./detail/use_brace_level1.hpp"
#include "./function.hpp"
#include "./generator.hpp"
#include "./object.hpp"
#include "./pipable.hpp"


namespace pstade { namespace egg {


    // 0ary

    template<class UnaryBase>
    struct baby_auxiliary0_result
    {
        UnaryBase m_base;

        typedef UnaryBase base_type;

        UnaryBase base() const
        {
            return m_base;
        }

    // as pipe
        typedef
            function<baby_auxiliary0_result>
        nullary_result_type;

        template<class Result>
        Result call() const
        {
            Result result = { { m_base } };
            return result;
        }

    // as function call
        template<class Myself, class A0>
        struct apply :
            result_of<UnaryBase const(A0&)>
        { };

        template<class Result, class A0>
        Result call(A0& a0) const
        {
            return m_base(a0);
        }
    };

    template<class A0, class UnaryBase> inline
    typename result_of<UnaryBase(A0&)>::type
    operator|(A0& a0, function< baby_auxiliary0_result<UnaryBase> > pi)
    {
        return pi.baby().m_base(a0);
    }

    template<class A0, class UnaryBase> inline
    typename result_of<UnaryBase(PSTADE_DEDUCED_CONST(A0)&)>::type
    operator|(A0 const& a0, function< baby_auxiliary0_result<UnaryBase> > pi)
    {
        return pi.baby().m_base(a0);
    }

    template<class UnaryBase>
    struct auxiliary0_result
    {
        typedef
            function< baby_auxiliary0_result<UnaryBase> >
        type;
    };

    #define PSTADE_EGG_AUXILIARY_RESULT_INITIALIZER(B) \
        { { B } } \
    /**/

    typedef
        generator<
            auxiliary0_result< deduce<boost::mpl::_1, as_value> >::type,
            detail::use_brace_level1
        >::type
    op_auxiliary0;

    PSTADE_EGG_OBJECT((op_auxiliary0), auxiliary0) = PSTADE_EGG_GENERATOR_INITIALIZER();


    // 1ary-

#define PSTADE_max_arity BOOST_PP_DEC(PSTADE_EGG_MAX_ARITY)
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_max_arity, <pstade/egg/auxiliary.hpp>))
    #include BOOST_PP_ITERATE()
#undef  PSTADE_max_arity


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Base>
    struct PSTADE_PP_CAT3(baby_auxiliary, n, _result)
    {
        Base m_base;

        typedef Base base_type;

        Base base() const
        {
            return m_base;
        }

        template<class Myself, PSTADE_EGG_APPLY_PARAMS(A)>
        struct apply { };

    // as pipe
        template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
        struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)> :
            result_of<
                typename result_of<op_pipable(Base const&)>::type(PSTADE_PP_ENUM_PARAMS_WITH(n, A, &))
            >
        { };    

        template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
        Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
        {
            return pipable(m_base)(BOOST_PP_ENUM_PARAMS(n, a));
        }

    // as function call
        template<class Myself, BOOST_PP_ENUM_PARAMS(BOOST_PP_INC(n), class A)>
        struct apply<Myself, BOOST_PP_ENUM_PARAMS(BOOST_PP_INC(n), A)> :
            result_of<Base const(PSTADE_PP_ENUM_PARAMS_WITH(BOOST_PP_INC(n), A, &))>
        { };    

        template<class Result, BOOST_PP_ENUM_PARAMS(BOOST_PP_INC(n), class A)>
        Result call(BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PP_INC(n), A, & a)) const
        {
            return m_base(BOOST_PP_ENUM_PARAMS(BOOST_PP_INC(n), a));
        }
    };

    template<class Base>
    struct PSTADE_PP_CAT3(auxiliary, n, _result)
    {
        typedef
            function< PSTADE_PP_CAT3(baby_auxiliary, n, _result)<Base> >
        type;
    };

    typedef
        generator<
            PSTADE_PP_CAT3(auxiliary, n, _result)< deduce<boost::mpl::_1, as_value> >::type,
            detail::use_brace_level1
        >::type
    BOOST_PP_CAT(op_auxiliary, n);

    PSTADE_EGG_OBJECT((BOOST_PP_CAT(op_auxiliary, n)), BOOST_PP_CAT(auxiliary, n)) = PSTADE_EGG_GENERATOR_INITIALIZER();


#undef n
#endif
