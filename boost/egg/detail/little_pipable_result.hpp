#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_DETAIL_LITTLE_PIPABLE_RESULT_HPP
#define BOOST_EGG_DETAIL_LITTLE_PIPABLE_RESULT_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/egg/apply_decl.hpp>
#include <boost/egg/by_ref.hpp>
#include <boost/egg/config.hpp> // BOOST_EGG_MAX_LINEAR_ARITY
#include <boost/egg/function_fwd.hpp>
#include <boost/egg/pack.hpp>
#include <boost/egg/preprocessor/enum_params_with.hpp>
#include <boost/egg/result_of.hpp>
#include <boost/egg/detail/deduced_const.hpp>
#include <boost/egg/detail/enable_if.hpp>
#include <boost/egg/detail/is_a_or_b.hpp>
#include <boost/egg/detail/tuple_fuse.hpp>
#include <boost/egg/detail/tuple_prepend.hpp>


#define BOOST_EGG_PIPABLE_MAX_ARITY \
    BOOST_PP_DEC(BOOST_EGG_MAX_LINEAR_ARITY) \
/**/


namespace boost { namespace egg { namespace details {


namespace pipable_operators {


    namespace here = pipable_operators;


    typedef X_tuple_prepend<by_ref> S_tuple_prepend;


    template<class O, class Base, class Args>
    struct result_of_output :
        result_of_<
            typename result_of_<
                T_tuple_fuse(Base const &)
            >::type(typename result_of_<S_tuple_prepend(Args const &, O &)>::type)
        >
    { };


    // Fortunately, tuples::null_type is a POD type.

    template<class Base, class Strategy, class OperandBytag, class Args = tuples::null_type>
    struct little_pipable_result
    {
        typedef X_pack<Strategy> S_pack;

        Base m_base;
        Args m_args;

        Base const &base() const
        {
            return m_base;
        }

        template<class O>
        typename result_of_output<O, Base, Args>::type
        output(O &o) const
        {
            return tuple_fuse(m_base)(S_tuple_prepend()(m_args, o));
        }

        template<class Args_>
        struct function_with
        {
            typedef
                function<little_pipable_result<Base, Strategy, OperandBytag, Args_>, Strategy>
            type;
        };

    // 0ary
        typedef typename
            function_with<tuples::null_type>::type
        nullary_result_type;

        template<class Re>
        Re call() const
        {
            Re r = { { m_base, {} } };
            return r;
        }

    // 1ary-
        template<class Me, BOOST_EGG_APPLY_DECL_PARAMS(BOOST_EGG_PIPABLE_MAX_ARITY, A)>
        struct BOOST_EGG_APPLY_DECL;

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_EGG_PIPABLE_MAX_ARITY, <boost/egg/detail/little_pipable_result.hpp>))
        #include BOOST_PP_ITERATE()
    };


    struct lookup_pipable_operator { };


    // operator|
    //

    template<class O, class Base, class Strategy, class OperandBytag, class Args> inline
    typename lazy_enable_if_< is_a_or_b<OperandBytag, by_perfect, by_ref>, result_of_output<O, Base, Args> >::type
    operator|(O &o, function<little_pipable_result<Base, Strategy, OperandBytag, Args>, Strategy> const &pi)
    {
        return pi.little().output(o);
    }

    template<class O, class Base, class Strategy, class OperandBytag, class Args> inline
    typename lazy_enable_if_< is_a_or_b<OperandBytag, by_perfect, by_cref>, result_of_output<BOOST_EGG_DEDUCED_CONST(O), Base, Args> >::type
    operator|(O const &o, function<little_pipable_result<Base, Strategy, OperandBytag, Args>, Strategy> const &pi)
    {
        return pi.little().output(o);
    }

    template<class O, class Base, class Strategy, class OperandBytag, class Args> inline
    typename lazy_enable_if_< is_same<OperandBytag, by_value>, result_of_output<O, Base, Args> >::type
    operator|(O o, function<little_pipable_result<Base, Strategy, OperandBytag, Args>, Strategy> const &pi)
    {
        // For movable types, we can't turn `o` into const-reference.
        return pi.little().output(o);
    }


    // operater|=
    //

    template<class O, class Base, class Strategy, class OperandBytag, class Args> inline
    typename lazy_enable_if_< is_a_or_b<OperandBytag, by_perfect, by_ref>, result_of_output<O, Base, Args> >::type
    operator|=(function<little_pipable_result<Base, Strategy, OperandBytag, Args>, Strategy> const &pi, O &o)
    {
        return pi.little().output(o);
    }

    template<class O, class Base, class Strategy, class OperandBytag, class Args> inline
    typename lazy_enable_if_< is_a_or_b<OperandBytag, by_perfect, by_cref>, result_of_output<BOOST_EGG_DEDUCED_CONST(O), Base, Args> >::type
    operator|=(function<little_pipable_result<Base, Strategy, OperandBytag, Args>, Strategy> const &pi, O const &o)
    {
        return pi.little().output(o);
    }

    template<class O, class Base, class Strategy, class OperandBytag, class Args> inline
    typename lazy_enable_if_< is_same<OperandBytag, by_value>, result_of_output<O, Base, Args> >::type
    operator|=(function<little_pipable_result<Base, Strategy, OperandBytag, Args>, Strategy> const &pi, O o)
    {
        return pi.little().output(o);
    }


} // namespace pipable_operators


    using pipable_operators::little_pipable_result;
    using pipable_operators::lookup_pipable_operator;


} } } // namespace boost::egg::details


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Me, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Me, BOOST_PP_ENUM_PARAMS(n, A)> :
        function_with<
            typename result_of_<S_pack(BOOST_EGG_PP_ENUM_PARAMS_WITH(n, A, &))>::type
        >
    { };

    template<class Re, BOOST_PP_ENUM_PARAMS(n, class A)>
    Re call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, &a)) const
    {
        Re r = { { m_base, S_pack()(BOOST_PP_ENUM_PARAMS(n, a)) } };
        return r;
    }


#undef  n
#endif
