#ifndef PSTADE_OVEN_COMPILE_HPP
#define PSTADE_OVEN_COMPILE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Pending...
//


// Note:
//
// Ranges are always copied.
// The inifinite number class seems required.


#include <limits> // numeric_limits
#include <boost/config.hpp> // BOOST_NESTED_TEMPLATE
#include <boost/xpressive/proto/compile.hpp>
#include <boost/xpressive/proto/operators.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/deduced_const.hpp>
#include <pstade/pipable.hpp>
#include <pstade/unused.hpp>
#include "./cycle_range.hpp"
#include "./joint_range.hpp"
#include "./range_iterator.hpp"
#include "./sub_range_result.hpp"


namespace pstade { namespace oven {


    namespace compile_detail {


        template< class Derived >
        struct compiler
        {
        private:
            template< class Expr, class State, class Visitor >
            struct apply_aux :
                Derived::BOOST_NESTED_TEMPLATE apply<Expr, State, Visitor>
            { };

        public:
            template< class Expr, class State, class Visitor >
            static typename apply_aux<Expr, State, Visitor>::type
            call(Expr const& expr, State const& state, Visitor& visitor)
            {
                return Derived().BOOST_NESTED_TEMPLATE call_<
                    typename apply_aux<Expr, State, Visitor>::type
                >(expr, state, visitor);
            }
        };


        namespace proto = boost::proto;


        struct oven_tag  { };
        struct state_t   { };
        struct visitor_t { };


        struct terminal_compiler :
            compiler<terminal_compiler>
        {
            template< class Expr, class State, class Visitor >
            struct apply :
                sub_range_result<PSTADE_DEDUCED_CONST(typename Expr::arg0_type)>
            { };

            template< class Result, class Expr, class State, class Visitor >
            Result call_(Expr const& expr, State const& state, Visitor& visitor)
            {
                pstade::unused(state, visitor);
                return proto::arg(expr);
            }
        };


        struct joint_compiler :
            compiler<joint_compiler>
        {
            template< class Expr, class State, class Visitor >
            struct apply
            {
                typedef typename Expr::arg0_type::expr_type left_type;
                typedef typename Expr::arg1_type::expr_type right_type;

                // compile the left branch
                typedef typename
                    proto::compiler<typename left_type::tag_type,  oven_tag>::BOOST_NESTED_TEMPLATE apply<left_type,  State, Visitor>::type
                left_compiled_type;

                // compile the right branch
                typedef typename
                    proto::compiler<typename right_type::tag_type, oven_tag>::BOOST_NESTED_TEMPLATE apply<right_type, State, Visitor>::type
                right_compiled_type;

                typedef
                    joint_range<left_compiled_type, right_compiled_type> const
                type;
            };

            template< class Result, class Expr, class State, class Visitor >
            Result call_(Expr const& expr, State const& state, Visitor& visitor)
            {
                return Result(
                    proto::compile(proto::left(expr),  state, visitor, oven_tag()),
                    proto::compile(proto::right(expr), state, visitor, oven_tag())
                );
            }
        };


        struct positive_compiler :
            compiler<positive_compiler>
        {
            template< class Expr, class State, class Visitor >
            struct apply
            {
                typedef typename Expr::arg0_type::expr_type expr_type;

                typedef typename
                    proto::compiler<typename expr_type::tag_type,  oven_tag>::BOOST_NESTED_TEMPLATE apply<expr_type,  State, Visitor>::type
                compiled_type;

                typedef
                    cycle_range<compiled_type, std::size_t> const
                type;
            };

            template< class Result, class Expr, class State, class Visitor >
            Result call_(Expr const& expr, State const& state, Visitor& visitor)
            {
                return Result(
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

    PSTADE_PIPABLE(as_term, (boost::proto::op::make_terminal))


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
