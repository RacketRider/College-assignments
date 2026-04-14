#include <stdio.h>
#include <stdlib.h>
/*Abhijit Prasad Mallick
20252501001*/
typedef struct node
{
    int n;
    int k[3];
    struct node *ptr[4];
    int leaf;
} node;

node *nw(int leaf)
{
    node *t = (node *)malloc(sizeof(node));
    t->n = 0;
    t->leaf = leaf;
    for (int i = 0; i < 4; i++)
        t->ptr[i] = NULL;
    return t;
}

void prtkey(node *r)
{
    printf("[");
    for (int i = 0; i < r->n; i++) {
        printf("%d", r->k[i]);
        if (i < r->n - 1)
            printf(",");
    }
    printf("]");
}

node *srch(node *r, int x, int *ctr, int *f)
{
    if (!r)
        return NULL;

    int i = 0;
    while (i < r->n) {
        (*ctr)++;
        if (x == r->k[i]) {
            *f = 1;
            return r;
        }
        if (x < r->k[i])
            break;
        i++;
    }

    if (r->leaf)
        return r;

    return srch(r->ptr[i], x, ctr, f);
}

void split(node *prnt, int i)
{
    node *y = prnt->ptr[i];
    node *z = nw(y->leaf);

    z->n = 1;
    z->k[0] = y->k[2];

    if (!y->leaf) {
        z->ptr[0] = y->ptr[2];
        z->ptr[1] = y->ptr[3];
    }

    y->n = 1;

    for (int j = prnt->n; j >= i + 1; j--)
        prnt->ptr[j + 1] = prnt->ptr[j];

    prnt->ptr[i + 1] = z;

    for (int j = prnt->n - 1; j >= i; j--)
        prnt->k[j + 1] = prnt->k[j];

    prnt->k[i] = y->k[1];
    prnt->n++;
}

void insnon(node *r, int x)
{
    int i = r->n - 1;

    if (r->leaf) {
        while (i >= 0 && x < r->k[i]) {
            r->k[i + 1] = r->k[i];
            i--;
        }
        r->k[i + 1] = x;
        r->n++;
    } else {
        while (i >= 0 && x < r->k[i])
            i--;
        i++;

        if (r->ptr[i]->n == 3) {
            split(r, i);
            if (x > r->k[i])
                i++;
        }

        insnon(r->ptr[i], x);
    }
}

void ins(node **r, int x)
{
    if (!(*r)) {
        *r = nw(1);
        (*r)->k[0] = x;
        (*r)->n = 1;
        return;
    }

    if ((*r)->n == 3) {
        node *s = nw(0);
        s->ptr[0] = *r;
        split(s, 0);

        int i = 0;
        if (x > s->k[0])
            i = 1;
        insnon(s->ptr[i], x);
        *r = s;
    } else
        insnon(*r, x);
}

int pred(node *r)
{
    while (!r->leaf)
        r = r->ptr[r->n];
    return r->k[r->n - 1];
}

int succ(node *r)
{
    while (!r->leaf)
        r = r->ptr[0];
    return r->k[0];
}

void merge(node *r, int i)
{
    node *c1 = r->ptr[i];
    node *c2 = r->ptr[i + 1];

    c1->k[1] = r->k[i];
    c1->k[2] = c2->k[0];

    if (!c1->leaf) {
        c1->ptr[2] = c2->ptr[0];
        c1->ptr[3] = c2->ptr[1];
    }

    c1->n = 3;

    for (int j = i; j < r->n - 1; j++)
        r->k[j] = r->k[j + 1];

    for (int j = i + 1; j < r->n; j++)
        r->ptr[j] = r->ptr[j + 1];

    r->n--;
    free(c2);
}

void borrowprev(node *r, int i)
{
    node *c = r->ptr[i];
    node *s = r->ptr[i - 1];

    for (int j = c->n - 1; j >= 0; j--)
        c->k[j + 1] = c->k[j];

    if (!c->leaf)
        for (int j = c->n; j >= 0; j--)
            c->ptr[j + 1] = c->ptr[j];

    c->k[0] = r->k[i - 1];

    if (!c->leaf)
        c->ptr[0] = s->ptr[s->n];

    r->k[i - 1] = s->k[s->n - 1];

    c->n++;
    s->n--;
}

