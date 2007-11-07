
#if 0

template<class Base>
struct lambda_functor;

template<class Action, class Args>
struct lambda_functor_base;

template<class Func>
struct lambda_adaptor;

template<int I, class Action>
struct action;



template<int I>
struct placeholder;

template< >
struct placeholder<0x02>
{
    template<class A0, class A1, class A2>
    struct sig
    {
        typedef A1 &type;
    };

    template<class Result, class A0, class A1, class A2> 
    Result call(A0 &a0, A1 &a1, A2 &a2, Env &env) const
    {
        return a1;
    }
};


template<class Base>
struct lambda_functor : Base
{
    template<class This, class A0, class A1, class A2>
    struct sig
    {
        typedef typename Base::template sig<A0, A1, A2>::type type;
    };

    template<class A0, class A1, class A2>
    typename Base::template sig<A0 &, A1 &, A2 &>::type
    operator()(A0 & a0, A1 &a1, A2 &a2) const
    { 
        return Base::template call<
            typename Base::template sig<A0 &, A1 &, A2 &>::type
        >(a0, a1, a2, cnull_type()); 
    }
};



template<class Target, class Arg>
lambda_functor<
    lambda_functor_base<
        action< 2, function_action<2> >
        boost::tuple<Target const, Arg const>
    >
> const
bind(Target const &fun, Arg const &arg)
{
    return
        lambda_functor<
            lambda_functor_base<
                action< 2, function_action<2> >
                boost::tuple<Target const, Arg const>
            >
        >(
            boost::tuple<Target const, Arg const>(fun, arg)
        )
    ;
}

#endif


#include <boost/lambda/bind.hpp>
#include <boost/lambda/core.hpp>


namespace bll = boost::lambda;


int f(int i) { return i+1; }
int g(int i) {
    return i-1;
}

int g(int i, int j) { return i + j; }

int main()
{
    int _20 = 20;
    bll::bind(&g, 10, bll::_1)(_20);
//    int _10 = 10;
//    bll::bind(&f, bll::bind(&g, bll::_1))(_10);
}

