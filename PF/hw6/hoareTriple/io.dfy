/**
 * Basic Dafny IO library (but only input) for the course
 * Programming Fundamentals at the University of Groningen.
 * 
 * This library can be used very easily by just writing
 *    include "io.dfy"
 * at the top of your Dafny files, after which you can use
 * the various functions using IO.<funname>().
 * 
 * Floris Westerman, 2023
 */

module IO {
    //
    // Defining some C# types for use in our Dafny code, so we can
    // interact with the native libraries for IO. An alternative would be
    // to write a C# library that would do all this for us, directly consuming
    // and producing Dafny-native types. However, that would complicate the
    // compilation/runtime command for students, which is not desirable.
    //
    import opened NativeTypes // Directly import in the IO scope for us to use
    module {:extern "System"} {:compile false} NativeTypes {
        // This is a neat trick we can do using integral types: making a new
        // type alias for integers within the specified bounds, which will then
        // be represented as a native "int" in the compiled code, instead of
        // "BigInteger" as is done by default. This allows us to interact with
        // native C# functions that do not accept a BigInteger, while allowing
        // direct conversion between int and NativeInt in Dafny itself.
        newtype {:nativeType "int"} NativeInt = x : int | -0x8000_0000 <= x < 0x8000_0000 {
            // We can even define functions here!
            static function {:extern "Int32", "Parse"} Parse(ns: NativeString): NativeInt
        }

        // Parse a biginteger
        class {:extern "BigInteger"} BigInteger {
            static function {:extern "BigInteger", "Parse"} Parse(ns: NativeString): int
        }

        // For Char and other types, no such "aliasing" is possible, so we just
        // define a Char class that won't be easily convertable. We define
        // some static functions that will come in useful.
        // 
        // Note that this char type is very different from the Dafny "char":
        // the C# char type is a 16-bit integer, while the Dafny char is
        // implemented as a "Rune", accepting any UTF codepoint.
        class {:extern "Char"} NativeChar {
            static function {:extern "Char", "Parse"} {:axiom} FromString(ns: NativeString): NativeChar
            static function {:extern "Convert", "ToChar"} {:axiom} FromInt(ni: NativeInt): NativeChar
            static function {:extern "Char", "IsWhiteSpace"} IsWhiteSpace(nc: NativeChar): bool
        }

        // Same for the decimal type, which has no Dafny equivalent even
        class {:extern "Decimal"} NativeDecimal {
            static function {:extern "Decimal", "Parse"} {:axiom} Parse(ns: NativeString): NativeDecimal

            // For this function we need to do some special work to make the
            // compiler stop complaining, even though the individual components
            // can definitely represent negative integers.
            // Sadly, the C# call returns an int[] instead of a uint[]. That would
            // have made this a lot neater.
            static function {:extern "Decimal", "GetBits"} {:axiom} GetBits(nd: NativeDecimal): (bits: array<NativeInt>)
                ensures bits.Length == 4 && forall k :: 0 <= k < 4 ==> 0 <= bits[k]
        }

        class {:extern "String"} NativeString {}
    }

    import opened DafnyTypes
    module {:extern "Dafny"} {:compile false} DafnyTypes {
        // Reals in Dafny are implemented as "BigRational"s in C#, but we can't
        // directly access the constructor of a real in Dafny itself. We can
        // call the constructor function of the class, as we do here, but then
        // we are left with a DafnyReal type which Dafny does not recognize as
        // a real "real".
        //
        // To convert from DafnyReal to real, we use an identity function provided
        // in the Dafny Helpers class, that will just map an object to itself,
        // and since the backing C# types of both DafnyReal and real are the same,
        // that will just work in C# while convincing Dafny we are suddenly able
        // to convert between both types...
        class {:extern "BigRational"} DafnyReal {
            constructor {:extern} FromRational(num: int, den: int)
        }
    }

    // Helper functions to convert types
    import opened Convert
    module {:compile false} Convert {
        import opened NativeTypes

        // Generic helper class to allow conversion of any type to another, provided
        // their backing types in C# are the same or have implicit casts between them.
        // For example, int <-> BigInteger would all work fine, but String and Char won't.
        class {:extern "Dafny.Helpers"} Convert<From> {
            static function {:extern "Dafny.Helpers", "Id"} From<Target>(from: From): Target

            // We also add a function for the string representation of any type
            static function {:extern "Dafny.Helpers", "ToString"} {:axiom} ToNativeString(from: From): NativeString

            // And then we sneak this one in, but it only really accepts a NativeString
            static function {:extern "Dafny.Sequence<Dafny.Rune>", "UnicodeFromString"} {:axiom} ToString(from: From): string
        }
    }

    // The native Console API exposed in Dafny using native types
    module {:compile false} Console {
        import opened NativeTypes

        function {:extern "Console", "ReadLine"} ReadLine() : (ns: NativeString?)
        function {:extern "Console", "Read"} Read() : (ni: NativeInt)
    }

    /*
        The real module functions that we want to expose to users
        of the IO module. These are intended for reading input in various
        forms, such as strings, ints, floats, bools, etc.
    */
    export provides ReadLine, ReadChar, ReadInt, ReadInts, ReadNat, ReadNats, ReadReal, ReadReals

    // Read a single line from the input and convert to a Dafny string
    method {:axiom} ReadLine() returns (s: string) {
        var ns := Console.ReadLine();
        expect ns != null, "ReadLine failed";
        return Convert.ToString(ns);
    }

    // Read the next character from the input and convert to a Dafny char (Rune)
    method {:axiom} ReadChar() returns (c: char) {
        var cint := Console.Read(); // read returns an integer that we have to cast
        expect cint >= 0 && cint < 256, "Read failed";
        return cint as char;
    }

