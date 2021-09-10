#include <stdio.h>
#include "advlist.h"

struct list_node{
	struct list_head mlist;
	int data;
};


int main()
{
	LIST_HEAD(mylist);
	struct list_head *ptr;
	int i;
	struct list_node mnodes[100];

	for(i = 0; i < 100; i++){
		mnodes[i].data = i;

		list_add(&mnodes[i].mlist, &mylist);
	}

	i = 0;
	list_for_each(ptr, &mylist){
		struct list_node * node;
		node = container_of(ptr, struct list_node, mlist);
		printf("[%d] data %d\n", i++ , node->data);
	}

	return 0;
}
