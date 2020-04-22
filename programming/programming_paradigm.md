# 面向过程
Algorithms + Data Structures = Programs（算法 + 数据结构 = 程序）—— Niklaus Wirth
数据和计算是两个不同的角色：

* 数据 存储 了程序运行的 状态
* 计算 通过修改数据，变换 运行的 状态

# 面向对象
* 封装 (encapsulation)：将数据和计算放到一起，并引入访问控制
* 继承 (inheritance)：共享数据和计算，避免冗余
* 多态 (polymorphism)：派发同一个消息（调用同一个方法），实现不同的操作（面向对象的核心）

通常，多态又分为两种：
* subtyping —— 运行时的 重写 (override)
* ad-hoc —— 编译时的 重载 (overload)

# 函数式
由于数据是 有状态的 (stateful)，而计算是 无状态的 (stateless)；所以需要将数据 绑定 (bind) 到函数上，得到“有状态”的函数，即 闭包 (closure)。通过构造、传递、调用 闭包，实现复杂的功能组合。

