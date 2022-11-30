#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef int SDataType;
typedef int Status;
typedef struct{
	SDataType *base; //栈底指针
	SDataType *top;  //栈顶指针
	int StackSize;   //当前已经分配的存储空间，以元素为单位 
}SqStack;

//初始化顺序栈，构造一个空??
Status InitStack(SqStack &S){
	//分配存储空间 
	S.base = (SDataType *)malloc(STACK_INIT_SIZE*sizeof(SDataType));
	if(!S.base){
		//如果分配失败，则返回error 
		return 0;
	}
	//S.top 始终指向栈顶元素的下一个位?? 
	S.top = S.base;    //初始状态下为空?? 
	S.StackSize = STACK_INIT_SIZE;   //当前已经分配的存储容量为100?? 
	return 1;	
}

//判断是否为空??
void judgeNull(SqStack &s){
	if(s.top == s.base){
		printf("此栈为空栈！\n");
	}else{
		printf("此栈不为空栈！\n");
	}
}

//判断是否为满??
void judgeFull(SqStack &s){
	if(s.top-s.base == s.StackSize){
		printf("栈满！\n");
	}else{
		printf("栈未满！\n");
	} 
}

//入栈
Status Push(SqStack &s,SDataType e){
	SDataType *p;
	//首先判断栈是不是满的（上溢） 
	if(s.top-s.base == s.StackSize){
		//追加空间 
		p = (SDataType *)realloc(s.base,(STACK_INIT_SIZE+STACKINCREMENT)*sizeof(SDataType));
		if(!p){
			//如果没有找到符合条件的存储空间，则返回error 
			return 0;
		}
		//成功找到则使s.base指向p 
		s.base = p;
		s.top = s.base + s.StackSize;
		s.StackSize +=  STACKINCREMENT;
	}
	//先插入元素，然后将栈顶指针加 1 
	*(s.top) = e;
	s.top++;
	return 1;
}
//出栈
Status Pop(SqStack &s,SDataType &e){
	//判断是否会发生下?? 
	if(s.top != s.base){
		s.top--;    //先将栈顶指针?? 1 
		e = *(s.top);
	}else{
		return 0;
	}
	return e;
}



//无头单链表储存栈
typedef struct LNode {
    /**
     * 结点数据域
     */
    int data;
    /**
     * 结点指针域，指向后继结点
     */
    struct LNode *next;
} LNode;
void init(LNode **stack) {
    // 即置为 NULL，没有头结点
    *stack = NULL;
}

/**
 * 判断链栈是否为空
 * @param stack 不带头结点的链栈
 * @return 如果链栈为空则返回 1，否则返回 0 表示非空
 */
int isEmpty(LNode *stack) {
    if (stack == NULL) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * 将元素入栈。注意，链栈不需要校验栈是否满的问题
 * @param stack 不带头结点的链栈
 * @param ele 元素值
 */
void push(LNode **stack, int ele) {
    // 1.创建新结点并为其指定数据域和初始化指针域
    LNode *newNode = (LNode *) malloc(sizeof(LNode));
    newNode->data = ele;
    newNode->next = NULL;

    // 2.但需要判断栈是否为空的问题，如果栈为空，则新结点是链栈的第一个结点；如果栈非空，则新结点成为链栈新的栈顶结点
    if (stack == NULL) {
        // 新结点直接称为栈顶结点
        *stack = newNode;
    } else {
        // 将新结点入栈
        newNode->next = *stack;
        *stack = newNode;
    }
}

/**
 * 将元素出栈
 * @param stack 不带头结点的链栈
 * @param ele 用来存储出栈元素的值
 * @return 如果栈空则返回 0 表示出栈失败，否则返回 1 表示出栈成功
 */
int pop(LNode **stack, int *ele) {
    // 1.需要校验是否是空栈
    if (*stack == NULL) {
        return 0;
    }
    // 2.将元素出栈
    LNode *node = *stack;
    // 2.1 用 ele 保存出栈元素的数据值
    *ele = node->data;
    // 2.2 删除栈顶结点
    *stack = node->next;
    // 2.3 释放结点空间
    free(node);
    // 2.4 返回 1 表示出栈成功
    return 1;
}

/**
 * 获取栈顶元素，但不出栈
 * @param stack 不带头结点的链栈
 * @param ele 用来存储出栈元素的值
 * @return 如果栈空则返回 0 表示出栈失败，否则返回 1 表示出栈成功
 */
int getTop(LNode *stack, int *ele) {
    // 1.如果栈空则返回 0 表示获取失败
    if (stack == NULL) {
        return 0;
    }
    // 2.用 ele 保存栈顶元素值
    *ele = stack->data;
    return 1;
}

/**
 * 获取链栈中结点个数
 * @param stack 不带头结点的链栈
 * @return 结点个数
 */
int size(LNode *stack) {
    // 变量，记录链栈结点个数
    int len = 0;
    // 从栈顶到栈底扫描链栈所有结点，统计个数
    while (stack != NULL) {
        len++;
        stack = stack->next;
    }
    return len;
}

/**
 * 打印链栈所有结点
 * @param stack 不带头结点的链栈
 */
void print(LNode *stack) {
    printf("[");
    while (stack != NULL) {
        printf("%d", stack->data);
        if (stack->next != NULL) {
            printf(", ");
        }
        stack = stack->next;
    }
    printf("]\n");
}

/**
 * 清空链栈
 * @param stack 不带头结点的链栈
 */
void clear(LNode **stack) {
    // 释放链栈中每一个结点的空间
    while (*stack != NULL) {
        LNode *node = (*stack)->next;
        free(*stack);
        *stack = node;
    }
    *stack = NULL;
}

/**
 * 销毁链栈
 * @param stack 不带头结点的链栈
 */
void destroy(LNode **stack) {
    free(*stack);
}




