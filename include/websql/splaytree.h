/*
 * =============================================================================
 *
 *       Filename:  splaytree.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/02/2013 11:02:45 AM
 *       Revision:  r1
 *       Compiler:  gcc (Ubuntu/Linaro 4.4.4-14ubuntu5) 4.4.5
 *
 *         Author:  Wang Wei (sofartogo), wangwei881116@gmail.com
 *        Company:  ICT ( Institute Of Computing Technology, CAS )
 *
 * =============================================================================
 */
#ifndef _SPLAY_TREE_H_
#define _SPLAY_TREE_H_

typedef struct tree_node_s_ splaytree_t;

struct tree_node_s_ {
    struct tree_node_s_ *left;
    struct tree_node_s_ *right;
    int key;
    int size;   /* maintained to be the number of nodes rooted here */

    void *data;
};


splaytree_t * splaytree_splay(splaytree_t *t, int key);
splaytree_t * splaytree_insert(splaytree_t *t, int key, void *data);
splaytree_t * splaytree_delete(splaytree_t *t, int key);
splaytree_t * splaytree_size(splaytree_t *t);

#define splaytree_size(x) (((x)==NULL) ? 0 : ((x)->size))
/* This macro returns the size of a node.  Unlike "x->size",     */
/* it works even if x=NULL.  The test could be avoided by using  */
/* a special version of NULL which was a real node with size 0.  */

#endif

