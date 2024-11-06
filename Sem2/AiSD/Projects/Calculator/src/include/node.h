#pragma once

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
    BRACKETS_END,
    COMMA
} T;



class node
{
private:
    T token;
    int value;
    int key;

    node* next;
public:
    node();
    node(T tok);
    node(int value);
    node(node* orig);

    T GetToken();
    void SetToken(T token);

    node* GetNext();
    void SetNext(node* next);

    int GetValue();
    void SetValue(int new_value);

    int GetKey();
    void SetKey(int key);

    ~node();
};

node::node()
{
    token = NUMBER;
    value = 0;
    next = nullptr;
    key = -1;
}

node::node(T tok)
{
    token = tok;
    value = 0;
    next = nullptr;
    key = -1;
}

node::node(int value)
{
    token = NUMBER;
    this->value = value;
    next = nullptr;
    key = -1;
}

node::node(node* orig)
{
    token = orig->GetToken();
    value = orig->GetValue();
    next = nullptr;
    key = orig->GetKey(); 
}

T node::GetToken()
{
    return token;
}

void node::SetToken(T token)
{
    this->token = token;
    return;
}

node* node::GetNext()
{
    return next;
}

void node::SetNext(node* next)
{
    this->next = next;
    return;
}

int node::GetValue()
{
    return value;
}

void node::SetValue(int new_value)
{
    this->value = new_value;
    return;
}

int node::GetKey()
{
    return key;
}

void node::SetKey(int key)
{
    this->key = key;
    return;
}

node::~node()
{
    if (next != nullptr)
    {
        delete next;
        next = nullptr;   
    }
}
