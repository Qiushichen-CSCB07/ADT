#include "avl_tree.h"

 
int main(){
    int choice;
    int number;
    Node *root = NULL;

    choice = -1;
    while(choice != 8){
        printf("Please select from the following options:\n");
        printf("0 - Insert a new node\n");
        printf("1 - Search for a node\n");
        printf("2 - Delete a node\n");
        printf("3 - Print nodes in in-order\n");
        printf("4 - Print nodes in pre-order\n");
        printf("5 - Print nodes in post-order\n");
		printf("6 - Show the rank of a given node\n");
		printf("7 - Show the node of a given rank\n");
        printf("8 - delete BST and exit\n");
		printf("9 - split an avl tree\n");
		printf("10 - union 2 avl trees\n");
		printf("11 - join L tree, k node and G tree\n");

        scanf("%d", &choice);
        getchar();

        if(choice == 0){
            printf("enter the number\n");
            scanf("%d", &number);
            getchar();
            root = Insert(root, number);
			printf("\n");
        }

        else if(choice == 1){
            printf("enter the search-targeted number\n");
            scanf("%d", &number);
            getchar();

            Node *t = search(root, number);
            if(t != NULL){
                printf("Node founded, with pointer%p\n", t);
            }
            else{
                printf("Target not found\n");
            }
			printf("\n");
        }

        else if(choice == 2){
            printf("enter the delete-targeted number\n");
            scanf("%d", &number);
            getchar();
            root = del(root, number);
			printf("\n");
        }

        else if(choice == 3){
            printf("in-order printing...\n");
            in_order(root);
			printf("\n");
        }

        else if(choice == 4){
            printf("pre-order printing...\n");
            pre_order(root);
			printf("\n");
        }

        else if(choice == 5){
            printf("post-order printing...\n");
            post_order(root);
			printf("\n");
        }
		else if(choice == 6){
			printf("enter the target value\n");
            scanf("%d", &number);
            getchar();
			int rank = get_rank(root, number);
			if(rank == NOTIN){
				printf("This value is not in the node!\n");
			}
			else{
				printf("the rank of the value is: %d\n", rank);
			}
			printf("\n");
		}
		else if(choice == 7){
			printf("enter the target rank\n");
            scanf("%d", &number);
            getchar();

			Node* t = findRank(root, number);
			if(t == NULL){
				printf("The rank value is not valid, node not found\n");
			}
			else{
				printf("Node founded, address:%p, key:%d, height:%d\n",(void*)t, t->key, t->height);
			}
			printf("\n");
		}

		else if(choice == 8){
			delete_AVL(root);
			printf("System terminated.\n");
			break;
		}
		else if(choice == 9){
			//split avltree
			int array[12] = {60, 20, 80, 10, 30, 70, 115, 35,65,75,100, 120};
			int x = 78;
			Node* Tsplit = NULL;
			for(int i = 0; i < 12; i ++){
				Tsplit = Insert(Tsplit,array[i]);
			}
			printf("The tree to be splited at key = %d in pre_order is:\n", x);
			pre_order(Tsplit);

			SplitResult result;
			result = split(Tsplit,x);
			Node* t1 = NULL;
			Node* t2 = NULL;
			t1 = result.left;
			t2 =  result.right;

			printf("\nResult tree 1 is:\n");
			pre_order(t1);

			printf("\nResult tree 2 is:\n");
			pre_order(t2);
			printf("\n");

			
			delete_AVL(t1);
			delete_AVL(t2);
			delete_AVL(Tsplit);

		}
		else if(choice == 10){
			//union 2 avl tree
			int treeA[6] = {11,10,25,9,20,28};
			int treeB[6] = {18,14,22,13,16,31};
			Node* t1 = NULL;
			Node *t2 = NULL;
			for(int i = 0; i < 6; i ++){
				t1 = Insert(t1, treeA[i]);
				t2 = Insert(t2,treeB[i]);
			}
			printf("\nTree1 in pre_order is:\n");
			pre_order(t1);
			printf("\nTree2 in pre_order is:\n");
			pre_order(t2);

			Node* t_union = tree_union(t1,t2);
			printf("\nthe unioned tree in pre_order is:\n");
			pre_order(t_union);
			printf("\n");

			delete_AVL(t1);
			delete_AVL(t2);
			delete_AVL(t_union);
		}
		else if(choice == 11){
			//join L, k and R
			int treeL[8] = {2,0,4,1,3,6,5,7};
			int treeR[2] = {10,9};

			Node* nodeL = NULL;
			Node* nodeR = NULL;
			for(int i = 0; i < 8; i++){
				nodeL = Insert(nodeL,treeL[i]);
			}
			for(int i = 0; i < 2; i ++){
				nodeR = Insert(nodeR, treeR[i]);
			}
			printf("\nTree L in pre-order is:\n");
			pre_order(nodeL);
			printf("\nThe k is: %d\n", 8);
			printf("\nTree R in pre-order is:\n");
			pre_order(nodeR);

			Node* nodeJoin = NULL;
			nodeJoin = join(nodeL, 8, nodeR);

			printf("\nThe joined tree is:\n");
			pre_order(nodeJoin);

			delete_AVL(nodeL);
			delete_AVL(nodeR);
			delete_AVL(nodeJoin);
			printf("\n");

		}
		else{
			printf("Please inter valid selection number.\n");
		}
		choice = -1;

    }
    //delete_AVL(root);
    return 0;
}


