#ifndef BOOST_EGG_IMPLICIT_HPP
#define BOOST_EGG_IMPLICIT_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
// 
// 'To x = a;' seems impossible without yet another forwarding.
// Use 'To x = a();' instead.


#include <boost/mpl/apply.hpp>
#include <boost/mpl/placeholders.hpp> // inclusion guaranteed
#include <boost/egg/detail/boost_workaround.hpp>
#include <boost/egg/detail/tuple_fuse.hpp>
#include <boost/egg/pack.hpp>
#include <boost/egg/result_of.hpp>
#include <boost/egg/variadic.hpp>

#if BOOST_WORKAROUND(__GNUC__, BOOST_TESTED_AT(4))
    #include <exception>
    #include <boost/type_traits/is_same.hpp>
    #include <boost/egg/detail/enable_if.hpp>
#endif


namespace boost { namespace egg {


    namespace implicit_detail {


        template<class Expr, class Strategy, class Args>
        struct from
        {
            Args m_args;

            template<class To>
            To get() const
            {
                typedef typename
                    mpl::apply2<Expr, To, Strategy>::type
                fun_t;

                return details::tuple_fuse(fun_t())(m_args);
            }

            template<class To>
            operator To() const
            {
                return get<To>();
            }
        };


        template<class Expr, class Strategy, class Args>
        struct ref_from
        {
            Args m_args;

            template<class To>
            To &get() const
            {
                typedef typename
                    mpl::apply2<Expr, To, Strategy>::type
                fun_t;

                return details::tuple_fuse(fun_t())(m_args);
            }

            template<class To>
            operator To &() const
#if BOOST_WORKAROUND(__GNUC__, BOOST_TESTED_AT(4))
                // Thanks to Sergey Shandar.
                // In fact, SFINAE in exception-specification isn't allowed.
                throw(typename details::disable_if<is_same<To, ref_from const>, std::exception>::type)
#endif
            {
                return get<To>();
            }
        };


        template<class Expr, class Strategy, template<class, class, class> class From>
        struct little
        {
            template<class Me, class Args>
            struct apply
            {
                typedef 
                    From<
                        Expr, Strategy,
                        typename result_of<
                            typename result_of<details::T_tuple_fuse(X_pack<Strategy>)>::type(Args &)
                        >::type
                    > const
                type;
            };

            template<class Re, class Args>
            Re call(Args &args) const
            {
                Re r = { details::tuple_fuse(X_pack<Strategy>())(args) };
                return r;
            }
        };


        template<class Expr, class Strategy, template<class, class, class> class From>
        struct aux_ :
            variadic<
                little<Expr, Strategy, From>,
                Strategy,
                use_default,
                use_nullary_result
            >
        { };


   } // namespace implicit_detail


    template<class Expr, class Strategy = use_default>
    struct implicit :
        implicit_detail::aux_<Expr, Strategy, implicit_detail::from>
    { };

    template<class Expr, class Strategy = use_default>
    struct implicit_ref :
        implicit_detail::aux_<Expr, Strategy, implicit_detail::ref_from>
    { };

    #define BOOST_EGG_IMPLICIT() BOOST_EGG_VARIADIC({})
    #define BOOST_EGG_IMPLICIT_REF BOOST_EGG_IMPLICIT


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
