#include <string>
#include <cstdlib>
#include <cstdio>

#define max (nodo->b - nodo->a)

enum OP
{
    NINGUNA,
    TO_ONES,
    TO_ZEROS,
    INVERT
};

enum POSITION
{
    IN,
    OUT,
    SECTION
};

using namespace std;

int testCases = 0;
int pairOfLines = 0;

int amountSet = 0;
int numberQueries = 0;
string finalString;
string auxString;

struct Node
{
    int a, b,
        counter = 0;
    OP operation = NINGUNA;
    Node *l, *r;
};

Node *root;

void buildTree();
Node *recursiveBuild(int, int);
void recursiveClear(Node *);
void clearTree();

void traverseTree(int, int, Node *, OP);
void lazyOperation(Node *, OP);
void executeOperation(Node *);
inline POSITION getPosition(int, int, Node *);

int query(Node *, int, int);

int main()
{

    cin >> testCases;
    int currentCase = 0;
    while (testCases--)
    {
        cout << "Case "<< ++currentCase << ':'<< endl;
        finalString.clear();
        finalString.reserve(102400);
        cin >> pairOfLines;
        while (pairOfLines--)
        {
            cin >> amountSet;
            cin >> auxString;
            for (int i = 0; i < amountSet; i++)
                finalString.append(auxString);
        }
        clearTree();
        buildTree();
        cin >> numberQueries;

        int currentGodsQuery = 0;
        while (numberQueries--)
        {
            char type;
            int a, b;
            cin >> type >> a >> b;
            b += 1;
            switch (type)
            {
            case 'F':
                traverseTree(a, b, root, TO_ONES);
                break;
            case 'E':
                traverseTree(a, b, root, TO_ZEROS);
                break;
            case 'I':
                traverseTree(a, b, root, INVERT);
                break;
            case 'S':
                cout <<'Q' << ++currentGodsQuery << ": " << query(root, a, b) << endl;
                break;
            }
        }
    }
    return 0;
}

// To query

int query(Node *nodo, int a, int b)
{
    if (nodo->operation != NINGUNA)
        executeOperation(nodo);

    int sum = 0;
    switch (getPosition(a, b, nodo))
    {
    case IN:
        sum = nodo->counter;
        break;
    case SECTION:
        sum = query(nodo->l, a, b) + query(nodo->r, a, b);
        break;
    }
    return sum;
}

// To create lazy operations

void traverseTree(int a, int b, Node *nodo, OP op)
{
    if (nodo->operation != NINGUNA)
        executeOperation(nodo);

    POSITION p = getPosition(a, b, nodo);

    switch (p)
    {
    case IN:
        lazyOperation(nodo, op);
        executeOperation(nodo);
        break;
    case SECTION:
        traverseTree(a, b, nodo->l, op);
        traverseTree(a, b, nodo->r, op);
        nodo->counter = nodo->l->counter + nodo->r->counter;
        break;
    default:
        break;
    }
    return;
}

inline POSITION getPosition(int a, int b, Node *nodo)
{
    if (nodo == NULL)
        return OUT;

    if (a <= nodo->a && nodo->b <= b)
        return IN;
    else if (nodo->b <= a || b <= nodo->a)
        return OUT;
    return SECTION;
}

void lazyOperation(Node *nodo, OP op)
{
    if (nodo == NULL || op == NINGUNA)
        return;
    if (nodo->operation != NINGUNA)
        executeOperation(nodo);
    nodo->operation = op;
}

void executeOperation(Node *nodo)
{
    switch (nodo->operation)
    {
    case TO_ONES:
        nodo->counter = max;
        break;
    case TO_ZEROS:
        nodo->counter = 0;
        break;
    case INVERT:
        nodo->counter = max - nodo->counter;
        break;
    }
    lazyOperation(nodo->l, nodo->operation);
    lazyOperation(nodo->r, nodo->operation);
    nodo->operation = NINGUNA;
    return;
}

// To create the segment tree

void clearTree()
{
    recursiveClear(root);
}

void recursiveClear(Node *nodo)
{
    if (nodo == NULL)
        return;
    recursiveClear(nodo->l);
    recursiveClear(nodo->r);
    delete nodo;
}

void buildTree()
{
    root = recursiveBuild(0, finalString.size());
    return;
}

Node *recursiveBuild(int a, int b)
{
    Node *ans = new Node;
    ans->a = a;
    ans->b = b;
    if (b - a <= 1)
    {
        ans->l = NULL;
        ans->r = NULL;
        ans->counter = finalString[a] == '1' ? 1 : 0;
    }
    else
    {
        ans->l = recursiveBuild(a, (a + b) / 2);
        ans->r = recursiveBuild((a + b) / 2, b);
        ans->counter = ans->l->counter + ans->r->counter;
    }
    return ans;
}