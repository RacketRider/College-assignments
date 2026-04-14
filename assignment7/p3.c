#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Abhijit Prasad Mallick
Roll No: 20252501001
*/

char rotmessage[256] = "";

typedef struct avl_node {
    int data;
    int height;
    struct avl_node *lchild, *rchild;
} avl_node;

int maxm(int a, int b) {
    return (a > b) ? a : b;
}

int gtheight(avl_node *nodeptr) {
    if (nodeptr == NULL)
        return 0;
    return nodeptr->height;
}

avl_node* cnode(int val) {
    avl_node *nnode = (avl_node*)malloc(sizeof(avl_node));
    nnode->data = val;
    nnode->height = 1;
    nnode->lchild = NULL;
    nnode->rchild = NULL;
    return nnode;
}

int gtbalance(avl_node *nodeptr) {
    if (nodeptr == NULL)
        return 0;
    return gtheight(nodeptr->lchild) - gtheight(nodeptr->rchild);
}

avl_node* rrotate(avl_node *y) {
    avl_node *x = y->lchild;
    avl_node *temp = x->rchild;

    x->rchild = y;
    y->lchild = temp;

    y->height = maxm(gtheight(y->lchild), gtheight(y->rchild)) + 1;
    x->height = maxm(gtheight(x->lchild), gtheight(x->rchild)) + 1;

    return x;
}

avl_node* lrotate(avl_node *x) {
    avl_node *y = x->rchild;
    avl_node *temp = y->lchild;

    y->lchild = x;
    x->rchild = temp;

    x->height = maxm(gtheight(x->lchild), gtheight(x->rchild)) + 1;
    y->height = maxm(gtheight(y->lchild), gtheight(y->rchild)) + 1;

    return y;
}

avl_node* innode(avl_node *rt, int val) {
    strcpy(rotmessage, "");

    if (rt == NULL)
        return cnode(val);

    if (val < rt->data)
        rt->lchild = innode(rt->lchild, val);
    else if (val > rt->data)
        rt->rchild = innode(rt->rchild, val);
    else
        return rt;

    rt->height = 1 + maxm(gtheight(rt->lchild), gtheight(rt->rchild));

    int balance_factor = gtbalance(rt);

    if (balance_factor > 1 && val < rt->lchild->data) {
        sprintf(rotmessage, "Unbalanced at %d: LL Case -->Right Rotation\n", rt->data);
        return rrotate(rt);
    }

    if (balance_factor < -1 && val > rt->rchild->data) {
        sprintf(rotmessage, "Unbalanced at %d: RR Case -->Left Rotation\n", rt->data);
        return lrotate(rt);
    }

    if (balance_factor > 1 && val > rt->lchild->data) {
        sprintf(rotmessage, "Unbalanced at %d: LR Case -->Left-Right Rotation\n", rt->data);
        rt->lchild = lrotate(rt->lchild);
        return rrotate(rt);
    }

    if (balance_factor < -1 && val < rt->rchild->data) {
        sprintf(rotmessage, "Unbalanced at %d: RL Case -->Right-Left Rotation\n", rt->data);
        rt->rchild = rrotate(rt->rchild);
        return lrotate(rt);
    }

    return rt;
}

avl_node* minm(avl_node *rt) {
    while (rt->lchild != NULL)
        rt = rt->lchild;
    return rt;
}

avl_node* dnode(avl_node *rt, int val) {
    if (rt == NULL)
        return rt;

    if (val < rt->data) {
        rt->lchild = dnode(rt->lchild, val);
    } else if (val > rt->data) {
        rt->rchild = dnode(rt->rchild, val);
    } else {
        if (rt->lchild == NULL) {
            avl_node *temp = rt->rchild;
            free(rt);
            return temp;
        } else if (rt->rchild == NULL) {
            avl_node *temp = rt->lchild;
            free(rt);
            return temp;
        }

        avl_node *temp = minm(rt->rchild);
        rt->data = temp->data;
        rt->rchild = dnode(rt->rchild, temp->data);
    }

    if (rt == NULL)
        return rt;

    rt->height = 1 + maxm(gtheight(rt->lchild), gtheight(rt->rchild));
    int balance_factor = gtbalance(rt);

    if (balance_factor > 1 && gtbalance(rt->lchild) >= 0) {
        sprintf(rotmessage, "Unbalanced at %d: LL Case -->Right Rotation\n", rt->data);
        return rrotate(rt);
    }

    if (balance_factor > 1 && gtbalance(rt->lchild) < 0) {
        sprintf(rotmessage, "Unbalanced at %d: LR Case -->Left-Right Rotation\n", rt->data);
        rt->lchild = lrotate(rt->lchild);
        return rrotate(rt);
    }

    if (balance_factor < -1 && gtbalance(rt->rchild) <= 0) {
        sprintf(rotmessage, "Unbalanced at %d: RR Case -->Left Rotation\n", rt->data);
        return lrotate(rt);
    }

    if (balance_factor < -1 && gtbalance(rt->rchild) > 0) {
        sprintf(rotmessage, "Unbalanced at %d: RL Case -->Right-Left Rotation\n", rt->data);
        rt->rchild = rrotate(rt->rchild);
        return lrotate(rt);
    }

    return rt;
}

