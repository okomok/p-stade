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
#include <pstade/nonassignable.hpp>
#include <pstade/pass_by.hpp>


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
        struct baby_fun
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

            explicit baby_fun() // DefaultConstructible iif 'CastFunction' is.
            { }

            explicit baby_fun(CastFunction const& fun) :
                m_fun(fun)
            { }

        private:
            CastFunction m_fun;
        };


        struct baby
        {
            template< class Myself, class CastFunction >
            struct apply
            {
                typedef typename pass_by_value<CastFunction>::type fun_t;
                typedef egg::function< baby_fun<fun_t> > type;
            };

            template< class Result, class CastFunction >
            Result call(CastFunction& fun) const
            {
                return Result(fun);
            }
        };


    } // namespace auto_castable_detail


    PSTADE_EGG_FUNCTION(auto_castable, auto_castable_detail::baby)


    #define PSTADE_AUTO_CASTABLE(Object, CastFunction) \
        typedef \
            boost::result_of<pstade::auto_castable_fun(CastFunction)>::type \
        BOOST_PP_CAT(Object, _fun); \
        \
        PSTADE_SINGLETON_CONST( \
            BOOST_PP_CAT(Object, _fun), \
            Object \
        ) \
    /**/


} // namespace pstade


#endif
