#include <stdio.h>
#include <stdlib.h>

typedef void* address;

typedef struct xlist_delegate_op {
  void (*add)(void*, address);
  address (*get)(void*, size_t);
} xlist_delegate_op;

typedef struct xlist {
  void* delegate;
  xlist_delegate_op *d_op;

  // public interfaces
  void (*add)(struct xlist*, address);
  address (*get)(struct xlist*, size_t);
  void (*map)( struct xlist*,  void* (*)(void*) );
} xlist;

void xlist_delegate_add(xlist* x, address e)
{
  x->d_op->add(x->delegate, e);
}

address xlist_delegate_get(xlist* x, size_t i)
{
  return x->d_op->get(x->delegate, i);
}

xlist* xlist_delegate( void* delegate , xlist_delegate_op *d_op )
{
  xlist* x = malloc( sizeof(xlist) );
  x->delegate = delegate;

  x->d_op = d_op;

  x->add = xlist_delegate_add;
  x->get = xlist_delegate_get;
  x->map = NULL; // not yet.

  return x;
}

typedef struct listnode {
  address addr;
  struct listnode *next;
} listnode;

typedef struct linkedlist {
  size_t len;
  listnode* null_head;
} linkedlist;

linkedlist* linkedlist_init()
{
  linkedlist* l = malloc( sizeof(linkedlist) );  
  l->len = 0;  
  l->null_head = malloc( sizeof(listnode) ); 
  return l;
}

linkedlist* cast(void* x)
{
  return (linkedlist*) x;
}

size_t linkedlist_len(void* x)
{
  linkedlist* _x = cast(x);
  return _x->len;
}

listnode* __linkedlist_get(void* x, size_t idx)
{
  printf("idx=%d\n", idx);
  linkedlist* _x = cast(x);
  listnode* cur = _x->null_head;
  int i;
  int end = idx;
  for(i=-1; i<end; i++){
    printf("inner %d\n", i);
    cur = cur->next;
  }
  return cur;
}

listnode* tail(void* x)
{
  linkedlist* _x = cast(x);
  return __linkedlist_get( _x, linkedlist_len(x)-1 ); 
}

void linkedlist_add(void* x, address e)
{
  linkedlist* l = cast(x);
  listnode* node = malloc( sizeof(listnode) ); 
  node->addr = e;
  tail(l)->next = node;   
  l->len++;
}

address linkedlist_get(void* x, size_t idx)
{
  printf("main idx=%d\n", idx);
  return __linkedlist_get(x, idx)->addr;
}

xlist_delegate_op linkedlist_op = {
  linkedlist_add,
  linkedlist_get
};

int main(void){
  xlist* l = xlist_delegate( linkedlist_init(), &linkedlist_op );
  int n = 100;
  printf("%p\n", &n);
  l->add(l, &n);
  l->get(l, 0);
  printf("%p\n", l->get(l, 0));
  return 0;
}
