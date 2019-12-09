#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/wait.h>

int main()
{
    int number, value, edges, i, j, visited[100], node_edges[100], node_vals[100], nodes_vis[100][100], node_repeats[100], c = 0, temp = 0;
    FILE *fp;
    for (i = 0; i < 100; i++){ 
        node_repeats[i] = 0; 
    } 
    fp = fopen("Struct.c", "w+");
    printf("Enter number of nodes: ");
    fprintf(fp, "#include <stdio.h>\n#include <stdlib.h>\n#include <unistd.h>\n#include <sys/types.h>\n#include <sys/wait.h>\n\nint main()\n{\n");
    scanf(" %d", &number);
    for(i = 0; i < number; i++)
    {
		printf("Enter value of node: ");
		scanf(" %d", &value);
		printf("Enter number of edges the %d node has: ", i+1);
		scanf(" %d", &edges);
		//fprintf(fp, "struct node%d {\n\tint val;\n\t", edges);
		node_edges[i] = edges;
		node_vals[i] = value;
		printf("Enter nodes attached to the %d node: ", i+1);
		for(j = 0; j < node_edges[i]; j++)
		{
			scanf(" %d", &edges);
			nodes_vis[i][j] = edges;
		}
	}
	for(i = 0; i < number; i++)
	{
		for(j = 0; j < c; j++)
		{
			if(node_edges[i] == visited[j])
			{
				goto mark;
			}
		}
		visited[c] = node_edges[i];
		c++;
		fprintf(fp, "\tstruct node%d \n\t{\n\t\tint val;\n\t", node_edges[i]);
		for(j = 0; j < node_edges[i]; j++)
		{
			fprintf(fp, "\tstruct node%d *next%d;\n\t", node_edges[nodes_vis[i][j]-1], j+1);
		}
		fprintf(fp, "};\n");
	}
	mark:
	for(i = 0; i < number; i++)
	{
		temp = 0;
		fprintf(fp, "\tstruct node%d *node%d = (struct node%d *) malloc(sizeof(struct node%d));\n", node_edges[i], i+1, node_edges[i], node_edges[i]);
		fprintf(fp, "\tnode%d->val = %d;\n", i+1, node_vals[i]);
		int size = sizeof(nodes_vis[i])/sizeof(nodes_vis[0][0]);
		/*for(j = 0; j < 100; j++)
		{
			if(nodes_vis[i][j] > 0)
			{
				temp++;
			}
			else
			{
				goto mark1;
			}
		}
		mark1:
		for(j = 0; j < temp; j++)
		{
			fprintf(fp, "\tnode%d->next%d = %d;\n", i+1, j+1, nodes_vis[i][j]);
		}*/
		node_repeats[node_edges[i]] = node_repeats[node_edges[i]] + 1;
	}
	for(i = 0; i < number; i++)
	{
		temp = 0;
		for(j = 0; j < 100; j++)
		{
			if(nodes_vis[i][j] > 0)
			{
				temp++;
			}
			else
			{
				goto mark1;
			}
		}
		mark1:
		for(j = 0; j < temp; j++)
		{
			fprintf(fp, "\tnode%d->next%d = node%d;\n", i+1, j+1, nodes_vis[i][j]);
		}
	}
	fprintf(fp, "\tprintf(\"Success.\");\n");
	fprintf(fp, "\treturn 0;\n}\n");
    fclose(fp);
    int status = system("gcc -o Struct Struct.c");
    int status_2 = system("./Struct");
    return 0;
}