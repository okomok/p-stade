#ifndef PSTADE_FORWARD_HPP
#define PSTADE_FORWARD_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Works around the forwarding problem.
// You can choose:
//     pstade::forward(lambda::_1)(1); or
//     lambda::_1(1|to_reference);
//
// Also, this can add 'boost::result_of/lambda::sig' support
// by passing the extra argument, as 'lambda::ret' does.


#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include <pstade/to_type.hpp>
#include <pstade/tupled.hpp>
#include <pstade/untupled.hpp>


namespace pstade {


    namespace forward_detail {

        
        struct use_default;


        template< class Function, class Arguments >
        struct result_of_aux
        {
            typedef typename
                boost::result_of<tupled_fun(Function&)>::type
            tfun_t;

            typedef typename
                boost::result_of<tfun_t(Arguments&)>::type
            type;
        };


        template< class Result_, class Function >
        struct baby_base
        {
            template< class Myself, class Arguments >
            struct apply :
                boost::mpl::eval_if< boost::is_same<Result_, use_default>,
                    result_of_aux<Function, Arguments>,
                    boost::mpl::identity<Result_>
                >
            { };

            template< class Result, class Arguments >
            Result call(Arguments& args) const
            {
                tupled needs result_of-supporing fun!!!
                return pstade::tupled(m_fun)(args);
            }

            explicit baby_base() // DefaultConstructible iff 'Function' is.
            { }

            explicit baby_base(Function const& fun) :
                m_fun(fun)
            { }

            typedef Function base_type;

            Function const& base() const
            {
                return m_fun;
            }

        private:
            Function m_fun;
        };


        template< class Function, class TypeResult >
        struct apply_aux
        {
            typedef typename
                boost::mpl::eval_if< boost::is_same<TypeResult, void>,
                    boost::mpl::identity<use_default>,
                    to_type<TypeResult>
                >::type
            result_t;

            typedef
                egg::function<
                    baby_base<result_t, typename pass_by_value<Function>::type>
                >
            base_t;

            typedef typename
                boost::result_of<untupled_fun(base_t)>::type
            type;
        };


        struct baby
        {
            template< class Myself, class Function, class TypeResult = void >
            struct apply :
                apply_aux<Function, TypeResult>
            { };

            template< class Result, class Function, class TypeResult >
            Result call(Function& fun, TypeResult) const
            {
                typedef typename Result::base_type base_t;
                return pstade::untupled(base_t(fun));
            }

            template< class Result, class Function >
            Result call(Function& fun) const
            {
                typedef typename Result::base_type base_t;
                return pstade::untupled(base_t(fun));
            } 
        };

            
    } // namespace forward_detail


    PSTADE_EGG_FUNCTION(forward, forward_detail::baby)
    PSTADE_PIPABLE(forwarded, forward_fun)


} // namespace pstade


#endif
