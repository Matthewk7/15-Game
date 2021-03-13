
/* LL: Class to create a linked list
 * constructors:  LL ();
 *                LL( const LL &);
 * static members: None
 */
template <class Type >
class LL
{
    struct node
    {
    Type item ;
    node * next ;
    node * prev ;
    };
public :
    // Class used for the iterator
    class iterator
    {
    public :
        friend class LL;
        iterator ();
        iterator ( node *);
        Type operator *();
        iterator operator ++( int );
        iterator operator --( int );
        bool operator ==( const iterator &) const ;
        bool operator !=( const iterator &) const ;
    private :
        node * current ;
    };

    LL ();
    LL( const LL &);
    const LL& operator =( const LL &);
    ~LL ();
    iterator begin () const ;
    iterator end () const ;
    void headRemove ();
    void tailRemove ();
    void removeNode ( const iterator &);
    bool isEmpty () const ;
    void headInsert ( const Type &);
    void tailInsert ( const Type &);
    void update ( const iterator & , const Type &);
private :
    node * head ;
    node * tail ;
};

/*
 * Iterator(): Constructor - Sets current to nullptr
 * Parameters: None
 * Return value: None
*/ 
template <class Type>
LL<Type>::iterator::iterator(){
    current = nullptr;
}

/*
 * Iterator(): Constructor - Sets current to the pointer
 * Parameters: None
 * Return value: None
*/ 
template <class Type>
LL<Type>::iterator::iterator(node * pointer){
    current = pointer;
}

/*
 * operator*(): Returns the item of the node that current points to
 * Parameters: None
 * Return value: Type
*/ 
template <class Type>
Type LL<Type>::iterator::operator*(){
    return current -> item;
    //  returns the item field of the node that current points to
}

/*
 * operator++(): Sets current to the next node
 * Parameters: None
 * Return value: None
*/ 
template <class Type>
typename LL<Type>::iterator LL<Type>::iterator::operator++(int){
    current = current -> next;
    return current;
}

/*
 *Operator--(): Sets current to the previous node
 * Parameters: None
 * Return value: None
*/ 
template <class Type>
typename LL<Type>::iterator LL<Type>::iterator::operator--(int){
    current = current -> prev;
    return current;
}

/*
 * operator==(): Returns true if *this points to the same node as rhs object
 * Parameters: iterator &rhs - object passed
 * Return value: Bool
*/ 
template <class Type>
bool LL<Type>::iterator::operator==(const iterator& rhs) const {
    if (*this == rhs){
        return true;
    }
    return false;
}

/*
 * operator!=(): returns false if *this and passed object do not point to the same node
 * Parameters: iterator &rhs - object to check
 * Return value: bool
*/ 
template <class Type>
bool LL<Type>::iterator::operator!=(const iterator& rhs) const {
    if (*this != rhs){
        return true;
    }
    return false;
}



/*
 * LL(): Constructor - sets head and tail to null
 * Parameters: None
 * Return value: None
*/
template <class Type>
LL<Type> :: LL(){
    head = nullptr;
    tail = nullptr;
} 

// Copy Constructor
template <class Type>
LL<Type> :: LL( const LL& copy){
    // Set head and tail of new list to null
    head = nullptr;
    tail = nullptr;

    node *currentNode;
    node *newNode;

    // If list is not clear then clear it
    if (head != nullptr){
        node *temp = nullptr;

        while (head != nullptr){
            temp = head;
            head = head -> next;
            delete temp;
        }
        tail = nullptr;
    }

    // If copy list is empty, set new list to empty
    if (copy.head == nullptr && copy.tail == nullptr){
        head = nullptr;
        tail = nullptr;
    }
    else{
        // Copy head node
        currentNode = copy.head;

        head = new node;

        head -> info = currentNode -> info;
        head -> prev = currentNode -> prev;
        head -> next = currentNode -> next;
        tail = head;
        
        currentNode = currentNode -> next;

        // Copy remaining nodes
        while (currentNode != nullptr){
            newNode = new node;
            newNode -> info = currentNode -> info;
            newNode -> prev = currentNode -> prev;
            newNode -> next = currentNode -> next;

            tail = newNode;
            currentNode = currentNode -> next;
            tail = newNode;

            currentNode = currentNode -> next;
        }
    }
}

/*
 * ~LL(): Destructor - destroy the linked list
 * Parameters: None
 * Return value: None
*/ 
template <class Type>
LL<Type> :: ~LL(){
    // Create temporary node
    node *temp;

    // Delete each head until there are none remaining
    while (head != nullptr){
        temp = head;
        head = head -> next;
        delete temp;
    }
}

