#include <rsa.h>

void rsa_keygen(bignum * n, bignum * e, bignum * d, int len)
{
  bignum p, q, phi_n;
  bignum t0, t1, bgcd, tmp;
  bignum ONE = bignum_from_int(1);

  p = bignum_rand_prime(len);
  q = bignum_rand_prime(len);

  while (bignum_cmp(p, q) == 0) {
    free(q.tab);
    q = bignum_rand_prime(len);
  }
  *n = bignum_mult(p, q);
  t0 = bignum_sub(p, ONE);
  t1 = bignum_sub(q, ONE);
  phi_n = bignum_mult(t0, t1);
  free(t0.tab);
  free(t1.tab);
  
  *e = bignum_from_int(3);

  while (1) {
    bgcd = bignum_gcd(*e, phi_n);
    if (bignum_cmp(bgcd, ONE) == 0) {
      free(bgcd.tab);

      *d = bignum_inverse(*e, phi_n);
      break;
    }

    int e_len;
    do {
      e_len = rand() % (bignum_length(*n));
    } while (e_len <= 1);

    do {
      free(e->tab);
      *e = bignum_rand(e_len);
    } while (bignum_is_zero(*e) || bignum_is_one(*e));
  }

  free(ONE.tab);
  free(p.tab);
  free(q.tab);
  free(phi_n.tab);
}

bignum rsa_encrypt(bignum m, bignum e, bignum n)
{
  return bignum_expmod(m, e, n);
}

bignum rsa_decrypt(bignum c, bignum d, bignum n)
{
  return bignum_expmod(c, d, n);
}

void test_rsa(int len)
{
  bignum n, e, d, m, c, _m;

  m = bignum_rand(len - 5);
  printf("Keygen\n");
  rsa_keygen(&n, &e, &d, len);
  printf("Encrypt\n");
  c = rsa_encrypt(m, e, n);
  printf("Decrypt\n");
  _m = rsa_decrypt(c, d, n);

  printf("%s\n", (bignum_cmp(m, _m) == 0) ? "Success" : "Fail");

  if (bignum_cmp(m, _m) != 0) {
    printf ("n = ");
    bignum_dump(n);
    printf ("e = ");
    bignum_dump(e);
    printf ("d = ");
    bignum_dump(d);
    printf ("m = ");
    bignum_dump(m);
    printf ("c = ");
    bignum_dump(c);
    printf ("_m = ");
    bignum_dump(_m);
  } else {
    printf ("n = ");
    bignum_dump(n);
    printf ("e = ");
    bignum_dump(e);
    printf ("d = ");
    bignum_dump(d);
  }
  
  free(n.tab);
  free(e.tab);
  free(d.tab);
  free(m.tab);
  free(c.tab);
  free(_m.tab);
}
