#ifndef BOOST_EGG_RESOLVE_HPP
#define BOOST_EGG_RESOLVE_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_member_function_pointer.hpp>
#include <boost/egg/detail/enable_if.hpp>


namespace boost { namespace egg {


    template<class F, class EnableIf = details::enabler>
    struct X_resolve
    {
        typedef F *result_type;

        result_type operator()(result_type f) const
        {
            return f;
        }
    };

    template<class F>
    struct X_resolve<F,
        typename details::enable_if<
            mpl::or_< is_pointer<F>, is_member_function_pointer<F> >
        >::type>
    {
        typedef F result_type;

        result_type operator()(result_type f) const
        {
            return f;
        }
    };


    template<class F> inline
    typename X_resolve<F>::result_type
    resolve(typename X_resolve<F>::result_type f)
    {
        return f;
    }


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
