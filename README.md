# Generic List for C Language

glist is an easy to use header only generic list for C language.

As it's not using template class but void pointers it's up to you to manage what list contains what type.

## Installation

Just drop and include the __glist.h__ file to your project !

## Usage

```c
// create a list
GLIST list = glist_create();

int a = 1;
// add a new element to the front of the list
glist_add_front(&list, &a, sizeof(int));

int b = 2;
// add a new element to the back of the list
glist_add_back(&list, &b, sizeof(int));

// remove the first element of the list
glist_remove(&list, list.first);

// clear the list
glist_clear(&list);

// iterate on each element of list
for (GLIST_ELEMENT* e = list.first; e != NULL; e = e->next)
{
    // get element data
    int* data = (int*)e->data;

    printf("%i\n", *data);
}

// reverse iterate on each element of list
for (GLIST_ELEMENT* e = list.last; e != NULL; e = e->previous)
{
    // ...
}
```
