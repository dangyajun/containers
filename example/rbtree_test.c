#include <string.h>
#include <stdio.h>
#include "rbtree.h"
/*
#if __linux__   //  or #if __GNUC__
    #if __x86_64__ || __ppc64__
        #define ENVIRONMENT64
    #else
        #define ENVIRONMENT32
    #endif
#else
    #if _WIN32
        #define ENVIRONMENT32
    #else
        #define ENVIRONMENT64
    #endif
#endif // __linux__

#ifdef ENVIRONMENT64
    #define PTR_OFFSET (unsigned long long int)
#else
    #define PTR_OFFSET (unsigned long int)
#endif // ENVIRONMENT64

#define adv_offsetof(TYPE, MEMBER) (PTR_OFFSET &((TYPE *)0)->MEMBER)

#define container_of(ptr, type, member) ({                      \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
               (type *)( (char *)__mptr - adv_offsetof(type,member) );})
*/


struct mytype {
	struct rb_node node;
	char *keystring;
};


struct mytype *my_search(struct rb_root *root, char *string)
{
	struct rb_node *node = root->rb_node;

	while (node) {
		struct mytype *data = container_of(node, struct mytype, node);
		int result;

		result = strcmp(string, data->keystring);

		if (result < 0)
			node = node->rb_left;
		else if (result > 0)
			node = node->rb_right;
		else
			return data;
	}
	return NULL;
}

int my_insert(struct rb_root *root, struct mytype *data)
{
	struct rb_node **new = &(root->rb_node), *parent = NULL;

	/* Figure out where to put new node */
	while (*new) {
		struct mytype *this = container_of(*new, struct mytype, node);
		int result = strcmp(data->keystring, this->keystring);

		parent = *new;
		if (result < 0)
			new = &((*new)->rb_left);
		else if (result > 0)
			new = &((*new)->rb_right);
		else
			return 0;
	}

	/* Add new node and rebalance tree. */
	rb_link_node(&data->node, parent, new);
	rb_insert_color(&data->node, root);
	return 1;
}

int main()
{
	struct rb_root mytree = RB_ROOT;
	int i;

	struct mytype node[5];
	struct mytype * ret;

	node[0].keystring = "0000";
	node[1].keystring = "ffff";
	node[2].keystring = "bbbb";
	node[3].keystring = "1111";
	node[4].keystring = "aaa";

	for(i = 0; i < 5; i++){
		printf("node[%d] @ %p\n", i, &node[i]);
		my_insert(&mytree, &node[i]);
	}
	

	ret = my_search(&mytree, "0000");
	printf("0000 ret @ %p\n", ret);

	ret = my_search(&mytree, "ffff");
	printf("ffff ret @ %p\n", ret);

	ret = my_search(&mytree, "1111");
	printf("1111 ret @ %p\n", ret);

	ret = my_search(&mytree, "aaa");
	printf("aaa ret @ %p\n", ret);


	return 0;
}
