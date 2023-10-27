typedef struct Node {
    int value;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct DoublyLinkedList {
    struct Node *first;
    struct Node *last;
} DoublyLinkedList;

void insert_at_end(DoublyLinkedList *, int);
int remove_from_front(DoublyLinkedList *);
