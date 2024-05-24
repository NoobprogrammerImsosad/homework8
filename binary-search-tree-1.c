/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */
int height(Node* head);//더럽고 추하게 함수 하나 더 쓰기

/* you may add your own defined functions if necessary */


int main()
{
	printf("[----- [TaeYoungKim] [2021041005] -----]");
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)//LVR
{
	if(ptr==NULL) return;//ptr이 NULL 이라면 윗 노드가 leaf node 이다.
	inorderTraversal(ptr->left);//좌측 
	printf("[%d] ",ptr->key);//가운데
	inorderTraversal(ptr->right);//우측
}

void preorderTraversal(Node* ptr)//VLR
{
	if(ptr==NULL) return;//ptr이 NULL 이라면 윗 노드가 leaf node 이다.
	printf("[%d] ",ptr->key);//가운데
	preorderTraversal(ptr->left);//좌측
	preorderTraversal(ptr->right);//우측
}

void postorderTraversal(Node* ptr)//LRV
{
	if(ptr==NULL) return;//ptr이 NULL 이라면 윗 노드가 leaf node 이다.
	postorderTraversal(ptr->left);//왼쪽
	postorderTraversal(ptr->right);//오른쪽
	printf("[%d] ",ptr->key);//가운데
}


int insert(Node* head, int key)
{
	if(head==NULL)//껍질 node가 없을때
	{
		printf("Please do initialize BST first\n");
		return -1;
	}
	Node *newnode = (Node*)malloc(sizeof(Node));//동적할당받기
	newnode->left =NULL;//새로운 node left,right NULL로 초기화
	newnode->right=NULL;
	newnode->key = key;//동적할당받은 node에 key값 집어넣기
	if(head->left==NULL)//tree가 비어있을때
	{
		head->left = newnode;//head가 가리키는 최상위 껍질 node의 left에 새로운 node 주소넣기
		return 0;
	}
	else head = head -> left;//안비어있다면 껍질 node 건너뛰기
	while(1){
	if(head->left==NULL)//head가 가리키는 node의 left가 NULL이고
	{
		if(head->key>key)//입력받은 key값이 node의 key값보다 작을 때
		{
			head->left = newnode;//head가 가리키는 node의 left에 새로만든 node의 주소를 넣어준다.
			return 0;//넣었으니 탈출
		}
	}
	if(head->right==NULL)//head가 가리키는 node의 right가 NULL이고
	{
		if(head->key<key)//입력받은 key값이 node의 key값보다 클 때
		{
			head->right = newnode;//head가 가리키는 node의 right에 새로만든 node의 주소를 넣어준다.
			return 0;//넣었으니 탈출
		}
	}
	if(head->key<key)//입력받은 key값이 head가 가리키는 node의 key값 보다 크다면
	{
		head = head->right;//오른쪽으로
		continue;
	}
	if(head->key==key)//입력받은 key값이 head가 가리키는 node의 key값과 같다면
	{
		printf("There is a same value in the tree\n");//같은 값이 Binary search tree에 있으면 안됨.
		free(newnode);//안쓰니까 free
		return -1;//탈출
	}
	if(head->key>key)//입력받은 key값이 head가 가리키는 node의 key값 보다 작다면
	{
		head = head->left;//왼쪽으로
		continue;
	}
	}
}

