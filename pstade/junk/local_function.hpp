
#include <vector>

//http://lists.boost.org/Archives/boost/2007/08/126215.php



template<class Tuple, class F>
struct local_function;

#define BOOST_LOCAL_FUNCTION_DEF(z, n, data)\
    template<class Tuple class R BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, class T)>\
    struct local_function<Tuple, R(BOOST_PP_ENUM_PARAMS_Z(z, n, T))> {\
        Tuple tuple;\
        R (*f)(BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, T));\
        local_function(const Tuple& t) : tuple(t) {}\
        R operator()(BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS_Z(z, n, T, t)) {\
            return(f(tuple BOOST_PP_ENUM_SHIFTED_TRAILING_PARAMS_Z(z, n, t)))\
        }\
    };

BOOST_PP_REPEAT(BOOST_PP_INC(BOOST_LOCAL_FUNCTION_MAX_ARITY), BOOST_LOCAL_FUNCTION_DEF, ~)

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


template<class T>
void foo()
{
  T& (*function_tag)() = 0;
  typedef typename remove_reference<BOOST_TYPEOF(function_tag)>::type sig;
}




struct body
{
    static char impl(double i, double j, int x, int y) const
    {

    }
};

bind(&body::impl, i, j, _1, _2);

boost::function<(char(int, int)> lf = uncurry(curry4(&body::impl)(i)(j));


template<class T>
function<int(T, char)>
foo()
{
    T i = 3;
    char j = 'a';

    CLOSURE(cf, int(T, char), T




closure<int(int x, int y), int, int> foo()
{
    int i = 3;
    int j = 4;

    CLOSURE(cf, int(int x, int y), (i)(j))
    {
        x = i;
        y = i;
        return x + y;
    }
    CLOSURE_END


    CLOSURE(int, cf, (int x)(int y), (int)(i)(int)(j))

    struct body
    {
        static int impl(int x, int y, separator, int i, int j)
        {

        }
    };

    boost::function<int(int, int)> cf = closure(&body::impl);



    boost::function<int(int& x, int y)> cf = uncurry(curry4(&body::impl)(i)(j));



    struct body
    {
        static int impl(int x, int y, int i, int j)
        {
            x = i;
            y = j;
            return x + y;
        }
    };

    boost::function<int(int, int)> cf = uncurry(curry4(&body::impl)(i)(j))
        
        bind(&body::impl, _1, _2, i, j);


    make_closure(&body::impl, i, j);

    closure<int(int, int), int, int> cf = {&body::impl, i,j};

    return cf;
}


PSTADE_EGG_LOCAL(int, name, (int x)(int y), (int i, int j))
{

}
PSTADE_EGG_LOCAL_END


typedef int

local<
    int(int i, int j, int x, int y),
    int,boost::tuple<int, int> > name = {i,j};


struct op_name {
    int operator()(int x, int y) const {
    }
    int i; int j;
} name = {i, j};


