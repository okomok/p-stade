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
#include <boost/mpl/placeholders.hpp> // inclusion guaranteed
#include <pstade/boost_workaround.hpp>
#include "./fuse.hpp"
#include "./variadic.hpp"

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
                // In fact, SFINAE in exception-specification isn't allowed.
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
        struct little
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


        template<class Lambda, class Strategy, template<class, class> class Automator>
        struct aux :
            variadic<little<Lambda, Automator>, Strategy, use_nullary_result>
        { };


    } // namespace automatic_detail


    template<class Lambda, class Strategy = boost::use_default>
    struct automatic :
        automatic_detail::aux<Lambda, Strategy, automatic_detail::automator>
    { };

    template<class Lambda, class Strategy = boost::use_default>
    struct automatic_ref :
        automatic_detail::aux<Lambda, Strategy, automatic_detail::automator_ref>
    { };

    #define PSTADE_EGG_AUTOMATIC() PSTADE_EGG_VARIADIC({})
    #define PSTADE_EGG_AUTOMATIC_REF PSTADE_EGG_AUTOMATIC


} } // namespace pstade::egg


#endif
