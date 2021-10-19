#include <stdio.h>
#include <stdlib.h>

#define bool unsigned char
#define TRUE 1
#define FALSE 0

struct page_frame {
  int page_number;
  unsigned char control_bits;
};

/*
 * I didn't get what is needed in second task
 */

int main() {
  int n, m, hit_rate = 0, miss_rate = 0;

  scanf("%d%d", &n, &m);
  struct page_frame *frames = malloc(sizeof(struct page_frame) * n);

  for (int i = 0; i < n; ++i) {
    frames[i].page_number = -1;
    frames[i].control_bits = 0;
  }

  int t_prev = 0, t, a, delete_candidate;
  bool is_hit = TRUE;

  for (int i = 0; i < m; ++i) {
    scanf("%d %d", &t, &a);

    if (t_prev != t) {
      for (int k = 0; k < n; ++k) {
        frames[k].control_bits >>= 1;
      }

      if (!is_hit) {
        frames[delete_candidate].control_bits = 1 << 7;
      }
    }
    printf("---------------------------------------------------\n Time: %d, "
           "Request on "
           "page: %d",
           t, a);

    t_prev = t;

    delete_candidate = 0;

    for (int k = 0; k < n; ++k) {
      if (frames[k].page_number == -1) {
        delete_candidate = k;
        break;
      }

      if (frames[delete_candidate].control_bits > frames[k].control_bits ||
          (frames[delete_candidate].control_bits == frames[k].control_bits &&
           frames[delete_candidate].page_number > frames[k].page_number)) {
        delete_candidate = k;
      }
    }

    printf(" Candidate for replace - element %d!\n", delete_candidate);
    is_hit = FALSE;

    for (int k = 0; k < n; ++k) {

      if (frames[k].page_number == a) {
        hit_rate++;
        frames[k].control_bits += 1 << 7;
        is_hit = TRUE;

        break;
      }
    }

    if (!is_hit) {
      miss_rate++;
      frames[delete_candidate].page_number = a;
    }

    for (int k = 0; k < n; ++k) {
      printf("%d[%d] ", frames[k].page_number, frames[k].control_bits);
    }

    printf("%d\n", is_hit);
  }

  printf("%lf", hit_rate * 1. / miss_rate);

  return 0;
}
