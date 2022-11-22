# Question 4 最小生成树
## 题目要求
1. 输入最小生成树的顶点数N
	- 序号默认是1 ~ N
	- 顶点数可以设置上限
2. 输入两顶点之间边权值
3. 计算出最小生成树 并且输出最小代价
3. 用Kruskal算法实现

## 思路
1. 用优先级队列实现小顶堆
1. 用并查集判断是否连通
2. 输出之前判断是否能够形成最小生成树
2. 检查无效或者错误的输入，抛出异常，重新输入

## 核心代码

1. Kruskal类的构造函数

```c++
/**
 * @brief Construct a new Kruskal:: Kruskal object
 * @param  num_of_edges     边数
 * @param  num_of_nodes     顶点数
 */
Kruskal::Kruskal(int num_of_edges, int num_of_nodes) {
    this->num_of_edges = num_of_edges;
    this->num_of_nodes = num_of_nodes;
    this->min_value = 0;
    this->father = new int[MAX_V];
    input_data();
    calculate_min_value();
}
```

2. 计算最小生成树

```c++
/**
 * @brief 计算最小代价并输出
 */
void Kruskal::calculate_min_value() {
    int num = 0;
    while (!min_heap.empty() && num != num_of_nodes - 1) {
        Edge temp = min_heap.top();
        min_heap.pop();
        int father_x = find(temp.from);
        int father_y = find(temp.to);
        if (father_x != father_y) {
            father[father_y] = find(father[father_x]);
            cout << temp.from << " --> " << temp.to << " = " << temp.cost << endl;
            min_value += temp.cost;
            num++;
        }
    }
    for (int i = 1; i <= num_of_nodes; i++) {
        father[i] = find(father[i]);
    }
    if (judge()) {
        cout << "min_value = " << min_value << endl;
    } else {
        cout << "min_value doesn't exist!" << endl;
    }
}
```

3. 判断是否能够生成最小生成树(即判断每一个结点的根是否都是father[1])

```c++
/**
 * @brief 判断是否存在最小生成树
 * @return true 存在
 */
inline bool Kruskal::judge() {
    int flag = father[1];
    for (int i = 2; i != num_of_nodes + 1; i++) {
        if (flag != find(father[i])) {
            return false;
        }
    }
    return true;
}
```

## 测试用例
- Sample 1
```
 Input
 
 8
 11
 2 1 3
 3 1 2
 3 2 4
 2 4 2
 3 4 3
 4 5 5
 3 5 2
 5 6 4
 7 6 5
 8 5 5
 7 8 4
 
 Output
 
3 --> 1 = 2
3 --> 5 = 2
2 --> 4 = 2
3 --> 4 = 3
7 --> 8 = 4
5 --> 6 = 4
7 --> 6 = 5
min_value = 22
```

- Sample 2

```
Input

7 12
1 2 20
2 3 15
3 4 3
4 5 17
5 6 28
6 1 23
1 7 1
2 7 4
3 7 9
4 7 16 
5 7 25
6 7 36

Output

1 --> 7 = 1
3 --> 4 = 3
2 --> 7 = 4
3 --> 7 = 9
4 --> 5 = 17
6 --> 1 = 23
min_value = 57
```

- Sample 3

```
Input

7 10
1 2 15
1 3 14
1 4 11
2 3 12
2 4 10
2 6 13
3 4 14
3 5 11
3 7 12
4 5 16

Output

2 --> 4 = 10
1 --> 4 = 11
3 --> 5 = 11
2 --> 3 = 12
3 --> 7 = 12
2 --> 6 = 13
min_value = 69
```

## 心得体会

1. Kruskal算法比较适合稀疏的网络
2. 小顶堆在STL中的实现方式是在第三个参数中使用std::greater

```c++
std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> min_heap;
```
3. 本题使用自己实现的min_heap.h替代stl中的优先级队列
