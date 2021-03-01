int NumOfNodesInFB = 0;
int NumOfNodesInGS = 0;

struct nodeFB
{
	int id;
	int age;
	struct nodeFB *next;
};

struct nodeGS
{
	int id;
	struct nodeGS *next;
};

struct newNodeFB
{
	int id;
	int age;
	struct newNodeGS *next;
};

struct newNodeGS
{
	int id;
	struct newNodeFB *next;
};

void insertFB(struct nodeFB **head, int id, int age)
{
	if(*head == NULL)
	{
		struct nodeFB *newnode = (struct nodeFB *)malloc(sizeof(struct nodeFB));
		newnode -> id = id;
		newnode -> age = age;
		newnode -> next = NULL;
		*head = newnode;
		++NumOfNodesInFB;
	}
	else
	{
		struct nodeFB *temp = *head;
		struct nodeFB *newnode = (struct nodeFB*)malloc(sizeof(struct nodeFB));
		newnode -> id = id;
		newnode -> age = age;
		if((temp -> id) > (newnode -> id))
		{
			newnode -> next = temp;
			*head = newnode;
			++NumOfNodesInFB;
			return;
		}
		while(temp -> next != NULL)
		{
			if((temp -> next -> id) > (newnode -> id))
				break;
			temp = temp -> next;
		}

		if(temp -> next == NULL)
		{
			temp -> next = newnode;
			newnode -> next = NULL;
		}
		else
		{
			newnode -> next = temp -> next;
			temp -> next = newnode;
		}
		++NumOfNodesInFB;
	}
}

void printFB(struct nodeFB *head)
{
	if(NumOfNodesInFB == 0)
		return;

	struct nodeFB *temp = head;
	printf("%d %d\n",temp -> id, temp -> age);
	while(temp -> next != NULL)
	{
		temp = temp -> next;
		printf("%d %d\n",temp -> id, temp -> age);
	}
	printf("\n");
}

void insertGS(struct nodeGS **head, int id)
{
	if(*head == NULL)
	{
		struct nodeGS *newnode = (struct nodeGS *)malloc(sizeof(struct nodeGS));
		newnode -> id = id;
		newnode -> next = NULL;
		*head = newnode;
		++NumOfNodesInGS;
	}
	else
	{
		struct nodeGS *temp = *head;
		struct nodeGS *newnode = (struct nodeGS*)malloc(sizeof(struct nodeGS));
		newnode -> id = id;
		if((temp -> id) < (newnode -> id))
		{
			newnode -> next = temp;
			*head = newnode;
			++NumOfNodesInGS;
			return;
		}

		while(temp -> next != NULL)
		{
			if((temp -> next -> id) < (newnode -> id))
				break;
			temp = temp -> next;
		}
		if(temp -> next == NULL)
		{
			newnode -> next = NULL;
			temp -> next = newnode;
		}
		else
		{
			newnode -> next = temp -> next;
			temp -> next = newnode;
		}
		++NumOfNodesInGS;
	}
}

void printGS(struct nodeGS *head)
{
	if(NumOfNodesInGS == 0)
		return;

	struct nodeGS *temp = head;
	printf("%d\n",temp -> id);
	while(temp -> next != NULL)
	{
		temp = temp -> next;
		printf("%d\n",temp -> id);
	}
	printf("\n");
}
void copy_FB_to_newFB(struct nodeFB * NFB, struct newNodeFB *NEWFB)
{
	NEWFB -> id = NFB -> id;
	NEWFB -> age = NFB -> age;
	NEWFB -> next = NULL;
}

void copy_GS_to_newGS(struct nodeGS * NGS, struct newNodeGS *NEWGS)
{
	NEWGS -> id = NGS -> id;
	NEWGS -> next = NULL;
}

void createFinalList(struct newNodeFB **root, struct nodeFB *headFB, struct nodeGS *headGS)
{
	for(int i = 0; (headFB != NULL) || (headGS != NULL); ++i)
	{
		if(i == 0)
		{
			struct newNodeFB *newnode = (struct newNodeFB*)malloc(sizeof(struct newNodeFB));
			copy_FB_to_newFB(headFB, newnode);
			*root = newnode;
			headFB = headFB -> next;
		}
		else if(i % 2 != 0)
		{
			struct newNodeGS *newnode = (struct newNodeGS*)malloc(sizeof(struct newNodeGS));
			copy_GS_to_newGS(headGS, newnode);

			struct newNodeGS *tempGS = (*root) -> next;
			struct newNodeFB *tempFB = *root;
			for(int i = 0; 1; ++i)
			{
				if(i % 2 == 0)
					tempGS = tempFB -> next;
				else
					tempFB = tempGS -> next;
				if(tempFB -> next == NULL)
					break;
			}
			tempFB -> next = newnode;
			headGS = headGS -> next;
		}
		else if(i % 2 == 0)
		{
			struct newNodeFB *newnode = (struct newNodeFB*)malloc(sizeof(struct newNodeFB));
			copy_FB_to_newFB(headFB, newnode);
			struct newNodeGS *tempGS = (*root) -> next;
			struct newNodeFB *tempFB = *root;
			for(int i = 0; 1; ++i)
			{
				if(i % 2 == 0)
					tempGS = tempFB -> next;
				else
					tempFB = tempGS -> next;
				if(tempGS -> next == NULL)
					break;
			}
			tempGS -> next = newnode;
			headFB = headFB -> next;
		}
	}
}



void printAll(struct newNodeFB *root)
{
	if(NumOfNodesInFB + NumOfNodesInGS == 0)
		return;
	struct newNodeGS *tempGS = root -> next;
	struct newNodeFB *tempFB = root;
	for(int i = 0; i < NumOfNodesInFB + NumOfNodesInGS; ++i)
	{
		if(i % 2 == 0)
		{
			if(tempFB != NULL)
			{
				printf("%d %d\n",tempFB -> id, tempFB -> age);
				tempGS = tempFB -> next;
			}
		}
		else
		{
			if(tempGS != NULL)
			{
				printf("%d\n",tempGS -> id);
				tempFB = tempGS -> next;
			}
		}
	}
}
