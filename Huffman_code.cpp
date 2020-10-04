//Huffman Coding for minimizing space requirement for disk server
#include<iostream>
#include<string>
#include<unordered_map>
#include<sstream>
#include<fstream>
#include<iomanip>
using namespace std;
int n;
unordered_map<char,string>umap; //Stores the character and its code
struct node //Node structure
{
    char a;
    int freq;
    struct node *left;
    struct node *right;

};
int parent(int i) //Returns parent index
{
    return ((i-1)/2);
}
struct node *buildNode(int num=0, char a=NULL)  //Constructs a node from a frequency and the character
{
    struct node *temp=(struct node *)malloc(sizeof(struct node));
    temp->a=a;
    temp->freq=num;
    temp->left=NULL;
    temp->right=NULL;
    return temp;

}
void heapify(struct node *root[], int i) //Heapify function to heapify a node(Min heap)
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
void buildHeap(struct node *root[]) //Builds a Min Heap
{
    int x=n/2 - 1;
    for(int i=x;i>=0;i--)
        heapify(root,i);
}
void heapInsert(struct node *root[],  struct node *p) //Inserts a node into the Min heap
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
struct node *extractMin(struct node *root[]) //Extracts/deletes a node from the Min Heap
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
void Huffman(struct node *root[]) //Huffman Code to construct the Huffman Tree
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

void printArr(int arr[], int n) //Printing the conents of an array
{ 
    int i; 
    for (i = 0; i < n; ++i) 
        cout<< arr[i]; 
  
    cout<<"\n"; 
} 
void printCodes(struct node *root, int arr[], int top)  //Traverses Huffman Tree to retrieve the codes and 
{                                                       //stores them in the unordered map umap
    if (root->left) { 
  
        arr[top] = 0; 
        printCodes(root->left, arr, top + 1); 
    } 
    if (root->right) { 
  
        arr[top] = 1; 
        printCodes(root->right, arr, top + 1); 
    } 

    if (root->left==NULL && root->right == NULL) { 
  
        cout<< root->a <<": "; 
        printArr(arr, top); 
        string str="";
        int size=sizeof(arr)/sizeof(arr[0]);
        for(int i=0;i<top;i++)
        {
            str+=to_string(arr[i]);
        }
        umap[root->a]=str;
    } 
} 
int leveloftree(struct node *root) //Returns level of tree
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

void currentlevel(struct node *root, int level) //Returns the current level of a tree
{	
	if (root!= NULL)
	{	
		if (level == 1)
		{
			cout<< root->freq<<" ";
		}
		
		else if (level > 1)
		{ 
			currentlevel(root->left, level-1); 
			currentlevel(root->right, level-1);
		}			
	}
}

void traverse_level(struct node* root)  //Level order traversal of a tree
{	
	int level = leveloftree(root);
	
        for(int i=1;i<=level;i++)
        {
		currentlevel(root,i);
        cout<<endl;
        }
}
void print_inorder(struct node *root) //Inorder traversal of a tree
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
    
    struct node *root[10000];
    
    //File Reading for Encoding
    fstream infile;
    unordered_map<char,int>store; //To store the characters and their respective frequencies
    infile.open("abc.txt",ios::in); //abc.txt has characters in any random order
    char chg;
    while(infile)
    {
        infile.get(chg);
        store[chg]=store[chg]+1;
    }
    int j=0;
    //Builds the array of structure variable swith the characters and the frequencies
    for(auto i=store.begin();i!=store.end();i++) 
    {
        root[j]=buildNode(i->second,i->first);
        j++;
    }
    n=j; //sets size to j
    //Prints each character with ts frequency
    for(int i=0;i<n;i++)
    {
        cout<<"Char = "<<root[i]->a<<" Freq = "<<root[i]->freq<<endl;
    }
    
    buildHeap(root);//Building the Min Heap
    Huffman(root);//Building the Huffman Tree
    int arr[100];
    cout<<"Inorder traversal "<<endl;
    print_inorder(root[0]);
    cout<<endl;
    cout<<"Level order traversal : "<<endl;
    traverse_level(root[0]);
    cout<<endl<<"Codes : "<<endl;
    printCodes(root[0],arr,0);//Prints the codes and stres them into the umap
    cout<<endl;

    //File Readig for decoding
    fstream infile1;
    infile1.open("bits.txt",ios::in); //bits.txt has the codes in any random order
    fstream outfile;
    outfile.open("decoded.txt",ios::app); //decoded.txt is the output file
    string str="";
    char x;
    while(infile1) //Reads the bits.txt
    {
        infile1>>x;
        str+=x;
        for(auto i=umap.begin();i!=umap.end();i++)
        {
            if(i->second == str) //If the string matches any code in the map, then it prints the corresponding
            {                    //character to the decoded.txt
                outfile<<i->first;
                str="";
                break;
            }
        }
    }
}