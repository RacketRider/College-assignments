#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*
Abhijit Prasad Mallick 
Roll No: 20252501001
*/
struct node
{
    int data;
    struct node *left;
    struct node *right;
};

struct node *root=NULL;
struct node* crtnode(int val)
{
    struct node *nnode=(struct node*)malloc(sizeof(struct node));
    nnode->data=val;
    nnode->left=NULL;
    nnode->right=NULL;
    return nnode;
}

struct node* innode(struct node *root,int val)
{
    if(root==NULL)
        return crtnode(val);

    if(val<root->data)
        root->left=innode(root->left,val);
    else if(val>root->data)
        root->right=innode(root->right,val);

    return root;
}

void inorder(struct node *root)
{
    if(root!=NULL)
    {
        inorder(root->left);
        printf("%d ",root->data);
        inorder(root->right);
    }
}

void preorder(struct node *root)
{
    if(root!=NULL)
    {
        printf("%d ",root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct node *root)
{
    if(root!=NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%d ",root->data);
    }
}

int size(struct node *root)
{
    if(root==NULL)
        return 0;
    return 1+size(root->left)+size(root->right);
}

int height(struct node *root)
{
    int lh,rh;
    if(root==NULL)
        return -1;

    lh=height(root->left);
    rh=height(root->right);

    if(lh>rh)
        return lh+1;
    else
        return rh+1;
}

int isComplete(struct node *root,int index,int total)
{
    if(root==NULL)
        return 1;

    if(index>=total)
        return 0;

    return isComplete(root->left,2*index+1,total) &&
           isComplete(root->right,2*index+2,total);
}

int leftDepth(struct node *root)
{
    int d=0;
    while(root!=NULL)
    {
        d++;
        root=root->left;
    }
    return d;
}

int isPerfect(struct node *root,int depth,int level)
{
    if(root==NULL)
        return 1;

    if(root->left==NULL && root->right==NULL)
        return (depth==level+1);

    if(root->left==NULL || root->right==NULL)
        return 0;

    return isPerfect(root->left,depth,level+1) &&
           isPerfect(root->right,depth,level+1);
}

void displayStats()
{
    printf("Size of BST: %d\n",size(root));
    printf("Height of BST: %d\n",height(root));
    printf("Complete Binary Tree: %s\n",isComplete(root,0,size(root)) ? "Yes" : "No");
    printf("Perfect Binary Tree: %s\n",isPerfect(root,leftDepth(root),0) ? "Yes" : "No");
}

void insertMultiple()
{
    int n,val,cnt=0;
    char line[1000];
    char *token;

    scanf("%d",&n);
    getchar();

    if(fgets(line,sizeof(line),stdin)==NULL)
        return;

    token=strtok(line," \n");
    while(token!=NULL)
    {
        val=atoi(token);
        root=innode(root,val);
        cnt++;
        token=strtok(NULL," \n");
    }

    if(cnt==n)
    {
        printf("Inorder Traversal: ");
        inorder(root);
        printf("\n");

        printf("Preorder Traversal: ");
        preorder(root);
        printf("\n");

        printf("Postorder Traversal: ");
        postorder(root);
        printf("\n");

        printf("Size of BST: %d\n",size(root));
        printf("Height of BST: %d\n",height(root));
        printf("Complete Binary Tree: %s\n",isComplete(root,0,size(root)) ? "Yes" : "No");
        printf("Perfect Binary Tree: %s\n",isPerfect(root,leftDepth(root),0) ? "Yes" : "No");
    }
}

void searchNode()
{
    int key,cmp=0;
    struct node *temp=root;

    scanf("%d",&key);

    while(temp!=NULL)
    {
        cmp++;
        if(temp->data==key)
        {
            printf("Value %d found in BST after %d comparisons.\n",key,cmp);
            return;
        }
        else if(key<temp->data)
            temp=temp->left;
        else
            temp=temp->right;
    }

    printf("Value %d not found in BST after %d comparisons.\n",key,cmp);
}

struct node* minValueNode(struct node *temp)
{
    struct node *current=temp;
    while(current!=NULL && current->left!=NULL)
        current=current->left;
    return current;
}

struct node* deleteNode(struct node *root,int val)
{
    if(root==NULL)
        return root;

    if(val<root->data)
        root->left=deleteNode(root->left,val);
    else if(val>root->data)
        root->right=deleteNode(root->right,val);
    else
    {
        if(root->left==NULL)
        {
            struct node *temp=root->right;
            free(root);
            return temp;
        }
        else if(root->right==NULL)
        {
            struct node *temp=root->left;
            free(root);
            return temp;
        }
        else
        {
            struct node *temp=minValueNode(root->right);
            root->data=temp->data;
            root->right=deleteNode(root->right,temp->data);
        }
    }
    return root;
}

void deletion()
{
    int val;
    scanf("%d",&val);

    printf("BST before deletion (Inorder): ");
    inorder(root);
    printf("\n");

    root=deleteNode(root,val);

    printf("BST after deletion (Inorder): ");
    inorder(root);
    printf("\n");
}

int main()
{
    int ch;

    while(scanf("%d",&ch)==1)
    {
        switch(ch)
        {
            case 1:
                insertMultiple();
                break;

            case 2:
                searchNode();
                break;

            case 3:
                deletion();
                break;

            case 4:
                printf("Inorder Traversal: ");
                inorder(root);
                printf("\n");
                break;

            case 5:
                printf("Preorder Traversal: ");
                preorder(root);
                printf("\n");
                break;

            case 6:
                printf("Postorder Traversal: ");
                postorder(root);
                printf("\n");
                break;

            case 7:
                displayStats();
                break;

            case 8:
                return 0;
        }
    }

    return 0;
}