#include <string.h>
#include <stdio.h>
#include "rbtree.h"

struct mytype {
	struct rb_node node;
	char *keystring;
};


struct mytype *my_search(struct rb_root_cached *root, char *string)
{
	struct rb_node *node = root->rb_root.rb_node;

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

int my_insert(struct rb_root_cached *root, struct mytype *data)
{
	struct rb_node **new = &(root->rb_root.rb_node), *parent = NULL;
	int _cache = 1;

	/* Figure out where to put new node */
	while (*new) {
		struct mytype *this = container_of(*new, struct mytype, node);
		int result = strcmp(data->keystring, this->keystring);

		parent = *new;
		if (result < 0)
			new = &((*new)->rb_left);
		else if (result > 0){
			new = &((*new)->rb_right);
			_cache = 0;
		}else
			return 0;
	}

	/* Add new node and rebalance tree. */
	rb_link_node(&data->node, parent, new);
	rb_insert_color_cached(&data->node, root, _cache);
	return 1;
}

int main()
{
	struct rb_root_cached mytree = RB_ROOT_CACHED;
	int i;

	struct mytype data[5];
	struct mytype * ret;
	struct rb_node * _node;

	data[0].keystring = "0000";
	data[1].keystring = "ffff";
	data[2].keystring = "bbbb";
	data[3].keystring = "1111";
	data[4].keystring = "aaa";

	for(i = 0; i < 5; i++){
		printf("data[%d] @ %p\n", i, &data[i]);
		my_insert(&mytree, &data[i]);
	}
	

	ret = my_search(&mytree, "0000");
	printf("0000 ret @ %p\n", ret);

	ret = my_search(&mytree, "ffff");
	printf("ffff ret @ %p\n", ret);

	ret = my_search(&mytree, "1111");
	printf("1111 ret @ %p\n", ret);

	ret = my_search(&mytree, "aaa");
	printf("aaa ret @ %p\n", ret);

	printf("\nwalking through tree\n");

	for ( _node = rb_first(&(mytree.rb_root)); _node; _node = rb_next(_node))
		printf("key=%s\n", rb_entry(_node, struct mytype, node)->keystring);

	_node = rb_first_cached(&mytree);
	printf("first cached %s\n", rb_entry(_node, struct mytype, node)->keystring);


	printf("\nremoving nodes\n");
	
	for(i = 0; i < (sizeof(data)/sizeof(data[0])); i++){
		struct mytype *pos, *next, *target;

		_node = rb_first_cached(&mytree);
		//target = container_of(_node, struct mytype, node);
		target = rb_entry(_node, struct mytype, node);

		printf("removing %s @ %p\n", target->keystring, target);
		rbtree_postorder_for_each_entry_safe(pos, next, &mytree.rb_root, node){
			if(pos == target){
				rb_erase_cached(&pos->node, &mytree);
			}
		}

		_node = rb_first_cached(&mytree);
		target = rb_entry_safe(_node, struct mytype, node);
		printf("i= %d first cached %s\n", i, target?target->keystring:"none");

	}

	/*ret = my_search(&mytree, "aaa");

	if (ret) {
		rb_erase_cached(&ret->node, &mytree);
		//myfree(data);
	}

	for ( _node = rb_first(&(mytree.rb_root)); _node; _node = rb_next(_node))
		printf("key=%s\n", rb_entry(_node, struct mytype, node)->keystring);
	*/


	return 0;
}
