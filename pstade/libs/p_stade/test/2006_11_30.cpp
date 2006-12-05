
#include <boost/type_traits/is_same.hpp> 
#include <boost/mpl/assert.hpp> 


#define MYLINE __COUNTER__ // compiles
// #define MYLINE __LINE__ // fails


#define MY_MPL_ASSERT(pred) \
enum { \
    BOOST_PP_CAT(mpl_assertion_in_line_,MYLINE) = sizeof( \
          boost::mpl::assertion_failed<false>( \
              boost::mpl::assert_arg( (void (*) pred)0, 1 ) \
            ) \
        ) \
}\
/**/

int main() 
{ 
    MY_MPL_ASSERT(( boost::is_same< char, char > )); 
}
