#include<iostream>

using namespace std;

struct Node {
    unsigned long long int value;
    Node* next;
    Node* prev;
};
struct Iterator {
    Node* arr[10];
};

void add_at_front_before(Node** head, Node** tail, unsigned long long int value)
{
    Node* new_node = new Node;
    new_node->value = value;
    new_node->next = *head;
    new_node->prev = NULL;
    if (*head != NULL)
    {
        (*head)->prev = new_node;
    }
    if (new_node->next == NULL)
    {
        *tail = new_node;
    }
    *head = new_node;
}

void add_at_front_after(Node** head, Node** tail, unsigned long long int value)
{
    Node* new_node = new Node;
    new_node->value = value;
    if (*head == NULL)
    {
        new_node->next = NULL;
        new_node->prev = NULL;
        *head = new_node;
        *tail = new_node;
    }
    else
    {
        if ((*head)->next == NULL)
        {
            new_node->prev = *head;
            new_node->next = NULL;
            *tail = new_node;
            (*head)->next = new_node;
        }
        else
        {
            new_node->prev = *head;
            new_node->next = (*head)->next;
            (*head)->next->prev = new_node;
            (*head)->next = new_node;
        }
    }
}

void add_at_end_after(Node** head, Node** tail, unsigned long long int value)
{
    Node* new_node = new Node;
    new_node->value = value;
    new_node->prev = *tail;
    new_node->next = NULL;
    if (*tail != NULL)
    {
        (*tail)->next = new_node;
    }
    *tail = new_node;
    if (new_node->prev == NULL)
    {
        *head = new_node;
    }
}

void add_at_end_before(Node** head, Node** tail, unsigned long long int value)
{
    Node* new_node = new Node;
    new_node->value = value;
    if (*head == NULL)
    {
        new_node->prev = NULL;
        new_node->next = NULL;
        *tail = new_node;
        *head = new_node;
    }
    else
    {
        if ((*tail)->prev != NULL)
        {
            new_node->next = *tail;
            new_node->prev = (*tail)->prev;
            (*tail)->prev->next = new_node;
            (*tail)->prev = new_node;
        }
        else
        {
            new_node->next = *tail;
            new_node->prev = NULL;
            (*tail)->prev = new_node;
            *head = new_node;
        }
    }
}

void add_after(Node** tail, Iterator* iterator, unsigned long long int value, int index)
{
    Node* new_node = new Node;
    Node* temp = iterator->arr[index];

    if (temp->next == NULL)
    {
        new_node->value = value;
        new_node->prev = temp;
        new_node->next = NULL;
        temp->next = new_node;
        *tail = new_node;
    }
    else
    {
        new_node->value = value;
        new_node->prev = temp;
        new_node->next = temp->next;
        temp->next = new_node;
        new_node->next->prev = new_node;
    }
}

void add_before(Node** head, Iterator* iterator, unsigned long long int value, int index)
{
    Node* new_node = new Node;
    Node* temp = iterator->arr[index];
    new_node->value = value;
    new_node->next = temp;
    if (temp->prev == NULL)
    {
        new_node->prev = NULL;
        temp->prev = new_node;
        *head = new_node;
    }
    else
    {
        new_node->prev = temp->prev;
        new_node->prev->next = new_node;
        temp->prev = new_node;
    }
}

void delete_first_node(Node** head, Node** tail)
{
    Node* temp = *head;
    if (temp->next != NULL)
    {
        temp->next->prev = NULL;
    }
    else
    {
        *tail = temp->next;
    }
    *head = temp->next;
    delete temp;
}

void delete_last_node(Node** head, Node** tail)
{
    Node* temp = *tail;
    if (temp->prev != NULL)
        temp->prev->next = NULL;
    else {
        *head = temp->prev;
    }
    *tail = temp->prev;
    delete temp;
}

