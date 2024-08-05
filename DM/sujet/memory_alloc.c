#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <setjmp.h>
#include "cmocka.h"
#include "memory_alloc.h"
#include <stdbool.h>


bool sort_enabled = false;

struct memory_alloc_t m;

/* Initialize the memory allocator */
void memory_init() {
  m.available_blocks = 16;
  m.first_block = 0;
  for (int i=m.first_block; i<m.available_blocks; i++) {
    m.blocks[i]=i+1;
  }
  m.blocks[m.available_blocks-1] = NULL_BLOCK;
  m.error_no = E_SUCCESS;
}

/* Return the number of consecutive blocks starting from first */
int nb_consecutive_blocks(int first) {
  /* TODO */
  int nb_consecutive = 1;
  int current = first;
  int next = m.blocks[first];
  while ((next != NULL_BLOCK) && (next==current+1)) {
    nb_consecutive++;
    current = next;
    next = m.blocks[next];
  }
  return nb_consecutive;
}

/* Reorder memory blocks */

void memory_reorder() {
  /* TODO (exercise 2) */
  //memory_print();
  int size = m.available_blocks;
  int previous = m.first_block;
  int current_val = m.first_block;
  int next_val = m.first_block;
  
  //printf("Size: %d\n", size);
  //printf("Initial First Block: %d\n", m.first_block);
  //memory_print();
  for (int step = 0; step < size - 1; step++) {
    previous = m.first_block;
    current_val = m.first_block;
    for (int i = 0; i < size - step - 1; i++) {
      next_val = m.blocks[current_val]; // current val pointe vers nextval
      //printf("Step %d, i %d: Current: %d, Next: %d, Previous: %d\n", step, i, current_val, next_val, previous);
      if (current_val > next_val) {
        //printf("Swapping %d and %d\n", current_val, next_val);
        m.blocks[current_val] = m.blocks[next_val]; // current val pointe maintenant vers l'adr contenue dans nextval
        m.blocks[next_val] = current_val; // next val pointe vers current_val
        if (i == 0) {
          m.first_block = next_val; // next val devient le nv first block, pas de previous a link
          //printf("Updating First Block: %d\n", m.first_block);
	  previous = next_val;
        } else {
	  //printf("First blocked not changed\n");
      	  m.blocks[previous] = next_val; // le previous de current?
	  // lier previous blocks[next] réparer ligne au dessus..
	  previous = next_val;
	}
	//	memory_print();
      } else {
	//printf("Not swapping  %d and %d\n", current_val, next_val);
	previous = current_val; // previous gardé en mémoire si besoin de swap à la prochaine étape
        current_val = next_val; // on check nouveau current et l'adr à laquelle il pointe (cf debut boucle)
      }
      //memory_print();
    }
  }

  //printf("Final First Block: %d\n", m.first_block);
}


/* Allocate size bytes
 * return -1 in case of an error
 */

int memory_allocate(size_t size) {
  /* TODO */

  int num_blocks = (size + 7) / 8;

  int nb_consecutives = 0;
  int previous = m.first_block;
  int current = m.first_block;
  int next = m.first_block;
  int first = -1;

  if (sort_enabled) { 
    //printf("Sorting is enabled\n");
    memory_reorder();
  }

  //  printf("Num blocks : %d\n", num_blocks);
  //  printf("Initial Previous: %d, Current: %d, Next: %d\n", previous, current, next);

  //  memory_print();
    
  while ((next != NULL_BLOCK) && (nb_consecutives < num_blocks)) {
    current = next;
    nb_consecutives = nb_consecutive_blocks(next);
    next = m.blocks[current + nb_consecutives - 1];

    // printf("Previous: %d, Current: %d, Next: %d, nb_consecutives: %d\n", previous, current, next, nb_consecutives);

    if (nb_consecutives < num_blocks) {
      previous = current + nb_consecutives - 1;
    }
  }

  if (nb_consecutives == num_blocks) {
    m.available_blocks -= num_blocks;
    m.error_no = E_SUCCESS;
    if (current == m.first_block) {
      initialize_buffer(m.first_block, size);
      m.first_block = next;
      first = current;
    } else {
      initialize_buffer(current, size);
      first = current;
      m.blocks[previous] = next;
    }
  } else if (nb_consecutives > num_blocks) {
    m.error_no = E_SUCCESS;
    m.available_blocks -= num_blocks;
    initialize_buffer(current, size);
    first = current;
    m.blocks[previous] = current + num_blocks;
  } else {
    first = -1;

    if (sort_enabled) {
      //printf("Sorting is enabled\n");
      m.error_no = E_SHOULD_PACK;
    } else {
      //printf("Sorting is not enabled\n");
      m.error_no = E_NOMEM;
    }
  }
  
  //  printf("Final Previous: %d, Current: %d, Next: %d, nb_consecutives: %d\n", previous, current, next, nb_consecutives);
  return first;
}

