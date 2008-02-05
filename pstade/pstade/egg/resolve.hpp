#ifndef PSTADE_EGG_RESOLVE_HPP
#define PSTADE_EGG_RESOLVE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_member_function_pointer.hpp>
#include <pstade/enable_if.hpp>


namespace pstade { namespace egg {


    template<class F, class EnableIf = enabler>
    struct X_resolve
    {
        typedef F *result_type;

        result_type operator()(result_type f) const
        {
            return f;
        }
    };

    template<class F>
    struct X_resolve<F, typename enable_if<
            boost::mpl::or_< boost::is_pointer<F>, boost::is_member_function_pointer<F> > >::type>
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


} } // namespace pstade::egg


#include "./detail/suffix.hpp"
#endif
