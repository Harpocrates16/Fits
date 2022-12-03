#include<stdio.h>
#include<stdlib.h>
struct node
{
	int no;
	int pid;
	int size;
	int pro_size;
	int size_frag;
	int alloc;
	struct node *link;
} *start=NULL;
void create(int s,int b_no)
{
	struct node *temp=start;
	struct node *newn=(struct node *)malloc(sizeof(struct node));
	if(start==NULL)
	{
		struct node *start=(struct node *)malloc(sizeof(struct node));
		start->no=b_no;
		start->size=s;
		start->pid=-1;
		start->pro_size=0;
		start->size_frag=newn->size - newn->pro_size;
		start->alloc=0;
		start->link=NULL;
	}
	else
	{
		newn->no=b_no;
		newn->alloc=0;
		newn->pid=-1;
		newn->pro_size=0;
		newn->size=s;
		newn->size_frag=newn->size - newn->pro_size;
		newn->link=NULL;
		while(temp->link!=NULL)
		{
			temp=temp->link;
		}
		temp->link=newn;
	}
}
void ff(int id,int psize)
{
	int flag=0;
	struct node *temp=start;
	if(start==NULL)
		printf("No partition created");
	else
	{
		while(temp!=NULL)
		{
			if(temp->alloc==0 && temp->size>psize)
			{
				temp->pid=id;
				temp->pro_size = psize;
				temp->size_frag=temp->size - temp->pro_size;
				temp->alloc = 1;
				flag=1;
				break;
			}
			temp=temp->link;
		}
		if(flag==0)
			printf("unable to allocate process pid:%d\n",id);
	}
}
void bf(int id,int psize)
{
	int flag=0;
	struct node *temp=start;
	struct node *pos=start;
	if(start==NULL)
		printf("No partition created");
	else
	{
		while(temp!=NULL)
		{
			if(temp->alloc==0 && temp->size>psize )
			{
				pos=temp;
			}
			temp=temp->link;
		}
		temp=start;
		while(temp!=NULL)
		{
			if(temp->alloc==0 && temp->size>psize && temp->size<pos->size)
			{
				pos=temp;
			}
			temp=temp->link;
		}
		temp=start;
		while(temp!=pos)
		{
			temp=temp->link;
		}
		temp->pid=id;
		temp->pro_size = psize;
		temp->size_frag=temp->size - temp->pro_size;
		temp->alloc = 1;
		flag=1;
		if(flag==0)
			printf("unable to allocate process pid:%d\n",id);
	}
}
void wf(int id,int psize)
{
	int flag=0;
	struct node *temp=start;
	struct node *pos;
	if(start==NULL)
		printf("No partition created");
	else
	{
		while(temp!=NULL)
		{
			if(temp->alloc==0 && temp->size>psize )
			{
				pos=temp;
			}
			temp=temp->link;
		}
		temp=start;
		while(temp!=NULL)
		{
			if(temp->alloc==0 && temp->size>psize && temp->size>pos->size)
			{
				pos=temp;
			}
			temp=temp->link;
		}
		temp=start;
		if(pos->alloc==0)
		{
			while(temp!=pos)
			{
				temp=temp->link;
			}
			temp->pid=id;
			temp->pro_size = psize;
			temp->size_frag=temp->size - temp->pro_size;
			temp->alloc = 1;
			flag=1;
		}
		else
			printf("unable to allocate process pid:%d\n",id);
	}
}
void initialise()
{
	struct node *temp=start;
	while(temp!=NULL)
	{
		temp->alloc=0;
		temp->pid=-1;
		temp->pro_size=0;
		temp->size_frag=temp->size - temp->pro_size;
		temp=temp->link;
	}
}
void display()
{
	struct node *temp=start;
	if(start==NULL)
		printf("Underflow");
	else
	{
	printf("Bno: \tBsize: \tpid: \tpsize: \tfsize: \tallocation: \n");
		while(temp!=NULL)
		{
			if(temp->alloc==1)
				printf("%d\t %d\t %d\t %d\t %d\t %d\t\n",temp->no,temp->size,temp->pid,temp->pro_size,temp->size_frag,temp->alloc);
			temp=temp->link;
		}
	}
}
void main()
{
	int np,i,nb,pro[100][100],size,ch=1,op;
	printf("Enter no of blocks: ");
	scanf("%d",&nb);
	for(i=0;i<nb;i++)
	{
		printf("Enter size: ");
		scanf("%d",&size);
		create(size,i);
	}
	printf("Enter no of processes: ");
	scanf("%d",&np);
	for(i=0;i<np;i++)
	{
		printf("Enter pid: ");
		scanf("%d",&pro[i][0]);
		printf("Enter size: ");
		scanf("%d",&pro[i][1]);
	}
	do{
	printf("\nMENU\n1.First fit\n2.Best fit\n3.Worst fit\n4.Exit\nSelect option");
	scanf("%d",&op);
	if(op==1)
	{
		printf("First fit\n");
		for(i=0;i<np;i++)
		{
			ff(pro[i][0],pro[i][1]);
		}
		display();
		initialise();
	}
	else if(op==2)
	{
		printf("\nBest fit\n");
		for(i=0;i<np;i++)
		{
		bf(pro[i][0],pro[i][1]);
		}
		display();
		initialise();
	}
	else if(op==3)
	{
		printf("\nWorst fit\n");
		for(i=0;i<np;i++)
		{
		wf(pro[i][0],pro[i][1]);
		}
		display();
		initialise();
	}
	else if(op==4)
	{
		ch=0;
	}
	}while(ch==1);
}