int deleteLeafNode(Node* head, int key)
{
	Node* headShadow = NULL;//head 위의 node에 접근할때 필요한 포인터
	int flag=-1;//node에서 내려올때 왼쪽으로 내려왔는지 오른쪽으로 내려왔는지 아는 flag. 좌 -1,우 1
	if(head==NULL)//껍질 node 없을 때
	{
		printf("Please do initialize BST first\n");
		return -1;
	}
	if(head->left==NULL)//껍질 node의 left가 비었을 때
	{
		printf("The tree is empty.\n");
		return -1;
	}
	else{ headShadow = head;head = head->left;}//안비었으면 껍질 node 건너 뛰기
	while(1){
		if(head==NULL)//일치하는 node가 없을 때
		{
			printf("There are no duplicate values in the tree");
			return -1;
		}
		if(head->key<key)//입력받은 key값이 head가 가리키는 node의 key값 보다 크다면
	{
		flag=1;//flag 바꾸고
		headShadow = head;//현재 node 주소 저장하고
		head = head->right;//오른쪽으로 내려가기
		continue;
	}
	if(head->key==key)//입력받은 key값이 head가 가리키는 node의 key값과 같다면
	{
		if(head->left==NULL&&head->right==NULL)//leaf node 일 때
		{
			if(flag==-1)//left로 내려왔을때
			{
				headShadow->left = NULL;//위에 노드 left 초기화 해주고 
				free(head);//노드 동적할당 풀어주기
				return 0;
			}
			if(flag==1)//right로 내려왔을때
			{
				headShadow->right = NULL;//위에 노드 right 초기화 해주고 
				free(head);//노드 동적할당 풀어주기
				return 0;
			}
		}
		else{//leaf node가 아닐 떄
			printf("The node you selected is not a leaf node.\n");
			return -1;
		}
	}
	if(head->key>key)//입력받은 key값이 head가 가리키는 node의 key값 보다 작다면
	{
		flag=-1;//flag 바꾸고
		headShadow = head;//현재 node 주소 저장하고
		head = head->left;//왼쪽으로 내려가기
	}
	}
}

Node* searchRecursive(Node* ptr, int key)//ptr이 head->left
{
	if(ptr==NULL)return NULL;//끝까지 내려갔는데 값이 없음
	if(ptr->key==key)return ptr;//찾음
	if(ptr->key>key)return searchRecursive(ptr->left,key);//입력값이 작으면 left 주솟값으로 재귀함수 결과값 return 하기
	if(ptr->key<key)return searchRecursive(ptr->right,key);//입력값이 크면 right 주솟값으로 재귀함수 결과값 return 하기
}

Node* searchIterative(Node* head, int key)
{
	if(head==NULL)//껍질 node 없을 때
	{
		printf("Please do initialize BST first\n");
		return NULL;
	}
	if(head->left==NULL)//껍질 node의 left가 비었을 때
	{
		printf("The tree is empty\n");
		return NULL;
	}
	else head = head->left;//껍질 node 넘어가기
	while(1)
	{
		if(head==NULL)//끝까지 내려왔는데도 못찾았을 때
		{
			return head;
		}
		if(head->key==key)//찾음
		{
			return head;
		}
		if(head->key<key)//입력받은 key값이 head가 가리키는 node의 key값 보다 크다면
		{
			head = head->right;//오른쪽으로
			continue;
		}
	
		if(head->key>key)//입력받은 key값이 head가 가리키는 node의 key값 보다 작다면
		{
			head = head->left;//왼쪽으로
			continue;
		}
	}
}


int freeBST(Node* head) {
    if (head == NULL) {//껍질 node가 없을 때
        return 0;
    }
    if(head->left==NULL){//빈 tree 일 때
		free(head);
		return 0;
	}
	else{
		head=head->left;//껍질 node 건너뛰기
	}
	//stack에 node들의 주소를 저장하며 내려간다.
    Node** stack = (Node**)malloc(sizeof(Node*) * height(head)); // 더럽고 추한 height 함수로 tree의 높이를 구해 stack 크기 결정
    int top = -1;
    stack[++top] = head;// 루트 노드를 push
    while (top >= 0) {
        Node* current = stack[top--];// pop
        // 좌우 자식 노드를 push (존재하는 경우)
        if (current->left != NULL) {
            stack[++top] = current->left;
        }
        if (current->right != NULL) {
            stack[++top] = current->right;
        }
        free(current);// 현재 node free
    }
}
int height(Node* root)
	{
    // Base case: root가 NULL이면 높이는 0
    if (root == NULL) {
        return 0;
    }
    
    // 왼쪽 서브트리의 높이 계산
    int leftHeight = height(root->left);
    // 오른쪽 서브트리의 높이 계산
    int rightHeight = height(root->right);
    
    // 더 큰 서브트리 높이에 1을 더해서 반환
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}





