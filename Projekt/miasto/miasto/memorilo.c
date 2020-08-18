#include <stdlib.h>
#include <stdio.h>

static struct __info
{
    const char * szFilename;
    int nLine;
    long int lSize;
    void * pAddress;
    
    struct __info * pNext;
} * __pHead = 0;


static struct __info * __addInfo (struct __info * pHead, long int size, const char* filename, int line, void * address)
{
    struct __info * pNew = malloc (sizeof *pNew); // according to https://stackoverflow.com/questions/605845/do-i-cast-the-result-of-malloc
    (*pNew).szFilename = filename;
    (*pNew).nLine = line;
    (*pNew).lSize = size;
    (*pNew).pAddress = address;
    
    (*pNew).pNext = pHead;
    return pNew;
}

static struct __info * __remove_info (struct __info * pH, void * pA)
{
	struct __info** owner = &pH;
	while (*owner)
	{
		if ((*owner)->pAddress == pA)
		{
			struct __info* tmp = (*owner)->pNext;
			free(*owner);
			*owner = tmp;
			break;
		}
		owner = &(*owner)->pNext;
	}
	return pH;

    //if (pH)
    //{
    //    if ((*pH).pAddress == pA) // usuwamy
    //    {
    //        struct __info * p = (*pH).pNext;
    //        free(pH);
    //        return p;
    //    }
    //    else 
    //    {
    //        (*pH).pNext = __remove_info((*pH).pNext, pA);
    //        return pH;
    //    }
    //}
}

void Free (void * p, const char* filename, int line)
{
    //printf ("%s (%d): memory from address %p desallocated\n", filename, line, p);
    __pHead = __remove_info(__pHead, p);
    
    free (p);
}

static struct __info *  __remove (struct __info * pHead)
{
	while (pHead)
	{
		struct __info* tmp = pHead->pNext;
		free(pHead);
		pHead = tmp;
	}
	return NULL;
    //if (pHead)
    //{
    //    __remove ((*pHead).pNext);
    //    free (pHead);
    //}
    //return 0;
}

static void __print (struct __info * pHead)
{
	while (pHead)
	{
		 printf ("%s (%d): %ld B allocated\n", (*pHead).szFilename, (*pHead).nLine, (*pHead).lSize);
		 pHead = pHead->pNext;
	}
    //if (pHead)
    //{
    //     printf ("%s (%d): %ld B allocated\n", (*pHead).szFilename, (*pHead).nLine, (*pHead).lSize);
    //     __print((*pHead).pNext);
    //}
}

void __print_report(void)
{    
    __print (__pHead);   
    __pHead = __remove(__pHead);
}

static void* __malloc_impl(long int size, const char* filename, int line)
{
	//printf ("%s (%d): %ld allocated\n", filename, line, size);
	void* address = malloc(size);
	__pHead = __addInfo(__pHead, size, filename, line, address);
	return address;
}
static void* __malloc_plus_register_print_report(long int size, const char* filename, int line);
static void* (*__cur_malloc_fun)(long int size, const char* filename, int line) = __malloc_plus_register_print_report;

/*
 ta funkcja bedzie odpalona tylko przy pierwszym uzyciu malloc i zarejestruje print report jako funkcje ktora ma sie wywolac
 gdy main sie skonczy
*/
static void* __malloc_plus_register_print_report(long int size, const char* filename, int line)
{
	atexit(__print_report);
	__cur_malloc_fun = __malloc_impl;
	return __cur_malloc_fun(size, filename, line);
}

void* Malloc(long int size, const char* filename, int line)
{
	return __cur_malloc_fun(size, filename, line);
}


//////////////////
/*
void* operator new (size_t size, const char* filename, int line) 
{
   void* ptr = malloc(size);
   memorilero.addVariable(reinterpret_cast<std::uintptr_t>(ptr), size, filename, line); 
   return ptr;
}

void* operator new[] (size_t size, const char* filename, int line) 
{
   void* ptr = malloc(size);
   memorilero.addArray(reinterpret_cast<std::uintptr_t>(ptr), size, filename, line); 
   return ptr;
}

void operator delete (void * ptr) noexcept
{
   if (memorilero.removeVariable (reinterpret_cast<std::uintptr_t>(ptr))) 
      free (ptr);
}
void operator delete[] (void * ptr) noexcept
{
   if (memorilero.removeArray (reinterpret_cast<std::uintptr_t>(ptr)))
      free(ptr);
}
*/
/////////////////////////