/* Free the block of data starting at address */
void memory_free(int address, size_t size) {
  /* TODO */
  int old_first = m.first_block;
  m.first_block = address;
  int num_blocks = (size + 7) / 8;
  for (int i=address; i<num_blocks+address; i++) {
    m.blocks[i] = i+1;
  }
  m.blocks[address+num_blocks-1] = old_first;
  m.available_blocks += num_blocks;
}

/* Print information on the available blocks of the memory allocator */
void memory_print() {
  printf("---------------------------------\n");
  printf("\tBlock size: %lu\n", sizeof(m.blocks[0]));
  printf("\tAvailable blocks: %lu\n", m.available_blocks);
  printf("\tFirst free: %d\n", m.first_block);
  printf("\tStatus: ");
  m.error_no = E_SUCCESS;
  memory_error_print(m.error_no);
  printf("\tContent:  ");

  /* TODO: browse the available blocks and print their index */

  printf("[%d] -> ", m.first_block);
  int current_index = m.blocks[m.first_block];
  while (current_index != NULL_BLOCK) {
    printf("[%d] -> ", current_index);
    current_index = m.blocks[current_index];
  }
  printf("NULL_BLOCK");
  printf("\n");
  printf("---------------------------------\n");
}


/* print the message corresponding to error_number */
void memory_error_print(enum memory_errno error_number) {
  switch(error_number) {
  case E_SUCCESS:
    printf("Success\n");
    break;
  case E_NOMEM:
    printf("Not enough memory\n");
    break;
  case  E_SHOULD_PACK:
    printf("Not enough contiguous blocks\n");
    break;
  default:
    printf("Unknown\n");
    break;
  }
}

/* Initialize an allocated buffer with zeros */
void initialize_buffer(int start_index, size_t size) {
  char* ptr = (char*)&m.blocks[start_index];
  for(int i=0; i<size; i++) {
    ptr[i]=0;
  }
}






/*************************************************/
/*             Test functions                    */
/*************************************************/

// We define a constant to be stored in a block which is supposed to be allocated:
// The value of this constant is such as it is different form NULL_BLOCK *and*
// it guarantees a segmentation vioaltion in case the code does something like
// m.blocks[A_B]
#define A_B INT32_MIN

/* Initialize m with all allocated blocks. So there is no available block */
void init_m_with_all_allocated_blocks() {
  struct memory_alloc_t m_init = {
    // 0    1    2    3    4    5    6    7    8    9   10   11   12   13   14   15
    {A_B, A_B, A_B, A_B, A_B, A_B, A_B, A_B, A_B, A_B, A_B, A_B, A_B, A_B, A_B, A_B},
    0,
    NULL_BLOCK,
    INT32_MIN // We initialize error_no with a value which we are sure that it cannot be set by the different memory_...() functions
  };
  m = m_init;
}

