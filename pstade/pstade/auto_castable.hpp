#ifndef PSTADE_AUTO_CASTABLE_HPP
#define PSTADE_AUTO_CASTABLE_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/apply.hpp>
#include <boost/mpl/placeholders.hpp> // inclusion guaranteed.
#include <boost/preprocessor/cat.hpp>
#include <pstade/callable1.hpp>
#include <pstade/constant.hpp>
#include <pstade/nonassignable.hpp>
#include <pstade/unparenthesize.hpp>


namespace pstade {


    namespace auto_castable_detail {


        template<class Lambda, class From>
        struct temp :
            private nonassignable
        {
            temp(From& from) :
                m_from(from)
            { }

            template<class To>
            operator To() const
            {
                typedef typename
                    boost::mpl::apply1<Lambda, To>::type
                fun_t;

                return fun_t()(m_from);
            }

        private:
            From& m_from;
        };


    } // namespace auto_castable_detail


    template<class Lambda>
    struct auto_castable :
        callable1<auto_castable<Lambda> >
    {
        template<class Myself, class From>
        struct apply
        {
            typedef
                auto_castable_detail::temp<Lambda, From> const
            type;
        };

        template<class Result, class From>
        Result call(From& from) const
        {
            return Result(from);
        }
    };


    #define PSTADE_AUTO_CASTABLE(Object, Lambda) \
        typedef \
            ::pstade::auto_castable<PSTADE_UNPARENTHESIZE(Lambda)> \
        BOOST_PP_CAT(op_, Object); \
        \
        PSTADE_CONSTANT( Object, (BOOST_PP_CAT(op_, Object)) ) \
    /**/


} // namespace pstade


#endif
