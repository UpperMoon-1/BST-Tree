/**
 * -------------------------------------
 * @file  bst.c
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
#include <string.h>
#include "bst.h"

BSTNODE* new_node(RECORD data);
BSTNODE* extract_smallest_node(BSTNODE **rootp);

BSTNODE* bst_search(BSTNODE *root, char *key) {
// your code
	if (root == NULL) {
		return NULL;
	} else if (strcmp(key, root->data.name) == 0) {
		return root;
	} else if (strcmp(key, root->data.name) < 0) {
		return bst_search(root->left, key);
	} else {
		return bst_search(root->right, key);
	}

}

void bst_insert(BSTNODE **rootp, RECORD data) {
// your code
	BSTNODE *root = *rootp;
	if (root == NULL) {
		*rootp = new_node(data);
	} else {
		if (strcmp(data.name, root->data.name) < 0) {
			if (root->left == NULL) {
				root->left = new_node(data);
			} else {
				bst_insert(&(root->left), data);
			}
		} else {
			if (root->right == NULL) {
				root->right = new_node(data);
			} else {
				bst_insert(&(root->right), data);
			}
		}
	}
}

void bst_delete(BSTNODE **rootp, char *key) {
// your code
	BSTNODE *root = *rootp;
	BSTNODE *tnp;
	if (root != NULL) {
		if (strcmp(key, root->data.name) == 0) {
			if (root->left == NULL && root->right == NULL) {
				free(root);
				*rootp = NULL;
			} else if (root->left != NULL && root->right == NULL) {
				tnp = root->left;
				*rootp = tnp;
				free(root);
			} else if (root->left == NULL && root->right != NULL) {
				tnp = root->right;
				*rootp = tnp;
				free(root);
			} else if (root->left != NULL && root->right != NULL) {
				tnp = extract_smallest_node(&root->right);
				tnp->left = root->left;
				tnp->right = root->right;
				*rootp = tnp;
				free(root);
			}
		} else {
			if (strcmp(key, root->data.name) < 0) {
				bst_delete(&root->left, key);
			} else {
				bst_delete(&root->right, key);
			}
		}
	}
	return;

}

BSTNODE* new_node(RECORD data) {
	BSTNODE *np = (BSTNODE*) malloc(sizeof(BSTNODE));
	if (np) {
		memcpy(np, &data, sizeof(BSTNODE));
		np->left = NULL;
		np->right = NULL;
	}
	return np;
}

BSTNODE* extract_smallest_node(BSTNODE **rootp) {
	BSTNODE *p = *rootp, *parent = NULL;
	if (p) {
		while (p->left) {
			parent = p;
			p = p->left;
		}

		if (parent == NULL)
			*rootp = p->right;
		else
			parent->left = p->right;

		p->left = NULL;
		p->right = NULL;
	}

	return p;
}

void clean_bst(BSTNODE **rootp) {
	BSTNODE *root = *rootp;
	if (root) {
		if (root->left)
			clean_bst(&root->left);
		if (root->right)
			clean_bst(&root->right);
		free(root);
	}
	*rootp = NULL;
}
