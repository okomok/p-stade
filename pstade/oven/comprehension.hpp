#ifndef PSTADE_OVEN_COMPREHENSION_HPP
#define PSTADE_OVEN_COMPREHENSION_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://www.cc.gatech.edu/~yannis/fc++/fcpp-lambda.pdf
//
// [x+y| x<-[1,2,3], y<-[2,3], x<y]
//     is equivalent to
// [1,2,3] `bind` (\x ->
//     [2,3] `bind` (\y ->
//         if not (x<y) then zero
//                      else unit (x+y) ))


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/function_facade.hpp>
#include <pstade/egg/lambda/bind.hpp>
#include <pstade/egg/lambda/placeholders.hpp>
#include <pstade/egg/lambda/unlambda.hpp>
#include <pstade/egg/envelope.hpp>
#include <pstade/egg/generator.hpp>
#include <pstade/dont_care.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include <pstade/result_of_lambda.hpp>
#include "./detail/monad.hpp"
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace comprehension_detail {


    // Note that 'nested' is always regularized by 'monad_bind'.

    template< class MakeRange, class Function >
    struct nested :
        egg::function_facade< nested<MakeRange, Function> >
    {
        template< class Myself, class Value1, class Value2 = void >
        struct apply :
            result_of<
                detail::op_monad_bind(
                    typename result_of<MakeRange const(Value1&, Value2&)>::type,
                    typename result_of<
                        egg::op_lambda_bind(
                            typename result_of<egg::op_lambda_unlambda(Function const&)>::type,
                            Value1&,
                            Value2&,
                            egg::op_lambda_1 const&
                        )
                    >::type
                )
            >
        { };

        template< class Result, class Value1, class Value2 >
        Result call(Value1& v1, Value2& v2) const
        {
            return detail::monad_bind(
                m_makeRng(v1, v2),
                egg::lambda_bind(
                    egg::lambda_unlambda(m_fun),
                    v1,
                    v2,
                    egg::lambda_1
                )
            );
        }

        template< class Myself, class Value1 >
        struct apply<Myself, Value1> :
            result_of<
                detail::op_monad_bind(
                    typename result_of<MakeRange const(Value1&)>::type,
                    typename result_of<
                        egg::op_lambda_bind(
                            typename result_of<egg::op_lambda_unlambda(Function const&)>::type,
                            Value1&,
                            egg::op_lambda_1 const&
                        )
                    >::type
                )
            >
        { };

        template< class Result, class Value1 >
        Result call(Value1& v1) const
        {
            return detail::monad_bind(
                m_makeRng(v1),
                egg::lambda_bind(
                    egg::lambda_unlambda(m_fun),
                    v1,
                    egg::lambda_1
                )
            );
        }

        nested(MakeRange makeRng, Function fun) :
            m_makeRng(makeRng), m_fun(fun)
        { }

    private:
        MakeRange m_makeRng;
        Function m_fun;
    };

    typedef
        egg::generator<
            nested< egg::deduce<boost::mpl::_1, egg::as_value>, egg::deduce<boost::mpl::_2, egg::as_value> >
        >::type
    op_make_nested;

    PSTADE_POD_CONSTANT((op_make_nested), make_nested) = PSTADE_EGG_GENERATOR_TYPE();


    template< class Expr, class Guard >
    struct to_unit :
        egg::function_facade< to_unit<Expr, Guard> >
    {
        template< class Myself, class Value1, class Value2 = void, class Value3 = void >
        struct apply :
            result_of<
                detail::op_monad_unit(typename result_of<Expr const(Value1&, Value2&, Value3&)>::type)
            >
        { };

        template< class Result, class Value1, class Value2, class Value3 >
        Result call(Value1& v1, Value2& v2, Value3& v3) const
        {
            typedef typename result_of<Expr const(Value1&, Value2&, Value3&)>::type val_t;

            if (m_guard(v1, v2, v3))
                return detail::monad_unit(m_expr(v1, v2, v3));
            else
                return detail::xp_monad_zero<val_t>()();
        }

        template< class Myself, class Value1, class Value2 >
        struct apply<Myself, Value1, Value2> :
            result_of<
                detail::op_monad_unit(typename result_of<Expr const(Value1&, Value2&)>::type)
            >
        { };

        template< class Result, class Value1, class Value2 >
        Result call(Value1& v1, Value2& v2) const
        {
            typedef typename result_of<Expr const(Value1&, Value2&)>::type val_t;

            if (m_guard(v1, v2))
                return detail::monad_unit(m_expr(v1, v2));
            else
                return detail::xp_monad_zero<val_t>()();
        }

        template< class Myself, class Value1 >
        struct apply<Myself, Value1> :
            result_of<
                detail::op_monad_unit(typename result_of<Expr const(Value1&)>::type)
            >
        { };

        template< class Result, class Value1 >
        Result call(Value1& v1) const
        {
            typedef typename result_of<Expr const(Value1&)>::type val_t;

            if (m_guard(v1))
                return detail::monad_unit(m_expr(v1));
            else
                return detail::xp_monad_zero<val_t>()();
        }

        to_unit(Expr expr, Guard guard) :
            m_expr(expr), m_guard(guard)
        { }

    private:
        Expr m_expr;
        Guard m_guard;
    };

    typedef
        egg::generator<
            to_unit< egg::deduce<boost::mpl::_1, egg::as_value>, egg::deduce<boost::mpl::_2, egg::as_value> >
        >::type
    op_make_to_unit;

    PSTADE_POD_CONSTANT((op_make_to_unit), make_to_unit) = PSTADE_EGG_GENERATOR_TYPE();


    struct baby
    {
        template< class Myself, class Expr, class Guard, class MakeRange1, class MakeRange2 = void, class MakeRange3 = void >
        struct apply :
            result_of<
                detail::op_monad_bind(
                    typename result_of<MakeRange1()>::type,
                    typename result_of<
                        op_make_nested(
                            MakeRange2&,
                            typename result_of<
                                op_make_nested(
                                    MakeRange3&,
                                    typename result_of<op_make_to_unit(Expr&, Guard&)>::type
                                )
                            >::type
                        )
                    >::type
                )
            >
        { };

        template< class Result, class Expr, class Guard, class MakeRange1, class MakeRange2, class MakeRange3 >
        Result call(Expr& expr, Guard& guard, MakeRange1& makeRng1, MakeRange2& makeRng2, MakeRange3& makeRng3) const
        {
            return detail::monad_bind(
                makeRng1(),
                make_nested(
                    makeRng2,
                    make_nested(
                        makeRng3,
                        make_to_unit(expr, guard) // 3ary
                    ) // 2ary
                ) // 1ary
            );
        }

        template< class Myself, class Expr, class Guard, class MakeRange1, class MakeRange2 >
        struct apply<Myself, Expr, Guard, MakeRange1, MakeRange2> :
            result_of<
                detail::op_monad_bind(
                    typename result_of<MakeRange1()>::type,
                    typename result_of<
                        op_make_nested(
                            MakeRange2&,
                            typename result_of<op_make_to_unit(Expr&, Guard&)>::type
                        )
                    >::type
                )
            >
        { };

        template< class Result, class Expr, class Guard, class MakeRange1, class MakeRange2 >
        Result call(Expr& expr, Guard& guard, MakeRange1& makeRng1, MakeRange2& makeRng2) const
        {
            return detail::monad_bind(
                makeRng1(),
                make_nested(
                    makeRng2,
                    make_to_unit(expr, guard) // 2ary
                ) // 1ary
            );
        }

        template< class Myself, class Expr, class Guard, class MakeRange1 >
        struct apply<Myself, Expr, Guard, MakeRange1> :
            result_of<
                detail::op_monad_bind(
                    typename result_of<MakeRange1()>::type,
                    typename result_of<op_make_to_unit(Expr&, Guard&)>::type
                )
            >
        { };

        template< class Result, class Expr, class Guard, class MakeRange1 >
        Result call(Expr& expr, Guard& guard, MakeRange1& makeRng1) const
        {
            return detail::monad_bind(
                makeRng1(),
                make_to_unit(expr, guard) // 1ary
            );
        }
    };


} // namespace comprehension_detail


