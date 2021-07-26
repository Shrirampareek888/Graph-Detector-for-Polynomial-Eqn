#include<stdio.h>
#include<stdlib.h>
#include<math.h>
struct node
{
    union{
        int expo;
        char var;
    }first;
    union{
        int coeff;
        struct node *down;
    }second;
    struct node *next;
};
struct node *accept(struct node *head)
{
    int z[6];
    int i,j,c;
    if(head==NULL)
    {
        struct node *new;
        new=(struct node *)malloc(sizeof(struct node));
        new->first.var = 'x';
        new->second.down=NULL;
        new->next=NULL;
        head=new;
    }
    for(i=2;i>=0;i--)
    {
        struct node *p,*head1=NULL,*q=head;
        while (q->next!=NULL)
            q=q->next;
        p=(struct node *)malloc(sizeof(struct node));
        p->first.expo=i;
        p->next=NULL;
        p->second.down=NULL;
        q->next=p;
        for(j=3-i;j>0;j--)
        {
            int a;
            if(head1==NULL)
            {
                struct node *new1;
                new1=(struct node *)malloc(sizeof(struct node));
                new1->first.var = 'y';
                new1->second.down=NULL;
                new1->next=NULL;
                p->second.down=new1;
                head1=new1;
            }
            struct node *l,*t=head1;
            while (t->next !=NULL)
                t=t->next;
            l=(struct node *)malloc(sizeof(struct node));
            l->first.expo=j-1;
            l->next=NULL;
            t->next=l;
            printf("Enter value of coefficient for the term x^%dy^%d : ",i,j-1);
            scanf("%d",&a);
            l->second.coeff=a;
        }
    }
    return(head);
}
void display(struct node *head)
{
    int i,j;
    struct node *t;
    t = head;
    printf("\n");
    for(i=0;i<20;i++)
    {
        printf("======");
    }
    printf("\nQuadratic equation is : ");
    int r=0;
    for(i=2;i>=0;i--)
    {
        t=t->next;
        struct node *p;
        p=t->second.down;

        for(j=3-i;j>0;j--)
        {

            p=p->next;
            printf("%dx^%dy^%d",p->second.coeff,t->first.expo,p->first.expo);
            if(r<5)
            {
                printf(" + ");
                r++;
            }
        }
    }
    printf(" = 0");
    printf("\n");

}
void detect (struct node *head)
{
    int i,j,res,res1;
    struct node *t;
    t = head;
    int a[6];
    int k=0;
    for(i=2;i>=0;i--)
    {
        t=t->next;
        struct node *p;
        p=t->second.down;
        for(j=3-i;j>0;j--)
        {
            p=p->next;
            a[k]=p->second.coeff;
            k++;
        }
    }
    res=a[0]*a[3]*a[5]+a[4]*a[3]*a[1]-a[0]*a[4]*a[4]-a[3]*a[2]*a[2]-(a[5]*a[1]*a[1])/4;
    res1=a[1]*a[1]/4-a[0]*a[3];
    if(res==0)
    {
        if(res1>0)
            printf("\n\nIt's an equation of pair of 2 DISTINCT REAL LINES \n");
        else if(res1==0)
            printf("\n\nIt's an equation of pair of 2 PARALLEL LINES \n");
        else
            printf("\n\nIt's an equation of 2 NON REAL LINES \n");
    }
    else
    {
        if(res1>0)
            printf("\n\nIt's an equation of HYPERBOLA \n");
        else if(res1==0)
            printf("\n\nIt's an equation of PARABOLA \n");
        else
        {
            if(a[0]==a[3])
                printf("\n\nIt's an equation of CIRCLE\n");
            else
                printf("\n\nIt's an equation of ELLIPSE\n");
        }
    }
}
struct node *delete(struct node *head,int m,int n)
{
    int i,j;
    struct node *t;
    t = head;
    for(i=0;i<3-m;i++)
    {
        t=t->next;;
    }
    t=t->second.down;
    for(j=0;j<3-m-n;j++)
    {
        t=t->next;
    }
    t->second.coeff=0;
    return (head);
};
int main()
{

    int i,y,k;
    for(i=0;i<20;i++)
    {
        printf("======");
    }
    printf("\n\t\t\t\t\tApplication of Multivariable Polynomial using GLL\n\n");
    for(i=0;i<20;i++)
    {
        printf("======");
    }
    printf("\n");
    printf("--> INSTRUCTIONS <--\n\n");
    printf("1) This program will tell the type of graph from the input given by the user\n\n");
    printf("2) The General equation is of the type: ax^2 + bxy + cy^2 + dx + ey + f\n\n");
    printf("3) Enter the coefficient corresponding to given terms\n\n");
    struct node *head = NULL;
    do
    {
        for(i=0;i<20;i++)
    {
        printf("======");
    }
    printf("\n");
    struct node *head = NULL;
    head = accept(head);
    display(head);
    detect(head);
    printf("\nEnter 0 to EXIT and 1 to delete a node: ");
    scanf("%d",&y);
    while(y==1)
    {
        if(y==1)
        {
            int m,n;
            printf("\nEnter the exponent of 'X' of the node that you want to delete : ");
            scanf("\t%d",&m);
            printf("\nEnter the exponent of 'y' of the node that you want to delete : ");
            scanf("\t%d",&n);
            head=delete(head,m,n);
            display(head);
            detect(head);
            printf("Enter 0 to exit or 1 to delete other node : ");
            scanf("%d",&k);
            y=k;
        }
    }
    }while(y!=0);
    return 0;
}
