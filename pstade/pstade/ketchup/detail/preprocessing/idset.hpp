

#include "../../config/limit_idset_size.hpp"

#define POOST_pp_header namespace pstade { namespace ketchup {
#define POOST_pp_footer } } // namespace pstade::ketchup
#define POOST_pp_arg ID
#define POOST_pp_param UINT
#define POOST_pp_def_arg 0
#define POOST_pp_name idset
#define POOST_pp_limit_params_size PSTADE_KETCHUP_LIMIT_IDSET_SIZE

#include "./poost_pp_variadic_forms.ipp"
