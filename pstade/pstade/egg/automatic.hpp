#ifndef PSTADE_EGG_AUTOMATIC_HPP
#define PSTADE_EGG_AUTOMATIC_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
// 
// 'To x = a;' seems impossible without yet another 'function<>'.
// Use 'To x = a();' instead.


#include <boost/mpl/apply.hpp>
#include <pstade/boost_workaround.hpp>
#include <pstade/result_of.hpp>
#include "./detail/default_pack.hpp"
#include "./detail/mpl_placeholders.hpp" // inclusion guaranteed
#include "./fuse.hpp"
#include "./variadic.hpp"

#if BOOST_WORKAROUND(__GNUC__, BOOST_TESTED_AT(4))
    #include <exception>
    #include <boost/type_traits/is_same.hpp>
    #include <pstade/enable_if.hpp>
#endif


namespace pstade { namespace egg {


    namespace automatic_detail {


        template<class Lambda, class Strategy, class Args>
        struct from
        {
            Args m_args;

            template<class To>
            To get() const
            {
                typedef typename
                    boost::mpl::apply2<Lambda, To, Strategy>::type
                fun_t;

                return fuse(fun_t())(m_args);
            }

            template<class To>
            operator To() const
            {
                return get<To>();
            }
        };


        template<class Lambda, class Strategy, class Args>
        struct ref_from
        {
            Args m_args;

            template<class To>
            To get() const
            {
                typedef typename
                    boost::mpl::apply2<Lambda, To, Strategy>::type
                fun_t;

                return fuse(fun_t())(m_args);
            }

            template<class To>
            operator To&() const
#if BOOST_WORKAROUND(__GNUC__, BOOST_TESTED_AT(4))
                // Thanks to Sergey Shandar.
                // In fact, SFINAE in exception-specification isn't allowed.
                throw(typename disable_if<boost::is_same<To, ref_from const>, std::exception>::type)
#endif
            {
                return get<To&>();
            }
        };


        template<class Lambda, class Strategy, template<class, class, class> class From>
        struct little
        {
            template<class Myself, class Args>
            struct apply
            {
                typedef 
                    From<
                        Lambda, Strategy,
                        typename result_of<
                            typename result_of<T_fuse(PSTADE_EGG_DEFAULT_PACK<Strategy>)>::type(Args&)
                        >::type
                    >
                type;
            };

            template<class Result, class Args>
            Result call(Args& args) const
            {
                Result r = { fuse(PSTADE_EGG_DEFAULT_PACK<Strategy>())(args) };
                return r;
            }
        };


        template<class Lambda, class Strategy, template<class, class, class> class From>
        struct aux_ :
            variadic<little<Lambda, Strategy, From>, Strategy, use_nullary_result>
        { };


   } // namespace automatic_detail


    template<class Lambda, class Strategy = boost::use_default>
    struct automatic :
        automatic_detail::aux_<Lambda, Strategy, automatic_detail::from>
    { };

    template<class Lambda, class Strategy = boost::use_default>
    struct automatic_ref :
        automatic_detail::aux_<Lambda, Strategy, automatic_detail::ref_from>
    { };

    #define PSTADE_EGG_AUTOMATIC() PSTADE_EGG_VARIADIC({})
    #define PSTADE_EGG_AUTOMATIC_REF PSTADE_EGG_AUTOMATIC


} } // namespace pstade::egg


#endif
