std::stringstream ss;
ss << "hello, memoized!";

::very_complicated_algorithm(
    oven::make_istream_range<char>(ss)
        | memoized
        | directed
        | indirected
        | sorted
        | memoized
);