void borrownext(node *r, int i)
{
    node *c = r->ptr[i];
    node *s = r->ptr[i + 1];

    c->k[c->n] = r->k[i];

    if (!c->leaf)
        c->ptr[c->n + 1] = s->ptr[0];

    r->k[i] = s->k[0];

    for (int j = 1; j < s->n; j++)
        s->k[j - 1] = s->k[j];

    if (!s->leaf)
        for (int j = 1; j <= s->n; j++)
            s->ptr[j - 1] = s->ptr[j];

    c->n++;
    s->n--;
}

void fill(node *r, int i)
{
    if (i != 0 && r->ptr[i - 1]->n >= 2)
        borrowprev(r, i);
    else if (i != r->n && r->ptr[i + 1]->n >= 2)
        borrownext(r, i);
    else {
        if (i != r->n)
            merge(r, i);
        else
            merge(r, i - 1);
    }
}

void delnode(node *r, int x);

void delint(node *r, int i)
{
    int x = r->k[i];

    if (r->ptr[i]->n >= 2) {
        int p = pred(r->ptr[i]);
        r->k[i] = p;
        delnode(r->ptr[i], p);
    } else if (r->ptr[i + 1]->n >= 2) {
        int s = succ(r->ptr[i + 1]);
        r->k[i] = s;
        delnode(r->ptr[i + 1], s);
    } else {
        merge(r, i);
        delnode(r->ptr[i], x);
    }
}

void delnode(node *r, int x)
{
    int i = 0;
    while (i < r->n && x > r->k[i])
        i++;

    if (i < r->n && r->k[i] == x) {
        if (r->leaf) {
            for (int j = i + 1; j < r->n; j++)
                r->k[j - 1] = r->k[j];
            r->n--;
        } else
            delint(r, i);
    } else {
        if (r->leaf)
            return;

        int f = (i == r->n);

        if (r->ptr[i]->n == 1)
            fill(r, i);

        if (f && i > r->n)
            delnode(r->ptr[i - 1], x);
        else
            delnode(r->ptr[i], x);
    }
}

void del(node **r, int x)
{
    if (!(*r))
        return;

    delnode(*r, x);

    if ((*r)->n == 0) {
        node *t = *r;
        if ((*r)->leaf)
            *r = NULL;
        else
            *r = (*r)->ptr[0];
        free(t);
    }
}

int ht(node *r)
{
    if (!r)
        return 0;
    if (r->leaf)
        return 1;
    return 1 + ht(r->ptr[0]);
}

void prt(node *r)
{
    if (!r)
        return;

    int h = ht(r);

    if (h == 1) {
        prtkey(r);
        printf("\n");
        return;
    }

    if (h == 2) {
        printf("        ");
        prtkey(r);
        printf("\n");

        printf("        ");
        for (int i = 0; i <= r->n; i++) {
            printf("|");
            if (i < r->n)
                printf(" ");
        }
        printf("\n\n");

        printf("    ");
        for (int i = 0; i <= r->n; i++) {
            prtkey(r->ptr[i]);
            if (i < r->n)
                printf("        ");
        }
        printf("\n");
        return;
    }

    node *q1[100], *q2[100];
    int c1 = 0, c2 = 0;

    q1[c1++] = r;

    while (c1) {
        for (int i = 0; i < c1; i++) {
            prtkey(q1[i]);
            if (i < c1 - 1)
                printf(" ");
            if (!q1[i]->leaf)
                for (int j = 0; j <= q1[i]->n; j++)
                    q2[c2++] = q1[i]->ptr[j];
        }
        printf("\n");
        for (int i = 0; i < c2; i++)
            q1[i] = q2[i];
        c1 = c2;
        c2 = 0;
    }
}

int main()
{
    int t;
    scanf("%d", &t);

    while (t--) {
        node *r = NULL;

        int n;
        scanf("%d", &n);

        int ar[n];
        for (int i = 0; i < n; i++)
            scanf("%d", &ar[i]);

        for (int i = 0; i < n; i++)
            ins(&r, ar[i]);

        int ch;
        scanf("%d", &ch);

        if (ch == 4)
            prt(r);

        int op;
        if (scanf("%d", &op) != 1)
            continue;

        if (op == 2) {
            int x;
            scanf("%d", &x);
            del(&r, x);
            printf("\nAfter delete\n");
            prt(r);
        } else if (op == 3) {
            int x, ctr = 0, f = 0;
            scanf("%d", &x);
            srch(r, x, &ctr, &f);
            if (f)
                printf("%d Found (%d comparisons)\n", x, ctr);
            else
                printf("\n%d Not Found (%d comparisons)\n", x, ctr);
        }
    }

    return 0;
}