// Template to complete the loadfunc program which locates a function
// in the text section of an ELF file. Sections that start with a
// CAPITAL in their comments require additions and modifications to
// complete the program (unless marked as PROVIDED).

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <elf.h>

int DEBUG = 0;                  // PROVIDED: controls whether to print debug messages

int main(int argc, char **argv){
  if( argc > 1 && strcmp(argv[1], "-d")==0 ){// PROVIDED: command line handling of debug options
    DEBUG = 1;                               // check 1st arg for -d debug
    argv++;                                  // shift forward if found
    argc--;
  }
  if(argc < 3){                              // PROVIDED: command line checks for proper # args
    printf("usage: %s [-d] <file> <funcname> \n",argv[0]);
    return 0;
  }
  char *objfile_name = argv[1];
  char *func_name = argv[2];

  // PROVIDED: open file to get file descriptor
  int fd = open(objfile_name, O_RDWR);       // open file to get file descriptor

  // DETERMINE size of file and create read/write memory map of the file
  // pointer to file contents
  struct stat stat_buf;
  fstat (fd, &stat_buf);
  int size = stat_buf.st_size;
  char *file_bytes = mmap(NULL, size, PROT_EXEC, MAP_SHARED, fd, 0); // using mmap

  // CREATE A POINTER to the intial bytes of the file which are an ELF64_Ehdr struct
  Elf64_Ehdr *ehdr = (Elf64_Ehdr *) file_bytes;

  int ei_correct = // boolean like variable
    ehdr->e_ident[0] == 0x7f &&
    ehdr->e_ident[1] == 'E' &&
    ehdr->e_ident[2] == 'L' &&
    ehdr->e_ident[3] == 'F';

  if (!ei_correct) { // if opening sequence is wrong, doesn't match type
    printf("ERROR: Magic bytes wrong, this is not an ELF file");
    munmap(file_bytes, size);
    close(fd);
    return 1;
  }

  // PROVIDED: check for a 64-bit file
  if(ehdr->e_ident[EI_CLASS] != ELFCLASS64){
    printf("ERROR: Not a 64-bit file ELF file\n");
    munmap(file_bytes, size);
    close(fd);
    return 1;
  }

  // PROVIDED: check for x86-64 architecture
  if(ehdr->e_machine != EM_X86_64){
    printf("ERROR: Not an x86-64 file\n");
    munmap(file_bytes, size);
    close(fd);
    return 1;
  }

  // DETERMINE THE OFFSET of the Section Header Array (e_shoff), the
  // number of sections (e_shnum), and the index of the Section Header
  // String table (e_shstrndx). These fields are from the ELF File
  // Header.
  int offset = ehdr->e_shoff;
  int sections = ehdr->e_shnum;
  int index = ehdr->e_shstrndx;

  // SET UP a pointer to the array of section headers. Use the section
  // header string table index to find its byte position in the file
  // and set up a pointer to it.
  Elf64_Shdr *shdr = (Elf64_Shdr *) (file_bytes + offset);

  char *secnames = (char *) (file_bytes + shdr[index].sh_offset);

  // SEARCH the Section Header Array for sections with names .symtab
  // (symbol table) .strtab (string table), and .text (executable code
  // section).  Note their positions in the file (sh_offset field).
  // Also note the size in bytes (sh_size) and and the size of each
  // entry (sh_entsize) for .symtab so its number of entries can be
  // computed. Finally, note the .text section's index (i value in
  // loop) and its load address (sh_addr).
  int sym_index = -1;
  int text_index = -1;
  long unsigned int text_offset = -1;
  long unsigned int text_address = -1;
  long unsigned int sym_offset = -1;
  long unsigned int str_offset = -1;
  long unsigned int sym_size = -1;
  long unsigned int entry_size = 0;
  char *sec_name;

  for(int i=0; i<sections; i++){
    sec_name = (char *) (shdr[i].sh_name + secnames); // if .text
    if (strcmp(sec_name, ".text") == 0) {
      text_offset = shdr[i].sh_offset;
      text_index = i;
      text_address = shdr[i].sh_addr;
    }
    else if (strcmp(sec_name, ".symtab") == 0) { // if .symtab
      sym_offset = shdr[i].sh_offset;
      sym_size = shdr[i].sh_size;
      entry_size = shdr[i].sh_entsize;
      sym_index = i;
    }
    else if (strcmp(sec_name, ".strtab") == 0) { // if .strtab
      str_offset = shdr[i].sh_offset;
    }
  }

  // ERROR check to ensure everything was found based on things that
  // could not be found.

  if(str_offset == -1){
    printf("ERROR: Couldn't find symbol table\n");
    munmap(file_bytes, size);
    close(fd);
    return 1;
  }

  if(str_offset == -1){
    printf("ERROR: Couldn't find string table\n");
    munmap(file_bytes, size);
    close(fd);
    return 1;
  }

  if(text_offset == -1){
    printf("ERROR: Couldn't find text section\n");
    munmap(file_bytes, size);
    close(fd);
    return 1;
  }

  // PRINT info on the .text section where function bytes are stored
  char *text_sec = (file_bytes + text_offset);
  printf(".text section\n");
  printf("- %hd section index\n",text_index);
  printf("- %lu bytes offset from start of file\n",text_offset);
  printf("- 0x%lx preferred virtual address for .text\n",text_address);

  // PRINT byte information about where the symbol table was found and
  // its sizes. The number of entries in the symbol table can be
  // determined by dividing its total size in bytes by the size of
  // each entry.

  printf(".symtab section\n");
  printf("- %d section index\n",sym_index);
  printf("- %lu bytes offset from start of file\n",sym_offset);
  printf("- %lu bytes total size\n",sym_size);
  printf("- %lu bytes per entry\n",entry_size);
  printf("- %lu entries\n",sym_size/entry_size);


  // SET UP pointers to the Symbol Table and associated String Table
  // using offsets found earlier. Then SEARCH the symbol table for for
  // the specified function.

  Elf64_Sym *sym_table = (Elf64_Sym *) (file_bytes+sym_offset);

  int func_sec_index = -1;
  int func_sym_index = -1;
  long unsigned int func_value = -1;
  long unsigned int func_size = -1;
  unsigned int func_name_int = -1;

  for (int i = 0; i < (sym_offset-str_offset); i++) {
    char *temp = (char *)(file_bytes+str_offset+i);
    if((*temp) == 0 && (*(temp+1)) == 0) { // this is to fix a segementation fault
      break;                               // checks if two chars in a row are blank
    }
    if(strcmp(temp, func_name) == 0) {
      func_name_int = i;
      break;
    }
  }

  // Iterated through whole symbol tabel and did not find symbol, error out.
  if (func_name_int == -1) {
    printf("ERROR: Function '%s' not found\n",func_name);
    munmap(file_bytes, size);
    close(fd);
    return 1;
  }

  for(int i = 0; i < (sym_offset-str_offset); i++){
    if(sym_table[i].st_name == func_name_int) {
      func_sec_index = sym_table[i].st_shndx;
      func_sym_index = i;
      func_value = sym_table[i].st_value;
      func_size = sym_table[i].st_size;
      break;
    }
  }

    // If symbol at position i matches the 'func_name' variable
    // defined at the start of main(), it is the symbol to work on.
    // PRINT data about the found symbol.

  printf("Found Function '%s'\n",func_name);
  printf("- %d symbol index\n",func_sym_index);
  printf("- 0x%lx value\n",func_value);
  printf("- %lu size\n",func_size);
  printf("- %hu section index\n",func_sec_index);

  // CHECK that the symbol table field st_shndx matches the index
  // of the .text section; otherwise the symbol is not a function
  // in the .text section and we should bail out now.
  if(func_sec_index != text_index){ // check symbol is actually in the .text section
    printf("ERROR: '%s' in section %hd, not in .text section %hd\n", func_name,func_sec_index,text_index);
    munmap(file_bytes, size);
    close(fd);
    return 1;
  }

  // CALCULATE the offset of the value into the .text section. The
  // 'value' field of the symbol is its preferred virtual
  // address. The .text section also has a preferred load virtual
  // address. The difference between these two is the offset into
  // the .text section of the mmap()'d file.
  long unsigned int text_func_offset = func_value-text_address;

  printf("- %ld offset in .text of start of function\n",text_func_offset);

  // ITERATE: through the bytes of the loaded function
  printf("Bytes of function '%s'\n",func_name);
  for(int i = 0; i < (func_size+7)/8; i++){
    printf("%4x: ", i * 8);
    for (int j = 0; j < 8; j++) {
      if ((i*8)+j == func_size) {
        break;
      }
      printf("%02hhx ", text_sec[(i*8)+j+text_func_offset]);
    }
    printf("\n");
  }

  if (argc > 3) {
    if (strcmp(argv[3], "void->int") == 0) { // void -> int function
      printf("running void->int function\n");
      int (*func_ptr)() = (int (*)())(file_bytes + (text_offset + text_func_offset));
      int ret_val = func_ptr();
      printf("returned: %d", ret_val);
    }
    else if (strcmp(argv[3], "(int,int)->int") == 0) { // (int, int) -> int function
      int int_one = atoi(argv[4]);
      int int_two = atoi(argv[5]);
      printf("running int,int->int function with arguments (%d,%d)\n", int_one, int_two);
      int (*func_ptr)(int, int) = (int (*)(int, int))(file_bytes + (text_offset + text_func_offset));
      int ret_val = func_ptr(int_one, int_two);
      printf("returned: %d", ret_val);
    }
    else if (strcmp(argv[3], "int*->void") == 0) { // int* -> void function
      int int_stand = (atoi(argv[4]));
      int *int_one = &int_stand;
      printf("running int*->void function, arg points to %d\n", (*int_one));
      void (*func_ptr)(int*) = (void (*)(int*))(file_bytes + (text_offset + text_func_offset));
      func_ptr(int_one);
      printf("arg is now: %d", (*int_one));
    }
  }

  munmap(file_bytes, size);
  close(fd);
}
