#include <stdio.h>

int stdq(int am_q) {
    if (am_q < 10)
    {
        return am_q;
    }
    else if (am_q >= 10 && am_q <= 20) {
        return am_q * 4 / 5;
    }
    else {
        int p = 80;
        for (int loop = 0; loop < (am_q / 10); loop++) {
            p -= (p / 8);
        }
        return am_q * p / 100;
    }
}

