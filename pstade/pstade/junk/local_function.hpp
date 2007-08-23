template<class Tuple, class F>
struct local_function;

#define BOOST_LOCAL_FUNCTION_DEF(z, n, data)\
    template<class Tuple class R BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, 
class T)>\
    struct local_function<Tuple, R(BOOST_PP_ENUM_PARAMS_Z(z, n, T))> {\
        Tuple tuple;\
        R (*f)(BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, T));\
        local_function(const Tuple& t) : tuple(t) {}\
        R operator()(BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS_Z(z, n, T, t)) {\
            return(f(tuple BOOST_PP_ENUM_SHIFTED_TRAILING_PARAMS_Z(z, n, 
t)))\
        }\
    };

BOOST_PP_REPEAT(BOOST_PP_INC(BOOST_LOCAL_FUNCTION_MAX_ARITY), 
BOOST_LOCAL_FUNCTION_DEF, ~)

So that

int BOOST_LOCAL_FUNCTION(name, (i)(j), (int x)(int y)) {
    //body here
} BOOST_LOCAL_FUNCTION_END

expands to

int result_tag;
typedef BOOST_TYPEOF(result_tag) result_type;
typedef BOOST_TYPEOF(i) type_0;
typedef BOOST_TYPEOF(j) type_1;
typedef boost::tuple<type_0, type_1> tuple_type;
typedef local_function<tuple_type, result_type(tuple_type, int x, int y)> function_type;
function_type name(make_tuple(i, j));
{
    function_type* function_ptr = &name;
    struct body {
        result_type impl(tuple_type& args, int x, int y) {
            type_0& i = boost::get<0>(args);
            type_1 j = boost::get<1>(args);
            {
                //body here
            }
        }
    };
    function_ptr->f = &body::impl;
}


int& (*result_tag)() = 0;
typedef result_of<BOOST_TYPEOF(result_tag)>::result_type result_type;






struct op_name { int operator()(int x, int y) const {

    // body here

} int i; int j; } name = {i, j};


