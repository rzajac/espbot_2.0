/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <quackmore-ff@yahoo.com> wrote this file.  As long as you retain this notice
 * you can do whatever you want with this stuff. If we meet some day, and you 
 * think this stuff is worth it, you can buy me a beer in return. Quackmore
 * ----------------------------------------------------------------------------
 */
#ifndef __DEBUG_H__
#define __DEBUG_H__

extern "C"
{
#include "mem.h"
}

#define ESPBOT_MEM 1

#ifdef ESPBOT_MEM

#define esp_zalloc(a) espmem.espbot_zalloc(a)
#define esp_free(a) espmem.espbot_free(a)
#define esp_stack_mon(a) espmem.stack_mon()

#else

#define esp_zalloc(a) os_zalloc(a)
#define esp_free(a) os_free(a)
#define esp_stack_mon(a)

#endif

struct heap_item
{
    int size;
    void *addr;
    int next_item;
};

#define HEAP_ARRAY_SIZE 20

class Esp_mem
{
  private:
    // stack infos
    uint32 m_stack_min_addr;
    uint32 m_stack_max_addr;
    // heap infos
    uint32 m_heap_start_addr;
    uint32 m_max_heap_size;
    uint32 m_min_heap_size;
    uint32 m_heap_objs;
    uint32 m_max_heap_objs;

    struct heap_item m_heap_array[HEAP_ARRAY_SIZE];
    int m_first_heap_item;
    int m_first_free_heap_item;

    void heap_mon(void);

  public:
    Esp_mem(){};
    ~Esp_mem(){};

    void init(void);

    void stack_mon(void);

    static void *espbot_zalloc(size_t);
    static void espbot_free(void *);

    uint32 get_min_stack_addr(void);
    uint32 get_max_stack_addr(void);

    uint32 get_start_heap_addr(void);
    uint32 get_max_heap_size(void);
    uint32 get_mim_heap_size(void);
    uint32 get_used_heap_size(void);
    uint32 get_max_heap_objs(void);
    struct heap_item *next_heap_item(int); // 0 -> return the first heap allocated item
                                           // 1 -> return the next heap allocated item
                                           // return NULL if no item is found
};

#endif