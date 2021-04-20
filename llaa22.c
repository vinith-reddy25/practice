#include<stdio.h> 
#include<stdlib.h> 
#include<ctype.h>
#include<string.h>

char cc;

struct node 
{ 
	int key; 
	struct node *left, *right;
	 int height; 
}; 

void inorder(struct node *root) 
{ 
	if (root != NULL) 
	{ 
		inorder(root->left); 
		printf("%d ", root->key); 
		inorder(root->right); 
	} 
}

// A utility function to get maximum of two integers 
int max(int a, int b); 

// A utility function to get height of the tree 
int height(struct node *N) 
{ 
	if (N == NULL) 
		return 0; 
	return N->height; 
} 

// A utility function to get maximum of two integers 
int max(int a, int b) 
{ 
	return (a > b)? a : b; 
} 

/* Helper function that allocates a new node with the given key and 
	NULL left and right pointers. */
struct node* newNode(int key) 
{ 
	struct node* node = (struct node*) 
						malloc(sizeof(struct node)); 
	node->key = key; 
	node->left = NULL; 
	node->right = NULL; 
	node->height = 1; // new node is initially added at leaf 
	return(node); 
} 

// A utility function to right rotate subtree rooted with y 
// See the diagram given above. 
struct node *rightRotate(struct node *y) 
{ 
	struct node *x = y->left; 
	struct node *T2 = x->right; 

	// Perform rotation 
	x->right = y; 
	y->left = T2; 

	// Update heights 
	y->height = max(height(y->left), height(y->right))+1; 
	x->height = max(height(x->left), height(x->right))+1; 

	// Return new root 
	return x; 
} 

// A utility function to left rotate subtree rooted with x 
// See the diagram given above. 
struct node *leftRotate(struct node *x) 
{ 
	struct node *y = x->right; 
	struct node *T2 = y->left; 

	// Perform rotation 
	y->left = x; 
	x->right = T2; 

	// Update heights 
	x->height = max(height(x->left), height(x->right))+1; 
	y->height = max(height(y->left), height(y->right))+1; 

	// Return new root 
	return y; 
} 

// Get Balance factor of node N 
int getBalance(struct node *N) 
{ 
	if (N == NULL) 
		return 0; 
	return height(N->left) - height(N->right); 
} 

struct node* insertr(struct node* node, int key) 
{ 
	/* 1. Perform the normal BST rotation */
	if (node == NULL) 
		return(newNode(key)); 

	if (key <= node->key) 
		node->left = insertr(node->left, key); 
	else if (key > node->key) 
		node->right = insertr(node->right, key); 
	else // Equal keys not allowed 
		return node; 

	/* 2. Update height of this ancestor node */
	node->height = 1 + max(height(node->left), 
						height(node->right)); 

	/* 3. Get the balance factor of this ancestor 
		node to check whether this node became 
		unbalanced */
	int balance = getBalance(node); 

	// If this node becomes unbalanced, then there are 4 cases 

	// Left Left Case 
	if (balance > 1 && key < node->left->key) 
		return rightRotate(node); 

	// Right Right Case 
	if (balance < -1 && key > node->right->key) 
		return leftRotate(node); 

	// Left Right Case 
	if (balance > 1 && key > node->left->key) 
	{ 
		node->left = leftRotate(node->left); 
		return rightRotate(node); 
	} 

	// Right Left Case 
	if (balance < -1 && key < node->right->key) 
	{ 
		node->right = rightRotate(node->right); 
		return leftRotate(node); 
	} 

	/* return the (unchanged) node pointer */
	return node; 
} 

/* Given a non-empty binary search tree, return the 
node with minimum key value found in that tree. 
Note that the entire tree does not need to be 
searched. */
struct node * minValueNode(struct node* node) 
{ 
	struct node* current = node; 

	/* loop down to find the leftmost leaf */
	while (current->left != NULL) 
		current = current->left; 

	return current; 
} 

// Recursive function to delete a node with given key 
// from subtree with given root. It returns root of 
// the modified subtree. 
struct node* deleteNoder(struct node* root, int key) 
{ 
	// STEP 1: PERFORM STANDARD BST DELETE 

