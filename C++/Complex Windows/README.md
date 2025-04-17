# Complex
A library defines 3 aggregate types for vectors, Vector1D, Vector3D and Vector7D
regard as the orientation component corresponds to Complex, Quaternion and
Octonion, while even higher dimensional Number utilized for Sedenion, Pathion,
Chingon, Routon, Voudon and so forth.

# Interfaces

The Cayley Dickson Algebra defines Number for general computational operation,
the operator \* achieving the multiplication of 2 Numbers where the procedures
first split the numbers into left and right portions then apply the operation
once more. The operation shall Merge the results from ultimate portions and
returns it. The Cayley Dickson Algebra defines Ev to trap some real arithmetic
to implementation-defined. The Module is to provide functionality for parsing,
formatting and converting between mathematical expressions and numerical arrays.
The ToString converts an array of numbers into a string representation of a
mathematical expression. The ToNumber parses a string representation of a
mathematical expression into an array of numbers. The Terms allows for flexible
term definitions either as named terms or as indexed terms. The Module handles
special floating-point values like NaN or Inf, ensuring robust handling of edge
cases in numerical computations.

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
Cos and Tan and their inverses, cyclometrics and hyperbolics at different level
to 24 combinations. The Arg, Ln, Power, Root, Log, and cyclometric combinations
overload a multi-value version. The conventions implement Str and Val to convert
in between string and that type. The casing implement Num and Val to interchange
format in between the underlying Number type from Cayley Dickson Algebra and
that type internally.