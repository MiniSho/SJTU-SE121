# Homework 2

* 1.证明对于任意等价的BST树（n个节点），都能通过O(n)次旋转（zig/zag）相互转化。(任意一次zig/zag都能增加右/左子树的高度)；

  * **Solution**

    按照中序遍历的顺序，从根结点开始右旋，直到左子树为空；然后对根结点的右子树进行相同的操作，直到二叉树退变成升序排列的右链。每进行一次右旋操作，都可以使右链上多一个节点，所以至多进行 $n-1$ 次右旋操作。因为旋转是可逆的，所以任意等价BST树都可以通过至多 $2n-2 = O(n)$ 次旋转转化。 



* 2.对于如下一棵splay树，依次访问节点3,9,1,给出bottom-up双层旋转的调整过程

  * **Solution**

    <img src="C:\Users\kobe\AppData\Roaming\Typora\typora-user-images\image-20200316174713421.png" alt="image-20200316174713421" style="zoom:33%;" />

    

    

    <img src="C:\Users\kobe\AppData\Roaming\Typora\typora-user-images\image-20200316174924344.png" alt="image-20200316174924344" style="zoom:33%;" />

    

    <img src="C:\Users\kobe\AppData\Roaming\Typora\typora-user-images\image-20200316174941150.png" alt="image-20200316174941150" style="zoom:33%;" />