	if (root == NULL) 
		return root; 

	// If the key to be deleted is smaller than the 
	// root's key, then it lies in left subtree 
	if ( key < root->key ) 
		root->left = deleteNoder(root->left, key); 

	// If the key to be deleted is greater than the 
	// root's key, then it lies in right subtree 
	else if( key > root->key ) 
		root->right = deleteNoder(root->right, key); 

	// if key is same as root's key, then This is 
	// the node to be deleted 
	else
	{ 
		// node with only one child or no child 
		if( (root->left == NULL) || (root->right == NULL) ) 
		{ 
			struct node *temp = root->left ? root->left : 
											root->right; 

			// No child case 
			if (temp == NULL) 
			{ 
				temp = root; 
				root = NULL; 
			} 
			else // One child case 
			*root = *temp; // Copy the contents of 
							// the non-empty child 
			free(temp); 
		} 
		else
		{ 
			// node with two children: Get the inorder 
			// successor (smallest in the right subtree) 
			struct node* temp = minValueNode(root->right); 

			// Copy the inorder successor's data to this node 
			root->key = temp->key; 

			// Delete the inorder successor 
			root->right = deleteNoder(root->right, temp->key); 
		} 
	} 

	// If the tree had only one node then return 
	if (root == NULL) 
	return root; 

	// STEP 2: UPDATE HEIGHT OF THE CURRENT NODE 
	root->height = 1 + max(height(root->left), 
						height(root->right)); 

	// STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to 
	// check whether this node became unbalanced) 
	int balance = getBalance(root); 

	// If this node becomes unbalanced, then there are 4 cases 

	// Left Left Case 
	if (balance > 1 && getBalance(root->left) >= 0) 
		return rightRotate(root); 

	// Left Right Case 
	if (balance > 1 && getBalance(root->left) < 0) 
	{ 
		root->left = leftRotate(root->left); 
		return rightRotate(root); 
	} 

	// Right Right Case 
	if (balance < -1 && getBalance(root->right) <= 0) 
		return leftRotate(root); 

	// Right Left Case 
	if (balance < -1 && getBalance(root->right) > 0) 
	{ 
		root->right = rightRotate(root->right); 
		return leftRotate(root); 
	} 

	return root; 
} 


int a=0;
// A utility function to create a new BST node 

// A utility function to do inorder traversal of BST 
 

/* A utility function to insert a new node with given key in BST */
struct node* insert(struct node* node, int key) 
{ 
	/* If the tree is empty, return a new node */
	if (node == NULL) return newNode(key); 

	/* Otherwise, recur down the tree */
	if (key <= node->key) 
		node->left = insert(node->left, key); 
	else
		node->right = insert(node->right, key); 

	/* return the (unchanged) node pointer */
	return node; 
} 

/* Given a non-empty binary search tree, return the node with minimum 
key value found in that tree. Note that the entire tree does not 
need to be searched. */


/* Given a binary search tree and a key, this function deletes the key 
and returns the new root */
struct node* deleteNode(struct node* root, int key) 
{ 
	// base case 
	if (root == NULL) return root; 

	// If the key to be deleted is smaller than the root's key, 
	// then it lies in left subtree 
	if (key < root->key) 
		root->left = deleteNode(root->left, key); 

	// If the key to be deleted is greater than the root's key, 
	// then it lies in right subtree 
	else if (key > root->key) 
		root->right = deleteNode(root->right, key); 

	// if key is same as root's key, then This is the node 
	// to be deleted 
	else
	{ 
		// node with only one child or no child 
		if (root->left == NULL) 
		{ 
			struct node *temp = root->right; 
			free(root); 
			return temp; 
		} 
		else if (root->right == NULL) 
		{ 
			struct node *temp = root->left; 
			free(root); 
			return temp; 
		} 

		// node with two children: Get the inorder successor (smallest 
		// in the right subtree) 
		struct node* temp = minValueNode(root->right); 

		// Copy the inorder successor's content to this node 
		root->key = temp->key; 

		// Delete the inorder successor 
		root->right = deleteNode(root->right, temp->key); 
	} 
	return root; 
}

