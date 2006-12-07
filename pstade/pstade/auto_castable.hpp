#ifndef PSTADE_AUTO_CASTABLE_HPP
#define PSTADE_AUTO_CASTABLE_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/type.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/function_adaptor.hpp>
#include <pstade/nonassignable.hpp>


namespace pstade {


    namespace auto_castable_detail {


        template< class CastFunction, class From >
        struct temp :
            private nonassignable
        {
            temp(CastFunction const& fun, From& from) :
                m_fun(fun), m_from(from)
            { }

            template< class To >
            operator To() const
            {
                return m_fun(m_from, boost::type<To>());
            }

        private:
            mutable CastFunction m_fun;
            From& m_from;
        };


        template< class CastFunction >
        struct baby_op_result
        {
            template< class Myself, class From >
            struct apply
            {
                typedef temp<CastFunction, From> const type;
            };

            template< class Result, class From >
            Result call(From& from) const
            {
                return Result(m_fun, from);
            }

            explicit baby_op_result() // DefaultConstructible iif 'CastFunction' is.
            { }

            explicit baby_op_result(CastFunction const& fun) :
                m_fun(fun)
            { }

        private:
            CastFunction m_fun;
        };


    } // namespace auto_castable_detail


    PSTADE_EGG_FUNCTION_ADAPTOR(auto_castable, auto_castable_detail::baby_op_result)


    #define PSTADE_AUTO_CASTABLE(Object, CastFunction) \
        typedef \
            boost::result_of<pstade::op_auto_castable(CastFunction)>::type \
        BOOST_PP_CAT(op_, Object); \
        \
        PSTADE_SINGLETON_CONST(Object, BOOST_PP_CAT(op_, Object)) \
    /**/


} // namespace pstade


#endif
