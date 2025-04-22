# Complex
A library defines 3 aggregate types for Vectors, Vector1D, Vector3D and Vector7D
regarded as the orientation components corresponding to Complex, Quaternion and
Octonion, while even higher dimensional Numbers are utilized for Sedenion,
Pathion, Chingon, Routon, Voudon and so forth.

# Interfaces
The Cayley Dickson Algebra defines Number for general computational operations,
the operator \* achieving the multiplication of 2 Numbers, where the procedure
first splits a Number into left and right portions, then applies the operation
again. The operation shall Merge the results from those ultimate portions and
return them. The Cayley Dickson Algebra defines Ev to trap some real arithmetic
to implementation-defined. The Module is to provide functionality for parsing,
formatting and converting between mathematical expressions and numerical arrays.
The ToString converts an array of numbers into a string representation of a
mathematical expression. The ToNumber parses a string representation of a
mathematical expression into an array of numbers. The Terms permit flexible term
definitions as either named or indexed terms. The Module shall handle specific
floating-point values like Nan or Inf, ensuring robust handling of edge cases in
numerical computations.

The Vector types introduce constants, basis, operators, multiples, fundamentals,
conventions and casing. The Number types introduce constants, basis, operators,
multiples, fundamentals, exponentials, trigonometrics, conventions and casing.
All aggregate type constants should provide zeros and their basis vectors. The
basis refer to the language-defined constructors (sometimes for casing) and
overrides (wrap for Str). The operators contain identicals and four arithmetic
operations. The multiples consist of Dot, Outer, Even and Cross, while Outer and
Even are only for Number types. The fundamentals define Abs, Arg, Conjg, Sgn,
Inverse, Exp and Ln, while these (except Abs and Sgn) are only for Number types.
The exponentials compute Power, Root and Log. The trigonometrics compute Sin,
Cos and Tan and their inverses, cyclometrics and hyperbolics at different levels
to 24 combinations. The Arg, Ln, Power, Root, Log, and cyclometrics overload
multi-value versions. The conventions implement Str and Val to convert between
strings and those types. The casing represents Num and Val from interchanging
formats internally between the underlying Number type from Cayley Dickson
Algebra and that type.
