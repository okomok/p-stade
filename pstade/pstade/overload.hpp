#ifndef PSTADE_OVERLOAD_HPP
#define PSTADE_OVERLOAD_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Deprecated!
//


// What:
//
// Triggers intentional ADL that jumps namespaces.


// See: 'tag' at <boost/foreach.hpp>
//
// Copyright 2004 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: 'version_type' at <boost/serialization/serialization.hpp>
//
// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Why: template
//
// Customization target types are not always "argument",
// so carry the target type using type2type.


#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>


#if !defined(PSTADE_OVERLOAD_MAX_ARITY)
    #define PSTADE_OVERLOAD_MAX_ARITY 5
#endif


struct pstade_overload_detail_adl_into_global_namespace
{ };


namespace pstade {


template<
    BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(PSTADE_OVERLOAD_MAX_ARITY, class T, void)
>
struct overload :
    ::pstade_overload_detail_adl_into_global_namespace
{ };


} // namespace pstade


#endif
