/*
TASK 1. Tests
*/

#include <stdio.h>
#include <stdlib.h>

long long modular_exponentiation(long long x, long long d, long long n) {
    if (d == 0) return 1;
    else if (d % 2 == 0) {
        int z = modular_exponentiation(x, d / 2, n);
        return (z * z) % n;
    } else {
        int z = modular_exponentiation(x, (d - 1) / 2, n);
        return (z * z * x) % n;
    }
}

int main() {
    long long chiselko = 0;
    scanf("%lld", &chiselko);
    long long t = chiselko - 1;
    long long s = 0;
    while (t % 2 == 0) {
        t /= 2;
        s++;
    }
    long long co1 = 0, co2 = 0, can = 0, hmmm = 1;
    for (long long a = 1; a <= chiselko - 1; ++a) {
        int flag1 = 0, flag2 = 0;
        long long x = modular_exponentiation(a, t, chiselko);
        if (x == 1) {
            co1++;
            flag1 = 1;
        }
        for (long long r = 0; r < s; r++) {
            long long zz = (long long)1 << r;
            long long rr = modular_exponentiation(a, zz * t, chiselko);
            if (rr == chiselko - 1) {
                co2++;
                flag2 = 1;
            }
        }
        if (flag1 + flag2 == 0) {
            can++;
            hmmm = 0;
        }
    }
    printf("Miller-Rabin test: %s %lld %lld %lld\n", hmmm ? "True" : "False", can, co1, co2);

    long long co = 0, cand = 0, hmm = 1;
    for (long long x = 1; x <= chiselko - 1; ++x) {
        long long r = modular_exponentiation(x, chiselko - 1, chiselko);
        if (r == 1) {
            co++;
        } else {
            hmm = 0;
            cand++;
        }
    }
    printf("Fermat test: %s %lld %lld", hmm ? "True" : "False", cand, co);
}

/*
TASK 2. Sieve
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    int start = 0, stop = 0;
    scanf("%d%d", &start, &stop);
    printf("Start and finish: %d %d\n", start, stop);

    int* range = (int*)malloc((stop + 1) * sizeof(int));
    for (int i = 0; i <= stop; ++i) range[i] = 0;

    int non_primes = 0;
    int iter = 0;

    for (int check = 2; check * check <= stop; ++check) {
        if (range[check] == 0) {
            int prime_count = 0;
            int* current = (int*)malloc((stop + 1) * sizeof(int));
            for (int i = 2; i <= stop; ++i) {
                if (i % check == 0 && i != check && range[i] == 0) {
                    if (i >= start && i <= stop) {
                        current[prime_count] = i;
                        prime_count++;
                        non_primes++;
                    }
                    range[i] = 1;
                }
                if (non_primes == stop - start + 1) break;
            }
            iter++;
            if (prime_count != 0) {
                printf("Iteration : %d\n", iter);
                for (int j = 0; j < prime_count; j++) printf("%d ", current[j]);
                printf("\n");
            }
            free(current);
        }
    }

    printf("Primes :\n");
    if (non_primes == stop - start + 1) printf("No primes");
    for (int i = start; i <= stop; ++i) if (range[i] != 1) printf("%d ", i);

    free(range);
    return 0;
}

/*
TASK 3. RSA (Rivest–Shamir–Adleman)
*/

#include <stdio.h>
#include <stdlib.h>

long long gcd(long long a, long long b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

void extended_euclid(long long a, long long b, long long* arr) {
    if (b == 0) {
        arr[0] = a;
        arr[1] = 1;
        arr[2] = 0;
        return;
    }
    extended_euclid(b, a % b, arr);
    long long g = arr[0];
    long long x = arr[1];
    long long y = arr[2];
    arr[1] = y;
    arr[2] = x - (a / b) * y;
}

long long modular_pow(__int128 base, long long exp, long long mod)
{
    __int128 result = 1;
    while (exp) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    long long p, q, e_start;
    scanf("%lld%lld%lld\n", &p, &q, &e_start);
    long long n = p * q;
    long long phi_n = (p - 1) * (q - 1);
    
    // Find e
    long long e;
    for (int i = e_start; i < 100000; i++) {
        if (gcd(phi_n, i) == 1) {
            e = i;
            break;
        }
    }
    
    long long arr[3] = {0};
    extended_euclid(phi_n, e, arr);
    long long d = arr[2] < 0 ? phi_n + arr[2] % phi_n : arr[2] % phi_n;

    printf("Private: %lld %lld\n", d, n);
    printf("Public: %lld %lld\n", e, n);

    char s[7];
    scanf("%s", s);
    
    int i = 0;
    __int128 x = (__int128)s[i];
    
    printf("Initial bytes: ");
    while (i < 6 && s[i] != '\n' && s[i] != '\0') {
        if (i >= 1) x = x * 256 + (__int128)s[i];
        printf("%lld ", (__int128)s[i]);
        i++;
    }
    printf("\n");
    
    __int128 y = modular_pow(x, e, n);
    __int128 mass[7];
    
    int index = 0;
    while (y > 0) {
        mass[index++] = y % 256;
        y /= 256;
    }
    
    printf("Encrypted bytes: ");
    for (int i = index - 1; i >= 0; i--) printf("%lld ", mass[i]);
    
    return 0;
}
