
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
	bchar< T, BOOST_PP_CAT(ch, i) > \
/**/

#define PSTADE_BISCUIT_iteration_limits PSTADE_BISCUIT_LIMIT_PARSER_ARITY
                                                                             //
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// header
//
namespace pstade { namespace biscuit {

                                                                             //
///////////////////////////////////////////////////////////////////////////////


#define BOOST_PP_ITERATION_LIMITS (0, PSTADE_BISCUIT_iteration_limits)
#define BOOST_PP_FILENAME_1 "./bchsetn.hpp"
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

                                                                             //
///////////////////////////////////////////////////////////////////////////////

#else // BOOST_PP_IS_ITERATING

#define i BOOST_PP_ITERATION()


///////////////////////////////////////////////////////////////////////////////
// i element making
//
template< class T BOOST_PP_COMMA_IF(i) BOOST_PP_ENUM_PARAMS(i, T ch) >
struct BOOST_PP_CAT(bchset, i) :
	BOOST_PP_CAT(or_, i)< BOOST_PP_ENUM(i, PSTADE_BISCUIT_enum_fun, ~) >
{ };

                                                                             //
///////////////////////////////////////////////////////////////////////////////

#undef i

#endif // BOOST_PP_IS_ITERATING
