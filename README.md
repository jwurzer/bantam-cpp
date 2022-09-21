bantam-cpp
==========

This is a tiny little C++ app to demonstrate Pratt parsing. For a full
explanation, see Bob Nystrom's blog post [**Pratt Parsers: Expression Parsing Made Easy**][blog].

[blog]: http://journal.stuffwithstuff.com/2011/03/19/pratt-parsers-expression-parsing-made-easy/

This is a C++ port of Bob Nystrom's [bantam][java].
The original bantam is implemented in Java (see: https://github.com/munificent/bantam).

[java]: https://github.com/munificent/bantam

## About this C++ port

This C++ port can be found on [github][cpp] at https://github.com/jwurzer/bantam-cpp.

[cpp]: https://github.com/jwurzer/bantam-cpp

This C++ version corresponds as best as possible to the original Java version.
It uses C++11. This C++ port is implemented as a **header-only** library.
All necessary files are located in the include directory. The member functions are
implemented directly in the according class in the header file instead of
in a separate C++ file. This also has the advantage that it looks even more like
the Java version. Only the test program for testing the implementation is located
in the C++ file src/main.cpp.

## Implementations & Ports

Original [bantam](https://github.com/munificent/bantam) in Java by Bob Nystrom.

This [C++11 port](https://github.com/jwurzer/bantam-cpp) by Jürgen Wurzer.

[C++20 port](https://github.com/stefanboca/bantam-cpp) by Stefan Boca.

[Rust port](https://github.com/jwurzer/bantam-rust) by Jürgen Wurzer.

[C# port](https://github.com/jfcardinal/BantamCs) by John Cardinal.


## License

bantam-cpp  is licensed like the original bantam under the very permissive [MIT license](LICENSE).
