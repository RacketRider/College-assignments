#include <stdio.h>
#include <stdlib.h>
/*Abhijit Prasad Mallick
20252501001*/
typedef struct node
{
    int d;
    char c;
    struct node *l, *r, *prnt;
} node;

node *nil;

node *nw(int d)
{
    node *t = (node *)malloc(sizeof(node));
    t->d = d;
    t->c = 'R';
    t->l = t->r = t->prnt = nil;
    return t;
}

void init()
{
    nil = (node *)malloc(sizeof(node));
    nil->c = 'B';
    nil->l = nil->r = nil->prnt = nil;
}

int mx(int a, int b)
{
    return a > b ? a : b;
}

void lrot(node **r, node *x)
{
    node *y = x->r;
    x->r = y->l;

    if (y->l != nil)
        y->l->prnt = x;

    y->prnt = x->prnt;

    if (x->prnt == nil)
        *r = y;
    else if (x == x->prnt->l)
        x->prnt->l = y;
    else
        x->prnt->r = y;

    y->l = x;
    x->prnt = y;
}

void rrot(node **r, node *x)
{
    node *y = x->l;
    x->l = y->r;

    if (y->r != nil)
        y->r->prnt = x;

    y->prnt = x->prnt;

    if (x->prnt == nil)
        *r = y;
    else if (x == x->prnt->r)
        x->prnt->r = y;
    else
        x->prnt->l = y;

    y->r = x;
    x->prnt = y;
}

int h(node *r)
{
    if (r == nil)
        return 0;
    return 1 + mx(h(r->l), h(r->r));
}

void lvl(node *r, int x)
{
    if (r == nil)
        return;

    if (x == 1)
        printf("%d(%c)", r->d, r->c);
    else {
        lvl(r->l, x - 1);
        if (r->l != nil && (r->r != nil || x == 2))
            printf(" ");
        lvl(r->r, x - 1);
    }
}

void prt(node *r)
{
    if (r == nil)
        return;

    int ht = h(r);
    for (int i = 1; i <= ht; i++) {
        lvl(r, i);
        printf("\n");
    }
}

void fixins(node **r, node *z)
{
    while (z->prnt->c == 'R') {
        if (z->prnt == z->prnt->prnt->l) {
            node *y = z->prnt->prnt->r;

            if (y->c == 'R') {
                printf("Recoloring parent %d, uncle %d, grandparent %d\n",
                       z->prnt->d, y->d, z->prnt->prnt->d);
                z->prnt->c = 'B';
                y->c = 'B';
                z->prnt->prnt->c = 'R';
                z = z->prnt->prnt;
            } else {
                if (z == z->prnt->r) {
                    z = z->prnt;
                    lrot(r, z);
                }
                printf("Right-Rotating grandparent %d\n", z->prnt->prnt->d);
                z->prnt->c = 'B';
                z->prnt->prnt->c = 'R';
                rrot(r, z->prnt->prnt);
            }
        } else {
            node *y = z->prnt->prnt->l;

            if (y->c == 'R') {
                printf("Recoloring parent %d, uncle %d, grandparent %d\n",
                       z->prnt->d, y->d, z->prnt->prnt->d);
                z->prnt->c = 'B';
                y->c = 'B';
                z->prnt->prnt->c = 'R';
                z = z->prnt->prnt;
            } else {
                if (z == z->prnt->l) {
                    z = z->prnt;
                    rrot(r, z);
                }
                printf("Left-Rotating grandparent %d\n", z->prnt->prnt->d);
                z->prnt->c = 'B';
                z->prnt->prnt->c = 'R';
                lrot(r, z->prnt->prnt);
            }
        }
    }
    (*r)->c = 'B';
}

void ins(node **r, int d)
{
    node *z = nw(d), *y = nil, *x = *r;

    while (x != nil) {
        y = x;
        if (z->d < x->d)
            x = x->l;
        else
            x = x->r;
    }

    z->prnt = y;

    if (y == nil)
        *r = z;
    else if (z->d < y->d)
        y->l = z;
    else
        y->r = z;

    z->l = z->r = nil;
    z->c = 'R';

    fixins(r, z);
}

node *srch(node *r, int x, int *ctr)
{
    *ctr = 0;
    while (r != nil) {
        (*ctr)++;
        if (x == r->d)
            return r;
        else if (x < r->d)
            r = r->l;
        else
            r = r->r;
    }
    return nil;
}

node *mnm(node *r)
{
    while (r->l != nil)
        r = r->l;
    return r;
}

void trns(node **r, node *u, node *v)
{
    if (u->prnt == nil)
        *r = v;
    else if (u == u->prnt->l)
        u->prnt->l = v;
    else
        u->prnt->r = v;

    v->prnt = u->prnt;
}

