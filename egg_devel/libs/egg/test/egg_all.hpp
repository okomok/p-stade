

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


//  Note: There are no include guards. This is intentional.


#include <boost/egg/adapted_to.hpp>
#include <boost/egg/always.hpp>
#include <boost/egg/ambi.hpp>
#include <boost/egg/apply.hpp>
#include <boost/egg/apply_decl.hpp>
#include <boost/egg/apply_little.hpp>
#include <boost/egg/auto_new.hpp>
#include <boost/egg/by_cref.hpp>
#include <boost/egg/by_perfect.hpp>
#include <boost/egg/by_ref.hpp>
#include <boost/egg/by_value.hpp>
#include <boost/egg/call_little.hpp>
#include <boost/egg/compose.hpp>
#include <boost/egg/config.hpp>
#include <boost/egg/const.hpp>
#include <boost/egg/construct.hpp>
#include <boost/egg/construct_braced1.hpp>
#include <boost/egg/construct_braced2.hpp>
#include <boost/egg/construct_unfused1.hpp>
#include <boost/egg/construct_variadic1.hpp>
#include <boost/egg/constructor.hpp>
#include <boost/egg/copy.hpp>
#include <boost/egg/copy_assign.hpp>
#include <boost/egg/curry.hpp>
#include <boost/egg/delete.hpp>
#include <boost/egg/delete_array.hpp>
#include <boost/egg/detect_result_type.hpp>
#include <boost/egg/do_swap.hpp>
#include <boost/egg/explicit.hpp>
#include <boost/egg/expr.hpp>
#include <boost/egg/fix.hpp>
#include <boost/egg/flip.hpp>
#include <boost/egg/forward.hpp>
#include <boost/egg/free.hpp>
#include <boost/egg/function.hpp>
#include <boost/egg/function_extension.hpp>
#include <boost/egg/function_facade.hpp>
#include <boost/egg/function_fwd.hpp>
#include <boost/egg/functional.hpp>
#include <boost/egg/fuse.hpp>
#include <boost/egg/generator.hpp>
#include <boost/egg/get.hpp>
#include <boost/egg/identity.hpp>
#include <boost/egg/iequal_to.hpp>
#include <boost/egg/if_else.hpp>
#include <boost/egg/implicit.hpp>
#include <boost/egg/indirect.hpp>
#include <boost/egg/infix.hpp>
#include <boost/egg/integral.hpp>
#include <boost/egg/is_same_obj.hpp>
#include <boost/egg/lazy.hpp>
#include <boost/egg/lexical.hpp>
#include <boost/egg/locale.hpp>
#include <boost/egg/memoize.hpp>
#include <boost/egg/mono.hpp>
#include <boost/egg/move_assign.hpp>
#include <boost/egg/nest.hpp>
#include <boost/egg/new.hpp>
#include <boost/egg/new_array.hpp>
#include <boost/egg/overloaded.hpp>
#include <boost/egg/ptr_new.hpp>
#include <boost/egg/resolve.hpp>
#include <boost/egg/shared_new.hpp>
#include <boost/egg/shared_new_array.hpp>
#include <boost/egg/not.hpp>
#include <boost/egg/pack.hpp>
#include <boost/egg/perfect.hpp>
#include <boost/egg/pipable.hpp>
#include <boost/egg/poly.hpp>
#include <boost/egg/register_nullary_result.hpp>
#include <boost/egg/regular.hpp>
#include <boost/egg/result_of.hpp>
#include <boost/egg/return.hpp>
#include <boost/egg/shared_object.hpp>
#include <boost/egg/starling.hpp>
#include <boost/egg/static.hpp>
#include <boost/egg/static_down.hpp>
#include <boost/egg/static_downcast.hpp>
#include <boost/egg/strong_assign.hpp>
#include <boost/egg/tagged.hpp>
#include <boost/egg/throw.hpp>
#include <boost/egg/to_ref.hpp>
#include <boost/egg/to_shared_ptr.hpp>
#include <boost/egg/to_string.hpp>
#include <boost/egg/to_value.hpp>
#include <boost/egg/uncurry.hpp>
#include <boost/egg/unfuse.hpp>
#include <boost/egg/variadic.hpp>


// pendings

#include <boost/egg/arg.hpp>
#include <boost/egg/bind.hpp>
#include <boost/egg/inlined.hpp>
#include <boost/egg/is_bind_expression.hpp>
#include <boost/egg/placeholders.hpp>
#include <boost/egg/protect.hpp>
#include <boost/egg/unlambda.hpp>
#if BOOST_VERSION >= 103500
#include <boost/egg/overload.hpp>
#endif


// bll

#include <boost/egg/bll/bind.hpp>
#include <boost/egg/bll/config.hpp>
#include <boost/egg/bll/functor_fwd.hpp>
#include <boost/egg/bll/extension_fwd.hpp>
#include <boost/egg/bll/optional.hpp>
#include <boost/egg/bll/placeholders.hpp>
#include <boost/egg/bll/poly.hpp>
#include <boost/egg/bll/protect.hpp>
#include <boost/egg/bll/sig_impl.hpp>
#include <boost/egg/bll/string.hpp>
#include <boost/egg/bll/result_of.hpp>
#include <boost/egg/bll/return_type.hpp>
#include <boost/egg/bll/unlambda.hpp>


// fusion

#include <boost/egg/fusion/drop.hpp>
#include <boost/egg/fusion/element.hpp>
#include <boost/egg/fusion/length.hpp>
#if defined(BOOST_EGG_HAS_FUSIONS)
    #include <boost/egg/fusion/pack.hpp>
#endif
#include <boost/egg/fusion/prepend.hpp>
