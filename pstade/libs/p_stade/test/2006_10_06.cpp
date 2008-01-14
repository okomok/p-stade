

void a() { }


template< class T >
void x(T const&) { }

template< class T >
void y(T&) { }

template< class T >
void z(T) { }


template< class T >
void o(T&) { }

template< class T >
void o(T const&) { }


int main()
{
    // x(a); // error (1)
    x(&a);

    y(a);
    // y(&a); // error

    z(a); // decayed
    z(&a);

    o(a); // ??? (2)
}
