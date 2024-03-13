mu[1] = 1;
for(int i = 1; i < LIM; i++)
    for(int j = i+i; j < LIM; j += i)
        mu[j] -= mu[i];
