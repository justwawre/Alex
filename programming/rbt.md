红黑树（Red-Black Tree，RBT）

# 二叉查找树（BST）
* 左子树上所有结点的值均小于或等于它的根结点的值。
* 右子树上所有结点的值均大于或等于它的根结点的值。
* 左、右子树也分别为二叉排序树。

# 红黑树是一种平衡的二叉查找树.
1. 节点是红色或黑色。
2. 根节点是黑色。
3. 每个叶子节点都是黑色的空节点（NIL节点）。
4. 每个红色节点的两个子节点都是黑色。(从每个叶子到根的所有路径上不能有两个连续的红色节点)
5. 从任一节点到其每个叶子的所有路径都包含相同数目的黑色节点。

我理解，根据规则2，3，4， 任何路径上，红色节点肯定比黑色的少。 而路径最短的情况是一路全黑为n个， 最长的情况是红色节点比黑色少一个为n-1.根据规则5， 最长路径为2n-1,最短的为n.
整个红黑树的查找，插入和删除都是O(logN)的，原因就是整个红黑树的高度是logN，查找从根到叶，走过的路径是树的高度，删除和插入操作是从叶到根的，所以经过的路径都是logN。

# data structure & operation

```C
struct rb_node
{
	unsigned long  rb_parent_color;
#define	RB_RED		0
#define	RB_BLACK	1
	struct rb_node *rb_right;
	struct rb_node *rb_left;
} __attribute__((aligned(sizeof(long))));

struct rb_root
{
	struct rb_node *rb_node;
};

//其上配套的操作

#define rb_parent(r)   ((struct rb_node *)((r)->rb_parent_color & ~3)) //低两位清0
#define rb_color(r)   ((r)->rb_parent_color & 1)                       //取最后一位
#define rb_is_red(r)   (!rb_color(r))                                  //最后一位为0？
#define rb_is_black(r) rb_color(r)                                     //最后一位为1？
#define rb_set_red(r)  do { (r)->rb_parent_color &= ~1; } while (0)    //最后一位置0
#define rb_set_black(r)  do { (r)->rb_parent_color |= 1; } while (0)   //最后一位置1

static inline void rb_set_parent(struct rb_node *rb, struct rb_node *p) //设置父亲
{
	rb->rb_parent_color = (rb->rb_parent_color & 3) | (unsigned long)p;
}
static inline void rb_set_color(struct rb_node *rb, int color)          //设置颜色
{
	rb->rb_parent_color = (rb->rb_parent_color & ~1) | color;
}

```
其中的一点骚操作是：

rb_parent_color这个域其实同时包含了颜色信息以及父亲节点的指针，因为该域是一个long的类型，而struct 是sizeof(long)的对齐，即使32位机器上，其后两位的数值永远是0，于是可以拿其中的一位来表示颜色，这里使用了最低位来表示颜色信息。

# rbt调整
但插入或删除node时，规则会被破坏，所以需要调整，调整手段不外乎
* node 变色
* 子树左旋
* 子树右旋

# usage example

```C
struct mytype *my_search(struct rb_root *root, char *string)
{
	struct rb_node *node = root->rb_node;
	while (node)
	{
		struct mytype *data = container_of(node, struct mytype, node);
		int result = strcmp(string, data->keystring);
		if (result < 0)
			node = node->rb_left;
		else if (result > 0)
			node = node->rb_right;
		else
			return data;
	}
	return NULL;
}

```
根据 container_of(ptr, type, member) 的规则，可以推出 mytype 的定义应该类似

```C
struct mytype
{
    struct rb_node *node;
    char *keystring;
};
```
与rbt库中的数据结构类似

```C
struct rb_root
{
	struct rb_node *rb_node;
};
```
也就是说牺牲一个 指针的空间，就可以使用rbt的所有功能了。
