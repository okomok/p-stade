#ifndef PSTADE_EGG_FROM_ANY_TO_HPP
#define PSTADE_EGG_FROM_ANT_TO_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Pending...


#include <boost/any.hpp>
#include <boost/none.hpp>
#include <boost/optional/optional.hpp> // inclusion guaranteed
#include <boost/type_traits/is_const.hpp>
#include <pstade/egg/automatic.hpp>
#include <pstade/egg/specified.hpp>


namespace pstade { namespace egg {


    // any_to
    //

    template<class X>
    struct X_any_to
    {
        typedef X &result_type;

        template<class Any>
        X &operator()(Any &a) const
        {
            return a.template content<X>();
        }

        template<class Any>
        X &operator()(Any const &a) const
        {
            return a.template content<X>();
        }

        X &operator()(boost::any &a) const
        {
            return boost::any_cast<X &>(a);
        }

        X &operator()(boost::any const &a) const
        {
            return boost::any_cast<X &>(a);
        }
    };

    PSTADE_EGG_SPECIFIED1(any_to, X_any_to, (class))


    // from_any
    //

    namespace from_any_detail {


        template<class Result, class To, bool IsConstAny, bool IsConstTo = boost::is_const<To>::value>
        struct boost_any
        {
            template<class Any>
            static Result call(Any &a)
            {
                To *p = boost::any_cast<To>(&a);
                if (p)
                    return *p;
                else
                    return boost::none;
            }
        };

        template<class Result, class To>
        struct boost_any<Result, To, true, false>
        {
            template<class Any>
            static Result call(Any const &)
            {
                return boost::none;
            }
        };


    } // namespace from_any_detail


    template<class X>
    struct X_from_any_to;

    template<class T>
    struct X_from_any_to< boost::optional<T &> >
    {
        typedef boost::optional<T &> result_type;

        template<class Any>
        result_type operator()(Any &a) const
        {
            if (a.template contains<T>())
                return a.template content<T>();
            else
                return boost::none;
        }

        template<class Any>
        result_type operator()(Any const &a) const
        {
            if (a.template contains<T>())
                return a.template content<T>();
            else
                return boost::none;
        }

        result_type operator()(boost::any &a) const
        {
            return from_any_detail::boost_any<result_type, T, false>::call(a);
        }

        result_type operator()(boost::any const &a) const
        {
            return from_any_detail::boost_any<result_type, T, true >::call(a);
        }
    };

    typedef automatic< X_from_any_to<boost::mpl::_> >::type T_from_any;
    PSTADE_POD_CONSTANT((T_from_any), from_any) = PSTADE_EGG_AUTOMATIC;


} } // namespace pstade::egg


#endif
