
#include "../../config/limit_begin_msg_map_size.hpp"

#define POOST_pp_header \
    namespace pstade { namespace ketchup { \
        struct begin_msg_map_entry_set : begin_msg_mapn_entry_set \
        { \
/**/

#define POOST_pp_footer \
        }; \
    } } \
/**/

#define POOST_pp_arg E
#define POOST_pp_param class
#define POOST_pp_def_arg boost::mpl::void_
#define POOST_pp_name begin_msg_map
#define POOST_pp_limit_params_size PSTADE_KETCHUP_LIMIT_BEGIN_MSG_MAP_SIZE

#include "./poost_pp_variadic_forms.ipp"
