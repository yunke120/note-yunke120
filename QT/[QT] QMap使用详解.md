# [QT] QMap使用详解

## 引言

​		QMap/QMultiMap属于关联式容器，其底层结构是通过二叉树实现，故其查找value的效率很快。QMap中的数据都是成对出现的，第一个称为key（键），第二个称value（键值）。

## 目录

1. 实例化QMap对象
2. 插入数据
3. 移除数据
4. 遍历数据
5. 由键查找对应键值
6. 由键值查找键
7. 修改键值
8. 查找是否包含某个键
9. 获取所有的键和键值
10. 清楚数据
11. 一个键对应多个值
12. QMultiMap遍历数据

### 实例化QMap对象

```cpp
    /* 创建QMap实例, 第一个参数为QString类型的键，第二个参数为int类型的值 */
    QMap<QString, int> map;
```
### 插入数据

```cpp
    /* 插入数据 两种方式*/
    map["math"] = 100; 
    map.insert("English", 99); /* 推荐 */
```
打印输出: QMap(("English", 99)("math", 100))

### 移除数据

```cpp
    /* 移除数据 */
    map.remove("math");
```
打印输出：QMap(("English", 99))

### 遍历数据

```cpp
    /* 遍历数据 (先随便插入几个)*/
    map.insert("Math", 100);
    map.insert("Chinese", 98);
    map.insert("physical", 97);
    map.insert("chemical", 96);
    map.insert("biological", 95);
    
    /* 遍历数据要使用迭代器，QT提供了两种方式的迭代 */
    /* 第一种是Java类型的迭代 */
    QMapIterator<QString, int> iterator(map);
    while (iterator.hasNext()) {
        iterator.next();
        qDebug() << iterator.key() << ":" << iterator.value();
    }

    /* 第二种是STL类型的迭代 */
    QMap<QString, int>::const_iterator iterator_1 = map.constBegin();
    while (iterator_1 != map.constEnd()) {
        qDebug() << iterator_1.key() << ":" << iterator_1.value();
        ++iterator_1;
    }
	/* 或 */
    for (QMap<QString, int>::const_iterator it = map.constBegin(); it != map.constEnd(); it++) {
        qDebug() << it.key() << ": " << it.value();
    }
```
打印输出：两种方法输出一样
"Chinese" : 98
"English" : 99
"Math" : 100
"biological" : 95
"chemical" : 96
"physical" : 97

### 由键查找对应键值

```cpp
map.value("Math");
```
打印输出：100

### 由键值查找键

```cpp
int val = map.value("Math");
qDebug() << "Math: " << val;
```
打印输出：Math:  100

### 修改键值

```cpp
    /* 通常一个键只对应一个值，如果再次调用insert()方法，会覆盖以前的值 */
    map.insert("Math", 120);
    qDebug() << map.value("Math");
```
打印输出：120

### 查找是否包含某个键

```cpp
    bool isok = map.contains("Math");
    qDebug() << isok;
```
打印输出：true

### 获取所有的键和键值

```cpp
    QList<QString> allKeys = map.keys();
    qDebug() << allKeys;
    QList<int> allValues = map.values();
    qDebug() << allValues;
```
打印输出：
("Chinese", "English", "Math", "biological", "chemical", "physical")
(98, 99, 120, 95, 96, 97)

### 清除数据

```cpp
    map.clear();
    qDebug() << map.isEmpty();
```

打印输出：true

### 一个键对应多个值

方式一：通过`insertMulti`方法

```cpp
    /* 通过insert方法进行插值会覆盖以前的值，但是通过insertMulti方法不会覆盖，而是会增加一对 */
    map.insert("Math", 100);
    map.insertMulti("Math", 150);
    qDebug() << map.value("Math");
    qDebug() << map.values("Math");/* 获取Math所有键值 */

    /* 查看当前键和键值的数量 */
    qDebug() << map.keys().size();
    qDebug() << map.values().size();
```
打印输出：150
                     (150, 100)
                     $\color{#FF0000}{2}$
                     2

总结：通过insertMulti方法可以使得一个键对应多个键值，通过value获取其最后一次插入得键值，通过values获取其所有键值。

注意：这一点与STL中得map不同，在STL中，map对象是不允许有多个相同键的

```
/* 这是STL测试用例 */
#include <iostream>
#include <map>
#include <string>

using namespace std;
int main()
{
    map<string, int> mp;
    mp.insert(pair<string, int>("Math", 100));
    /* 再次插入一个键为"Math"的map */
    mp.insert(make_pair("Math",120));

    for(map<string, int>::iterator it = mp.begin(); it != mp.end(); it++)
    {
        cout << "key = " << it->first << " value: " << it->second << endl;
    }
    return 0;
}
```

打印输出：key = Math value: 100

虽然插入了两次，但是因为都是同一个键，故第二次插入无效。

方式二：通过QMultiMap类

```c++
    map.insert("Math", 100);
    map.insertMulti("Math", 150);
    map.insertMulti("Math", 120);
    qDebug() << map.values("Math");
    
    QMultiMap<QString, int> multiMap;
    multiMap.insert("Math", 100);
    multiMap.insert("Math", 90);
    multiMap.insert("Math", 80);
    qDebug() << multiMap.values("Math");
```

打印输出：

(120, 150, 100)
(80, 90, 100)

两种方法效果是一样的。

### QMultiMap遍历数据

```c++
    /* 遍历全部 */
for (QMultiMap<QString, int>::iterator it = multiMap.begin(); it != multiMap.end(); it++) {
    qDebug() << it.key() << ": " << it.value();
}
    /* 只遍历指定键 */
for (QMultiMap<QString, int>::iterator it = multiMap.find("Math"); it != multiMap.end(); it++) {
    qDebug() << it.key() << ": " << it.value();
}
```