/* Test memory_init() */
void test_exo1_memory_init(){
  init_m_with_all_allocated_blocks();

  memory_init();

  // Check that m contains [0]->[1]->[2]->[3]->[4]->[5]->[6]->[7]->[8]->[9]->[10]->[11]->[12]->[13]->[14]->[15]->NULL_BLOCK
  assert_int_equal(m.first_block, 0);

  assert_int_equal(m.blocks[0], 1);
  assert_int_equal(m.blocks[1], 2);
  assert_int_equal(m.blocks[2], 3);
  assert_int_equal(m.blocks[3], 4);
  assert_int_equal(m.blocks[4], 5);
  assert_int_equal(m.blocks[5], 6);
  assert_int_equal(m.blocks[6], 7);
  assert_int_equal(m.blocks[7], 8);
  assert_int_equal(m.blocks[8], 9);
  assert_int_equal(m.blocks[9], 10);
  assert_int_equal(m.blocks[10], 11);
  assert_int_equal(m.blocks[11], 12);
  assert_int_equal(m.blocks[12], 13);
  assert_int_equal(m.blocks[13], 14);
  assert_int_equal(m.blocks[14], 15);
  assert_int_equal(m.blocks[15], NULL_BLOCK);
  
  assert_int_equal(m.available_blocks, DEFAULT_SIZE);

  // We do not care about value of m.error_no
}

/* Initialize m with some allocated blocks. The 10 available blocks are: [8]->[9]->[3]->[4]->[5]->[12]->[13]->[14]->[11]->[1]->NULL_BLOCK */
void init_m_with_some_allocated_blocks() {
  struct memory_alloc_t m_init = {
    // 0           1    2    3    4    5    6    7    8    9   10   11   12   13   14   15
    {A_B, NULL_BLOCK, A_B,   4,   5,  12, A_B, A_B,   9,   3, A_B,   1,  13,  14,  11, A_B},
    10,
    8,
    INT32_MIN // We initialize error_no with a value which we are sure that it cannot be set by the different memory_...() functions
  };
  m = m_init;
}

/* Test nb_consecutive_block() at the beginning of the available blocks list */
void test_exo1_nb_consecutive_blocks_at_beginning_linked_list(){
  init_m_with_some_allocated_blocks();
  memory_print(); // Ligne ajoutee
  assert_int_equal(nb_consecutive_blocks(8), 2);
}

/* Test nb_consecutive_block() at the middle of the available blocks list */
void test_exo1_nb_consecutive_blocks_at_middle_linked_list(){
  init_m_with_some_allocated_blocks();

  assert_int_equal(nb_consecutive_blocks(3), 3);
}

/* Test nb_consecutive_block() at the end of the available blocks list */
void test_exo1_nb_consecutive_blocks_at_end_linked_list(){
  init_m_with_some_allocated_blocks();

  assert_int_equal(nb_consecutive_blocks(1), 1);
}

/* Test memory_allocate() when the blocks allocated are at the beginning of the linked list */
void test_exo1_memory_allocate_beginning_linked_list(){
  init_m_with_some_allocated_blocks();

  assert_int_equal(memory_allocate(16), 8);
  //printf("OK1\n");
  /*
    // 0           1    2    3    4    5    6    7    8    9   10   11   12   13   14   15
    {A_B, NULL_BLOCK, A_B,   4,   5,  12, A_B, A_B,   9,   3, A_B,   1,  13,  14,  11, A_B}

   [8]->[9]->[3]->[4]->[5]->[12]->[13]->[14]->[11]->[1]->NULL_BLOCK
  */
  
  // We check that m contains [3]->[4]->[5]->[12]->[13]->[14]->[11]->[1]->NULL_BLOCK 
  assert_int_equal(m.first_block, 3);

  assert_int_equal(m.blocks[3], 4);
  assert_int_equal(m.blocks[4], 5);
  assert_int_equal(m.blocks[5], 12);
  assert_int_equal(m.blocks[12], 13);
  assert_int_equal(m.blocks[13], 14);
  assert_int_equal(m.blocks[14], 11);
  assert_int_equal(m.blocks[11], 1);
  assert_int_equal(m.blocks[1], NULL_BLOCK);
  
  assert_int_equal(m.available_blocks, 8);

  assert_int_equal(m.error_no, E_SUCCESS);
}

