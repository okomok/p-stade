#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_AUXILIARY_HPP
#define PSTADE_EGG_AUXILIARY_HPP
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
#include <boost/utility/result_of.hpp>
#include <pstade/deduced_const.hpp>
#include <pstade/deferred.hpp>
#include <pstade/preprocessor.hpp>
#include "./apply_params.hpp"
#include "./aggregate1.hpp"
#include "./baby/generator.hpp"
#include "./deduce.hpp"
#include "./detail/config.hpp" // PSTADE_EGG_MAX_ARITY
#include "./function.hpp"
#include "./object.hpp"
#include "./pipable.hpp"


namespace pstade { namespace egg {


    // 0ary

    template<class UnaryBase>
    struct baby_auxiliary_result0
    {
        UnaryBase m_base;

        typedef UnaryBase base_type;

        UnaryBase base() const
        {
            return m_base;
        }

    // as pipe
        typedef
            function<baby_auxiliary_result0>
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
            boost::result_of<PSTADE_DEFERRED(UnaryBase const)(A0&)>
        { };

        template<class Result, class A0>
        Result call(A0& a0) const
        {
            return m_base(a0);
        }
    };

    template<class A0, class UnaryBase> inline
    typename boost::result_of<UnaryBase(A0&)>::type
    operator|(A0& a0, function< baby_auxiliary_result0<UnaryBase> > pi)
    {
        return pi.baby().m_base(a0);
    }

    template<class A0, class UnaryBase> inline
    typename boost::result_of<UnaryBase(PSTADE_DEDUCED_CONST(A0)&)>::type
    operator|(A0 const& a0, function< baby_auxiliary_result0<UnaryBase> > pi)
    {
        return pi.baby().m_base(a0);
    }

    typedef
        function<
            baby::generator<
                function<
                    baby_auxiliary_result0< deduce<boost::mpl::_1, as_value> >
                >,
                aggregate1
            >
        >
    op_auxiliary0;

    PSTADE_EGG_OBJECT((op_auxiliary0), auxiliary0) = { {} };


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
    struct BOOST_PP_CAT(baby_auxiliary_result, n)
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
            boost::result_of<
                typename boost::result_of<op_pipable(Base const&)>::type(
                    PSTADE_PP_ENUM_PARAMS_WITH(n, A, &)
                )
            >
        { };    

        template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
        Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
        {
            return pipable(m_base)(
                BOOST_PP_ENUM_PARAMS(n, a)
            );
        }

    // as function call
        template<class Myself, BOOST_PP_ENUM_PARAMS(BOOST_PP_INC(n), class A)>
        struct apply<Myself, BOOST_PP_ENUM_PARAMS(BOOST_PP_INC(n), A)> :
            boost::result_of<
                PSTADE_DEFERRED(Base const)(PSTADE_PP_ENUM_PARAMS_WITH(BOOST_PP_INC(n), A, &))
            >
        { };    

        template<class Result, BOOST_PP_ENUM_PARAMS(BOOST_PP_INC(n), class A)>
        Result call(BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PP_INC(n), A, & a)) const
        {
            return m_base(BOOST_PP_ENUM_PARAMS(BOOST_PP_INC(n), a));
        }
    };

    typedef
        function<
            baby::generator<
                function<
                    BOOST_PP_CAT(baby_auxiliary_result, n)< deduce<boost::mpl::_1, as_value> >
                >,
                aggregate1
            >
        >
    BOOST_PP_CAT(op_auxiliary, n);

    PSTADE_EGG_OBJECT((BOOST_PP_CAT(op_auxiliary, n)), BOOST_PP_CAT(auxiliary, n)) = { {} };


#undef n
#endif
