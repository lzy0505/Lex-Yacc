include<stdio.h>
include<stdlib.h>
include<assert.h>
struct Node
{
	int data;
	struct Node* next;
};
struct Stack
{
struct Node* head;
int size;
};
void StackInit(struct Stack* stack)
{
	stack->head = NULL;
	stack->size = 0;
}
void StackPush(struct Stack* stack, const int data)//½øÕ» 
{
struct Node* node;
node = (struct Node*)malloc(sizeof(struct Node));
assert(node != NULL);
node->data = data;
node->next = stack->head;
stack->head = node;
++stack->size;
}
int StackEmpty(struct Stack* stack)
{
return (stack->size == 0);
}
int StackPop(struct Stack* stack, int* data)//³öÕ»  
{
if (StackEmpty(stack))
{
	return 0;
	}
	struct Node* tmp = stack->head;
	*data = stack->head->data;
	stack->head = stack->head->next;
	free(tmp);
--stack->size;
	return 1;
}
int StackTop(struct Stack* stack, int* data)
{
	if (StackEmpty(stack))
	{
		return 0;
	}
	*data = stack->head->data;
	return 1;
}
void StackCleanup(struct Stack* stack)
{
struct Node* tmp;
while (stack->head)
{
		tmp = stack->head;
		stack->head = stack->head->next;
		free(tmp);
	}
	stack->size = 0;
}
int main(int argc,char **argv)
{
Struct Stack stateStack;
Struct Stack symbolStack;
StackInit(&stateStack);
StackInit(&symbolStack);
StackPush(&stateStack,???);
StackPush(&symbolStack);
int token=0;
int item=0;
getOneToken(token);
do{
item=yy_next[ yy_base[StackTop(&stateStack)]+yy_char_vec[token]
}
