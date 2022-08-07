#include <QCoreApplication>
#include <QMap>
#include <QDebug>

bool Compare()
{
    return true;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QMap<QString, int> map; /* 实例化 */
#if 0
    /* 插入数据 两种方式*/
    map["math"] = 100;
    map.insert("English", 99); /* 推荐 */

    /* 移除数据 */
    map.remove("math");

    /* 遍历数据 (先随便插入几个)*/
    map.insert("Math", 100);
    map.insert("Chinese", 98);
    map.insert("physical", 97);
    map.insert("chemical", 96);
    map.insert("biological", 95);

    /* 遍历输出 */
    for (QMap<QString, int>::const_iterator it = map.constBegin(); it != map.constEnd(); it++) {
        qDebug() << it.key() << ": " << it.value();
    }


    /* 由键查找对应键值 */
    int val = map.value("Math");
    qDebug() << "Math: " << val;

    map.insert("Math", 120);
    qDebug() << map.value("Math");

    bool isok = map.contains("Math");
    qDebug() << isok;

    QList<QString> allKeys = map.keys();
    qDebug() << allKeys;
    QList<int> allValues = map.values();
    qDebug() << allValues;
#endif
    map.clear();
    qDebug() << map.isEmpty();

    /* 通过insert方法进行插值会覆盖以前的值，但是通过insertMulti方法不会覆盖，而是会增加一对 */
//    map.insert("Math", 100);
//    map.insertMulti("Chinese", 100);
//    map.insertMulti("physical", 100);
//    qDebug() << map.keys(100);

    QMultiMap<QString, int> multiMap;
    multiMap.insert("Math", 100);
    multiMap.insert("Math", 90);
    multiMap.insert("Math", 80);

    multiMap.insert("Chinese", 100);
    multiMap.insert("Chinese", 90);
    multiMap.insert("Chinese", 80);
    qDebug() << multiMap.values("Math");

    for (QMultiMap<QString, int>::iterator it = multiMap.begin(); it != multiMap.end(); it++) {
        qDebug() << it.key() << ": " << it.value();
    }

    for (QMultiMap<QString, int>::iterator it = multiMap.find("Math"); it != multiMap.end(); it++) {
        qDebug() << it.key() << ": " << it.value();
    }

    return a.exec();
}
