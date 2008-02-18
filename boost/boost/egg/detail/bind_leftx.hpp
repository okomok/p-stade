#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_DETAIL_BIND_LEFTX_HPP
#define BOOST_EGG_DETAIL_BIND_LEFTX_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// bind_leftx means bind_left2,bind_left3,...
//
// bind_left3(f, a1, a2, a3)(a4)
//   is equivalent to f(a1, a2, a3, a4).
// bind_left3(f, a1, a2, a3) returns a 1ary function object.
// The arity could be more, but not required to implement currying.


#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/egg/by_perfect.hpp>
#include <boost/egg/by_value.hpp>
#include <boost/egg/config.hpp> // BOOST_EGG_MAX_ARITY
#include <boost/egg/const.hpp>
#include <boost/egg/result_of.hpp>
#include <boost/egg/detail/pp_cat3.hpp>
#include <boost/egg/detail/pp_enum_params_with.hpp>


namespace boost { namespace egg { namespace details {


    #define BOOST_EGG_BIND_LEFTX_INIT {{}}


#define BOOST_EGG_arg(Z, N, _) BOOST_PP_CAT(Arg, N) BOOST_PP_CAT(m_arg, N);
#define BOOST_EGG_max_arity BOOST_PP_DEC(BOOST_EGG_MAX_ARITY)
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (2, BOOST_EGG_max_arity, <boost/egg/detail/bind_leftx.hpp>))
    #include BOOST_PP_ITERATE()
#undef  BOOST_EGG_max_arity
#undef  BOOST_EGG_arg


} } } // namespace boost::egg::details


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Base, BOOST_PP_ENUM_PARAMS(n, class Arg)>
    struct BOOST_EGG_PP_CAT3(little_bind_left, n, _result)
    {
        Base m_base;
        BOOST_PP_REPEAT(n, BOOST_EGG_arg, ~)

        Base const &base() const
        {
            return m_base;
        }

        template<class Me, class ArgZ>
        struct apply :
            result_of<
                Base const(BOOST_EGG_PP_ENUM_PARAMS_WITH(n, Arg, const &), ArgZ &)
            >
        { };

        template<class Re, class ArgZ>
        Re call(ArgZ &argZ) const
        {
            return m_base(BOOST_PP_ENUM_PARAMS(n, m_arg), argZ);
        }
    };


    struct BOOST_PP_CAT(little_bind_left, n)
    {
        template<class Me, class Base, BOOST_PP_ENUM_PARAMS(n, class Arg)>
        struct apply
        {
            typedef
                function<
                    BOOST_EGG_PP_CAT3(little_bind_left, n, _result)<
                        Base, BOOST_PP_ENUM_PARAMS(n, Arg)
                    >,
                    by_perfect
                >
            type;
        };

        template<class Re, class Base, BOOST_PP_ENUM_PARAMS(n, class Arg)>
        Re call(Base base, BOOST_PP_ENUM_BINARY_PARAMS(n, Arg, arg)) const
        {
            Re r = { { base, BOOST_PP_ENUM_PARAMS(n, arg) } };
            return r;
        }
    };

    typedef function<BOOST_PP_CAT(little_bind_left, n), by_value> BOOST_PP_CAT(T_bind_left, n);
    BOOST_EGG_CONST((BOOST_PP_CAT(T_bind_left, n)), BOOST_PP_CAT(bind_left, n)) = BOOST_EGG_BIND_LEFTX_INIT;


#undef  n
#endif
