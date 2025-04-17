/**
 * -------------------------------------
 * @file  myrecord_bst.c
 * file description
 * -------------------------------------
 * @author Giuseppe Akbari, 169057752, akba7752@mylaurier.ca
 *
 * @version 2025-03-01
 *
 * -------------------------------------
 */

#include <stdio.h>
#include <math.h>
#include "queue_stack.h"
#include "bst.h"
#include "myrecord_bst.h"

void add_record(BSTDS *ds, RECORD record) {
// your code
	ds->count++;
	//calculate mean
	bst_insert(&ds->root, record);

	float holderMean = 0;
	float holderS = 0;

	QUEUE queue = { 0 };
	enqueue(&queue, ds->root);
	while (queue.front != NULL) {
		BSTNODE *tnp = (BSTNODE*) dequeue(&queue);
		holderMean += tnp->data.score;
		holderS += tnp->data.score * tnp->data.score;
		if (tnp->left != NULL) {
			enqueue(&queue, tnp->left);
		}
		if (tnp->right != NULL) {
			enqueue(&queue, tnp->right);
		}

	}
	ds->mean = (1.0 / ds->count) * holderMean;
	ds->stddev = sqrt(((1.0 / ds->count) * holderS) - (ds->mean * ds->mean));

	return;
}

void remove_record(BSTDS *ds, char *name) {
// your code
	ds->count--;
	bst_delete(&ds->root, name);
	if (ds->count == 0) {
		ds->mean = 0;
		ds->stddev = 0;
		return;
	}

	float holderMean = 0;
	float holderS = 0;

	QUEUE queue = { 0 };
	enqueue(&queue, ds->root);
	while (queue.front != NULL) {
		BSTNODE *tnp = (BSTNODE*) dequeue(&queue);
		holderMean += tnp->data.score;
		holderS += tnp->data.score * tnp->data.score;
		if (tnp->left != NULL) {
			enqueue(&queue, tnp->left);
		}
		if (tnp->right != NULL) {
			enqueue(&queue, tnp->right);
		}

	}
	ds->mean = (1.0 / ds->count) * holderMean;
	ds->stddev = sqrt(((1.0 / ds->count) * holderS) - (ds->mean * ds->mean));
	return;
}

void clean_bstds(BSTDS *ds) {
	clean_bst(&ds->root);
	ds->count = 0;
	ds->mean = 0;
	ds->stddev = 0;
}
