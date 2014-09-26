inline const Scalar& w() const
{
	static_assert( ColsAtCompileTime != Dynamic, "w() can only be called on static-sized vector types");
	static_assert( ColsAtCompileTime == 1 || RowsAtCompileTime == 1, "w() can only be called on vectors");
	static_assert( (ColsAtCompileTime == 1 && RowsAtCompileTime == 4) || (ColsAtCompileTime == 4 && RowsAtCompileTime == 1), "w() can only be called on 4-dimensional vectors types");
	return ( *this ) ( 3 );
}

inline void setW(const Scalar& w)
{
	static_assert(ColsAtCompileTime != Dynamic, "setW() can only be called on static-sized vector types");
	static_assert(ColsAtCompileTime == 1 || RowsAtCompileTime == 1, "setW() can only be called on vectors");
	static_assert((ColsAtCompileTime == 1 && RowsAtCompileTime == 4) || (ColsAtCompileTime == 4 && RowsAtCompileTime == 1), "setW() can only be called on 4-dimensional vectors types");
	(*this) (3) = w;
}