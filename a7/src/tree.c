/**
 * -------------------------------------
 * @file  tree.c
 * file description
 * -------------------------------------
 * @author Giuseppe Akbari, 169057752, akba7752@mylaurier.ca
 *
 * @version 2025-03-01
 *
 * -------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include "queue_stack.h"
#include "tree.h"

TPROPS tree_property(TNODE *root) {
// your code
	TPROPS r = { 0 };
	printf("hi");
	if (root) {
		TPROPS left = tree_property(root->left);

		TPROPS right = tree_property(root->right);
		r.order = 1 + left.order + right.order;
		if (left.height > right.height) {
			r.height = 1 + left.height;
		} else {
			r.height = right.height;
		}
	}
	return r;
}

void preorder(TNODE *root) {
// your code
	if (root != NULL) {
		printf("%c ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
	return;

}

void inorder(TNODE *root) {
// your code
	if (root != NULL) {
		inorder(root->left);
		printf("%c ", root->data);
		inorder(root->right);
	}
	return;
}

void postorder(TNODE *root) {
// your code
	if (root != NULL) {
		postorder(root->left);
		postorder(root->right);
		printf("%c ", root->data);
	}
}

void bforder(TNODE *root) {
// your code
	QUEUE q = { 0 };
	TNODE *c = root;
	enqueue(&q, c);
	while (q.front) {
		c = (TNODE*) dequeue(&q);
		printf("%c ", c->data);
		if (c->left != NULL) {
			enqueue(&q, c->left);
		}
		if (c->right != NULL) {
			enqueue(&q, c->right);
		}

	}
	clean_queue(&q);

	return;
}

TNODE* bfs(TNODE *root, char val) {
// your code
	QUEUE q = { 0 };
	TNODE *c = root;
	enqueue(&q, c);
	while (q.front) {
		c = (TNODE*) dequeue(&q);
		if (c->data == val) {
			break;
		}
		if (c->left != NULL) {
			enqueue(&q, c->left);
		}
		if (c->right != NULL) {
			enqueue(&q, c->right);
		}
	}
	clean_queue(&q);

	return c;
}

TNODE* dfs(TNODE *root, char val) {
//
	STACK s = { 0 };
	TNODE *c = root;
	push(&s, c);
	while (s.top) {
		c = (TNODE*) pop(&s);
		if (c->data == val) {
			break;
		}
		if (c->left != NULL) {
			push(&s, c->left);
		}
		if (c->right != NULL) {
			push(&s, c->right);
		}
	}
	clean_stack(&s);
	return c;
}
// the following functions are given, need to add to your program.

TNODE* tree_node(char val) {
	TNODE *np = (TNODE*) malloc(sizeof(TNODE));
	if (np != NULL) {
		np->data = val;
		np->left = NULL;
		np->right = NULL;
	}
	return np;
}

void clean_tree(TNODE **rootp) {
	TNODE *p = *rootp;
	if (p) {
		if (p->left)
			clean_tree(&p->left);
		if (p->right)
			clean_tree(&p->right);
		free(p);
	}
	*rootp = NULL;
}

void insert_tree(TNODE **rootp, char val) {
	if (*rootp == NULL) {
		*rootp = tree_node(val);
	} else {
		QUEUE queue = { 0 };
		TNODE *p;
		enqueue(&queue, *rootp);
		while (queue.front) {
			p = dequeue(&queue);
			if (p->left == NULL) {
				p->left = tree_node(val);
				break;
			} else {
				enqueue(&queue, p->left);
			}

			if (p->right == NULL) {
				p->right = tree_node(val);
				break;
			} else {
				enqueue(&queue, p->right);
			}
		}
	}
}
