inline const Scalar& x() const
{
	static_assert( ColsAtCompileTime != Dynamic, "x() can only be called on static-sized vector types");
	static_assert( ColsAtCompileTime == 1 || RowsAtCompileTime == 1, "x() can only be called on vectors");
	static_assert( (ColsAtCompileTime == 1 && RowsAtCompileTime >= 1 && RowsAtCompileTime <= 4) || (ColsAtCompileTime >= 1 && ColsAtCompileTime <= 4 && RowsAtCompileTime == 1), "x() can only be called on 1, 2, 3 or 4-dimensional vectors types");
	return ( *this ) ( 0 );
}

inline const Scalar& y() const
{
	static_assert( ColsAtCompileTime != Dynamic, "y() can only be called on static-sized vector types");
	static_assert( ColsAtCompileTime == 1 || RowsAtCompileTime == 1, "y() can only be called on vectors");
	static_assert( (ColsAtCompileTime == 1 && RowsAtCompileTime >= 2 && RowsAtCompileTime <= 4) || (ColsAtCompileTime >= 2 && ColsAtCompileTime <= 4 && RowsAtCompileTime == 1), "y() can only be called on 2, 3 or 4-dimensional vectors types");
	return ( *this ) ( 1 );
}

inline const Scalar& z() const
{
	static_assert( ColsAtCompileTime != Dynamic, "z() can only be called on static-sized vector types");
	static_assert( ColsAtCompileTime == 1 || RowsAtCompileTime == 1, "z() can only be called on vectors");
	static_assert( (ColsAtCompileTime == 1 && RowsAtCompileTime >= 3 && RowsAtCompileTime <= 4) || (ColsAtCompileTime >= 3 && ColsAtCompileTime <= 4 && RowsAtCompileTime == 1), "z() can only be called on 3 or 4-dimensional vectors types");
	return ( *this ) ( 2 );
}

inline void setX(const Scalar &x)
{
	static_assert(ColsAtCompileTime != Dynamic, "setX() can only be called on static-sized vector types");
	static_assert(ColsAtCompileTime == 1 || RowsAtCompileTime == 1, "setX() can only be called on vectors");
	static_assert((ColsAtCompileTime == 1 && RowsAtCompileTime >= 1 && RowsAtCompileTime <= 4) || (ColsAtCompileTime >= 1 && ColsAtCompileTime <= 4 && RowsAtCompileTime == 1), "setX() can only be called on 1, 2, 3 or 4-dimensional vectors types");
	(*this) (0) = x;
}

inline void setY(const Scalar &y)
{
	static_assert(ColsAtCompileTime != Dynamic, "setY() can only be called on static-sized vector types");
	static_assert(ColsAtCompileTime == 1 || RowsAtCompileTime == 1, "setY() can only be called on vectors");
	static_assert((ColsAtCompileTime == 1 && RowsAtCompileTime >= 2 && RowsAtCompileTime <= 4) || (ColsAtCompileTime >= 2 && ColsAtCompileTime <= 4 && RowsAtCompileTime == 1), "setY() can only be called on 2, 3 or 4-dimensional vectors types");
	(*this) (1) = y;
}

inline void setZ(const Scalar &z)
{
	static_assert(ColsAtCompileTime != Dynamic, "setZ() can only be called on static-sized vector types");
	static_assert(ColsAtCompileTime == 1 || RowsAtCompileTime == 1, "setZ() can only be called on vectors");
	static_assert((ColsAtCompileTime == 1 && RowsAtCompileTime >= 3 && RowsAtCompileTime <= 4) || (ColsAtCompileTime >= 3 && ColsAtCompileTime <= 4 && RowsAtCompileTime == 1), "setZ() can only be called on 3 or 4-dimensional vectors types");
	(*this) (2) = z;
}