template <class Type>
const LL<Type>& LL<Type>::operator=(const LL& rhs){
    if (this == rhs){
        return this;
    }

    // Set head and tail of new list to null
    head = nullptr;
    tail = nullptr;

    node *currentNode;
    node *newNode;

    // If list is not clear then clear it
    if (head != nullptr){
        node *temp = nullptr;

        while (head != nullptr){
            temp = head;
            head = head -> next;
            delete temp;
        }
        tail = nullptr;
    }

    // If copy list is empty, set new list to empty
    if (rhs.head == nullptr && rhs.tail == nullptr){
        head = nullptr;
        tail = nullptr;
    }
    else{
        // Copy head node
        currentNode = rhs.head;

        head = new node;

        head -> info = currentNode -> info;
        head -> prev = currentNode -> prev;
        head -> next = currentNode -> next;
        tail = head;
        
        currentNode = currentNode -> next;

        // Copy remaining nodes
        while (currentNode != nullptr){
            newNode = new node;
            newNode -> info = currentNode -> info;
            newNode -> prev = currentNode -> prev;
            newNode -> next = currentNode -> next;

            tail = newNode;
            currentNode = currentNode -> next;
            tail = newNode;

            currentNode = currentNode -> next;
        }
    }
}

/*
 * begin(): Returns a pointer assigned to the head
 * Parameters: None
 * Return value: Typename pointer to the head
*/
template <class Type>
typename LL<Type>::iterator LL<Type>::begin() const{
    return head;
}

/*
 * end(): Returns a pointer assigned to the tail
 * Parameters: None
 * Return value: Typename pointer to the tail
*/
template <class Type>
typename LL<Type>::iterator LL<Type>::end() const{
    return tail;
}

/*
 * removeNode(): Delete the node that the iterator is pointing to
 * Parameters: Iterator
 * Return value: None
*/
template <class Type>
void LL<Type>::removeNode(const iterator& it){
    // Create temporary node 
    node *temp = new node;

    // Set the previous node to the next node and vice versa
    temp = it -> prev;
    temp -> next = it -> next;
    temp = it -> next;
    temp -> prev = it -> prev;

    // Delete the node
    delete it;
}

/*
 * headRemove(): Removes the head in the linked list
 * Parameters: None
 * Return value: None
*/
template <class Type>
void LL<Type>::headRemove(){
    // Removes the front node
    if (head == nullptr){
        return;
    }

    node *temp;
    temp = new node;
    temp = head;
    head = head -> next;

    if (head == nullptr){
        tail = nullptr;
    }
    delete temp;
}

/*
 * tailRemove(): Removes the tail in the linked list
 * Parameters: None
 * Return value: None
*/
template <class Type>
void LL<Type>::tailRemove(){
    // Removes the end node
    if (tail == nullptr){
        return;
    }

    node *temp;
    temp = new node;
    temp = tail;
    tail = tail -> prev;
    
    delete temp;
}

/*
 * isEmpty(): Returns true if list is empty and false if not empty
 * Parameters: None 
 * Return value: Bool
*/
template <class Type>
bool LL<Type>::isEmpty() const {
    if (head == nullptr){
        return true;
    }
    return false;
    // returns true if the list is empty and returns false if the list is not empty
}

/*
 * headInset(const Type& element): Insert an element to the beginning of the linked list
 * Parameters: Element to insert
 * Return value: None
*/
template <class Type>
void LL<Type>::headInsert(const Type& element){
    // Create new node
    node *newNode;
    newNode = new node;

    // Sets the element, next and prev of new node
    newNode -> item = element;
    newNode -> next = head;
    newNode -> prev = nullptr;

    // Set old head previous pointer to the new node
    if (head != nullptr){
        head -> prev = newNode;
    }

    // Make the head new node
    head = newNode;

    // Set tail to new node if it's the first item in list
    if (tail == nullptr){
        tail = newNode;
    }

}

/*
 * TailInsert(cosnt Type& element): Insert element at the end of linked list
 * Parameters: Value of element to add
 * Return value: None
*/
template <class Type>
void LL<Type>::tailInsert(const Type& element){
    // Create new node
    node *newNode;
    newNode = new node;

    // Sets the element, next and prev of the new node
    newNode -> item = element;
    newNode -> prev = tail;
    newNode -> next = nullptr;

    // Set the old tail next pointer to the new node
    if (tail != nullptr){
        tail -> next = newNode;
    }

    // Make the new node the tail
    tail = newNode;

    // Set head to newNode if it is the first value in list
    if (head == nullptr){
        head = newNode;
    }
}

/*
 * update(): Assignes the passed element to iterator pointing to a node
 * Parameters: iterator &it - Iterator, Type &element - element to assign
 * Return value: None
*/
template <class Type>
void LL<Type>::update(const LL<Type>::iterator& it, const Type& element) {
    it.current -> item = element;
    // assigns the item field of the node that the iterator object points to with the element passed into the function
}