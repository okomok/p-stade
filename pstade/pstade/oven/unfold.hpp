#ifndef PSTADE_OVEN_UNFOLD_HPP
#define PSTADE_OVEN_UNFOLD_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/deferred.hpp>
#include <pstade/egg/function_facade.hpp>
#include <pstade/egg/generator.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "./detail/unfold_iterator.hpp"
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace unfold_detail {


    template< class State, class Operate, class Next >
    struct base
    {
        typedef
            detail::unfold_iterator<
                typename pass_by_value<State>::type,
                typename pass_by_value<Operate>::type,
                typename pass_by_value<Next>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(State& init, Operate& op, Next& next) const
        {
            return result_type(
                iter_t(init, op, next, detail::begin_tag()),
                iter_t(init, op, next, detail::end_tag())
            );
        }
    };


} // namespace unfold_detail


typedef PSTADE_EGG_DEFER((unfold_detail::base<boost::mpl::_, boost::mpl::_, boost::mpl::_>)) T_unfold;
PSTADE_POD_CONSTANT((T_unfold), unfold) = PSTADE_EGG_DEFERRED;


namespace nonpure_detail {


    template< class UnaryFun >
    struct result_ :
        egg::function_facade< result_<UnaryFun> >
    {
        typedef result_ is_nonpure;

        template< class Myself, class State >
        struct apply :
            result_of<UnaryFun const(State&)>
        { };

        template< class Result, class State >
        Result call(State& s) const
        {
            return m_fun(s);
        }

        explicit result_()
        { }

        explicit result_(UnaryFun fun) :
            m_fun(fun)
        { }

    private:
        UnaryFun m_fun;        
    };


} // namespace nonpure_detail


typedef
    egg::generator<
        nonpure_detail::result_< egg::deduce<boost::mpl::_1, egg::as_value> >
    >::type
T_nonpure;

PSTADE_POD_CONSTANT((T_nonpure), nonpure) = PSTADE_EGG_GENERATOR;


} } // namespace pstade::oven


#endif
