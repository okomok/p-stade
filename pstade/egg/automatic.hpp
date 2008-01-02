#ifndef PSTADE_EGG_AUTOMATIC_HPP
#define PSTADE_EGG_AUTOMATIC_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
// 
// 'To x = a;' seems impossible without yet another 'function<>'.
// Use 'To x = a();' instead.


#include <boost/mpl/apply.hpp>
#include <boost/mpl/placeholders.hpp> // inclusion guaranteed
#include <pstade/boost_workaround.hpp>
#include "./by_cref.hpp"
#include "./fuse.hpp"
#include "./unfuse.hpp"

#if BOOST_WORKAROUND(__GNUC__, BOOST_TESTED_AT(4))
    #include <exception>
    #include <boost/type_traits/is_same.hpp>
    #include <pstade/enable_if.hpp>
#endif


namespace pstade { namespace egg {


    namespace automatic_detail {


        template<class Lambda, class ArgTuple>
        struct automator
        {
            ArgTuple m_args;

            template<class To>
            operator To() const
            {
                typedef typename
                    boost::mpl::apply1<Lambda, To>::type
                fun_t;

                return fuse(fun_t())(m_args);
            }
        };


        template<class Lambda, class ArgTuple>
        struct automator_ref
        {
            ArgTuple m_args;

            template<class To>
            operator To&() const
#if BOOST_WORKAROUND(__GNUC__, BOOST_TESTED_AT(4))
                // Thanks to Sergey Shandar.
                // In fact, SFINAE in exception-specification probably isn't allowed.
                throw(typename disable_if<boost::is_same<To, automator_ref const>, std::exception>::type)
#endif
            {
                typedef typename
                    boost::mpl::apply1<Lambda, To>::type
                fun_t;

                return fuse(fun_t())(m_args);
            }
        };


        template<class Lambda, template<class, class> class Automator>
        struct little_fused
        {
            template<class Myself, class ArgTuple>
            struct apply
            {
                typedef
                    Automator<Lambda, ArgTuple> const
                type;
            };

            template<class Result, class ArgTuple>
            Result call(ArgTuple& args) const
            {
                // 'automator' must *copy* it to 'm_args';
                // 'args' is destructed as soon as this 'call' returns.
                Result r = { args };
                return r;
            }
        };


        template<class Lambda, template<class, class> class Automator, class Strategy>
        struct aux :
            result_of_unfuse<
                function<little_fused<Lambda, Automator>, by_cref>,
                boost::use_default,
                use_nullary_result,
                Strategy
            >
        { };


    } // namespace automatic_detail


    template<class Lambda, class Strategy = boost::use_default>
    struct automatic :
        automatic_detail::aux<Lambda, automatic_detail::automator, Strategy>
    { };

    template<class Lambda, class Strategy = boost::use_default>
    struct automatic_ref :
        automatic_detail::aux<Lambda, automatic_detail::automator_ref, Strategy>
    { };

    #define PSTADE_EGG_AUTOMATIC \
        PSTADE_EGG_UNFUSE_L {{}} PSTADE_EGG_UNFUSE_M PSTADE_EGG_UNFUSE_DEFAULT_PACK PSTADE_EGG_UNFUSE_R
    /**/

    #define PSTADE_EGG_AUTOMATIC_REF PSTADE_EGG_AUTOMATIC


} } // namespace pstade::egg


#endif
