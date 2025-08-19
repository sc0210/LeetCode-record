/* 3304. Find the K-th Character in String Game I */
#include <math.h>

char kthCharacter(int k)
{
    /*  a
    *   a b

        0 1 2 3
        1 2 3 4
    *   a b b c

    *   0 1 2 3 4 5 6 7
    *   1 2 3 4 5 6 7 8
        a b b c b c c d
          ^   ^       ^                      ^
    *   0 1 2 3 4 5 6 7  8  9 10 11 12 13 14 15
    *   1 2 3 4 5 6 7 8  9 10 11 12 13 14 15 16
    *   a b b c b c c d  b  c  c  d  c  d  d  e
    */

    // 2^0, 2^1, 2^2, 2^3,...

    if (k == 1)
        return 'a';

    int count = 0, half = 1;

    while (k > 2) {
        half = 1;  // reset the val of half
        for (int i = 1; i < k; i++) {
            if ((pow(2, i) < k) && (k <= pow(2, i + 1))) {
                half = pow(2, i);
                break;
            }
        }

        k = k % half;
        if (k == 0)
            k = half;  // modify the edge value

        count++;
    }

    if (k == 1)
        return 'a' + count;  // k == 1, start from 'a'
    return 'b' + count;      // k == 2, start from 'b'
}