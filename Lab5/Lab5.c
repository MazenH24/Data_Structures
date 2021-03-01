#include <stdio.h>
#include <stdlib.h>

typedef struct customer
{
  int bank_ID;
  int starting_time;
  int mins_processing;
} Customer;

typedef struct employee
{
  int id;
  int working_time;
  int fin_time;
  int time[1000];
} Employee;

typedef struct processed_data
{
  int bank_ID;
  int employee;
  int starting_time;
  int finishing_time;
  int waiting_time;
} Report_Segment;

typedef struct list_node
{
  Report_Segment data;
  struct list_node* next;
} Report;

typedef struct queue_node
{
  Customer data;
  struct queue_node* next;
  struct queue_node* previous;
  struct queue_node* end;
} Queue_Node;

void Enqeue(Queue_Node **head, Customer data)
{
  Queue_Node *temp = (Queue_Node*)malloc(sizeof(Queue_Node));
  temp -> data = data;
  if(*head == NULL)
  {
    temp -> next = NULL;
    temp -> previous = NULL;
    temp -> end = temp;
    *head = temp;
  }
  else
  {
    temp -> next = (*head);
    temp -> end = (*head) -> end;
    temp -> previous = NULL;
    (*head) -> previous = temp;
    (*head) = temp;
  }
}

Customer Deqeue(Queue_Node **head)
{
  Queue_Node *temp = (*head) -> end;
  Customer temp_customer = temp -> data;
  if(temp -> previous != NULL)
  {
    temp -> previous -> next = NULL;
    temp = temp -> previous;
    free(temp -> next);
    Queue_Node *end = temp;
    while(temp != NULL)
    {
      temp -> end = end;
      temp = temp -> previous;
    }
  }
  else
  {
    free(*head);
    *head = NULL;
  }
  return temp_customer;
}

void id_sort(Employee *arr, int len) //according to id
{
  for(int i = 0; i < len; ++i) //loop from 0 to n
  {
    for(int j = i + 1; j < len; ++j) // loop from i to n
    {
      if(arr[i].id < arr[j].id) //if ith elemnt is greater than jth swap them
      {
        Employee temp = arr[j];
        arr[j] = arr[i];
        arr[i] = temp;
      }
    }
  }
}

void ft_sort(Employee *arr, int len) //according to finishing time
{
  for(int i = 0; i < len; ++i) //loop from 0 to n
  {
    for(int j = i + 1; j < len; ++j) // loop from i to n
    {
      if(arr[i].fin_time < arr[j].fin_time) //if ith elemnt is greater than jth swap them
      {
        Employee temp = arr[j];
        arr[j] = arr[i];
        arr[i] = temp;
      }
      else if(arr[i].fin_time == arr[j].fin_time)
      {
        if(arr[i].id < arr[j].id) //if ith elemnt is greater than jth swap them
        {
          Employee temp = arr[j];
          arr[j] = arr[i];
          arr[i] = temp;
        }
      }
    }
  }
}

void Print_Queue(Queue_Node *head)
{
  Queue_Node *temp = head;
  if(temp == NULL)
    printf("Queue is Empty!\n");
  while(temp != NULL)
  {
    printf("%d %d %d\n", temp -> data.bank_ID, temp -> data.starting_time, temp -> data.mins_processing);
    printf("it's end %d %d %d\n", temp -> end -> data.bank_ID, temp -> end -> data.starting_time, temp -> end -> data.mins_processing);
    temp = temp -> next;
  }
}

void Append(Report **list, Report_Segment segment)
{
  Report *node =(Report*)malloc(sizeof(Report));
  node -> next = NULL;
  node -> data = segment;
  if(*list == NULL)
      *list = node;
  else
  {
    Report *temp = *list;
    while(temp -> next != NULL)
      temp = temp -> next;
    temp -> next = node;
  }
}

void Print_Report(Report *list)
{
  Report *temp = list;
  while(temp != NULL)
  {
    printf("%d %d %d %d %d\n", temp -> data.bank_ID, temp -> data.employee, temp -> data.starting_time, temp -> data.finishing_time, temp -> data.waiting_time);
    temp = temp -> next;
  }
}

void Print_Employees(Employee *Employees, int num_employees)
{
  for(int i = 0; i < num_employees; ++i)
    printf("%d %d\n", Employees[i].id, Employees[i].working_time);
}

void Process(Queue_Node *Customers, Employee *Employees, int num_employees)
{
  Report *list = NULL;
  Customer temp_c = {0, 0, 0};
  Employee temp_e = {0, 0, 0, {0}};
  while(Customers != NULL)
  {
      temp_c = Deqeue(&Customers);
      int employee_index = 0;
      int waiting_time  = 0;
      for(employee_index = 0; employee_index < num_employees; ++employee_index)
      {
        int employee_flag = 1;
        for(int j = temp_c.starting_time; j < temp_c.starting_time + temp_c.mins_processing; ++j)
          if(Employees[employee_index].time[j] == 1)
          {
            employee_flag = 0;
            break;
          }
        if(employee_flag)
          break;
      }
      if(employee_index == num_employees)
      {
        while(1)
        {
          employee_index = 0;
          ++temp_c.starting_time;
          ++waiting_time;
          for(employee_index = 0; employee_index < num_employees; ++employee_index)
          {
            int employee_flag = 1;
            for(int j = temp_c.starting_time; j < temp_c.starting_time + temp_c.mins_processing; ++j)
              if(Employees[employee_index].time[j] == 1)
              {
                employee_flag = 0;
                break;
              }
            if(employee_flag)
              break;
          }
          if(!(employee_index == num_employees))
            break;
        }
      }
      for(int j = temp_c.starting_time; j < temp_c.starting_time + temp_c.mins_processing; ++j)
      {
        Employees[employee_index].time[j] = 1;
        Employees[employee_index].fin_time = j-1;
      }
      Employees[employee_index].working_time += temp_c.mins_processing;
      Report_Segment entery = {temp_c.bank_ID, Employees[employee_index].id, temp_c.starting_time, temp_c.starting_time + temp_c.mins_processing, waiting_time};
      Append(&list, entery);
      ft_sort(Employees, 6);
//      Print_Employees(Employees, 6);
//      printf("\n");
  }
  Print_Report(list);
  printf("\n");
  id_sort(Employees, 6);
  Print_Employees(Employees, num_employees);
}

int main()
{
  Customer temp_customer = {0, 0, 0};
  Employee temp_employee = {0, 0, 0, {0}};
  Queue_Node *Queue = NULL;
  Employee Stack[6];

  for(int i = 0; i < 6; ++i)
  {
    temp_employee.id = 6 - i;
    temp_employee.fin_time = 0;
    Stack[i] = temp_employee;
  }

  scanf("%d", &temp_customer.bank_ID);
  while(temp_customer.bank_ID != -1)
  {
    scanf("%d%d", &temp_customer.starting_time, &temp_customer.mins_processing);
    Enqeue(&Queue, temp_customer);
    scanf("%d", &temp_customer.bank_ID);
  }
  Process(Queue, Stack, 6);
  return 0;
}
