/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x|~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(~x & ~y) & ~(x & y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if(!x){
        if(y){
            return 0;
        }
        return 1;
    }
    if(!y){
        return 0;
    }  
    return !((x>>31)^(y>>31));

}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int s;
    int r=0;
    s=(v>0xFFFF)<<4;
    v=v>>s;
    r=r|s;
    s=(v>0xFF)<<3;
    v=v>>s;
    r=r|s;
    s=(v>0xF)<<2;
    v=v>>s;
    r=r|s;
    s=(v>0x3)<<1;
    v=v>>s;
    r=r|s;
    s=(v>0x1)<<0;
    v=v>>s;
    r=r|s;
    return r;
}   

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int a=n<<3;
    int b=m<<3;
    int p=0xFF<<a;
    int q=0xFF<<b;
    int shan=x&(~p & ~q);
    int aa=(x>>a)&0xFF;
    int bb=(x>>b)&0xFF;
    int pp=aa<<b;
    int qq=bb<<a;
    int r=shan|(pp|qq);

    return r;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned r = 0;
    int i = 32;
    while (i) {
        r = (r << 1) | (v & 1);
        v = v >> 1;
        i = i - 1;
    }
    return r;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int t=((1<<31)>>n)<<1;
    return (x>>n)&~t;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int n;
    int r=0;
    n=(!(~(x>>16)))<<4;
    x=x<<n;
    r+=n;
    n=(!(~(x>>24)))<<3;
    x=x<<n;
    r+=n;
    n=(!(~(x>>28)))<<2;
    x=x<<n;
    r+=n;
    n=(!(~(x>>30)))<<1;
    x=x<<n;
    r+=n;
    n=(!(~(x>>31)))<<0;
    x=x<<n;
    r+=n;
    r+=!(~(x>>31));
    return r;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned ux = x;
    unsigned sign = ux & 0x80000000;
    unsigned abs_x = ux;
    if (x < 0) abs_x = -ux;
    if (abs_x == 0) return 0;

    int k = -1;
    unsigned temp = abs_x;
    while (temp) {
        temp = temp >> 1;
        k = k + 1;
    }

    unsigned exp = k + 127;
    unsigned frac;

    if (k < 24) {
        frac = abs_x << (23 - k);
    } else {
        int shift = k - 23;
        unsigned mask = (1 << shift) - 1;
        unsigned dropped = abs_x & mask;
        unsigned half = 1 << (shift - 1);
        frac = abs_x >> shift;

        if (dropped > half) {
            frac = frac + 1;
        } else if (dropped == half) {
            if (frac & 1) frac = frac + 1;
        }

        if (frac & 0x1000000) {
            frac = frac >> 1;
            exp = exp + 1;
        }
    }

    return sign | (exp << 23) | (frac & 0x7FFFFF);
}


/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned sign = uf & 0x80000000;
    unsigned exp = (uf >> 23) & 0xFF;
    unsigned frac = uf & 0x7FFFFF;

    if (exp == 0xFF) return uf;          

    if (exp == 0) {                      
        frac = frac << 1;
        if (frac & 0x800000) {           
            exp = 1;
            frac = frac & 0x7FFFFF;
        }
        return sign | (exp << 23) | frac;
    }

    exp = exp + 1;                       
    if (exp == 0xFF) {                   
        return sign | 0x7F800000;
    }
    return sign | (exp << 23) | frac;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    unsigned sign = uf2 >> 31;
    unsigned exp = (uf2 >> 20) & 0x7FF;
    unsigned frac_hi = uf2 & 0xFFFFF;
    unsigned frac_lo = uf1;
    unsigned e;
    unsigned abs;
    unsigned shift;
    unsigned frac_shifted;

    if (exp >= 0x7FF) return 0x80000000;
    if (!exp) return 0;
    if (exp < 1023) return 0;
    e = exp - 1023;
    if (e >= 31) return 0x80000000;

    shift = 52 - e;

    if (shift >= 32) {
        frac_shifted = frac_hi >> (shift - 32);
    } else {
        frac_shifted = (frac_hi << (32 - shift)) | (frac_lo >> shift);
    }

    abs = (1 << e) + frac_shifted;

    if (sign) return -abs;
    return abs;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if (x > 127) return 0x7F800000;      
    if (x < -149) return 0;              
    if (x < -126) {                      
        return 1 << (x + 149);
    }
    return (x + 127) << 23;              
}