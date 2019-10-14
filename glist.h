#ifndef GLIST__H
#define GLIST__H

// ------------------------- INCLUDES -------------------------- //

#include <stdlib.h>

// --------------------- TYPES DEFINITIONS --------------------- //

typedef struct GLIST_ELEMENT GLIST_ELEMENT;
typedef struct GLIST GLIST;

// ------------------------ STRUCTURES ------------------------- //

struct GLIST_ELEMENT
{
	GLIST_ELEMENT* next;
	GLIST_ELEMENT* previous;

	void* data;
};

struct GLIST
{
	GLIST_ELEMENT* first;
	GLIST_ELEMENT* last;

	// This variable is strictly reserved
	// for the internal glist functions
	size_t count;
};

// ------------------- FUNCTIONS -------------------- //

// Return an initialized list
static inline GLIST glist_create()
{
	GLIST list;

	list.first = NULL;
	list.last = NULL;
	list.count = 0;

	return list;
}

static inline void* copy_to_heap(void* _source, size_t _memSize)
{
	char* sourceBytes = (char*)_source;
	char* heapBytes = (char*)malloc(_memSize);

	// Copy byte per byte
	for (size_t i = 0; i < _memSize; i++)
		*(heapBytes + i) = *(sourceBytes + i);

	return heapBytes;
}

static inline void glist_add_front(GLIST* _list, void* _data, size_t _dataMemSize)
{
	void* data = copy_to_heap(_data, _dataMemSize);

	GLIST_ELEMENT* oldFirst = _list->first;

	GLIST_ELEMENT* newFirst = (GLIST_ELEMENT*)malloc(sizeof(GLIST_ELEMENT));
	newFirst->data = data;
	newFirst->next = oldFirst;
	newFirst->previous = NULL;

	if (oldFirst != NULL)
		oldFirst->previous = newFirst;

	_list->first = newFirst;

	if (_list->count == 0)
		_list->last = newFirst;

	_list->count++;
}

static inline void glist_add_back(GLIST* _list, void* _data, size_t _dataMemSize)
{
	void* data = copy_to_heap(_data, _dataMemSize);

	GLIST_ELEMENT* oldLast = _list->last;

	GLIST_ELEMENT* newLast = (GLIST_ELEMENT*)malloc(sizeof(GLIST_ELEMENT));
	newLast->data = data;
	newLast->next = NULL;
	newLast->previous = oldLast;

	if (oldLast != NULL)
		oldLast->next = newLast;

	_list->last = newLast;

	if (_list->count == 0)
		_list->first = newLast;

	_list->count++;
}

static inline void glist_remove(GLIST* _list, GLIST_ELEMENT* _elementToRemove)
{
	if (_elementToRemove == NULL)
		return;

	if (_list->first == _elementToRemove)
		_list->first = _list->first->next;

	if (_list->last == _elementToRemove)
		_list->last = _list->last->previous;

	if (_elementToRemove->next != NULL)
		_elementToRemove->next->previous = _elementToRemove->previous;

	if (_elementToRemove->previous != NULL)
		_elementToRemove->previous->next = _elementToRemove->next;

	free(_elementToRemove->data);
	free(_elementToRemove);

	_list->count--;
}

static inline void glist_clear(GLIST* _list)
{
	GLIST_ELEMENT* elementToRemove;
	GLIST_ELEMENT* currentElement;

	for (currentElement = _list->first; currentElement != NULL;)
	{
		elementToRemove = currentElement;
		currentElement = currentElement->next;

		free(elementToRemove->data);
		free(elementToRemove);
	}

	// Re-initialization
	_list->first = NULL;
	_list->last = NULL;
	_list->count = 0;
}

#endif // GLIST__H