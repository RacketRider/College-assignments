#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
Abhijit Prasad Mallick
20252501001
*/
typedef struct node
{
    int n, leaf;
    int ar[3];
    struct node *ptr[4];
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

void srt3(int *a, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (a[i] > a[j]) {
                int t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
}

void prtkey(node *r)
{
    printf("[");
    for (int i = 0; i < r->n; i++) {
        printf("%d", r->ar[i]);
        if (i < r->n - 1)
            printf(",");
    }
    printf("]");
}

int pos(node *r, int x)
{
    int i = 0;
    while (i < r->n && x > r->ar[i])
        i++;
    return i;
}

int ins(node *r, int x, int *up, node **nr)
{
    int p = pos(r, x);

    if (r->leaf) {
        if (r->n == 1) {
            if (x < r->ar[0]) {
                r->ar[1] = r->ar[0];
                r->ar[0] = x;
            } else
                r->ar[1] = x;
            r->n = 2;
            return 0;
        } else {
            int t[3] = {r->ar[0], r->ar[1], x};
            srt3(t, 3);

            r->ar[0] = t[0];
            r->n = 1;

            *up = t[1];
            *nr = nw(1);
            (*nr)->ar[0] = t[2];
            (*nr)->n = 1;
            return 1;
        }
    }

    int k;
    node *c = NULL;
    int sp = ins(r->ptr[p], x, &k, &c);

    if (!sp)
        return 0;

    if (r->n == 1) {
        if (p == 0) {
            r->ar[1] = r->ar[0];
            r->ar[0] = k;
            r->ptr[2] = r->ptr[1];
            r->ptr[1] = c;
        } else {
            r->ar[1] = k;
            r->ptr[2] = c;
        }
        r->n = 2;
        return 0;
    } else {
        int t[3], j = 0;
        node *ch[4];

        if (p == 0) {
            t[0] = k; t[1] = r->ar[0]; t[2] = r->ar[1];
            ch[0] = r->ptr[0]; ch[1] = c; ch[2] = r->ptr[1]; ch[3] = r->ptr[2];
        } else if (p == 1) {
            t[0] = r->ar[0]; t[1] = k; t[2] = r->ar[1];
            ch[0] = r->ptr[0]; ch[1] = r->ptr[1]; ch[2] = c; ch[3] = r->ptr[2];
        } else {
            t[0] = r->ar[0]; t[1] = r->ar[1]; t[2] = k;
            ch[0] = r->ptr[0]; ch[1] = r->ptr[1]; ch[2] = r->ptr[2]; ch[3] = c;
        }

        r->ar[0] = t[0];
        r->n = 1;
        r->ptr[0] = ch[0];
        r->ptr[1] = ch[1];
        r->ptr[2] = NULL;

        *up = t[1];
        *nr = nw(0);
        (*nr)->ar[0] = t[2];
        (*nr)->n = 1;
        (*nr)->ptr[0] = ch[2];
        (*nr)->ptr[1] = ch[3];

        return 1;
    }
}

void add(node **r, int x)
{
    if (!(*r)) {
        *r = nw(1);
        (*r)->ar[0] = x;
        (*r)->n = 1;
        return;
    }

    int k;
    node *nr = NULL;
    int sp = ins(*r, x, &k, &nr);

    if (sp) {
        node *t = nw(0);
        t->ar[0] = k;
        t->n = 1;
        t->ptr[0] = *r;
        t->ptr[1] = nr;
        *r = t;
    }
}

int pred(node *r)
{
    while (!r->leaf)
        r = r->ptr[r->n];
    return r->ar[r->n - 1];
}

void borrowl(node *r, int i)
{
    node *c = r->ptr[i];
    node *s = r->ptr[i - 1];

    for (int j = c->n; j > 0; j--)
        c->ar[j] = c->ar[j - 1];

    if (!c->leaf)
        for (int j = c->n + 1; j > 0; j--)
            c->ptr[j] = c->ptr[j - 1];

    c->ar[0] = r->ar[i - 1];
    if (!c->leaf)
        c->ptr[0] = s->ptr[s->n];

    r->ar[i - 1] = s->ar[s->n - 1];
    s->n--;
    c->n++;
}

void borrowr(node *r, int i)
{
    node *c = r->ptr[i];
    node *s = r->ptr[i + 1];

    c->ar[c->n] = r->ar[i];
    if (!c->leaf)
        c->ptr[c->n + 1] = s->ptr[0];

    r->ar[i] = s->ar[0];

    for (int j = 1; j < s->n; j++)
        s->ar[j - 1] = s->ar[j];

    if (!s->leaf)
        for (int j = 1; j <= s->n; j++)
            s->ptr[j - 1] = s->ptr[j];

    s->n--;
    c->n++;
}

void merge(node *r, int i)
{
    node *a = r->ptr[i];
    node *b = r->ptr[i + 1];

    a->ar[1] = r->ar[i];
    a->n = 2;

    if (b->n == 1) {
        a->ar[2] = b->ar[0];
        a->n = 3;
    }

    if (!a->leaf) {
        a->ptr[2] = b->ptr[0];
        a->ptr[3] = b->ptr[1];
        if (b->n == 2) {
            a->ptr[4 - 1] = b->ptr[2];
            a->ar[2] = b->ar[0];
            a->n = 3;
        }
    }

    for (int j = i + 1; j < r->n; j++)
        r->ar[j - 1] = r->ar[j];

    for (int j = i + 2; j <= r->n; j++)
        r->ptr[j - 1] = r->ptr[j];

    r->n--;
    free(b);
}

void fix(node *r, int i)
{
    if (i > 0 && r->ptr[i - 1]->n == 2)
        borrowl(r, i);
    else if (i < r->n && r->ptr[i + 1]->n == 2)
        borrowr(r, i);
    else {
        if (i < r->n)
            merge(r, i);
        else
            merge(r, i - 1);
    }
}

void del(node *r, int x)
{
    int i = pos(r, x);

    if (r->leaf) {
        if (i < r->n && r->ar[i] == x) {
            for (int j = i + 1; j < r->n; j++)
                r->ar[j - 1] = r->ar[j];
            r->n--;
        }
        return;
    }

    if (i < r->n && r->ar[i] == x) {
        int p = pred(r->ptr[i]);
        r->ar[i] = p;
        del(r->ptr[i], p);
        if (r->ptr[i]->n == 0)
            fix(r, i);
    } else {
        del(r->ptr[i], x);
        if (r->ptr[i]->n == 0)
            fix(r, i);
    }
}

void inorder(node *r)
{
    if (!r)
        return;

    if (r->leaf) {
        for (int i = 0; i < r->n; i++) {
            printf("%d", r->ar[i]);
            if (i < r->n - 1)
                printf(" ");
        }
        return;
    }

    if (r->n == 1) {
        inorder(r->ptr[0]);
        printf(" %d ", r->ar[0]);
        inorder(r->ptr[1]);
    } else {
        inorder(r->ptr[0]);
        printf(" %d ", r->ar[0]);
        inorder(r->ptr[1]);
        printf(" %d ", r->ar[1]);
        inorder(r->ptr[2]);
    }
}

void prt(node *r)
{
    if (!r)
        return;

    if (r->leaf) {
        printf("    ");
        prtkey(r);
        printf("\n");
        return;
    }

    printf("        ");
    prtkey(r);
    printf("\n");
    printf("        /              \\\n\n");
    printf("    ");

    for (int i = 0; i <= r->n; i++) {
        prtkey(r->ptr[i]);
        if (i < r->n)
            printf("        ");
    }
    printf("\n");
}

int main()
{
    int t;
    scanf("%d", &t);

    while (t--) {
        node *r = NULL;


        int n;
        scanf("%d", &n);     
        { int c; while ((c = getchar()) != EOF && c != '\n'); }

        char line[4096];
        int ins_vals[1000], ins_n = 0;
        if (fgets(line, sizeof(line), stdin)) {
            char *p = line;
            while (*p) {
                while (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n') p++;
                if (*p == '\0') break;
                ins_vals[ins_n++] = (int)strtol(p, &p, 10);
            }
        }

        int del_val = -1, has_del = 0;
        int ch;
        if (scanf("%d", &ch) == 1) {
            if (ch == 2) {
                int x;
                if (scanf("%d", &x) == 1) {
                    del_val = x;
                    has_del = 1;
                }
            }
        }

        for (int i = 0; i < ins_n; i++) {
            add(&r, ins_vals[i]);

            int is_last = (i == ins_n - 1);

            if (is_last && has_del) {
                printf("Tree structure:\n");
                prt(r);
                printf("\n\nInorder: ");
                inorder(r);
                printf("\n\n");
            } else {
                printf("--- After inserting %d ---\n", ins_vals[i]);
                printf("Tree structure:\n");
                prt(r);
                printf("\n\nInorder: ");
                inorder(r);
                printf("\n\n");
            }
        }

        if (has_del) {
            del(r, del_val);
            if (r && r->n == 0) {
                node *tmp = r;
                r = r->leaf ? NULL : r->ptr[0];
                free(tmp);
            }
            printf("--- After deletion ---\n");
            prt(r);
            printf("\n\n");
        }
    }

    return 0;
}