typedef egg::function<comprehension_detail::baby> op_comprehension;
PSTADE_POD_CONSTANT((op_comprehension), comprehension) = {{}};


// always_return
//

namespace always_return_detail {


    template< class Value >
    struct result_
    {
        typedef Value result_type;

        Value operator()(dont_care = 0, dont_care = 0, dont_care = 0) const
        {
            return m_value;
        }

        explicit result_(Value const& v) :
            m_value(v)
        { }

        template< class Iterator >
        result_(Iterator first, Iterator last) :
            m_value(first, last)
        { }

    private:
        Value m_value;
    };


    struct baby
    {
        template< class Myself, class Range >
        struct apply
        {
            typedef
                // Hold by value to avoid dangling.
                result_<typename iter_range_of<Range>::type>
            type;
        };

        template< class Result, class X >
        Result call(X& x) const
        {
            return call_aux(x, egg::envelope<Result>());
        }

        template< class Result, class Range >
        Result call_aux(Range& rng, egg::envelope<Result>) const
        {
            // If 'rng' is 'initial_values(..)',
            // neither copy-initialization nor direct-initialization doesn't work;
            //   copy-initialization => 'copy_range' to iter_range is impossible.
            //   direct-initialization => ambiguous: template constructor vs conversion-operator.
            return Result(boost::begin(rng), boost::end(rng));
        }

        template< class Myself >
        struct apply<Myself, bool>
        {
            typedef
                result_<bool>
            type;
        };

        template< class Myself >
        struct apply<Myself, bool const>
        {
            typedef
                result_<bool>
            type;
        };

        template< class Result >
        Result call_aux(bool b, egg::envelope<Result>) const
        {
            return Result(b);
        }
    };


} // namespace always_return_detail


typedef egg::function<always_return_detail::baby> op_always_return;
PSTADE_POD_CONSTANT((op_always_return), always_return) = {{}};


} } // namespace pstade::oven


#endif