int snode(avl_node *rt, int val, int *comp) {
    if (rt == NULL)
        return 0;

    (*comp)++;

    if (val == rt->data)
        return 1;
    if (val < rt->data)
        return snode(rt->lchild, val, comp);
    return snode(rt->rchild, val, comp);
}

void intrav(avl_node *rt, int *fst) {
    if (rt != NULL) {
        intrav(rt->lchild, fst);
        if (*fst)
            *fst = 0;
        else
            printf(" ");
        printf("%d (BF: %d)", rt->data, gtbalance(rt));
        intrav(rt->rchild, fst);
    }
}

void pretrav(avl_node *rt, int *fst) {
    if (rt != NULL) {
        if (*fst)
            *fst = 0;
        else
            printf(" ");
        printf("%d (BF: %d)", rt->data, gtbalance(rt));
        pretrav(rt->lchild, fst);
        pretrav(rt->rchild, fst);
    }
}

void potrav(avl_node *rt, int *fst) {
    if (rt != NULL) {
        potrav(rt->lchild, fst);
        potrav(rt->rchild, fst);
        if (*fst)
            *fst = 0;
        else
            printf(" ");
        printf("%d (BF: %d)", rt->data, gtbalance(rt));
    }
}

int tree_height(avl_node *rt) {
    if (rt == NULL)
        return 0;
    int left_h = tree_height(rt->lchild);
    int right_h = tree_height(rt->rchild);
    return maxm(left_h, right_h) + 1;
}

typedef struct {
    int val;
    int position;
} DisplayNode;

void collect_nodes(avl_node *nodeptr, int current_level, int target_level, int position, int spacing, DisplayNode *nodes, int *ctr) {
    if (nodeptr == NULL)
        return;

    if (current_level == target_level) {
        nodes[*ctr].val = nodeptr->data;
        nodes[*ctr].position = position;
        (*ctr)++;
    } else if (current_level < target_level) {
        collect_nodes(nodeptr->lchild, current_level + 1, target_level, position - spacing, spacing / 2, nodes, ctr);
        collect_nodes(nodeptr->rchild, current_level + 1, target_level, position + spacing, spacing / 2, nodes, ctr);
    }
}

void display_level(avl_node *rt, int level) {
    if (rt == NULL)
        return;

    DisplayNode nodes[100];
    int ctr = 0;

    collect_nodes(rt, 1, level, 40, 20, nodes, &ctr);

    if (ctr == 0)
        return;

    for (int i = 0; i < ctr - 1; i++) {
        for (int j = 0; j < ctr - 1 - i; j++) {
            if (nodes[j].position > nodes[j + 1].position) {
                DisplayNode temp = nodes[j];
                nodes[j] = nodes[j + 1];
                nodes[j + 1] = temp;
            }
        }
    }

    int current_pos = 0;
    for (int i = 0; i < ctr; i++) {
        int spaces = nodes[i].position - current_pos;
        for (int j = 0; j < spaces; j++)
            printf(" ");
        printf("%d", nodes[i].val);
        current_pos = nodes[i].position + 1;
    }
    printf("\n");
}

void display_tree(avl_node *rt) {
    if (rt == NULL)
        return;

    int height = tree_height(rt);

    for (int level = 1; level <= height; level++) {
        display_level(rt, level);
        printf("\n");
    }
}

int main() {
    avl_node *rt = NULL;
    int opt, ctr, val, skey, comp;

    scanf("%d", &opt);

    if (opt == 1) {
        scanf("%d", &ctr);

        for (int i = 0; i < ctr; i++) {
            scanf("%d", &val);
            rt = innode(rt, val);

            printf("Tree after inserting %d:\n", val);
            if (strlen(rotmessage) > 0) {
                printf("%s", rotmessage);
            }
            display_tree(rt);
        }

        printf("Inorder: ");
        int fst = 1;
        intrav(rt, &fst);
        printf("\n");

        printf("Preorder: ");
        fst = 1;
        pretrav(rt, &fst);
        printf("\n");

        printf("Postorder: ");
        fst = 1;
        potrav(rt, &fst);
        printf("\n");
    }

    if (scanf("%d", &opt) == 1) {
        if (opt == 3) {
            scanf("%d", &skey);
            comp = 0;

            if (snode(rt, skey, &comp))
                printf("Key %d found after %d comparisons.\n", skey, comp);
            else
                printf("Key %d not found.\n", skey);
        } else if (opt == 2) {
            scanf("%d", &val);
            strcpy(rotmessage, "");

            rt = dnode(rt, val);

            if (strlen(rotmessage) > 0) {
                printf("%s", rotmessage);
            }

            printf("Tree after deleting %d:\n", val);
            display_tree(rt);
        }
    }

    return 0;
}