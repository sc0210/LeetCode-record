/* 371 Sum of Two integers */

/*
    Key: In C, left-shifting a signed integer into the sign bit
         is undefined behavior.
*/

int getSum(int a, int b)
{
    unsigned int ua = (unsigned int) a;
    unsigned int ub = (unsigned int) b;

    while (ub != 0) {
        unsigned int carry = (ua & ub) << 1;
        ua = ua ^ ub;
        ub = carry;
    }

    return (int) ua;
}