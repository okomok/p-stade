wostream os(out);
os.reset(out);
os = out; // is the same as os.reset(out).
bool b = os; // b is true iif os holds a stream.
os << stm;
os << stm0 << stm1 << ... << stmN;
