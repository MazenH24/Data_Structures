
struct nodeClass
{
	int classID;
	double classMidtermAverage;
	struct nodeClass *next;
	struct nodeStudent *studentPtr;
};

struct nodeStudent
{
	int studentID;
	int midterm;
	struct nodeStudent *next;
};


// You must write all the function definitions to be used in this lab into this file.
// You may also write other functions that may be called from our functions.
// Do not make any changes to the main.c file.
// Upload function.h file to the system as StudentNumber.h.

void insert_student(struct nodeStudent **head, int id, int midterm)
{
	if((*head) == NULL)
	{
		*head = (struct nodeStudent*)malloc(sizeof(struct nodeStudent));
		(*head) -> studentID = id;
		(*head) -> midterm = midterm;
		(*head) -> next = NULL;
		return;
	}

	struct nodeStudent *newnode = (struct nodeStudent*)malloc(sizeof(struct nodeStudent));
	newnode -> studentID = id;
	newnode -> midterm = midterm;
	newnode -> next = NULL;

	if((*head) -> midterm < newnode -> midterm)
	{
		newnode -> next = *head;
		*head = newnode;
	}
	else if((*head) -> midterm == newnode -> midterm)
	{
		if((*head) -> studentID < newnode -> studentID)
		{
			newnode -> next = *head;
			*head = newnode;
		}
		else
			(*head) -> next = newnode;
	}
	else
	{
		struct nodeStudent *temp_ptr = *head;
		struct nodeStudent *pre_temp_ptr = *head;
		while(temp_ptr -> next != NULL)
		{
			if(temp_ptr -> midterm <= newnode -> midterm)
				break;
			pre_temp_ptr = temp_ptr;
			temp_ptr = temp_ptr -> next;
		}

		if(temp_ptr -> midterm < newnode -> midterm)
		{
			newnode -> next = temp_ptr;
			pre_temp_ptr -> next = newnode;
		}
		else if(temp_ptr -> midterm == newnode -> midterm)
		{
			if(temp_ptr -> studentID > newnode -> studentID)
			{
				newnode -> next = temp_ptr;
				pre_temp_ptr -> next = newnode;
			}
			else
			{
				pre_temp_ptr = temp_ptr;
				temp_ptr = temp_ptr -> next;
				newnode -> next = temp_ptr;
				pre_temp_ptr -> next = newnode;
			}
		}
		else if(temp_ptr -> next == NULL)
			temp_ptr -> next = newnode;
	}
}

void insert(struct nodeClass **head, int id, int midterm)
{
	if(*head == NULL)
	{
		*head = (struct nodeClass*)malloc(sizeof(struct nodeClass));
		struct nodeClass *temp_ptr = *head;
		int temp_class_id = 66;
		temp_ptr -> classID = temp_class_id;
		temp_class_id += 11;
		for(int i = 0; i < 3; ++i, temp_class_id += 11)
		{
			temp_ptr -> next = (struct nodeClass*)malloc(sizeof(struct nodeClass));
			temp_ptr -> studentPtr = NULL;
			temp_ptr = temp_ptr -> next;
			temp_ptr -> classID = temp_class_id;
		}
		temp_ptr -> next = NULL;
	}

	int class_of_student = id / 1000;
	struct nodeClass *temp_ptr_class = *head;
	while(temp_ptr_class -> classID != class_of_student)
		temp_ptr_class = temp_ptr_class -> next;
	insert_student(&(temp_ptr_class -> studentPtr), id, midterm);
}

void computeClassAverage(struct nodeClass *head)
{
	struct nodeClass *temp_class = head;
	for(int i = 0; i < 4; ++i)
	{
		struct nodeStudent *temp_ptr_student = temp_class -> studentPtr;
		int sum = 0;
		int num_of_students = 0;
		while(temp_ptr_student != NULL)
		{
			sum += temp_ptr_student -> midterm;
			++num_of_students;
			temp_ptr_student = temp_ptr_student -> next;
		}
		temp_class -> classMidtermAverage = ((double)sum / num_of_students);
		temp_class = temp_class -> next;
	}
}

void printAll(struct nodeClass *head)
{
	struct nodeClass *temp_class = head;
	for(int i = 0; i < 4; ++i)
	{
		printf("%d %0.2lf\n", i+1, temp_class -> classMidtermAverage);
		struct nodeStudent *temp_ptr_student = temp_class -> studentPtr;
		while(temp_ptr_student != NULL)
		{
			printf("%d %d\n", temp_ptr_student -> studentID, temp_ptr_student -> midterm);
			temp_ptr_student = temp_ptr_student -> next;
		}
		temp_class = temp_class -> next;
	}
}
