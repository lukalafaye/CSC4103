#ifndef MEMORY_ALLOC_H
#define MEMORY_ALLOC_H

#include <stdint.h>

/* a block that does not exists */
#define NULL_BLOCK INT32_MAX

/* number of blocks */
#define DEFAULT_SIZE 16

/* a memory page is 8 bytes (64 bits) */
typedef int64_t memory_page_t;

/* result of the last memroy operation */
enum memory_errno {
  E_SUCCESS,			/* success */
  E_NOMEM,			/* error: not enough memory */
  E_SHOULD_PACK,		/* error: not enough consecutive blocks */
};

struct memory_alloc_t {
  /* blocks that can be allocated */
  memory_page_t blocks[DEFAULT_SIZE];

  /* number of blocks that are available */
  size_t available_blocks;

  /* index of the first available block */
  int first_block;

  /* error of the last memory operation. to be updated during each
   * call to memory_free/memory_alloc/memory_init
   */
  enum memory_errno error_no;
};

extern struct memory_alloc_t m;

/* Initialize the memory_alloc_t structure */
void memory_init();

/* return the number of consecutive blocks starting from first */
int nb_consecutive_blocks(int first);

/* Print the current status of the memory_alloc_t structure */
void memory_print();

/* Allocate size consecutive bytes and return the index of the first
 * memory block
 */
int memory_allocate(size_t size);

/* Free the size bytes memory space starting at address addr */
void memory_free(int addr, size_t size);

/* Print a message corresponding to errno */
void memory_error_print(enum memory_errno error_number);

/* Initialize an allocated buffer with zeros */
void initialize_buffer(int start_index, size_t size);


#endif	/* MEMORY_ALLOC_H */
