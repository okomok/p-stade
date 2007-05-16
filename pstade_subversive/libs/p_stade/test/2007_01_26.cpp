 
#include <boost/utility/result_of.hpp> 


template<class F>
struct forward
{
    template<class A>
    // typename boost::result_of<F(A&)>::type // (1)
    typename boost::result_of<F const(A&)>::type // (2)
    operator()(A& a) const
    {
        return m_f(a);
    }

    explicit forward(F f) : m_f(f)
    { }

private:
    F m_f;
};

template<class F>
forward<F> make_forward(F f)
{
    return forward<F>(f);
}

int foo(int i)
{
    return i+1;
}

int main() 
{ 
    int i = 0;
    make_forward(&foo)(i);
} 
