#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	struct node2 
	{
		int val;
		struct node1 *next1;
		struct node1 *next2;
	};
	struct node1 
	{
		int val;
		struct node2 *next1;
	};
	struct node2 *node1 = (struct node2 *) malloc(sizeof(struct node2));
	node1->val = 10;
	struct node1 *node2 = (struct node1 *) malloc(sizeof(struct node1));
	node2->val = 20;
	struct node1 *node3 = (struct node1 *) malloc(sizeof(struct node1));
	node3->val = 30;
	node1->next1 = node2;
	node1->next2 = node3;
	node2->next1 = node1;
	node3->next1 = node1;
	printf("Success
");
	return 0;
}
