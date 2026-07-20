#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>


typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef i8 b8;
typedef i32 b32;

#define ARENA_BASE_POS (sizeof(mem_arena))
#define ARENA_ALIGN (sizeof(void*)) // better to align with size of word(=void*)


#define Kib(n) ((u64)(n) << 10)
#define Mib(n) ((u64)(n) << 20)
#define Gib(n) ((u64)(n) << 30)

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define ALIGN_UP_POW2(n, p) (((u64)(n) + ((u64)(p) - 1)) & (~((u64)(p) - 1)))

typedef struct{
    u64 capacity;
    u64 pos;
} mem_arena;


mem_arena* arena_create(u64 capacity);
void arena_deatroy(mem_arena* arena);

void* arena_push(mem_arena* arena, u64 size, b32 non_zero); //pushing memory to the arena, pushing bc we working on a stuck
void arena_pop(mem_arena* arena, u64 size);
void arena_pop_to(mem_arena* arena, u64 pos);
void arena_clear(mem_arena* arena);

#define PUSH_STRUCT(arena, T) (T*)arena_push(arena, sizeof(T), false)
#define PUSH_STRUCT_NZ(arena, T) (T*)arena_push(arena, sizeof(T), true)
#define PUSH_ARRAY(arena, T, n) (T*)arena_push(arena, sizeof(T) * (n), false)
#define PUSH_ARRAY_NZ(arena, T, n) (T*)arena_push(arena, sizeof(T) * (n), true)

int main(void){
   mem_arena* perm_arena = arena_create(Mib(1));

   

    arena_deatroy(perm_arena);    
    return 0;
}



mem_arena* arena_create(u64 capacity){
    mem_arena* arena = (mem_arena*)malloc(capacity);

    arena->capacity = capacity;
    arena->pos = ARENA_BASE_POS;

    return arena;
}

void arena_deatroy(mem_arena* arena){
    free(arena);
}

void* arena_push(mem_arena* arena, u64 size, b32 non_zero){
    u64 pos_aligned = ALIGN_UP_POW2(arena->pos, ARENA_ALIGN);
    u64 new_pos = pos_aligned + size;
    
    if(new_pos > arena->capacity) {return NULL;}

    arena->pos = new_pos;

    u8* out = (u8*)arena + pos_aligned;

    if(!non_zero){
        memset(out, 0, size);
    }

    return out;
}

void arena_pop(mem_arena* arena, u64 size){ // make sure size not too much and remove size from the pos
    size = MIN(size, arena->pos - ARENA_BASE_POS);
    arena->pos -= size;
}

void arena_pop_to(mem_arena* arena, u64 pos){
    u64 size = pos < arena->pos ? arena->pos - pos : 0;
    arena_pop(arena,size);
}

void arena_clear (mem_arena* arena){ 
    arena_pop_to(arena, ARENA_BASE_POS);
}


