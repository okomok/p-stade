#ifndef PSTADE_OVEN_UNFOLDR_HPP
#define PSTADE_OVEN_UNFOLDR_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/adapt.hpp>
#include <pstade/egg/function_facade.hpp>
#include <pstade/egg/generator.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "./detail/unfoldr_iterator.hpp"
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace unfoldr_detail {


    template< class B, class UnaryFun >
    struct base
    {
        typedef
            detail::unfoldr_iterator<
                typename pass_by_value<B>::type,
                typename pass_by_value<UnaryFun>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(B& b, UnaryFun& fun) const
        {
            return result_type(iter_t(b, fun), iter_t(fun));
        }
    };


} // namespace unfoldr_detail


typedef PSTADE_EGG_ADAPT((unfoldr_detail::base<boost::mpl::_, boost::mpl::_>)) op_unfoldr;
PSTADE_POD_CONSTANT((op_unfoldr), unfoldr) = PSTADE_EGG_ADAPT_INITIALIZER();


namespace pure_detail {


    template< class UnaryFun >
    struct result_ :
        egg::function_facade< result_<UnaryFun> >
    {
        typedef result_ is_pure;

        template< class Myself, class B >
        struct apply :
            result_of<UnaryFun const(B&)>
        { };

        template< class Result, class B >
        Result call(B& b) const
        {
            return m_f(b);
        }

        explicit result_()
        { }

        explicit result_(UnaryFun f) :
            m_f(f)
        { }

    private:
        UnaryFun m_f;        
    };


} // namespace pure_detail


typedef
    egg::generator<
        pure_detail::result_< egg::deduce<boost::mpl::_1, egg::as_value> >
    >::type
op_pure;

PSTADE_POD_CONSTANT((op_pure), pure) = PSTADE_EGG_GENERATOR_INITIALIZER();


} } // namespace pstade::oven


#endif