void search(struct node* root, int ke) 
{ 
    // Base Cases: root is null or key is present at root 
    if (root == NULL) { 
         printf("No\n");
		 return;
		  }
     if(root->key==ke){
          printf("Yes\n");
		  return;
	 }
    // Key is greater than root's key 
    if (root->key < ke) {
        search(root->right, ke); 
	   }
    // Key is smaller than root's key 
    if(root->key > ke){
	 search(root->left, ke);
	} 
} 


unsigned int getLeafCount(struct node* node) 
{ 
  if(node == NULL)        
    return 0; 
  if(node->left == NULL && node->right==NULL)       
    return 1;             
  else 
    return getLeafCount(node->left)+ 
           getLeafCount(node->right);       
} 
  
  static int count = 0;
  
  int countnodes(struct node *root)
{
    if(root != NULL)
    {
        countnodes(root->left);
        count++;
        countnodes(root->right);
    }
    return count;
}


void printPostorder(struct node* node) 
{ 
     if (node == NULL) 
        return; 
  
     // first recur on left subtree 
     printPostorder(node->left); 
  
     // then recur on right subtree 
     printPostorder(node->right); 
  
     // now deal with the node 
     printf("%d ", node->key); 
} 
  
/* Given a binary tree, print its nodes in inorder*/
void printInorder(struct node* node) 
{ 
     if (node == NULL) 
          return; 
  
     /* first recur on left child */
     printInorder(node->left); 
  
     /* then print the data of node */
     printf("%d ", node->key);   
  
     /* now recur on right child */
     printInorder(node->right); 
} 

int heig(struct node* node) 
{ 
    if (node==NULL) 
        return 0; 
    else
    { 
        /* compute the height of each subtree */
        int lheight = heig(node->left); 
        int rheight = heig(node->right); 
  
        /* use the larger one */
        if (lheight > rheight) 
            return(lheight+1); 
        else return(rheight+1); 
    } 
}

void printGivenLevel(struct node* root, int level) 
{ 
    if (root == NULL) 
        return; 
    if (level == 1) 
        printf("%d ", root->key); 
    else if (level > 1) 
    { 
        printGivenLevel(root->left, level-1); 
        printGivenLevel(root->right, level-1); 
    } 
} 

void printLevelOrder(struct node* root) 
{ 
    int h = heig(root); 
    int i; 
    for (i=1; i<=h; i++) 
        printGivenLevel(root, i); 
} 
  
/* Print nodes at a given level */

int maxDepth(struct node* node)  
{ 
   if (node==NULL)  
       return 0; 
   else 
   { 
       /* compute the depth of each subtree */
       int lDepth = maxDepth(node->left); 
       int rDepth = maxDepth(node->right); 
  
       /* use the larger one */
       if (lDepth > rDepth)  
           return(lDepth+1); 
       else return(rDepth+1); 
   } 
}
  

int y;
int k=0;

