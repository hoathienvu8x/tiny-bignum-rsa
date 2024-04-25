#ifndef __RSA_H__
#define __RSA_H__

#include <bignum.h>

/* plain RSA algorithm */
void rsa_keygen(bignum * n, bignum * e, bignum * d, int length);
bignum rsa_encrypt(bignum m, bignum e, bignum n);
bignum rsa_decrypt(bignum c, bignum d, bignum n);
void test_rsa(int length);

#endif

