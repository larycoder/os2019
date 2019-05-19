# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>

# define buffer_size 2

typedef struct {
  char *name; // name of package
  char *version; // version of package
  char *author; // who created this package
} pkg;

pkg buffer[buffer_size]; // queue to transfer package from productor to user
int first = 0;
int last = 0;

void produce (pkg *i);
pkg receive (void);
pkg pack (char *name, char *version, char *author);

void *factory_thread (void *arg);
void *user_thread (void *arg);


int main(){
  pthread_t factory_addr;
  pthread_t user_addr;
  pthread_create (&factory_addr, NULL, factory_thread, NULL);
  pthread_create (&user_addr, NULL, user_thread, NULL);
  pthread_join(factory_addr,NULL);
  pthread_join(user_addr,NULL);
  return 0;
}

// productor will produce package
void produce (pkg *i) {
  while ((first + 1) % buffer_size == last) {
    ; // wait for empty queue
  }
  memcpy(&buffer[first], i, sizeof(pkg));
  first = (first + 1) % buffer_size;
  printf("\nLog of send package: \nFirst: %d\nLast: %d\n",first,last);
}

// user will receive package
pkg receive (void) {
  pkg i;
  while (first == last) {
    ; // wait for package put to queue
  }
  memcpy(&i, &buffer[last], sizeof(pkg));
  last = (last + 1) % buffer_size;
  printf("\nLog of recieve package: \nFirst: %d\nLast: %d\n",first,last);
  return i;
}

// pack package to send to user
pkg pack (char *name, char *version, char *author) {
  pkg box;
  box.name = name;
  box.version = version;
  box.author = author;
  return box;
}

// factory thread produce package
void *factory_thread (void *arg) {
  pkg sbox1 = pack("ls","1.0","anonymous");
  pkg sbox2 = pack("bc","2.1","anonymous");
  pkg sbox3 = pack("ls","beta","anonymous");
  produce(&sbox1);
  produce(&sbox2);
  produce(&sbox3);
  return NULL;
}

// user thread receive package
void *user_thread (void *arg) {
  for (int i =0; i<2; i++) {
    pkg rbox = receive();
    printf("\nthe package number %d:\n",i+1);
    printf ("name: %s\n",rbox.name);
    printf ("version: %s\n",rbox.version);
    printf ("author: %s\n",rbox.author);
  }
  return NULL;
}