void fixdel(node **r, node *x)
{
    while (x != *r && x->c == 'B') {
        if (x == x->prnt->l) {
            node *w = x->prnt->r;

            if (w->c == 'R') {
                w->c = 'B';
                x->prnt->c = 'R';
                lrot(r, x->prnt);
                w = x->prnt->r;
            }

            if (w->l->c == 'B' && w->r->c == 'B') {
                w->c = 'R';
                x = x->prnt;
            } else {
                if (w->r->c == 'B') {
                    w->l->c = 'B';
                    w->c = 'R';
                    rrot(r, w);
                    w = x->prnt->r;
                }

                w->c = x->prnt->c;
                x->prnt->c = 'B';
                w->r->c = 'B';
                lrot(r, x->prnt);
                x = *r;
            }
        } else {
            node *w = x->prnt->l;

            if (w->c == 'R') {
                w->c = 'B';
                x->prnt->c = 'R';
                rrot(r, x->prnt);
                w = x->prnt->l;
            }

            if (w->r->c == 'B' && w->l->c == 'B') {
                w->c = 'R';
                x = x->prnt;
            } else {
                if (w->l->c == 'B') {
                    w->r->c = 'B';
                    w->c = 'R';
                    lrot(r, w);
                    w = x->prnt->l;
                }

                w->c = x->prnt->c;
                x->prnt->c = 'B';
                w->l->c = 'B';
                rrot(r, x->prnt);
                x = *r;
            }
        }
    }
    x->c = 'B';
}

void del(node **r, int x)
{
    node *z = *r;

    while (z != nil && z->d != x) {
        if (x < z->d)
            z = z->l;
        else
            z = z->r;
    }

    if (z == nil)
        return;

    node *y = z, *t;
    char oc = y->c;

    if (z->l == nil) {
        t = z->r;
        trns(r, z, z->r);
    } else if (z->r == nil) {
        t = z->l;
        trns(r, z, z->l);
    } else {
        y = mnm(z->r);
        oc = y->c;
        t = y->r;

        if (y->prnt == z)
            t->prnt = y;
        else {
            trns(r, y, y->r);
            y->r = z->r;
            y->r->prnt = y;
        }

        trns(r, z, y);
        y->l = z->l;
        y->l->prnt = y;
        y->c = z->c;
    }

    free(z);

    if (oc == 'B')
        fixdel(r, t);
}

void ino(node *r)
{
    if (r == nil)
        return;
    ino(r->l);
    printf("%d(%c) ", r->d, r->c);
    ino(r->r);
}

void pre(node *r)
{
    if (r == nil)
        return;
    printf("%d(%c) ", r->d, r->c);
    pre(r->l);
    pre(r->r);
}

void post(node *r)
{
    if (r == nil)
        return;
    post(r->l);
    post(r->r);
    printf("%d(%c) ", r->d, r->c);
}

int sz(node *r)
{
    if (r == nil)
        return 0;
    return 1 + sz(r->l) + sz(r->r);
}

int ht(node *r)
{
    if (r == nil)
        return 0;
    return 1 + mx(ht(r->l), ht(r->r));
}

int comp(node *r, int i, int n)
{
    if (r == nil)
        return 1;
    if (i >= n)
        return 0;
    return comp(r->l, 2 * i + 1, n) && comp(r->r, 2 * i + 2, n);
}

int iscomp(node *r)
{
    return comp(r, 0, sz(r));
}

int dep(node *r)
{
    int d = 0;
    while (r != nil) {
        d++;
        r = r->l;
    }
    return d;
}

int perf(node *r, int d, int l)
{
    if (r == nil)
        return 1;

    if (r->l == nil && r->r == nil)
        return d == l + 1;

    if (r->l == nil || r->r == nil)
        return 0;

    return perf(r->l, d, l + 1) && perf(r->r, d, l + 1);
}

int isperf(node *r)
{
    return perf(r, dep(r), 0);
}

int main()
{
    init();

    int t;
    scanf("%d", &t);

    while (t--) {
        node *r = nil;
        int n;
        scanf("%d", &n);

        int ar[n];
        for (int i = 0; i < n; i++)
            scanf("%d", &ar[i]);

        for (int i = 0; i < n; i++) {
            ins(&r, ar[i]);
            if (i == n - 1)
                printf("Tree after inserting %d\n", ar[i]);
            else
                printf("Tree after inserting %d:\n", ar[i]);
            prt(r);
        }

        int ch;
        if (scanf("%d", &ch) != 1)
            continue;

        if (ch == 2) {
            int x;
            scanf("%d", &x);
            printf("Tree before deletion:\n");
            prt(r);
            del(&r, x);
            printf("Tree after deletion:\n");
            prt(r);
        } else if (ch == 3) {
            int x, ctr;
            scanf("%d", &x);
            node *ptr = srch(r, x, &ctr);
            if (ptr != nil)
                printf("Element found with %d comparisons\n", ctr);
            else
                printf("Element not found\n");
        } else if (ch == 4) {
            printf("Inorder Traversal: ");
            ino(r);
            printf("\n");
            printf("Preorder Traversal: ");
            pre(r);
            printf("\n");
            printf("Postorder Traversal: ");
            post(r);
            printf("\n");
        } else if (ch == 5) {
            printf("Size: %d\n", sz(r));
            printf("Height: %d\n", ht(r));
            printf("Complete Binary Tree: %s\n", iscomp(r) ? "Yes" : "No");
            printf("Perfect Binary Tree: %s\n", isperf(r) ? "Yes" : "No");
        }
    }

    return 0;
}