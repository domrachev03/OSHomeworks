#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define N 10
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t var = PTHREAD_COND_INITIALIZER;
int counter = 0;
int array[N];

void *producer_func(void *abc) {
  int current_value = 0;
  time_t last_print_time = time(NULL);

  while (1) {
    if (counter < N && time(NULL) - last_print_time > 3) {
      array[counter] = current_value;
      counter++;

      if (counter > 0) {
        pthread_cond_signal(&var);
      }

      current_value++;
      last_print_time = time(NULL);
    } else if (counter >= N) {
      pthread_cond_wait(&var, &mutex);
    }
  }
  return 0;
}

void *consumer_func(void *abc) {
  while (1) {
    if (counter > 0) {
      printf("Number I got is %d!\n", array[counter - 1]);
      counter--;
      if (counter < N) {
        pthread_cond_signal(&var);
      }
    } else {
      pthread_cond_wait(&var, &mutex);
    }
  }
  return 0;
}

int main() {
  pthread_t consumer, producer;
  pthread_create(&producer, NULL, producer_func, NULL);
  pthread_create(&consumer, NULL, consumer_func, NULL);

  pthread_join(consumer, NULL);
  pthread_join(producer, NULL);
  return 0;
}
