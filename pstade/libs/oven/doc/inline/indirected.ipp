int src[]    = { 1,2,0,4,5 };
int answer[] = { 1,2,3,4,5 };
int *ptrs[]  = {&src[0],&src[1],&src[2],&src[3],&src[4]};

BOOST_FOREACH (int& i, ptrs|indirected) {
    if (i == 0)
        i = 3;
}

BOOST_CHECK( oven::equals(src, answer) );