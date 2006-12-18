#ifndef PSTADE_OVEN_COMPILE_HPP
#define PSTADE_OVEN_COMPILE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <limits> // numeric_limits
#include <boost/xpressive/proto/compile.hpp>
#include <boost/xpressive/proto/operators.hpp>
#include <pstade/callable.hpp>
#include <pstade/const.hpp>
#include <pstade/constant.hpp>
#include <pstade/pipable.hpp>
#include <pstade/unused.hpp>
#include "./cycle_range.hpp"
#include "./joint_range.hpp"
#include "./range_iterator.hpp"
#include "./sub_range_result.hpp"


namespace pstade { namespace oven {


    namespace compile_detail {


        namespace proto = boost::proto;


        struct oven_tag  { };
        struct state_t   { };
        struct visitor_t { };


        struct terminal_compiler
        {
            template< class Expr, class State, class Visitor >
            struct apply :
                sub_range_result<PSTADE_CONST(typename Expr::arg0_type)>
            { };

            template< class Expr, class State, class Visitor >
            static typename apply<Expr, State, Visitor>::type
            call(Expr const& expr, State const& state, Visitor& visitor)
            {
                pstade::unused(state, visitor);
                return proto::arg(expr);
            }
        };


        struct joint_compiler
        {
            template< class Expr, class State, class Visitor >
            struct apply
            {
                typedef typename Expr::arg0_type::expr_type left_type;
                typedef typename Expr::arg1_type::expr_type right_type;

                // compile the left branch
                typedef typename
                    proto::compiler<typename left_type::tag_type,  oven_tag>::template apply<left_type,  State, Visitor>::type
                left_compiled_type;

                // compile the right branch
                typedef typename
                    proto::compiler<typename right_type::tag_type, oven_tag>::template apply<right_type, State, Visitor>::type
                right_compiled_type;

                typedef
                    joint_range<left_compiled_type, right_compiled_type> const
                type;
            };

            template< class Expr, class State, class Visitor >
            static typename apply<Expr, State, Visitor>::type
            call(Expr const& expr, State const& state, Visitor& visitor)
            {
                return typename apply<Expr, State, Visitor>::type(
                    proto::compile(proto::left(expr),  state, visitor, oven_tag()),
                    proto::compile(proto::right(expr), state, visitor, oven_tag())
                );
            }
        };


        struct positive_compiler
        {
            template< class Expr, class State, class Visitor >
            struct apply
            {
                typedef typename Expr::arg0_type::expr_type expr_type;

                typedef typename
                    proto::compiler<typename expr_type::tag_type,  oven_tag>::template apply<expr_type,  State, Visitor>::type
                compiled_type;

                typedef
                    cycle_range<compiled_type, std::size_t> const
                type;
            };

            template< class Expr, class State, class Visitor >
            static typename apply<Expr, State, Visitor>::type
            call(Expr const& expr, State const& state, Visitor& visitor)
            {
                return typename apply<Expr, State, Visitor>::type(
                    proto::compile(proto::arg(expr), state, visitor, oven_tag()),
                    (std::numeric_limits<std::size_t>::max)()
                );
            }
        };


        struct op :
            callable<op>
        {
            template< class Myself, class Xpr >
            struct apply :
                // prefer 'meta' to 'boost::result_of'.
                // Boost.Proto seems not to be well ported to VC++ yet.
                proto::meta::compile<Xpr, state_t,  visitor_t, oven_tag>
            { };

            template< class Result, class Xpr >
            Result call(Xpr& xpr) const
            {
                state_t state;
                visitor_t visitor;
                return proto::compile(xpr, state, visitor, oven_tag());
            }
        };


    } // namespace compile_detail


    typedef compile_detail::op op_compile;
    PSTADE_CONSTANT(compile, (op_compile))

    PSTADE_PIPABLE(as_expr, (boost::proto::op::make_terminal))


} } // namespace pstade::oven


namespace boost { namespace proto {


    template< >
    struct compiler<tag::terminal, pstade::oven::compile_detail::oven_tag> :
        pstade::oven::compile_detail::terminal_compiler
    { };


    template< >
    struct compiler<tag::right_shift, pstade::oven::compile_detail::oven_tag> :
        pstade::oven::compile_detail::joint_compiler
    { };


    template< >
    struct compiler<tag::unary_plus, pstade::oven::compile_detail::oven_tag> :
        pstade::oven::compile_detail::positive_compiler
    { };


} } // namespace boost::proto


#endif