/* Test memory_allocate() when the blocks allocated are at in the middle of the linked list */
void test_exo1_memory_allocate_middle_linked_list(){
  init_m_with_some_allocated_blocks();

  assert_int_equal(memory_allocate(17), 3);
  
  // We check that m contains [8]->[9]->[12]->[13]->[14]->[11]->[1]->NULL_BLOCK 
  assert_int_equal(m.first_block, 8);

  assert_int_equal(m.blocks[8], 9);
  assert_int_equal(m.blocks[9], 12);
  assert_int_equal(m.blocks[12], 13);
  assert_int_equal(m.blocks[13], 14);
  assert_int_equal(m.blocks[14], 11);
  assert_int_equal(m.blocks[11], 1);
  assert_int_equal(m.blocks[1], NULL_BLOCK);
  
  assert_int_equal(m.available_blocks, 7);

  assert_int_equal(m.error_no, E_SUCCESS);
}

/* Test memory_allocate() when we ask for too many blocks ==> We get -1 return code and m.error_no is M_NOMEM */
void test_exo1_memory_allocate_too_many_blocks(){
  init_m_with_some_allocated_blocks();

  assert_int_equal(memory_allocate(256), -1);
  
  // We check that m does not change and still contains: [8]->[9]->[3]->[4]->[5]->[12]->[13]->[14]->[11]->[1]->NULL_BLOCK
  assert_int_equal(m.first_block, 8);

  assert_int_equal(m.blocks[8], 9);
  assert_int_equal(m.blocks[9], 3);
  assert_int_equal(m.blocks[3], 4);
  assert_int_equal(m.blocks[4], 5);
  assert_int_equal(m.blocks[5], 12);
  assert_int_equal(m.blocks[12], 13);
  assert_int_equal(m.blocks[13], 14);
  assert_int_equal(m.blocks[14], 11);
  assert_int_equal(m.blocks[11], 1);
  assert_int_equal(m.blocks[1], NULL_BLOCK);
  
  assert_int_equal(m.available_blocks, 10);

  assert_int_equal(m.error_no, E_NOMEM);
}

/* Test memory_free() */
void test_exo1_memory_free(){
  init_m_with_some_allocated_blocks();

  memory_free(6, 9);
  
  // We check that m contains: [6]->[7]->[8]->[9]->[3]->[4]->[5]->[12]->[13]->[14]->[11]->[1]->NULL_BLOCK
  assert_int_equal(m.first_block, 6);

  assert_int_equal(m.blocks[6], 7);
  assert_int_equal(m.blocks[7], 8);
  assert_int_equal(m.blocks[8], 9);
  assert_int_equal(m.blocks[9], 3);
  assert_int_equal(m.blocks[3], 4);
  assert_int_equal(m.blocks[4], 5);
  assert_int_equal(m.blocks[5], 12);
  assert_int_equal(m.blocks[12], 13);
  assert_int_equal(m.blocks[13], 14);
  assert_int_equal(m.blocks[14], 11);
  assert_int_equal(m.blocks[11], 1);
  assert_int_equal(m.blocks[1], NULL_BLOCK);
  
  assert_int_equal(m.available_blocks, 12);

  // We do not care about value of m.error_no
}

/* Test memory_reorder() */
void test_exo2_memory_reorder(){
  init_m_with_some_allocated_blocks();

  memory_reorder();
  
  // We check that m contains: [1]->[3]->[4]->[5]->[8]->[9]->[11]->[12]->[13]->[14]->NULL_BLOCK
  assert_int_equal(m.first_block, 1);

  assert_int_equal(m.blocks[1], 3);
  assert_int_equal(m.blocks[3], 4);
  assert_int_equal(m.blocks[4], 5);
  assert_int_equal(m.blocks[5], 8);
  assert_int_equal(m.blocks[8], 9);
  assert_int_equal(m.blocks[9], 11);
  assert_int_equal(m.blocks[11], 12);
  assert_int_equal(m.blocks[12], 13);
  assert_int_equal(m.blocks[13], 14);
  assert_int_equal(m.blocks[14], NULL_BLOCK);  
  assert_int_equal(m.available_blocks, 10);

  // We do not care about value of m.error_no
}

