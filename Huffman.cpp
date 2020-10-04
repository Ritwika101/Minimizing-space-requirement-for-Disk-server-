//Huffman Coding for minimizing space requirement for disk server
#include<iostream>
#include<cmath>
using namespace std;
int n;
struct node
{
    char a;
    int freq;
    struct node *left;
    struct node *right;

};
int parent(int i)
{
    return ((i-1)/2);
}
struct node *buildNode(int num=0, char a=NULL)
{
    struct node *temp=(struct node *)malloc(sizeof(struct node));
    temp->a=a;
    temp->freq=num;
    temp->left=NULL;
    temp->right=NULL;
    return temp;

}
void heapify(struct node *root[], int i)
{
    int smallest=i;
    int l = 2*i +1;
    int r = 2*i +2;
    if(l<n && root[l]->freq<root[smallest]->freq)
        smallest=l;
    if(r<n && root[r]->freq<root[smallest]->freq)
        smallest=r;
    if(smallest!=i)
    {
        int c=root[i]->freq;
        char p=root[i]->a;
        struct node *t1=root[i];
        root[i]=root[smallest];
        root[smallest]=t1;
        heapify(root,smallest);
        
    }
     
}
void buildHeap(struct node *root[])
{
    
    int x=n/2 - 1;
    for(int i=x;i>=0;i--)
        heapify(root,i);
}
void heapInsert(struct node *root[],  struct node *p)
{
    n=n+1;
    int i=n-1;
    root[i]=buildNode();
    while(i>0 && root[parent(i)]->freq>(p->freq))
    {
        
        root[i]->a=root[parent(i)]->a;
        root[i]->freq=root[parent(i)]->freq;
        root[i]->left=root[parent(i)]->left;
        root[i]->right=root[parent(i)]->right;
        i=parent(i);
    }
    root[i]->freq=p->freq;
    root[i]->a=p->a;
    root[i]->left=p->left;
    root[i]->right=p->right;
}
struct node *extractMin(struct node *root[])
{
    int min=root[0]->freq;
    char c=root[0]->a;
    struct node *temp=(struct node *)malloc(sizeof(struct node));
    temp->freq=min;
    temp->a=c;
    temp->left=root[0]->left;
    temp->right=root[0]->right;
    root[0]=root[n-1];
    n--;
    heapify(root,0);
    return temp;
}
void Huffman(struct node *root[])
{
    cout<<endl<<"Min Heap : "<<endl;
    int n1=n-1;
    for(int i=0;i<n1;i++){
    struct node *z=buildNode();
    z->left=extractMin(root);
    z->right=extractMin(root);
    z->freq=z->left->freq+z->right->freq;
    heapInsert(root,z);
    for(int i=0;i<n;i++)
    {
        cout<<root[i]->freq<<"  ";
    }
    cout<<endl;}
}

void printArr(int arr[], int n) 
{ 
    int i; 
    for (i = 0; i < n; ++i) 
        cout<< arr[i]; 
    cout<<"\n"; 
} 
void Codes(struct node *root, int ar[], int top)  //To print the codes
{
    if (root->left) { 
  
        ar[top] = 0; 
        Codes(root->left, ar, top + 1); 
    } 
    if (root->right) { 
  
        ar[top] = 1; 
        Codes(root->right, ar, top + 1); 
    } 

    if (root->left==NULL && root->right == NULL) { 
  
        cout<< root->a <<": "; 
        printArr(ar, top); 
    } 
} 
int leveloftree(struct node *root)
{
	int max;
	if (root==NULL)
		return 0;
	else
	{
		int ltree = leveloftree(root->left);
		int rtree = leveloftree(root->right);
		if (ltree > rtree)
		{
			max = ltree + 1;
			return max;
		}
		else
		{
			max = rtree + 1;
			return max;
		}
	}
}

void currentlevel(struct node *root, int level)
{	
	if (root!= NULL)
	{	
		if (level == 1)
			cout<< root->freq<<" ";
		else if (level > 1)
		{ 
			currentlevel(root->left, level-1); 
			currentlevel(root->right, level-1);
		}			
	}
}

void traverse_level(struct node* root)
{	
	int level = leveloftree(root);
        for(int i=1;i<=level;i++)
        {
		currentlevel(root,i);
        cout<<endl;
        }
}
void print_inorder(struct node *root)
{
    if (root)
    {
        print_inorder(root->left);
        cout<<root->freq<<" ";
        print_inorder(root->right);
    }
}
int main()
{
    
    int f;
    cout<<"Enter the number of characters :";
    cin>>n;
    struct node *root[10000];
    char c;
    for(int i=0;i<n;i++)
    {
        cout<<"Enter character :";
        cin>>c;
        cout<<"Enter frequency :";  
        cin>>f;
        root[i]=buildNode(f,c);
    }
    cout<<endl<<"Inputs : "<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<"Char = "<<root[i]->a<<" Freq = "<<root[i]->freq<<endl;
    }
    buildHeap(root);
    Huffman(root);
    int ar[100];
    cout<<"Inorder traversal "<<endl;
    print_inorder(root[0]);
    cout<<endl;
    cout<<"Level order traversal : "<<endl;
    traverse_level(root[0]);
    cout<<endl<<"Codes : "<<endl;
    Codes(root[0],ar,0);
    cout<<endl;
    

}
