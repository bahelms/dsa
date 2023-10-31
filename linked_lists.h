typedef struct Node {
    int value;
    struct Node *next;
    struct Node *prev;
} Node;

Node *init_node(int);
Node *insert_after(int, Node *);
Node *reverse(Node *);
void print_list(Node *);

typedef struct DoublyLinkedList {
    struct Node *first;
    struct Node *last;
} DoublyLinkedList;

void insert_at_end(DoublyLinkedList *, int);
int remove_from_front(DoublyLinkedList *);
