#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 1024


struct Address
{
	char name[40];
	char phonenum[11];
	struct Address *next; 
};


struct Address *pool = NULL;
int count = 0;



void InsertAddress(struct Address **address)
{
	struct Address *p;
	static struct Address *tail; 
	
	
	//����ڴ�طǿգ���ֱ�Ӵ������ȡ�ռ�
	if(pool != NULL)
	{
		p = pool;
		pool = pool->next;
		count--;
	} 
	//����ڴ��Ϊ�գ������malloc��������ռ� 
	else
	{
		p = (struct Address *)malloc(sizeof(struct Address));
		if(!p)
		{
			printf("�ڴ����ʧ��"); 
			exit(0); 
		}	
	} 
	
	if((*address) != NULL)
	{
		tail->next = p;
		p->next = NULL;
		printf("\n������������");
		scanf("%s", p->name);
		printf("\n��������ϵ��ʽ��");
		scanf("%s", p->phonenum); 
	} 
	else
	{
		(*address) = p;
		p->next = NULL;
		printf("\n������������");
		scanf("%s", p->name);
		printf("\n��������ϵ��ʽ��");
		scanf("%s", p->phonenum);	
	}
	
	tail = p;
	putchar('\n');
}


struct Address *FindAddress(struct Address *address, char *str)
{
	struct Address *temp;
	temp = address;
	while(temp != NULL)
	{
		if(!strcmp(temp->name, str))
		{ 
			break; 
		}
		 
		temp = temp->next;
	}
	printf("\n����ϵ�˵ĺ���Ϊ��%s", temp->phonenum);
	return temp;
}


void ChangeAddress(struct Address *address)
{
	struct Address  *temp;
	temp = address; 
	printf("\n��������ĺ���룺");
	scanf("%s", temp->phonenum);
}

void DeletAddress(struct Address **address, char str[10])
{
	struct Address *previous;
	struct Address *current;
	struct Address *p;
	struct Address *temp;
	
	p = FindAddress(*address, str);
	
	if(p == NULL)
	{
		printf("\nδ�ҵ���ϵ��"); 
	}
	
	current = (*address);
	if(p == (*address))
	{
		(*address) = current->next;
	}
	else
	{
		while(current != p)
		{
			previous = current;
			current = current->next;
		}
		
		previous->next = current->next;
		
	}
	
	if(count < MAX)
	{
		if(pool != NULL)
		{
			temp = pool;
			pool = p;
			p->next = temp;
		} 
		else
		{
			pool = p;
			p->next = NULL;
		}
	}
	else
	{
		free(p);
	}
	
}


void PrintAddress(struct Address *address)
{
	struct Address *temp;
	temp = address;
	while(temp != NULL)
	{
		
		printf("\n��ϵ�˵�����: %s", temp->name);
		printf("\n��ϵ�˵ĺ���Ϊ: %s", temp->phonenum);
		temp = temp->next;
	}
}


void ReleaseAddress(struct Address **address)
{
	struct Address *temp;
	
	while(*address != NULL)
	{
	    temp = *address;
		*address = (*address)->next;
		free(temp);
	}
	
} 


void ReleasePool(void)
{
	struct Address *temp;
	while(pool != NULL)
	{
		temp = pool;
		pool = pool->next;
		free(temp);
	}
}



int main(void)
{
    struct Address *address = NULL;
    struct Address *temp;
    char name[40];
    int op;
    
    printf("| ��ӭʹ��ͨѶ¼������� |");
    printf("\n|--- 1:�����µ���ϵ��--- |");
    printf("\n|--- 2:����������ϵ��--- |");
    printf("\n|--- 3:����������ϵ��--- |");
    printf("\n|--- 4:ɾ��������ϵ��--- |");
    printf("\n|--- 5:��ʾ��ǰͨѶ¼--- |");
    printf("\n|--- 6:�˳���ǰͨѶ¼--- |\n");
    
    
	
	
	while(1)
	{
		printf("\n������ָ����룺");
		scanf("%d", &op);
//		do
//		{
//			op = getchar(); 
//		}while(op != '1' && op != '2' && op != '3' && op != '4' && op != '5');
		
		switch(op)
		{
			case 1:
				InsertAddress(&address);
				break;
			case 2:
				printf("\n������Ҫ������ϵ�˵�������");
				scanf("%s", name);
				temp = FindAddress(address, name);
				if(temp == NULL)
				{
					printf("δ�ҵ�"); 
				}
				
				break;
			case 3:
			    printf("\n������Ҫ������ϵ�˵�������");
			    scanf("%s, name");
			    temp = FindAddress(address, name);
			    if(temp == NULL)
				{
					printf("δ�ҵ�"); 
				}
				else
				{
					ChangeAddress(temp);
				}
			    
			    break;
			case 4:
			    printf("\n������Ҫɾ����ϵ�˵�������");
			    scanf("%s, name");
				DeletAddress(&address, name);
				break;
			    
			case 5:
				printf("\n###��ǰͨѶ¼��������ϵ��###");
				PrintAddress(address);
				break;
			case 6:
				exit(0);
				break;
		} 	
		
	}
	
    

    return 0;
}

