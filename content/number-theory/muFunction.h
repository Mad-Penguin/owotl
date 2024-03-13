/**
 * Author: Diego Garcia
 * Date: 2024-03-13
 * License: ???
 * Source: ~I made it up~ Folklore
 * Description: Sieve that computes $\mu$
 * Status: Tested
 */
 mu[1] = 1;
for(int i = 1; i < LIM; i++)
    for(int j = i+i; j < LIM; j += i)
        mu[j] -= mu[i];
