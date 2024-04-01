// #define NUMBER 1
// #define ADD 2
// #define SUBSTRUCT 3
// #define MULTIPLY 4
// #define DIVIDE 5
// #define IF 6
// #define N 7
// #define MIN 8
// #define MAX 9
// #define BRACKETS_START 10
// #define BRACKETS_END 11


typedef enum {
    NUMBER,
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    IF,
    N,
    MIN,
    MAX,
    BRACKETS_START,
    BRACKETS_END
} T;



class node
{
private:
    T token;
    int value;

    node* next;
public:
    node();
    node(T token);
    node(int value);

    T GetToken();
    void SetToken(T token);

    node* GetNext();
    void SetNext(node* next);

    int GetValue();

    ~node();
};

node::node()
{
    token = NUMBER;
    value = 0;
    next = nullptr;
}

node::node(T token)
{
    this->token = token;
    this->next = next;
    next = nullptr;
}

node::node(int value)
{
    this->token = NUMBER;
    this->value = value;
    next = nullptr;
}

T node::GetToken()
{
    return token;
}

void node::SetToken(T token)
{
    this->token = token;
}

node* node::GetNext()
{
    return next;
}

void node::SetNext(node* next)
{
    this->next = next;
}

int node::GetValue()
{
    return value;
}

node::~node()
{
    delete next;
    next = nullptr;
}