void delete_node(Node** head, Node** tail, Iterator* iterator, int index)
{
    Node* temp = iterator->arr[index];
    for (int i = 0; i < 10; i++)
    {
        if (iterator->arr[i] == temp)
        {
            if (iterator->arr[i]->next != NULL)
                iterator->arr[i] = iterator->arr[i]->next;
            else
                iterator->arr[i] = iterator->arr[i]->prev;
        }
    }
    if (temp == *head)
        *head = temp->next;
    if (temp == *tail)
        *tail = temp->prev;
    if (temp->next != NULL)
        temp->next->prev = temp->prev;
    if (temp->prev != NULL)
        temp->prev->next = temp->next;
    delete temp;
}

void add_iterator(Node** head, Node** tail, Iterator* iterator, int position, char index[])
{
    if (strcmp(index, "BEG") == 0)
    {
        iterator->arr[position] = (*head);
    }
    else if (strcmp(index, "END") == 0)
    {
        iterator->arr[position] = (*tail);
    }
}

void move_forward(Iterator* iterator, unsigned long long int position)
{
    if (iterator->arr[position]->next != NULL)
        iterator->arr[position] = iterator->arr[position]->next;
}
void move_backward(Iterator* iterator, unsigned long long int position)
{
    if (iterator->arr[position]->prev != NULL)
        iterator->arr[position] = iterator->arr[position]->prev;
}

void print(Node* head)
{
    Node* temp = head;
    while (temp != NULL)
    {
        cout << temp->value << " ";
        temp = temp->next;
    }
    cout << endl;
}

void deleteAll(Node** head)
{
    Node* temp = *head;
    while (temp != NULL)
    {
        Node* temp2 = temp->next;
        delete temp;
        temp = temp2;
    }
}

void print_iterator(Iterator* iterator, unsigned long long int index)
{
    if (iterator->arr[index] != NULL)
        cout << iterator->arr[index]->value << endl;
}

void input(Node** head, Node** tail, Iterator* iterator, char command[], char index[])
{
    unsigned long long int value;
    unsigned long long int index_int;
    cin >> command;
    if (strcmp(command, ".A") == 0)
    {
        cin >> index;
        cin >> value;
        if (strcmp(index, "BEG") == 0)
        {
            add_at_front_before(head, tail, value);
        }
        else if (strcmp(index, "END") == 0)
        {
            add_at_end_before(head, tail, value);
        }
        else
        {
            index_int = index[0] - '0';
            add_before(head, iterator, value, index_int);
        }
    }
    else if (strcmp(command, "A.") == 0)
    {
        cin >> index;
        cin >> value;
        if (strcmp(index, "BEG") == 0)
        {
            add_at_front_after(head, tail, value);
        }
        else if (strcmp(index, "END") == 0)
        {
            add_at_end_after(head, tail, value);
        }
        else
        {
            index_int = index[0] - '0';
            add_after(tail, iterator, value, index_int);
        }
    }
    else if (strcmp(command, "R") == 0)
    {
        cin >> index;
        if (strcmp(index, "BEG") == 0)
        {
            delete_first_node(head, tail);
        }
        else if (strcmp(index, "END") == 0)
        {
            delete_last_node(head, tail);
        }
        else
        {
            index_int = index[0] - '0';
            delete_node(head, tail, iterator, index_int);
        }
    }
    else if (strcmp(command, "i") == 0)
    {
        int position;
        cin >> position;
        cin >> index;
        add_iterator(head, tail, iterator, position, index);
    }
    else if (strcmp(command, "+") == 0)
    {
        cin >> value;
        move_forward(iterator, value);
    }
    else if (strcmp(command, "-") == 0)
    {
        cin >> value;
        move_backward(iterator, value);
    }
    else if (strcmp(command, "P") == 0)
    {
        cin >> index;
        if (strcmp(index, "ALL") == 0)
        {
            print(*head);
        }
        else
        {
            index_int = index[0] - '0';
            print_iterator(iterator, index_int);
        }
    }
    else if (strcmp(command, "I") == 0)
    {
        int a;
        cin >> a;
    }
}

int main()
{
    char command[2];
    char index[3];
    Node* head = NULL;
    Node* tail = NULL;
    Iterator iterator;
    for (int i = 0; i < 10; i++)
    {
        iterator.arr[i] = NULL;
    }
    while (true)
    {
        input(&head, &tail, &iterator, command, index);
        if (feof(stdin) != 0)
        {
            break;
        }
    }
    deleteAll(&head);
}
