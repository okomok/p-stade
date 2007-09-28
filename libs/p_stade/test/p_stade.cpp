#include <boost/utility/result_of.hpp>


#include <pstade/result_of.hpp>
using pstade::result_of;


struct test_function1
{
     template <typename SignatureT>
     struct result;

     template <typename Self, typename T>
     struct result<Self const (T)>
     {
         typedef T type;
     };

     template <typename T>
     T operator () (T t) const
     {
         return t;
     }
};

template <typename ArgT>
struct test_function2
{
     template <typename SignatureT>
     struct result;

     template <typename Self, typename T>
     struct result<Self const (T)>
     {
         typedef T type;
     };

     template <typename T>
     T operator () (T t) const
     {
         return t;
     }
};

int main(int argc, char *argv[])
{
     typedef result_of<
         test_function1 const(int)>::type result_type;
     typedef result_of<
         test_function2<float> const(int)>::type result_type_;
     return 0;
}
