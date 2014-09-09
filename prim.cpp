#include <iostream>
#include <iomanip>
#include <string>
#include <stdio.h>
#include <math.h>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>
#include <vector>
#include <algorithm>
#include <limits.h>
using namespace std;
struct Adjacency_List_Node
{
	int destination;
	float weight;
	struct Adjacency_List_Node *next;
};
struct Adjacency_List
{
	struct Adjacency_List_Node *head;
};
struct Graph
{
	int number_of_vertices;
	struct Adjacency_List* array;
};
struct Adjacency_List_Node* New_Adjacency_List_Node(int destination,float weight)
{
	struct Adjacency_List_Node* new_node = (struct Adjacency_List_Node*)malloc(sizeof(Adjacency_List_Node));
	new_node->destination=destination;
	new_node->weight=weight;
	new_node->next=NULL;
	return new_node;
}
struct Graph* Create_New_Graph(int number_of_vertices)
{
	struct Graph* new_graph=(struct Graph*)malloc(sizeof(struct Graph));
	new_graph->number_of_vertices=number_of_vertices;
	new_graph->array=(struct Adjacency_List*)malloc(number_of_vertices*sizeof(struct Adjacency_List));
	for (int k = 0; k < number_of_vertices; ++k)
	{
		new_graph->array[k].head=NULL;
	}
	return new_graph;
}
void Add_New_Edge(struct Graph* graph,int source,int destination,float weight)
{
	struct Adjacency_List_Node* new_node;
	new_node=New_Adjacency_List_Node(destination, weight);
	new_node->next=graph->array[source].head;
	graph->array[source].head=new_node;
	new_node=New_Adjacency_List_Node(source, weight);
	new_node->next=graph->array[destination].head;
	graph->array[destination].head=new_node;
}
struct Min_Heap_Node
{
	int v;
	float key;
};
struct Min_Heap
{
	int number_of_heap_nodes;
	int capacity;
	int *pos;
	struct Min_Heap_Node **array;	
};
struct Min_Heap_Node* New_Min_Heap_Node(int v,int key)
{
	struct Min_Heap_Node* min_heap_node=(struct Min_Heap_Node*)malloc(sizeof(struct Min_Heap_Node));
	min_heap_node->v=v;
	min_heap_node->key=key;
	return min_heap_node;
}
struct Min_Heap* Create_Min_Heap(int capacity)
{
	struct Min_Heap* min_heap=(struct Min_Heap*)malloc(sizeof(struct Min_Heap));
	min_heap->pos=(int *)malloc(capacity*sizeof(int));
	min_heap->number_of_heap_nodes=0;
	min_heap->capacity=capacity;
	min_heap->array=(struct Min_Heap_Node**)malloc(capacity*sizeof(struct Min_Heap_Node*));
	return min_heap;
}
void Swap_Min_Heap_Nodes(struct Min_Heap_Node** a,struct Min_Heap_Node** b)
{
	struct Min_Heap_Node* temp=*a;
	*a=*b;
	*b=temp;
}
void Min_Heapify(struct Min_Heap* min_heap,int index)
{
	int smallest,left,right;
	smallest=index;
	left=2*index+1;
	right=2*index+2;
	if(left<min_heap->number_of_heap_nodes && min_heap->array[left]->key<min_heap->array[smallest]->key)
	{
		smallest=left;
	}
	if(right<min_heap->number_of_heap_nodes && min_heap->array[right]->key<min_heap->array[smallest]->key)
	{
		smallest=right;
	}
	if(smallest != index)
	{
		Min_Heap_Node *smallest_node=min_heap->array[smallest];
		Min_Heap_Node *index_node=min_heap->array[index];
		min_heap->pos[smallest_node->v]=index;
		min_heap->pos[index_node->v]=smallest;
		Swap_Min_Heap_Nodes(&min_heap->array[smallest],&min_heap->array[index]);
		Min_Heapify(min_heap,smallest);
	}
}
int Is_Empty(struct Min_Heap* min_heap)
{
    return min_heap->number_of_heap_nodes == 0;
}
struct Min_Heap_Node* Extract_Minimum(struct Min_Heap* min_heap)
{
	if(Is_Empty(min_heap))
	{
		return NULL;
	}
	struct Min_Heap_Node* root_of_heap=min_heap->array[0];
	struct Min_Heap_Node* last_node_of_heap=min_heap->array[min_heap->number_of_heap_nodes-1];
	min_heap->array[0]=last_node_of_heap;
	min_heap->pos[root_of_heap->v]=min_heap->number_of_heap_nodes-1;
	min_heap->pos[last_node_of_heap->v]=0;
	--min_heap->number_of_heap_nodes;
	Min_Heapify(min_heap,0);
	return root_of_heap;
}
void Decrease_Key(struct Min_Heap* min_heap,int v,float key)
{
	int i=min_heap->pos[v];
	min_heap->array[i]->key=key;
	//cout<<"i=="<<i<<" , "<<"key="<<key<<endl;;
	//cout<<"(min_heap->array[i]->key)="<<(min_heap->array[i]->key)<<" , "<<"(min_heap->array[(i-1)/2]->key)=="<<(min_heap->array[(i-1)/2]->key)<<endl;
	while(i && ((min_heap->array[i]->key) < (min_heap->array[(i-1)/2]->key)))
	{
		//cout<<"i=="<<i<<",(i-1)/2="<<(i-1)/2<<"\n";
		min_heap->pos[min_heap->array[i]->v]=(i-1)/2;
		min_heap->pos[min_heap->array[(i - 1)/2]->v]=i;
		Swap_Min_Heap_Nodes(&min_heap->array[i], &min_heap->array[(i-1)/2]);
		i=(i-1)/2;
		//cout<<"i=="<<i<<",(i-1)/2="<<(i-1)/2<<"\n";
	}
	//cout<<endl;
}
bool Is_In_Min_heap(struct Min_Heap* min_heap,int v)
{
	if(min_heap->pos[v] < min_heap->number_of_heap_nodes)
	{
		return true;
	}
	return false;

}
int minimum(int a , int b)
{
	if(a<b)return a;
	return b;
}
int maximum(int a , int b)
{
	if(a>b)return a;
	return b;
}
vector< pair<float, pair<int, int> > > arr1;
void Print_An_Array(int array[],float weight[],int size,float sum)
{
	printf("%.2f\n",sum);
	//cout<<sum<<endl;
	arr1.resize(size);
	for (int l = 1; l < size; ++l)
	{
		// cout<<array[l]<<" "<<l<<" "<<weight[l]<<endl;
		arr1[l].first=weight[l];
		arr1[l].second.first=minimum(array[l],l);
		arr1[l].second.second=maximum(array[l],l);
	}
	sort(arr1.begin(), arr1.end());
	for (int i = 1; i < size; ++i)
	{
		if(arr1[i].first>-1000000 && arr1[i].first<1000000)
		{
			cout<<arr1[i].second.first<<" "<<arr1[i].second.second<<" ";
			//cout<<arr1[i].first<<endl;
			printf("%.2f\n",arr1[i].first);
		}
	}
}
void Prim_Minimum_Spanning_Tree(struct Graph* graph)
{
	int number_of_vertices=graph->number_of_vertices;
	int parent[number_of_vertices];
	float key[number_of_vertices];
	float sum=0;
	struct Min_Heap* min_heap= Create_Min_Heap(number_of_vertices);
	for (int v = 1; v < number_of_vertices; ++v)
	{
		parent[v]=-1;
		key[v]=2000000000;
		min_heap->array[v]=New_Min_Heap_Node(v,key[v]);
		min_heap->pos[v]=v;
	}
	//Print_An_Array(parent,number_of_vertices);cout<<endl;
	key[0]=0;
	min_heap->array[0]=New_Min_Heap_Node(0,key[0]);
	min_heap->pos[0]=0;
	//Print_An_Array(parent,number_of_vertices);cout<<endl;
	//cout<<"Number of vertices="<<number_of_vertices<<endl;
	min_heap->number_of_heap_nodes=number_of_vertices;
	//Print_An_Array(parent,number_of_vertices);cout<<endl;
	while(!Is_Empty(min_heap))
	{
		struct Min_Heap_Node* min_heap_node=Extract_Minimum(min_heap);
		int minimum_vertex=min_heap_node->v;
		struct Adjacency_List_Node* traversal_node=graph->array[minimum_vertex].head;
		// Print_An_Array(parent,number_of_vertices);cout<<endl;
		while(traversal_node!=NULL)
		{
			int v=traversal_node->destination;
			//cout<<"v=="<<v<<", ";
			//Print_An_Array(parent,number_of_vertices);cout<<endl;
			//cout<<"traversal_node->weight=="<<traversal_node->weight<<", key["<<v<<"]=="<<key[v]<<endl;
			//cout<<(Is_In_Min_heap(min_heap,v) && traversal_node->weight < key[v])<<endl;
			if(Is_In_Min_heap(min_heap,v) && traversal_node->weight < key[v])
			{
				//cout<<"coming"<<endl;
				key[v]=traversal_node->weight;
				//cout<<"parent["<<v<<"]=="<<parent[v]<<endl;
				parent[v]=minimum_vertex;
				Decrease_Key(min_heap,v,key[v]);
			}
			//sum=sum+key[v];
			traversal_node=traversal_node->next;
		}
		//Print_An_Array(parent,number_of_vertices);cout<<endl;
	}
	//cout<<"number of vertices="<<number_of_vertices<<endl;
	for (int j = 1; j < number_of_vertices; ++j)
	{

		if(key[j]>-1000000 && key[j]<1000000)
		{
			sum=sum+key[j];
			//cout<<"sum="<<sum<<endl;
		}
	}
	Print_An_Array(parent,key,number_of_vertices,sum);
}
int main()
{
	//int V = 9;
    
    int u,v,nodes;
	cin>>nodes;
	float w;
	struct Graph* graph = Create_New_Graph(nodes);
	while((scanf("%d",&u)!=EOF)&&(scanf("%d",&v)!=EOF)&&scanf("%f",&w)!=EOF)
	{
		Add_New_Edge(graph,u,v,w);
	}
    Prim_Minimum_Spanning_Tree(graph);
	return 0;
}