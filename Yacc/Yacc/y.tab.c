include<stdio.h>
include<stdlib.h>
include<assert.h>
void lex_init(char* fileName);
int yy_lex();
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
lex_init("q.txt");
Struct Stack stateStack;
Struct Stack symbolStack;
StackInit(&stateStack);
StackInit(&symbolStack);
StackPush(&stateStack,0);
StackPush(&symbolStack,-2);
int token=0;
int item=0;
int producerStart=0;
int producerLength=0;
token=yy_lex();
do{
item=yy_next[ yy_base[StackTop(&stateStack)]+token
if(item==0)
{
prinf("accepted!");
}
if(item>0)
{
StackPush(&symbolStack,token);
StackPush(&stateStack,item);
if((token=yy_lex())==-1)
break;
}
if(item<0)
{
producerStart=index[2*(-item)];
producerLength=index[2*(-item)+1];
int check=1;
int reverseIndex=producerStart+producerLenght-1;
int stackTopItem=0;
for(int i=reverseIndex;i>producerStart;i--)
{
if(StackPop(&stateStack,&stackTopItem)==0)
{
prinf("ERROR:STACK EMPTY!");
check=0;
return;
}
if(StackPop(&symbolStack,&stackTopItem)==0)
{
prinf("ERROR:STACK EMPTY!");
check=0;
return;
}
if(yy_producer_data[i]!=stackTopItem)
{
prinf("ERROR:SYNTAX ERROR!");
check=0;
}
}
if(check==1)
{
StackPush(&symbolStack,yy_producer_data[producerStart]);
item=yy_next[ yy_base[StackTop(&stateStack)]+yy_producer_data[producerStart]]
StackPush(&stateSatck,item);
printf("%s
",yy_tokens[(-item)])
}
}while(token!=-1);
}
