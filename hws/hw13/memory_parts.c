// memory_parts.c: Allocate memory for variables in different regions
// then pause to allow command pmap to be run. Demonstrates several
// call to mmap() as well to map files and create blocks at specific
// virtual addresses.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>


char global_arr[4096] = {};
double global_var = 1.2345;

int main(int argc, char *argv[]){
  char local_arr[512] = {};

  char *malloc_arr = malloc(128);

  // memory map a file
  int fd = open("gettysburg.txt", O_RDONLY); // open file to get file descriptor
  struct stat stat_buf;
  fstat(fd, &stat_buf);                      // get stats on the open file such as size
  int size = stat_buf.st_size;               // size for mmap()'ed memory is size of file
  char *file_chars =                         // pointer to file contents
    mmap(NULL, size, PROT_READ, MAP_PRIVATE, // call mmap with given size and file descriptor
         fd, 0);                             // read only, not shared, offset 0

  // create 2 blocks of mmap()'d space starting at a fixed address
  // which are contiguous
  char *address = (char *) 0x0000600000000000; // requested starting address for block
  size_t bsize = 0x1000;
  char *block1 =
    mmap(address, bsize,                     // request start address and size
         PROT_READ | PROT_WRITE,             // can read and write this block
         MAP_PRIVATE | MAP_ANONYMOUS,        // not shared or tied to a file
         -1, 0);                             // default options for anonymous block
  char *block2 =
    mmap(address+bsize, bsize,               // start at end of previous block
         PROT_READ | PROT_WRITE,             // similar options to previous block
         MAP_PRIVATE | MAP_ANONYMOUS,
         -1, 0);

  printf("%p : main()\n", main);
  printf("%p : global_arr\n", global_arr);
  printf("%p : local_arr\n",  local_arr);
  printf("%p : malloc_arr\n", malloc_arr);
  printf("%p : mmap'd file\n", file_chars);
  printf("%p : mmap'd block1\n", block1);
  printf("%p : mmap'd block2\n", block2);
  int pid = getpid();
  printf("my pid is %d\n",pid);

  printf("press any key to continue\n");
  getc(stdin);                  // get a character

  free(malloc_arr);                          // free malloc'd array
  munmap(file_chars, size);                  // unmap and close file
  munmap(block1, bsize*2);                   // single unamp for contiguous memory

  close(fd);

  return 0;
}