    // Read the next character from the input and convert it to a native C# char
    method {:axiom} ReadNativeChar() returns (nc: NativeTypes.NativeChar) {
        // We obtain a native integer from the native read, which we convert to
        // the Dafny equivalent type to do an EOF check.
        var ni := Console.Read();
        expect ni != -1, "Unexpected End-of-File!";

        // Convert the original native integer to a native char
        nc := NativeChar.FromInt(ni);
    }

    // Read the next "word" from the input, defined as a sequence of characters
    // surrounded by whitespace. This will ignore any leading whitespace and will
    // stop reading as soon as whitespace is encountered.
    //
    // Note: We don't verify this function, since the while loops iterating over
    // the input cannot have a termination proof. We could artificially limit their
    // iteration count, but that distracts from the purpose of this library.
    method {:axiom} ReadWord() returns (ns: NativeTypes.NativeString) {
        // We create a sequence of native chars which we then convert to
        // a native string.
        var ncs := [];

        // Read the first character and determine whether it's whitespace
        var nc := ReadNativeChar();
        var isWhiteSpace := NativeChar.IsWhiteSpace(nc);

        // First we ignore any whitespace present at the start of the input
        while(isWhiteSpace) {
            nc := ReadNativeChar();
            isWhiteSpace := NativeChar.IsWhiteSpace(nc);

            // Dirty trick to keep Dafny happy
            assume {:axiom} false;
        }

        // As soon as we found non-whitespace, we read all non-whitespace
        // characters and put them in the sequence
        while(!isWhiteSpace) {
            ncs := ncs + [nc];

            nc := ReadNativeChar();
            isWhiteSpace := NativeChar.IsWhiteSpace(nc);

            // Dirty trick to keep Dafny happy
            assume {:axiom} false;
        }

        // Convert the sequence of native chars to a native string
        return Convert.ToNativeString(ncs);
    }

    // Read the next int from the input
    method ReadInt() returns (i: int) {
        // Approach: read the next "word" from the input and try to convert
        // it to an integer
        var ns := ReadWord();
        return BigInteger.Parse(ns);
    }

    // Read the next 'n' ints from the input
    method {:axiom} ReadInts(n: nat) returns (ints: seq<int>)
        ensures |ints| == n
    {
        ints := [];

        for _ := 0 to n {
            var i := ReadInt();
            ints := ints + [i];
        }
        expect |ints| == n, "Not enough integers";
    }

    // Read next natural number from the input
    method {:axiom} ReadNat() returns (n: nat) {
        // Approach: read the next integer and make sure it's not
        // negative.
        var i := ReadInt();
        expect i >= 0, "Input is not an integer";

        return i;
    }

    // Read the next 'n' natural numbers from the input
    method {:axiom} ReadNats(n: nat) returns (nats: seq<nat>)
        ensures |nats| == n
    {
        nats := [];
        
        for _ := 0 to n {
            var i := ReadNat();
            nats := nats + [i];
        }
        expect |nats| == n, "Not enough natural numbers";
    }

    // Read the next real from the input
    // Don't try to enable verification here, the large bit vectors
    // overwhelm Dafny
    method {:axiom} ReadReal() returns (r: real) {
        // Approach is to read a word from the input, and convert it to
        // a C# "decimal" type, which can accurately represent nearly any
        // number (in particular, always any number you can input in a
        // string up to 79228162514264337593543950335)
        //
        // Since there is no Dafny-provided way to convert a decimal
        // into their own real ("BigRational") type, we have to do this
        // ourselves by obtaining the binary representation of the decimal
        // and reconstruct the rational number from it.
        
        // First, obtain the binary representation of the decimal
        var word := ReadWord();
        var bits := NativeDecimal.GetBits(NativeDecimal.Parse(word));

        // The first 96 bits contain the real and raw value: "1.0" is
        // represented as 10. These bits are in inverse order, with later
        // bits at higher significance.
        //
        // We will concatenate these bits, so we work with a 96-bit value.
        // (bv96 is a bit vector of 96 bits)
        var rawBinary := 0 as bv96;
        for i := 0 to 3 {
            // Unfortunately, the components of bits[] are 32-bit integers in C#,
            // and Dafny interprets them as "int"s with infinite precision. As
            // a consequence, simply converting the value to a bv96 would cause
            // a negative value to be reinterpreted.
            // So if C# returns 0xFFFF_FFFF, Dafny interprets it as (-1), which
            // then becomes 0xFFFF_FFFF_FFFF_FFFF_FFFF_FFFF in bv96...
            // So first we cast to a 32-bit vector, then to a 96-bit one, and then
            // we can perform the bit shift and addition.
            rawBinary := rawBinary + (((bits[i] as bv32) as bv96) << (i * 32));
        }
        var raw := rawBinary as int;

        // The last 32 bits contain the "flags": the scale (location of the
        // decimal point), and the sign.
        var flags := bits[3] as bv32;

        // The scale is located in bits 16-23, and is just the 10-base exponent
        // of the number.
        var scale := ((flags >> 16) & 0x7F) as int;
        var exp := 1;
        for _ := 0 to scale { exp := exp * 10; }

        // The sign is located in bit 31 of the flags register
        var sign := (flags & 0x8000_0000) != 0;
        if(sign) { raw := raw * -1; }

        // We then create a new "BigRational" instance and convince Dafny it's
        // a type it knows.
        var rational := new DafnyReal.FromRational(raw, exp);
        return Convert.From(rational);
    }

    // Read the next 'n' reals from the input
    method {:axiom} ReadReals(n: nat) returns (reals: seq<real>)
        ensures |reals| == n
    {
        reals := [];

        for _ := 0 to n {
            var r := ReadReal();
            reals := reals + [r];
        }

        expect |reals| == n, "Not enough reals";
    }
}