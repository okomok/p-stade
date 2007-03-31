#ifndef PSTADE_AUTOMATIC_HPP
#define PSTADE_AUTOMATIC_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// This couldn't support the reference type as 'To',
// because the behavior of conversion-operator template
// varies from compiler to compiler...


#include <boost/mpl/apply.hpp>
#include <boost/mpl/placeholders.hpp> // inclusion guaranteed
#include <boost/preprocessor/cat.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/fuse.hpp>
#include <pstade/nonassignable.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/unfuse.hpp>
#include <pstade/unparenthesize.hpp>


namespace pstade {


    namespace automatic_detail {


        template<class Lambda, class Arguments>
        struct temp :
            private nonassignable
        {
            explicit temp(Arguments const& args) :
                m_args(args)
            { }

            template<class To>
            operator To() const
            {
                typedef typename
                    boost::mpl::apply1<Lambda, To>::type
                fun_t;

                return fuse(fun_t())(m_args);
            }

        private:
            Arguments m_args;
        };


        template<class Lambda>
        struct base_op :
            callable<base_op<Lambda> >
        {
            template<class Myself, class Arguments>
            struct apply
            {
                typedef
                    temp<
                        Lambda,
                        // 'pass_by_value' is needless here in fact.
                        typename pass_by_value<Arguments>::type
                    > const
                type;
            };

            template<class Result, class Arguments>
            Result call(Arguments& args) const
            {
                // 'args' is destructed as soon as this 'call' returns,
                // so that 'temp' must *copy* it to 'm_args'.
                return Result(args); 
            }
        };


    } // namespace automatic_detail


    template<class Lambda>
    struct automatic :
        boost::result_of<op_unfuse(automatic_detail::base_op<Lambda>)>::type
    {
        template<class To>
        operator To() const
        {
            typedef typename
                boost::mpl::apply1<Lambda, To>::type
            fun_t;

            return fun_t()();
        }
    };


    #define PSTADE_AUTOMATIC(Object, Lambda) \
        namespace BOOST_PP_CAT(pstade_automatic_workarea_of_, Object) { \
            using namespace ::boost::mpl::placeholders; \
            typedef ::pstade::automatic<PSTADE_UNPARENTHESIZE(Lambda)> op; \
        } \
        \
        typedef BOOST_PP_CAT(pstade_automatic_workarea_of_, Object)::op BOOST_PP_CAT(op_, Object); \
        PSTADE_CONSTANT( Object, (BOOST_PP_CAT(op_, Object)) ) \
    /**/


} // namespace pstade


PSTADE_CALLABLE_NULLARY_RESULT_OF_TEMPLATE(pstade::automatic, 1)


#endif