void fun(){
	int flag,x;
		   char str[1000];
		scanf("%s",str);
		if(isdigit(str[strlen(str)-1])==1){
			flag=1;
		}
		else{
			flag=0;
		}
		if(flag==1){
           sscanf(str,"%d",&x);
		   if(x>0){
			    y=x;  
		   }
		   if(cc=='A' && y>0){
			 k=1;
		   }
		    if(cc=='U' && y>0){
			   k=2;
		   }
		   if(y<=0){
			   k=0;
		   }
		   }
		   if(flag==0){
			cc=str[0];
			k=0;
		}
		   
}

 void bst(){
   struct node *root = NULL;
   char c;
   int flag=0,x,fd;
    while(1){
	char str[1000];
		scanf("%s",str);
		if(isdigit(str[strlen(str)-1])==1){
			flag=1;
			
		}
		else{
			flag=0;
		}
		if(flag==1){
           sscanf(str,"%d",&x);
		   if(x>0){
			    y=x;
			  
			   root=insert(root,y);
		   }
		   else{
			   y=-x;
			   root=deleteNode(root,y);
		   }
		}
		if(flag==0){
			cc=str[0];
			break;
		}
	}
	while(1){
      switch(cc) {
          case 'H' :
            break;

           case 'A':
            fun();
			 if(k==1){root=insert(root,y);}
		     continue;
          
		  case 'U' :
		    fun();
			if(k==2){root=deleteNode(root,y);}
	       continue;
        
		   case 'F' :
             scanf("%d",&fd);
			 search(root,fd);
			 scanf(" %c",&cc);
			 break;

			case 'Q' :
			printf("%d\n",getLeafCount(root));
			scanf(" %c",&cc);
			break; 
	  
	        case 'N' :
			printf("%d\n",countnodes(root));
			 scanf(" %c",&cc);
			  count=0;
			 break;

			 case 'I' :
			 printInorder(root);
			 printf("\n");
			 scanf(" %c",&cc);
			 break;

			 case 'S' :
			 printInorder(root);
			 printf("\n");
			 scanf(" %c",&cc);
			 break;

			 case 'L' :
			  printLevelOrder(root);
			   printf("\n");
			  scanf(" %c",&cc);
			  break;

			  case 'D' :
			   int add = maxDepth(root);
	            printf("%d\n",add);
                  break;
	  }
	 
  if(cc=='H') {break;}
 }
 
 inorder(root);
	 printf("\n");
 }

void rbt(){
	 struct node *root = NULL;
   int flag=0,x,fd;
    while(1){
	char str[1000];
		scanf("%s",str);
		if(isdigit(str[strlen(str)-1])==1){
			flag=1;
			
		}
		else{
			flag=0;
		}
		if(flag==1){
           sscanf(str,"%d",&x);
		   if(x>0){
			    y=x;
			 
			   root=insertr(root,y);
		   }
		   else{
			   y=-x;
			   root=deleteNoder(root,y);
		   }
		}
		if(flag==0){
		   cc=str[0];
			break;
		}
	}
		while(1){
      switch(cc) {
          case 'T' :
            break;

           case 'A':
            fun();
			 if(k==1){root=insertr(root,y);}
		     continue;
          
		  case 'U' :
		    fun();
			if(k==2){root=deleteNoder(root,y);}
	       continue;
	  
	       case 'F' :
		   scanf("%d",&fd);
		   search(root,fd);
		   scanf(" %c",&cc);
		    break;

		   case 'Q' :
			printf("%d\n",getLeafCount(root));
			scanf(" %c",&cc);
			break; 

			case 'N' :
			printf("%d\n",countnodes(root));
			count=0;
			scanf(" %c",&cc);
			break;

			case 'I' :
			 printInorder(root);
			  printf("\n");
			 scanf(" %c",&cc);
			 break;

			 case 'S' :
			 printInorder(root);
			  printf("\n");
			 scanf(" %c",&cc);
			 break;

			 case 'L' :
			  printLevelOrder(root);
			   printf("\n");
			  scanf(" %c",&cc);
	 		  break;

			 case 'D' :
			   int add = maxDepth(root);
	           printf("%d\n",add);
                  break;
	  }
	 
  if(cc=='T') {break;}
 }
 
	
	 inorder(root);
   printf("\n");
}

// Driver Program to test above functions 
int main() 
{ 
	
	int i,f; 
	printf("Enter no.of queries:");
	scanf("%d",&f);
    
    char aa;
	printf("Enter char:\n");
	 scanf(" %c",&aa);
	for(i=0;i<f;i++){
		//printf("ssssss\n");
	  if(aa=='T'){
	  bst();
	 // printf("one");
	  }
	 // printf("two");
	if(aa=='H'){
	rbt();
	 //printf("three");
	 }
	 if(i<f-1){ 
		aa=cc;
		// scanf(" %c",&aa);}
 //printf("fff\n"); 
	}
	}
    //printf("%d",root->key);
	return 0; 
 
}
