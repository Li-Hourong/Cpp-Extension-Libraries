#pragma once
#include "cstdlib"
#include "iostream"

namespace Allocator
{
	class Allocator
	{
	public:
		Allocator(int);
		~Allocator();
		void* alloc(int);
		template<typename type> void dealloc(type*&);

	private:
		int ptr_num;
		int table_size;
		void** ptr_table;
	};

	Allocator::Allocator(int size)
	{
		ptr_table = (void**)malloc(size*sizeof(void*));
		for (int i = 0; i < size; i++)
			ptr_table[i] = nullptr;
		ptr_num = 0;
		table_size = size;
	}

	Allocator::~Allocator()
	{
		if (ptr_num != 0)
		{
			for (int i = 0; i < table_size; i++)
			{
				if (ptr_table[i])
				{
					free(ptr_table[i]);
					ptr_table[i] = nullptr;
				}
			}
		}
		free(ptr_table);
		ptr_table = nullptr;
	}

	void* Allocator::alloc(int mem_size)
	{
		if (ptr_num == table_size)
		{
			void** table = (void**)realloc(ptr_table, 2 * table_size);
			if (table) ptr_table = table;
			else
			{
				void** table = (void**)malloc(2 * table_size);
				for (int i = 0; i < table_size; i++)
					table[i] = ptr_table[i];
				for (int i = table_size; i < 2 * table_size; i++)
					table[i] = nullptr;
				free(ptr_table);
				ptr_table = table;
			}
			table_size = 2 * table_size;
		}
		void* ptr = malloc(mem_size);
		if (!ptr)
		{
			throw "Memory allocation failure.";
			return nullptr;
		}
		for (int i = 0; i < table_size; i++)
		{
			if (ptr_table[i] == nullptr)
			{
				ptr_table[i] = ptr;
				ptr_num++;
				return ptr;
			}
		}
	}

	template<typename type> void Allocator::dealloc(type*& aim_ptr)
	{
		if (!aim_ptr)
		{
			throw "Target pointer is null";
			return;
		}
		for (int i = 0; i < table_size; i++)
		{
			if (ptr_table[i] == aim_ptr)
			{
				free(aim_ptr);
				ptr_table = nullptr;
				aim_ptr = nullptr;
				ptr_num--;
				return;
			}
		}
	}
}

Allocator::Allocator allocator(2);
#define alc allocator.alloc
#define del allocator.dealloc
