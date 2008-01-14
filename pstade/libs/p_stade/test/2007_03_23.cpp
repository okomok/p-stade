

#include <utility>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/has_template_xxx.hpp>

// Create has_template_result to detect nested members like
// template<class T> struct result {}.
// The first macro argument is the member name and the second argument
// is the number of template parameters.
BOOST_MPL_HAS_TEMPLATE_XXX_TRAIT_DEF(result, 1)

struct pair_maker {
   template<typename F> struct result;
   template<typename F, typename Arg0, typename Arg1>
   struct result<F(Arg0, Arg1)> {
       typedef std::pair<Arg0, Arg1> type;
   };

   template<typename Arg0, typename Arg1>
   typename result<pair_maker(Arg0, Arg1)>::type
   operator()(Arg0 a0, Arg1 a1) const
   {
       return std::make_pair(a0, a1);
   }
};

int main()
{
   using namespace boost;

   typedef char value_type;
   BOOST_MPL_ASSERT((
       has_template_result<
           pair_maker,
           pair_maker(value_type, value_type)
       >
   ));
} 
