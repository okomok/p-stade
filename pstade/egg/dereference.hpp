#ifndef PSTADE_EGG_DEREFERENCE_HPP
#define PSTADE_EGG_DEREFERENCE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// References:
//
// [1] OptionalPointee Concept
//     http://www.boost.org/libs/utility/OptionalPointee.html


#include <boost/indirect_reference.hpp>
#include <boost/optional/optional_fwd.hpp>
#include <pstade/affect.hpp>
#include <pstade/pod_constant.hpp>
#include "./adapt.hpp"


namespace pstade { namespace egg {


    template<class X>
    struct Dereferenceable
    {
        typedef typename
            boost::indirect_reference<X>::type
        reference;
    };

    template<class X>
    struct Dereferenceable<X const> :
        Dereferenceable<X>
    { };


    template<class T>
    struct Dereferenceable< boost::optional<T> >
    {
        typedef T reference;
    };


    namespace dereference_detail {


        template<class Der>
        struct base
        {
            typedef typename
                affect<
                    Der&,
                    typename Dereferenceable<Der>::reference
                >::type
            result_type;

            result_type operator()(Der& der) const
            {
                return *der;
            }
        };


    } // namespace dereference_detail


    typedef PSTADE_EGG_ADAPT((dereference_detail::base<boost::mpl::_>)) op_dereference;
    PSTADE_POD_CONSTANT((op_dereference), dereference) = PSTADE_EGG_ADAPT_TYPE;


} } // namespace pstade::egg


#endif
