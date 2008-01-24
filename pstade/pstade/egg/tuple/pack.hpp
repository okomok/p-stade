#ifndef PSTADE_EGG_TUPLE_PACK_HPP
#define PSTADE_EGG_TUPLE_PACK_HPP
#include "../detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/tuple/tuple.hpp>
#include <pstade/pod_constant.hpp>
#include "../by_perfect.hpp"
#include "../detail/little_pack.hpp"
#include "../function_fwd.hpp" // by_value
#include "../register_nullary_result.hpp"
#include "./config.hpp" // PSTADE_EGG_TUPLE_MAX_SIZE


namespace pstade { namespace egg {


    namespace tuple_detail {
        #define  PSTADE_EGG_LITTLE_PACK_TEMPLATE(N) boost::tuples::tuple
        #define  PSTADE_EGG_LITTLE_PACK_MAX_ARITY PSTADE_EGG_TUPLE_MAX_SIZE
        #include PSTADE_EGG_LITTLE_PACK()
    }


    #define PSTADE_EGG_TUPLE_PACK_INIT {{}}


    template<class Strategy = by_perfect>
    struct X_tuple_pack :
        function<tuple_detail::little_pack<Strategy>, Strategy>
    { };


    typedef X_tuple_pack<>::function_type T_tuple_pack;
    PSTADE_POD_CONSTANT((T_tuple_pack), tuple_pack) = PSTADE_EGG_TUPLE_PACK_INIT;


} } // namespace pstade::egg


PSTADE_EGG_REGISTER_NULLARY_RESULT_OF_TEMPLATE(pstade::egg::X_tuple_pack, (class))


#endif
