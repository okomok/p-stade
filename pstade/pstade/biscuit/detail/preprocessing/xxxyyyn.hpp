
#if !defined(BOOST_PP_IS_ITERATING)

#include <boost/preprocessor/iteration/iterate.hpp>

///////////////////////////////////////////////////////////////////////////////
// included files
//
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include "../../config/limit_parser_arity.hpp"
                                                                             //
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// local macros definitions
//
#define PSTADE_BISCUIT_enum_fun(z, i, data) \
	PSTADE_BISCUIT_XXXYYYN_ARG_elem_typename< BOOST_PP_CAT(PSTADE_BISCUIT_XXXYYYN_ARG_arg, i) > \
/**/

#define PSTADE_BISCUIT_iteration_limits PSTADE_BISCUIT_LIMIT_PARSER_ARITY
                                                                             //
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// header
//
namespace pstade { namespace biscuit {


// empty
template< class Dummy = boost::mpl::void_ >
struct BOOST_PP_CAT(PSTADE_BISCUIT_XXXYYYN_ARG_typename, 0);

template<>
struct BOOST_PP_CAT(PSTADE_BISCUIT_XXXYYYN_ARG_typename, 0)<boost::mpl::void_> :
	BOOST_PP_CAT(PSTADE_BISCUIT_XXXYYYN_ARG_operation, 0)< BOOST_PP_ENUM(0, PSTADE_BISCUIT_enum_fun, ~) >
{ };

                                                                             //
///////////////////////////////////////////////////////////////////////////////


#define BOOST_PP_ITERATION_LIMITS (1, PSTADE_BISCUIT_iteration_limits)
#define BOOST_PP_FILENAME_1 "./xxxyyyn.hpp"
#include BOOST_PP_ITERATE()


///////////////////////////////////////////////////////////////////////////////
// footer
//

} } // namespace pstade::biscuit
                                                                             //
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// local macros undefinitions
//
#undef PSTADE_BISCUIT_iteration_limits
#undef PSTADE_BISCUIT_enum_fun

#undef PSTADE_BISCUIT_XXXYYYN_ARG_typename
#undef PSTADE_BISCUIT_XXXYYYN_ARG_param
#undef PSTADE_BISCUIT_XXXYYYN_ARG_arg
#undef PSTADE_BISCUIT_XXXYYYN_ARG_elem_typename
#undef PSTADE_BISCUIT_XXXYYYN_ARG_operation
                                                                             //
///////////////////////////////////////////////////////////////////////////////

#else // BOOST_PP_IS_ITERATING

#define i BOOST_PP_ITERATION()


///////////////////////////////////////////////////////////////////////////////
// i element making
//
template< BOOST_PP_ENUM_PARAMS(i, PSTADE_BISCUIT_XXXYYYN_ARG_param PSTADE_BISCUIT_XXXYYYN_ARG_arg) >
struct BOOST_PP_CAT(PSTADE_BISCUIT_XXXYYYN_ARG_typename, i) :
	BOOST_PP_CAT(PSTADE_BISCUIT_XXXYYYN_ARG_operation, i)< BOOST_PP_ENUM(i, PSTADE_BISCUIT_enum_fun, ~) >
{ };

                                                                             //
///////////////////////////////////////////////////////////////////////////////

#undef i

#endif // BOOST_PP_IS_ITERATING
