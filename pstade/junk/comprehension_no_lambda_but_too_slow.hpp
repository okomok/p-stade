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
#include <pstade/egg/compose2.hpp>
#include <pstade/egg/curry.hpp>
#include <pstade/egg/envelope.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/function_facade.hpp>
#include <pstade/egg/generator.hpp>
#include <pstade/egg/uncurry.hpp>
#include <pstade/dont_care.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include <pstade/result_of_lambda.hpp>
#include "./detail/monad.hpp"
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace comprehension_detail {


    template< class Expr, class Guard >
    struct unit_expr :
        egg::function_facade< unit_expr<Expr, Guard> >
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

        unit_expr(Expr expr, Guard guard) :
            m_expr(expr), m_guard(guard)
        { }

    private:
        Expr m_expr;
        Guard m_guard;
    };

    typedef
        egg::generator<
            unit_expr< egg::deduce<boost::mpl::_1, egg::as_value>, egg::deduce<boost::mpl::_2, egg::as_value> >
        >::type
    op_make_unit_expr;

    PSTADE_POD_CONSTANT((op_make_unit_expr), make_unit_expr) = PSTADE_EGG_GENERATOR;


    struct baby
    {
        template< class UnitExpr, class GenRange1 >
        struct result_of_aux1 :
            result_of<
                detail::op_monad_bind(typename result_of<GenRange1()>::type, UnitExpr)
            >
        { };

        template< class UnitExpr, class GenRange1, class GenRange2 >
        struct result_of_aux2 :
            result_of_aux1<
                typename result_of<
                    egg::op_compose2(detail::op_monad_bind, GenRange2, typename result_of<egg::op_curry2(UnitExpr)>::type)
                >::type,
                GenRange1
            >
        { };

        template< class UnitExpr, class GenRange1, class GenRange2, class GenRange3 >
        struct result_of_aux3 :
            result_of_aux2<
                typename result_of<
                    egg::op_compose2(detail::op_monad_bind, GenRange3, typename result_of<egg::op_uncurry(typename result_of<egg::op_curry3(UnitExpr)>::type)>::type)
                >::type,
                GenRange1, GenRange2
            >
        { };

        template< class Myself, class Expr, class Guard, class GenRange1, class GenRange2 = void, class GenRange3 = void >
        struct apply :
            result_of_aux3<
                typename result_of<op_make_unit_expr(Expr&, Guard&)>::type,
                GenRange1, GenRange2, GenRange3
            >
        { };

        template< class Result, class Expr, class Guard, class GenRange1, class GenRange2, class GenRange3 >
        Result call(Expr& expr, Guard& guard, GenRange1& genRng1, GenRange2& genRng2, GenRange3& genRng3) const
        {
            // monad_bind(genRng1(), \x ->
            //     monad_bind(genRng2(x), \y ->
            //         monad_bind(genRng3(y), \z ->
            //             make_unit_expr(expr, guard)(x, y, z) ) ) )

            return detail::monad_bind(
                genRng1(),
                egg::compose2(
                    detail::monad_bind,
                    genRng2,
                    egg::curry2(

                        egg::compose2(
                            detail::monad_bind,
                            genRng3,
                            egg::uncurry(egg::curry3(make_unit_expr(expr, guard)))
                        )

                    )
                )
            );
        }

        template< class Myself, class Expr, class Guard, class GenRange1, class GenRange2 >
        struct apply<Myself, Expr, Guard, GenRange1, GenRange2> :
            result_of_aux2<
                typename result_of<op_make_unit_expr(Expr&, Guard&)>::type,
                GenRange1, GenRange2
            >
        { };

        template< class Result, class Expr, class Guard, class GenRange1, class GenRange2 >
        Result call(Expr& expr, Guard& guard, GenRange1& genRng1, GenRange2& genRng2) const
        {
            // monad_bind(genRng1(), \x ->
            //     monad_bind(genRng2(x), \y ->
            //         make_unit_expr(expr, guard)(x, y) ) )

            return detail::monad_bind(
                genRng1(),

                egg::compose2(
                    detail::monad_bind,
                    genRng2,
                    egg::curry2(make_unit_expr(expr, guard))
                )

            );
        }

        template< class Myself, class Expr, class Guard, class GenRange1 >
        struct apply<Myself, Expr, Guard, GenRange1> :
            result_of_aux1<
                typename result_of<op_make_unit_expr(Expr&, Guard&)>::type,
                GenRange1
            >
        { };

        template< class Result, class Expr, class Guard, class GenRange1 >
        Result call(Expr& expr, Guard& guard, GenRange1& genRng1) const
        {
            return detail::monad_bind(
                genRng1(),
                make_unit_expr(expr, guard) // 1ary
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
