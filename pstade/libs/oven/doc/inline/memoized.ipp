std::stringstream ss;
ss << "hello, memoized!";

::very_complicated_algorithm(
    oven::stream_input<char>(ss)
        | memoized
        | directed
        | indirected
        | sorted
        | memoized
);