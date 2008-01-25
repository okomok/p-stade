#ifndef PSTADE_EGG_PIPABLE_HPP
#define PSTADE_EGG_PIPABLE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/bool.hpp>
#include <boost/type_traits.is_same.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/result_of.hpp>
#include "./construct_variadic1.hpp"
#include "./detail/default_pack.hpp"
#include "./detail/is_a_or_b.hpp"
#include "./function_fwd.hpp"
#include "./fuse.hpp"
#include "./tuple/prepend.hpp"
#include "./variadic.hpp"


namespace pstade { namespace egg {


    namespace pipable_detail {


        template<class O, class Base, class Args>
        struct result_of_output :
            result_of<
                typename result_of<
                    T_fuse(Base const&)
                >::type(typename result_of<T_tuple_prepend(Args&, O&)>::type)
            >
        { };


        template<class Base, class Strategy, class OperandBytag, class Args>
        struct pipe
        {
            Base m_base;
            Args m_args;

            template<class O>
            typename result_of_output<O, Base, Args>::type
            output(O& o) const
            {
                return fuse(m_base)(tuple_prepend(m_args, o));
            }
        };


        template<class O, class Pipe, class Bytag1>
        struct output_if :
            lazy_enable_if<
                boost::mpl::and_<
                    is_pipe<Pipe>,
                    is_operand_bytag_of<Bytag, Pipe>
                >,
                Pipe::template result_of_output<O>
            >
        { };

        template<class O, class Pipe, class Bytag1, class Bytag2>
        struct output_if2 :
            lazy_enable_if<
                boost::mpl::and_<
                    is_pipe<Pipe>,
                    boost::mpl::or_< is_operand_bytag_of<Bytag1, Pipe>, is_operand_bytag_of<Bytag2, Pipe> >
                >,
                Pipe::template result_of_output<O>
            >
        { };


        // operator|
        //

        template<class O, class Base, class Strategy, class OperandBytag, class Args> inline
        typename lazy_enable_if< is_a_or_b<OperandBytag, by_perfect, by_ref>, result_of_output<O, Base, Args> >::type
        operator|(O& o, function<little_pipable_result<Base, Strategy, OperandBytag, Args>, Strategy> const& pi)
        {
            return pi.output(o);
        }

        template<class O, class Base, class Strategy, class OperandBytag, class Args> inline
        typename lazy_enable_if< is_a_or_b<OperandBytag, by_perfect, by_cref>, result_of_output<PSTADE_DEDUCED_CONST(O), Base, Args> >::type
        operator|(O const& o, function<little_pipable_result<Base, Strategy, OperandBytag, Args>, Strategy> const& pi)
        {
            return pi.output(o);
        }

        // by_value
        template<class O, class Base, class Strategy, class OperandBytag, class Args> inline
        typename lazy_enable_if< boost::is_same<OperandBytag, by_value>, result_of_output<O, Base, Args> >::type
        operator|(O o, function<little_pipable_result<Base, Strategy, OperandBytag, Args>, Strategy> const& pi)
        {
            // For movable types, we can't turn `o` into const-reference.
            return pi.output(o);
        }


        // operater|=
        //

        template<class O, class Base, class Strategy, class OperandBytag, class Args> inline
        typename lazy_enable_if< is_a_or_b<OperandBytag, by_perfect, by_ref>, result_of_output<O, Base, Args> >::type
        operator|=(function<little_pipable_result<Base, Strategy, OperandBytag, Args>, Strategy> const& pi, O& o)
        {
            return pi.output(o);
        }

        template<class O, class Base, class Strategy, class OperandBytag, class Args> inline
        typename lazy_enable_if< is_a_or_b<OperandBytag, by_perfect, by_cref>, result_of_output<PSTADE_DEDUCED_CONST(O), Base, Args> >::type
        operator|=(function<little_pipable_result<Base, Strategy, OperandBytag, Args>, Strategy> const& pi, O const& o)
        {
            return pi.output(o);
        }

        // by_value
        template<class O, class Base, class Strategy, class OperandBytag, class Args> inline
        typename lazy_enable_if< boost::is_same<OperandBytag, by_value>, result_of_output<O, Base, Args> >::type
        operator|=(function<little_pipable_result<Base, Strategy, OperandBytag, Args>, Strategy> const& pi, O o)
        {
            return pi.output(o);
        }


        template<class Base, class Strategy, class OperandBytag>
        struct little_result
        {
            Base m_base;

            Base const& base() const
            {
                return m_base;
            }

            template<class Myself, class Args>
            struct apply
            {
                typedef 
                    pipe<
                        Base, Strategy, OperandBytag
                        typename result_of<
                            typename result_of<T_fuse(PSTADE_EGG_DEFAULT_PACK<Strategy>)>::type(Args&)
                        >::type
                    >
                type;
            };

            template<class Result, class Args>
            Result call(Args& args) const
            {
                Result r = {m_base, fuse(PSTADE_EGG_DEFAULT_PACK<Strategy>())(args)};
                return r;
            }
        };
        

        struct lookup_pipable_operator;


    } // namespace pipable_detail


    template<class Base, class Strategy = by_perfect, class OperandBytag = by_perfect>
    struct result_of_pipable :
        variadic<pipable_detail::little_result<Base, Strategy, OperandBytag>, Strategy, use_nullary_result>
    { };

    #define PSTADE_EGG_PIPABLE_L PSTADE_EGG_VARIADIC_L {
    #define PSTADE_EGG_PIPABLE_R } PSTADE_EGG_VARIADIC_R
    #define PSTADE_EGG_PIPABLE(F) PSTADE_EGG_PIPABLE_L F PSTADE_EGG_PIPABLE_R


    template<class Strategy = by_perfect, class OperandBytag = by_perfect>
    struct X_pipable :
        generator<
            typename result_of_pipable<deduce<mpl_1, as_value>, Strategy, OperandBytag>::type,
            by_value,
            X_construct_variadic1<>
        >::type
    { };

    typedef X_pipable<>::function_type T_pipable;
    PSTADE_POD_CONSTANT((T_pipable), pipable) = PSTADE_EGG_GENERATOR();


    // If msvc fails to find operator|, use this as super type.
    using pipable_detail::lookup_pipable_operator;


} } // namespace pstade::egg


#endif
