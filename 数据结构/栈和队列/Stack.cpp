#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef int SDataType;
typedef int Status;
typedef struct{
	SDataType *base; //ջ��ָ��
	SDataType *top;  //ջ��ָ��
	int StackSize;   //��ǰ�Ѿ�����Ĵ洢�ռ䣬��Ԫ��Ϊ��λ 
}SqStack;

//��ʼ��˳��ջ������һ����??
Status InitStack(SqStack &S){
	//����洢�ռ� 
	S.base = (SDataType *)malloc(STACK_INIT_SIZE*sizeof(SDataType));
	if(!S.base){
		//�������ʧ�ܣ��򷵻�error 
		return 0;
	}
	//S.top ʼ��ָ��ջ��Ԫ�ص���һ��λ?? 
	S.top = S.base;    //��ʼ״̬��Ϊ��?? 
	S.StackSize = STACK_INIT_SIZE;   //��ǰ�Ѿ�����Ĵ洢����Ϊ100?? 
	return 1;	
}

//�ж��Ƿ�Ϊ��??
void judgeNull(SqStack &s){
	if(s.top == s.base){
		printf("��ջΪ��ջ��\n");
	}else{
		printf("��ջ��Ϊ��ջ��\n");
	}
}

//�ж��Ƿ�Ϊ��??
void judgeFull(SqStack &s){
	if(s.top-s.base == s.StackSize){
		printf("ջ����\n");
	}else{
		printf("ջδ����\n");
	} 
}

//��ջ
Status Push(SqStack &s,SDataType e){
	SDataType *p;
	//�����ж�ջ�ǲ������ģ����磩 
	if(s.top-s.base == s.StackSize){
		//׷�ӿռ� 
		p = (SDataType *)realloc(s.base,(STACK_INIT_SIZE+STACKINCREMENT)*sizeof(SDataType));
		if(!p){
			//���û���ҵ����������Ĵ洢�ռ䣬�򷵻�error 
			return 0;
		}
		//�ɹ��ҵ���ʹs.baseָ��p 
		s.base = p;
		s.top = s.base + s.StackSize;
		s.StackSize +=  STACKINCREMENT;
	}
	//�Ȳ���Ԫ�أ�Ȼ��ջ��ָ��� 1 
	*(s.top) = e;
	s.top++;
	return 1;
}
//��ջ
Status Pop(SqStack &s,SDataType &e){
	//�ж��Ƿ�ᷢ����?? 
	if(s.top != s.base){
		s.top--;    //�Ƚ�ջ��ָ��?? 1 
		e = *(s.top);
	}else{
		return 0;
	}
	return e;
}



//��ͷ��������ջ
typedef struct LNode {
    /**
     * ���������
     */
    int data;
    /**
     * ���ָ����ָ���̽��
     */
    struct LNode *next;
} LNode;
void init(LNode **stack) {
    // ����Ϊ NULL��û��ͷ���
    *stack = NULL;
}

/**
 * �ж���ջ�Ƿ�Ϊ��
 * @param stack ����ͷ������ջ
 * @return �����ջΪ���򷵻� 1�����򷵻� 0 ��ʾ�ǿ�
 */
int isEmpty(LNode *stack) {
    if (stack == NULL) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * ��Ԫ����ջ��ע�⣬��ջ����ҪУ��ջ�Ƿ���������
 * @param stack ����ͷ������ջ
 * @param ele Ԫ��ֵ
 */
void push(LNode **stack, int ele) {
    // 1.�����½�㲢Ϊ��ָ��������ͳ�ʼ��ָ����
    LNode *newNode = (LNode *) malloc(sizeof(LNode));
    newNode->data = ele;
    newNode->next = NULL;

    // 2.����Ҫ�ж�ջ�Ƿ�Ϊ�յ����⣬���ջΪ�գ����½������ջ�ĵ�һ����㣻���ջ�ǿգ����½���Ϊ��ջ�µ�ջ�����
    if (stack == NULL) {
        // �½��ֱ�ӳ�Ϊջ�����
        *stack = newNode;
    } else {
        // ���½����ջ
        newNode->next = *stack;
        *stack = newNode;
    }
}

/**
 * ��Ԫ�س�ջ
 * @param stack ����ͷ������ջ
 * @param ele �����洢��ջԪ�ص�ֵ
 * @return ���ջ���򷵻� 0 ��ʾ��ջʧ�ܣ����򷵻� 1 ��ʾ��ջ�ɹ�
 */
int pop(LNode **stack, int *ele) {
    // 1.��ҪУ���Ƿ��ǿ�ջ
    if (*stack == NULL) {
        return 0;
    }
    // 2.��Ԫ�س�ջ
    LNode *node = *stack;
    // 2.1 �� ele �����ջԪ�ص�����ֵ
    *ele = node->data;
    // 2.2 ɾ��ջ�����
    *stack = node->next;
    // 2.3 �ͷŽ��ռ�
    free(node);
    // 2.4 ���� 1 ��ʾ��ջ�ɹ�
    return 1;
}

/**
 * ��ȡջ��Ԫ�أ�������ջ
 * @param stack ����ͷ������ջ
 * @param ele �����洢��ջԪ�ص�ֵ
 * @return ���ջ���򷵻� 0 ��ʾ��ջʧ�ܣ����򷵻� 1 ��ʾ��ջ�ɹ�
 */
int getTop(LNode *stack, int *ele) {
    // 1.���ջ���򷵻� 0 ��ʾ��ȡʧ��
    if (stack == NULL) {
        return 0;
    }
    // 2.�� ele ����ջ��Ԫ��ֵ
    *ele = stack->data;
    return 1;
}

/**
 * ��ȡ��ջ�н�����
 * @param stack ����ͷ������ջ
 * @return ������
 */
int size(LNode *stack) {
    // ��������¼��ջ������
    int len = 0;
    // ��ջ����ջ��ɨ����ջ���н�㣬ͳ�Ƹ���
    while (stack != NULL) {
        len++;
        stack = stack->next;
    }
    return len;
}

/**
 * ��ӡ��ջ���н��
 * @param stack ����ͷ������ջ
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
 * �����ջ
 * @param stack ����ͷ������ջ
 */
void clear(LNode **stack) {
    // �ͷ���ջ��ÿһ�����Ŀռ�
    while (*stack != NULL) {
        LNode *node = (*stack)->next;
        free(*stack);
        *stack = node;
    }
    *stack = NULL;
}

/**
 * ������ջ
 * @param stack ����ͷ������ջ
 */
void destroy(LNode **stack) {
    free(*stack);
}




