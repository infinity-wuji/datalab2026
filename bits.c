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
    return ~(~x | ~y); // 德摩根律
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
    if (!((x ^ 0) && (y ^ 0))) // 先处理至少一个为0的情况
        return !(x ^ y);
    return !((x >> 31) ^ (y >> 31)); // 都非0直接比较最高位
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
int logtwo(int v) { // 等价于找最高位1
    int ans = 0;

    int move16 = ((v >> 16) > 0) << 4; // 是否在高16位，构造一个在/不在分别对应16/0的变量
    v = v >> move16; // 右移16/0位
    ans = ans | move16; // 至少有16位

    int move8 = ((v >> 8) > 0) << 3; // 是否在高8位
    v = v >> move8;
    ans = ans | move8;

    int move4 = ((v >> 4) > 0) << 2; // 是否在高4位
    v = v >> move4;
    ans = ans | move4;

    int move2 = ((v >> 2) > 0) << 1; // 是否在高2位
    v = v >> move2;
    ans = ans | move2;

    int move1 = ((v >> 1) > 0); // 是否在高1位
    v = v >> move1;
    ans = ans | move1;

    return ans;
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
    int nBits = n << 3; // 移动到nth Byte需要的位数
    int mBits = m << 3; // 移动到mth Byte需要的位数
    int ans = x;

    int nthByte = (x >> nBits) & 0xFF; // 取出nth Byte到最低位并将ans的nth Byte设置为0
    ans = ans & ~(0xFF << nBits);

    int mthByte = (x >> mBits) & 0xFF; // 取出mth Byte到最低位并将ans的mth Byte设置为0
    ans = ans & ~(0xFF << mBits);

    ans = ans | (nthByte << mBits); // 将nth Byte放到mth Byte处
    ans = ans | (mthByte << nBits); // 将mth Byte放到nth Byte处

    return ans;
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
    unsigned ans = 0;

    for (int i = 0; 32 - i; i++)
    {
        ans = ans << 1;
        ans = ans | ((v >> i) & 0x1U); // 把最后一位放到ans末尾
    }

    return ans;
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
    int m = !n; // 判断n是否为0
    int move = n + ~0 + m; // n为0/非0分别右移(n - 1)/0
    int mask = (0x7FFFFFFF >> move) | (~m + 1); // 高n位为0，其余为1

    return (x >> n) & mask;
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
    int y = ~x; // 取反后类似logtwo，定位最高位1
    int ans = 31 + !y;

    int move16 = (!!((y >> 16) ^ 0)) << 4;
    y = y >> move16;
    ans = ans + (~move16 + 1);

    int move8 = (!!((y >> 8) ^ 0)) << 3;
    y = y >> move8;
    ans = ans + (~move8 + 1);

    int move4 = (!!((y >> 4) ^ 0)) << 2;
    y = y >> move4;
    ans = ans + (~move4 + 1);

    int move2 = (!!((y >> 2) ^ 0)) << 1;
    y = y >> move2;
    ans = ans + (~move2 + 1);

    int move1 = !!((y >> 1) ^ 0);
    y = y >> move1;
    ans = ans + (~move1 + 1);

    return ans;
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
    if (x == 0) // 单独处理0
    {
        return 0;
    }

    unsigned un_x = x; // 用unsigned存绝对值，避免Tmin取负溢出
    unsigned s = 0;
    unsigned exp = 0;
    unsigned frac = 0;
    unsigned move = 0;

    if (x < 0) // 负数单独处理s
    {
        s = 0x80000000U;
        un_x = -un_x;
    }

    while ((un_x >> move) > 1) // 类似logtwo，定位最高位1
    {
        move++;
    }
    exp = move + 127;

    if (move < 24) // 有效位不超过24位
    {
        frac = un_x << (23 - move);
    }
    else // 有效位超过24位
    {
        unsigned drop = move - 23; // 需要丢掉的低位位数
        unsigned rest = un_x & ((1 << drop) - 1);
        unsigned half = 1 << (drop - 1); // 丢掉的部分等于half
        frac = un_x >> drop;

        if ((rest > half) | ((rest == half) & (frac & 1))) // 超过一半进位，正好一半时末位为1才进位，保证取偶
        {
            frac = frac + 1;
        }

        if (frac >> 24) // 舍入后多出一位，右移一位并将指数加1
        {
            exp = exp + 1;
            frac = frac >> 1;
        }
    }

    return s | (exp << 23) | (frac & 0x007FFFFFU);
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
    unsigned s = (uf >> 31) & 0x1U;
    unsigned exp = (uf >> 23) & 0xFFU;
    unsigned frac = uf & 0x007FFFFFU; // 分段

    if (exp == 255U) // 对应Infinity和NaN
    {
        return uf;
    }

    if (exp == 0) // 对应+-0和非规格数
    {
        return (s << 31) | (exp << 23) | (frac << 1);
    }

    exp = exp + 1; // 对应规格数

    if (exp == 255U) // 避免溢出成NaN，修改为Infinity
    {
        frac = 0U;
    }

    return (s << 31) | (exp << 23) | frac;
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
    unsigned s = uf2 >> 31;

    unsigned exp = (uf2 >> 20) & 0x7FF;

    unsigned ans = 0x80000000U | ((uf2 & 0xFFFFF) << 11) | (uf1 >> 21); // 补上隐藏最高位1

    if (exp < 1023) // 绝对值小于1，向0取整后为0，也包括非规格数
    {
        return 0;
    }

    if (exp > 1054) // 实际指数超过31，超出int范围，也包括Infinity和NaN
    {
        return 0x80000000U;
    }
    
    ans = ans >> (1054 - exp); // 最高位1原来在第31位，右移到实际指数的位置，丢掉小数部分

    if (s) // 负数
    {
        if (ans > 0x80000000U) // 溢出
        {
            return 0x80000000U;
        }

        return -ans;
    }

    else // 正数
    {
        if (ans > 0x7FFFFFFFU) // 溢出
        {
            return 0x80000000U;
        }

        return ans;
    }
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
    if ( x < -149) // 非规格数以下
    {
        return 0;
    }

    if (x >= -149 && x <= -127) // 非规格数
    {
        return 0 | (0x800000 >> (-126 - x));
    }

    if (x >= -126 && x <= 128) // 规格数
    {
        return 0 | ((x + 127) << 23);
    }

    return 0x7F800000; // +INF
}