/* Test memory_reorder() leading to successful memory_allocate() because we find enough consecutive bytes */
void test_exo2_memory_reorder_leading_to_successful_memory_allocate(){
  sort_enabled=true;
  init_m_with_some_allocated_blocks();

  assert_int_equal(memory_allocate(32), 11);
  // We check that m contains: [1]->[3]->[4]->[5]->[8]->[9]->NULL_BLOCK
  assert_int_equal(m.first_block, 1);

  assert_int_equal(m.blocks[1], 3);
  assert_int_equal(m.blocks[3], 4);
  assert_int_equal(m.blocks[4], 5);
  assert_int_equal(m.blocks[5], 8);
  assert_int_equal(m.blocks[8], 9);
  assert_int_equal(m.blocks[9], NULL_BLOCK);
  
  assert_int_equal(m.available_blocks, 6);

  assert_int_equal(m.error_no, E_SUCCESS);
}

/* Test memory_reorder() leading to failed memory_allocate() because not enough consecutive bytes */
void test_exo2_memory_reorder_leading_to_failed_memory_allocate(){
  sort_enabled=true;
  init_m_with_some_allocated_blocks();

  assert_int_equal(memory_allocate(56), -1);

  // We check that m contains: [1]->[3]->[4]->[5]->[8]->[9]->[11]->[12]->[13]->[14]->NULL_BLOCK
  assert_int_equal(m.first_block, 1);

  assert_int_equal(m.blocks[1], 3);
  assert_int_equal(m.blocks[3], 4);
  assert_int_equal(m.blocks[4], 5);
  assert_int_equal(m.blocks[5], 8);
  assert_int_equal(m.blocks[8], 9);
  assert_int_equal(m.blocks[9], 11);
  assert_int_equal(m.blocks[11], 12);
  assert_int_equal(m.blocks[12], 13);
  assert_int_equal(m.blocks[13], 14);
  assert_int_equal(m.blocks[14], NULL_BLOCK);  
  assert_int_equal(m.available_blocks, 10);

  assert_int_equal(m.available_blocks, 10);

  assert_int_equal(m.error_no, E_SHOULD_PACK);
}

int main(int argc, char**argv) {
  const struct CMUnitTest tests[] = {
    /* a few tests for exercise 1.
     *
     * If you implemented correctly the functions, all these tests should be successfull
     * Of course this test suite may not cover all the tricky cases, and you are free to add
     * your own tests.
     */
    cmocka_unit_test(test_exo1_memory_init),
    cmocka_unit_test(test_exo1_nb_consecutive_blocks_at_beginning_linked_list),
    cmocka_unit_test(test_exo1_nb_consecutive_blocks_at_middle_linked_list),
    cmocka_unit_test(test_exo1_nb_consecutive_blocks_at_end_linked_list),
    cmocka_unit_test(test_exo1_memory_allocate_beginning_linked_list),
    cmocka_unit_test(test_exo1_memory_allocate_middle_linked_list),
    cmocka_unit_test(test_exo1_memory_allocate_too_many_blocks),
    cmocka_unit_test(test_exo1_memory_free),

    /* Run a few tests for exercise 2.
     *
     * If you implemented correctly the functions, all these tests should be successfull
     * Of course this test suite may not cover all the tricky cases, and you are free to add
     * your own tests.
     */

    cmocka_unit_test(test_exo2_memory_reorder),
    cmocka_unit_test(test_exo2_memory_reorder_leading_to_successful_memory_allocate),
    cmocka_unit_test(test_exo2_memory_reorder_leading_to_failed_memory_allocate)
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
