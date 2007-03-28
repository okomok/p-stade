template< class Fun, class T >
void apply(Fun f, T& x)
{
    f(x);
}

void reset(double& d) { d = 0.0; }
void resee(double ) { /*output value*/ }
// ...

double d = 3;
d = d*d;
d = d/d;

::apply(::reset, d); // oops: resee intended