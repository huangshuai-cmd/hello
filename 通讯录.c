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
	
	
	//如果内存池非空，则直接从里面获取空间
	if(pool != NULL)
	{
		p = pool;
		pool = pool->next;
		count--;
	} 
	//如果内存池为空，则调用malloc函数申请空间 
	else
	{
		p = (struct Address *)malloc(sizeof(struct Address));
		if(!p)
		{
			printf("内存分配失败"); 
			exit(0); 
		}	
	} 
	
	if((*address) != NULL)
	{
		tail->next = p;
		p->next = NULL;
		printf("\n请输入姓名：");
		scanf("%s", p->name);
		printf("\n请输入联系方式：");
		scanf("%s", p->phonenum); 
	} 
	else
	{
		(*address) = p;
		p->next = NULL;
		printf("\n请输入姓名：");
		scanf("%s", p->name);
		printf("\n请输入联系方式：");
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
	printf("\n该联系人的号码为：%s", temp->phonenum);
	return temp;
}


void ChangeAddress(struct Address *address)
{
	struct Address  *temp;
	temp = address; 
	printf("\n请输入更改后号码：");
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
		printf("\n未找到联系人"); 
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
		
		printf("\n联系人的姓名: %s", temp->name);
		printf("\n联系人的号码为: %s", temp->phonenum);
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
    
    printf("| 欢迎使用通讯录管理程序 |");
    printf("\n|--- 1:插入新的联系人--- |");
    printf("\n|--- 2:查找已有联系人--- |");
    printf("\n|--- 3:更改已有联系人--- |");
    printf("\n|--- 4:删除已有联系人--- |");
    printf("\n|--- 5:显示当前通讯录--- |");
    printf("\n|--- 6:退出当前通讯录--- |\n");
    
    
	
	
	while(1)
	{
		printf("\n请输入指令代码：");
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
				printf("\n请输入要查找联系人的姓名：");
				scanf("%s", name);
				temp = FindAddress(address, name);
				if(temp == NULL)
				{
					printf("未找到"); 
				}
				
				break;
			case 3:
			    printf("\n请输入要更改联系人的姓名：");
			    scanf("%s, name");
			    temp = FindAddress(address, name);
			    if(temp == NULL)
				{
					printf("未找到"); 
				}
				else
				{
					ChangeAddress(temp);
				}
			    
			    break;
			case 4:
			    printf("\n请输入要删除联系人的姓名：");
			    scanf("%s, name");
				DeletAddress(&address, name);
				break;
			    
			case 5:
				printf("\n###当前通讯录有以下联系人###");
				PrintAddress(address);
				break;
			case 6:
				exit(0);
				break;
		} 	
		
	}
	
    

    return 0;
}

