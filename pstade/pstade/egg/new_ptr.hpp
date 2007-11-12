#ifndef PSTADE_NEW_PTR_HPP
#define PSTADE_NEW_PTR_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/pointee.hpp>
#include "./compose1.hpp"
#include "./construct.hpp"
#include "./new.hpp"
#include "./nullary_result_of.hpp"


namespace pstade { namespace egg {


    namespace new_ptr_detail {


        template<class P>
        struct pod_ :
            result_of_compose1<
                typename X_construct<P>::pod_type,
                typename X_new_<typename boost::pointee<P>::type>::pod_type,
                P
            >
        { };


    } // namespace new_ptr_detail


    template<class P>
    struct X_new_ptr :
        new_ptr_detail::pod_<P>::type
    {
        typedef typename new_ptr_detail::pod_<P>::type pod_type;
    };


} } // namespace pstade::egg


PSTADE_EGG_NULLARY_RESULT_OF_TEMPLATE(pstade::egg::X_new_ptr, (class))


#endif
