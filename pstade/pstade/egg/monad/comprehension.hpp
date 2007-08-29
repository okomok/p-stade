#ifndef PSTADE_EGG_MONAD_OPTIONAL_HPP
#define PSTADE_EGG_MONAD_OPTIONAL_HPP
#include "../detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./core.hpp"


namespace pstade { namespace egg {


    namespace comprehension_detail {


       template<class Expr, class Guard>
        struct unit_expr :
            egg::function_facade< unit_expr<Expr, Guard> >
        {
            template<class Myself, class Value1, class Value2 = void, class Value3 = void>
            struct apply :
                result_of<
                    op_monad_return(typename result_of<Expr const(Value1&, Value2&, Value3&)>::type)
                >
            { };

            template<class Result, class Value1, class Value2, class Value3>
            Result call(Value1& v1, Value2& v2, Value3& v3) const
            {
                typedef typename result_of<Expr const(Value1&, Value2&, Value3&)>::type val_t;

                if (m_guard(v1, v2, v3))
                    return monad_return(m_expr(v1, v2, v3));
                else
                    return xp_monad_zero<val_t>()();
            }

            template<class Myself, class Value1, class Value2>
            struct apply<Myself, Value1, Value2> :
                result_of<
                    op_monad_return(typename result_of<Expr const(Value1&, Value2&)>::type)
                >
            { };

            template<class Result, class Value1, class Value2>
            Result call(Value1& v1, Value2& v2) const
            {
                typedef typename result_of<Expr const(Value1&, Value2&)>::type val_t;

                if (m_guard(v1, v2))
                    return monad_return(m_expr(v1, v2));
                else
                    return xp_monad_zero<val_t>()();
            }

            template<class Myself, class Value1>
            struct apply<Myself, Value1> :
                result_of<
                    op_monad_return(typename result_of<Expr const(Value1&)>::type)
                >
            { };

            template<class Result, class Value1>
            Result call(Value1& v1) const
            {
                typedef typename result_of<Expr const(Value1&)>::type val_t;

                if (m_guard(v1))
                    return monad_return(m_expr(v1));
                else
                    return xp_monad_zero<val_t>()();
            }

            unit_expr(Expr expr, Guard guard) :
                m_expr(expr), m_guard(guard)
            { }

        private:
            Expr m_expr;
            Guard m_guard;
        };

        typedef
            generator<
                unit_expr< deduce<boost::mpl::_1, as_value>, deduce<boost::mpl::_2, as_value> >
            >::type
        op_make_unit_expr;

        PSTADE_POD_CONSTANT((op_make_unit_expr), make_unit_expr) = PSTADE_EGG_GENERATOR;


        struct baby_nested_bind
        {
            template<class Myself, class UnitExpr, class Gen0, class Gen1 = void, class Gen2 = void>
            struct apply :
                result_of<
                    function<baby_aux>(
                        typename result_of<
                            op_compose2(op_monad_bind const&, Gen2&, typename result_of<op_uncurry(typename result_of<op_curry3(UnitExpr&)>::type)>::type)
                        >::type,
                        Gen0&, Gen1&
                    )
                >
            { };

            template<class Myself, class UnitExpr, class Gen0, class Gen1, class Gen2>
            Result call(Expr& expr, Gen0& gen0, Gen0& gen1, Gen2& gen2) const
            {
                return make_function(*this)(
                    compose2(monad_bind, gen2, uncurry(curry3(expr))),
                    gen0, gen1
                 );
            }

            template<class Myself, class UnitExpr, class Gen0, class Gen1>
            struct apply<UnitExpr, Gen0, Gen1> :
                result_of<
                    function<baby_aux>(
                        typename result_of<
                            op_compose2(op_monad_bind const&, Gen1&, typename result_of<op_curry2(UnitExpr&)>::type)
                        >::type,
                        Gen0&
                    )
                >
            { };

            template<class Myself, class UnitExpr, class Gen0, class Gen1>
            Result call(UnitExpr& expr, Gen0& gen0, Gen0& gen1) const
            {
                return make_function(*this)(
                    compose2(monad_bind, gen1, curry2(expr)),
                    gen0
                );
            }

            template<class Myself, class UnitExpr, class Gen0>
            struct apply<UnitExpr, Gen0> :
                result_of<
                    op_monad_bind(typename result_of<Gen0()>::type, UnitExpr&)
                >
            { };

            template<class Myself, class UnitExpr, class Gen0,>
            Result call(UnitExpr& expr, Gen0& gen0) const
            {
                return monad_bind(gen0(), expr);
            }
        };

        typedef function<baby_nested_bind> op_nested_bind;
        PSTADE_POD_CONSTANT((op_nested_bind)), nested_bind) = {{}};


        struct baby
        {
            template<class Myself, class Expr, class Guard, class Gen0, class Gen1 = void, class Gen2 = void>
            struct apply :
                result_of<
                    op_nested_bind(typename result_of<op_make_unit_expr(Expr&, Guard&)>::type, Gen0&, Gen1&, Gen2&)
                >
            { };

            template<class Myself, class Expr, class Guard, class Gen0, class Gen1, class Gen2>
            Result call(Expr& expr, Guard& guard, Gen0& gen0, Gen0& gen1, Gen2& gen2) const
            {
                return nested_bind(make_unit_expr(expr, guard), gen0, gen1, gen2);
            }

            template<class Myself, class Expr, class Guard, class Gen0, class Gen1>
            struct apply<Expr, Guard, Gen0, Gen1> :
                result_of<
                    op_nested_bind(typename result_of<op_make_unit_expr(Expr&, Guard&)>::type, Gen0&, Gen1&)
                >
            { };

            template<class Myself, class Expr, class Guard, class Gen0, class Gen1>
            Result call(Expr& expr, Guard& gurad, Gen0& gen0, Gen0& gen1) const
            {
                return nested_bind(make_unit_expr(expr, guard), gen0, gen1);
            }

            template<class Myself, class Expr, class Guard, class Gen0>
            struct apply<Expr, Guard, Gen0> :
                result_of<
                    op_nested_bind(typename result_of<op_make_unit_expr(Expr&, Guard&)>::type, Gen0&)
                  >
            { };

            template<class Myself, class Expr, class Guard, class Gen0>
            Result call(Expr& expr, Guard& gurad, Gen0& gen0) const
            {
                return nested_bind(make_unit_expr(expr, guard), gen0);
            }
        };


    } // namespace comprehension_detail


} } // namespace pstade::egg


#endif
