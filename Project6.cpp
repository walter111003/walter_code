#include "Recursion.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* Return the sum of the elements in array x[]
 * there are n elements in x[] (x[0].. x[n-1])
 * solve the problem recursively and
 * use an "n-1" type of decomposition
 *
 * NOTE: This function will NOT be graded and is merely provided for practice.
 */
int sumNums1(int x[], int n, int *calls) {
   *calls += 1;
    if (n == 0) {
        return 0;
    }

    return x[n-1] + sumNums1(x, n-1, calls);


}

/*
 * Return the sum of the elements in array x[]
 * there are n elements in x[] (x[0].. x[n-1])
 * n may be either odd or even
 * solve the problem recursively and
 * use an "n/2" type of decomposition
 *
 * NOTE: This function will NOT be graded and is merely provided for practice.
 */
int sumNums2(int x[], int n, int *calls) {
 
  // TODO: Your code here
 *calls += 1;
    if (n == 0) {
        return 0;

        
    } else if (n == 1) {

        return x[0];
    }
    int mid = n / 2;

    return sumNums2(x, mid, calls) + sumNums2(x + mid, n - mid, calls);
}

/*
 * Write a recursive function that revereses a positive n-digit integer x.
 * For example, if x = 12345, the function should return 54321.
 * Hint: use pow() from math.h
 */
int reverse(int x, int n, int *calls) {

  *calls += 1;
if (n == 1) {
        return x;
    }
    return (x % 10) * pow(10, n - 1) + reverse(x / 10, n - 1, calls);

}


/*
 * Given a linked list, remove all nodes that contain the character val
 * Don't forget to free memory for any nodes you remove
*/
Node* remove_nodes(Node* head, char val, int* calls) {
  *calls += 1;

    if (head == NULL) {
        return NULL;


    }


    if (head->data == val) {

        Node* temp = head->next;

        free(head);

        return remove_nodes(temp, val, calls);

    }


    head->next = remove_nodes(head->next, val, calls);

    return head;
}

/* You are given a list of item weights that represent the weight of the ith
 * index item You are also given a maximum weight that your bag can hold.
 * Return the total weight of the subset of items that maximize the total weight
 * of the bag without going over the maximum weight
 */
int knapsack(int weights[], int n, int max_weight, int *calls) {
  *calls += 1;
    if (n == 0 || max_weight == 0) {
        return 0;


    }
    if (weights[n-1] > max_weight) {


        return knapsack(weights, n-1, max_weight, calls);


    } else {
        int include = weights[n-1] + knapsack(weights, n-1, max_weight - weights[n-1], calls);


        int exclude = knapsack(weights, n-1, max_weight, calls);


        return include > exclude ? include : exclude;
    }
}

// Given a binary tree, return the weight of the least weight path (the path
// with the smallest sum of node values)
int least_weight_path(BinaryNode *root, int *calls) {
  *calls += 1;

    *calls += 1;
    if (root == NULL) {
        return 0;
    }
    if (root->left == NULL && root->right == NULL) {
        return root->data;
    }
    if (root->left == NULL) {
        return root->data + least_weight_path(root->right, calls);
    }
    if (root->right == NULL) {

        return root->data + least_weight_path(root->left, calls);
    }
    int left_path = least_weight_path(root->left, calls);

    int right_path = least_weight_path(root->right, calls);

    return root->data + (left_path < right_path ? left_path : right_path);
}

bool is_win(char board[3][3], char player) {
 for (int i = 0; i < 3; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||

            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {

            return true;
        }
    }
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }
    return false;
}

/*
 * Given a tic-tac-toe board, return a Record struct that contains the number of
 * ways that X can win, the number of ways that O can win, and the number of
 * draws from the current board position.
 * The possible values of the board are 'X', 'O', and ' ' (space character for empty)
 */
Record tic_tac_toe(char board[3][3], bool is_x_turn, int *calls) {
  *calls += 1;
   *calls += 1;

    Record record = {0, 0, 0};
    if (is_win(board, 'X')) {
        record.x_wins = 1;
        return record;
    }
    if (is_win(board, 'O')) {
        record.o_wins = 1;
        return record;
    }

    bool draw = true;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                draw = false;


                board[i][j] = is_x_turn ? 'X' : 'O';


                Record result = tic_tac_toe(board, !is_x_turn, calls);


                record.x_wins += result.x_wins;

                record.o_wins += result.o_wins;

                record.draws += result.draws;
                board[i][j] = ' ';
            }
        }
    }
    if (draw) {
        record.draws = 1;
    }
    return record;
  
}
