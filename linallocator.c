#include <iostream>

struct linear_allocator_t
{
    void* base_pointer; // указатель на выделенный с помощью стандартной функции участок памяти
    size_t size;        // размер выделенной памяти
    size_t offset;      // смещение, относительно последнего выделения памяти, уже нашим собственным аллокатором.
};

//typedef struct linear_allocator_t linear_allocator_t;

// инициализация аллокатора
int la_init(linear_allocator_t* allocator, size_t memory_size) 
{
    if (memory_size == 0)
        return 0;

    allocator->offset = 0;
    allocator->size = memory_size;
    allocator->base_pointer = malloc(memory_size);
    return allocator->base_pointer != nullptr;
}

// выделение памяти аллокатором
void* la_allocate(linear_allocator_t* allocator, size_t allocated_size)
{
    // Проверяем на достаточное количество памяти для выделения
    if (allocator->offset + allocated_size > allocator->size)
        return nullptr;

    // Проверяем на ненулевой размер и на выравнивание
    if ((allocated_size == 0) || (allocator->size % allocated_size != 0))
        return nullptr;

    size_t allocated_pointer = (size_t)allocator->base_pointer + allocator->offset;
    allocator->offset += allocated_size;
    return (void*)allocated_pointer;
}

// освобождение памяти аллокатором
void la_reset(linear_allocator_t* allocator)
{
    free(allocator->base_pointer);
}

// Тестовая структура, только для проверки
struct vector_4d_t
{
    double x, y, z, w;
};

//typedef struct vector_4d_t vector_4d_t;


int main()
{
    // В данном примере фрагментация отсутствует
    linear_allocator_t allocator;
    la_init(&allocator, sizeof(vector_4d_t) * 10);
    for (int32_t i = 0; i < 10; i++)
    {
        vector_4d_t* vector = (vector_4d_t*)la_allocate(&allocator, sizeof(vector_4d_t));
        vector->x = vector->y = vector->z = vector->w = i;
    }
    la_reset(&allocator);
}