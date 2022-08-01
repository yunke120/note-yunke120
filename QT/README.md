# QT学习笔记

## QGraphicsView

​		**QGraphicsView** 为 **QGraphicsScene** 提供了显示的窗口。

### 枚举

#### CacheModeFlag

这个枚举类型可设置 **QGraphicsView** 的缓存模式。参数如下：

```
enum CacheModeFlag {
        CacheNone = 0x0,
        CacheBackground = 0x1
};
```

​		其中，CacheNone 表示无缓存，所有描绘直接在viewport中完成；CacheBackground  缓存背景。!!!

​		相关函数：

```
CacheMode  cacheMode () const 
void setCacheMode (CacheMode mode )
```

#### DragMode

 此枚举描述视图的默认动作，在视口中按下并拖曳鼠标时。

```
enum DragMode {
        NoDrag,
        ScrollHandDrag,
        RubberBandDrag
    };
```

​		NoDrag 什么都不发生；ScrollHandDrag 光标变为手；RubberBandDrag 交互模式下为拖拽选中样式。

​		相关函数：

```
DragMode dragMode() const;
void setDragMode(DragMode mode);
```

#### ViewportAnchor

此枚举表示当视图大小变化是的锚点位置。参数如下：

```
    enum ViewportAnchor {
        NoAnchor,
        AnchorViewCenter,
        AnchorUnderMouse
    };
```

​		NoAnchor 无锚点，或者说锚点为(0,0)点；AnchorViewCenter  视图中心的场景点用作锚点；  AnchorUnderMouse  鼠标下点用作锚点。 

​		相关函数：

```
ViewportAnchor transformationAnchor() const;
void setTransformationAnchor(ViewportAnchor anchor);

ViewportAnchor resizeAnchor() const;
void setResizeAnchor(ViewportAnchor anchor);
```

#### ViewportUpdateMode

​		描述当 viewport 变化时，QGraphicsView该如何更新的标志。默认值为 MinimalViewportUpdate。

```
enum ViewportUpdateMode {
        FullViewportUpdate,
        MinimalViewportUpdate,
        SmartViewportUpdate,
        NoViewportUpdate,
        BoundingRectViewportUpdate
    };
```

​		相关函数：

```
ViewportUpdateMode viewportUpdateMode() const;
void setViewportUpdateMode(ViewportUpdateMode mode);
```



### 属性

#### alignment

​	   当整个场景可见时，此属性保存视图中场景的对齐方式 

#### backgroundBrush 

​		 此特性保持场景的背景画笔 

#### cacheMode 

​		 此特性保持被缓存视图的哪些部分 

#### foregroundBrush 

​		 此特性保持场景的前景笔刷 

#### interactive 

​		 此特性保持视图是否允许场景交互。 

```c++
bool isInteractive() const;
void setInteractive(bool allowed);
```

#### optimizationFlags 

​		 此标志可以用于微调 QGraphicsView 的性能。 

```c++
OptimizationFlags optimizationFlags() const;
void setOptimizationFlag(OptimizationFlag flag, bool enabled = true);
void setOptimizationFlags(OptimizationFlags flags);
```

#### renderHints 

​		 此特性保持视图的默认渲染提示 

```c++
QPainter::RenderHints renderHints() const;
void setRenderHint(QPainter::RenderHint hint, bool enabled = true);
void setRenderHints(QPainter::RenderHints hints);
```

#### resizeAnchor 

​		 当重置视图大小时，视图应如何定位场景。 

#### rubberBandSelectionMode 

​		此属性保存使用橡皮筋选择矩形选择项的行为。

```c++
Qt::ItemSelectionMode rubberBandSelectionMode() const;
void setRubberBandSelectionMode(Qt::ItemSelectionMode mode);
QRect rubberBandRect() const;
```

#### sceneRect 

​		 此特性保持由此视图可视化的场景区域。 

```c++
QRectF sceneRect() const;
void setSceneRect(const QRectF &rect);
inline void setSceneRect(qreal x, qreal y, qreal w, qreal h);
```

#### transformationAnchor 

​		 视图在变换期间应如何定位场景。 

```c++
ViewportAnchor transformationAnchor() const;
void setTransformationAnchor(ViewportAnchor anchor);
```

#### viewportUpdateMode 

​		 视口应如何更新其内容。 

```c++
ViewportUpdateMode viewportUpdateMode() const;
void setViewportUpdateMode(ViewportUpdateMode mode);
```



##  [QGraphicsScene](http://qt5.digitser.net/5.9/zh-CN/qgraphicsscene.html) 

​		QGraphicsScene类为管理大量2D图形项提供了一个表面。

​		这个类用作QGraphicsItems的容器。它与QGraphicsView一起用于在2D表面上可视化图形项，如线、矩形、文本，甚至自定义项。QGraphicsScene是图形视图框架的一部分。

​		QGraphicsScene还提供了一些功能，可以让您高效地确定项目的位置，并确定在场景的任意区域中哪些项目是可见的。使用QGraphicsView小部件，您既可以可视化整个场景，也可以放大并只查看场景的一部分。

​		注意，QGraphicsScene没有自己的视觉外观;它只管理项目。您需要创建一个QGraphicsView小部件来可视化场景。要向场景添加项目，首先要构造一个QGraphicsScene对象。然后，您有两个选择:通过调用addItem()添加现有的QGraphicsItem对象，或者您可以调用其中一个方便的函数addEllipse()、addLine()、addPath()、addPixmap()、addPolygon()、addRect()或addText()，它们都返回一个指向新添加项的指针。通过这些函数添加的物品的尺寸是相对于物品的坐标系统的，物品的位置在场景中初始化为(0,0)。

​		然后可以使用QGraphicsView可视化该场景。当场景变化时(例如，当一个项目移动或转换)，QGraphicsScene发出changed()信号。要删除一个项，请调用removeItem()。
​		QGraphicsScene使用索引算法来有效地管理条目的位置。默认情况下，使用BSP(二进制空间分区)树;一种适合于大多数物体保持静态(即不移动)的大型场景的算法。你可以通过调用setItemIndexMethod()来禁用这个索引。有关可用索引算法的更多信息，请参见itemIndexMethod属性。

​		场景的边界矩形通过调用setscen竖立()来设置。物品可以放置在场景中的任何位置，场景的大小默认不受限制。场景rect仅用于内部记账，维护场景的项目索引。如果场景矩形未设置，QGraphicsScene将使用itemsBoundingRect()返回的所有项目的边界区域作为场景矩形。然而，itemsBoundingRect()是一个相对耗时的函数，因为它通过收集场景中每个项目的位置信息来操作。正因为如此，当在大型场景中操作时，你应该总是设置场景的rect。
​		QGraphicsScene最大的优势之一是它能够高效地确定物品的位置。即使场景中有数百万项，items()函数也可以在几毫秒内确定项的位置。items()有几种重载:一种用于查找特定位置的项，另一种用于查找位于多边形或矩形内部或与多边形或矩形相交的项，等等。返回的项目列表按堆叠顺序排序，最上面的项目是列表中的第一个项目。为了方便起见，还有一个itemAt()函数，它返回给定位置上最上面的项。
​		QGraphicsScene维护场景的选择信息。要选择项目，调用setSelectionArea()，要清除当前选择，调用clearSelection()。调用selectedItems()来获取所有选定项的列表。

### 枚举

#### ItemIndexMethod

​		 此枚举描述索引算法 [QGraphicsScene ](http://qt5.digitser.net/5.9/zh-CN/qgraphicsscene.html)提供用于管理场景中项的有关位置信息 

```c++
enum ItemIndexMethod {
        BspTreeIndex,
        NoIndex = -1
    };
```

​		BspTreeIndex 应用了二进制空间分区树。所有QGraphicsScene的物品定位算法通过使用二分搜索，其复杂度都接近于对数。添加、移动和移除项目是对数的。这种方法最适合静态场景(即大多数物品都不会移动的场景)。NoIndex 没有应用索引。物品位置具有线性复杂性，因为场景中的所有物品都要搜索。然而，添加、移动和移除项目都是在恒定的时间内完成的。这种方法是理想的动态场景，许多项目被添加，移动或删除不断。

​		相关函数：

```c++
ItemIndexMethod itemIndexMethod() const;
void setItemIndexMethod(ItemIndexMethod method);
```

#### SceneLayer

​		此枚举描述QGraphicsScene中的呈现层。当QGraphicsScene绘制场景内容时，它按顺序分别渲染这些层。

```c++
enum SceneLayer {
        ItemLayer = 0x1,
        BackgroundLayer = 0x2,
        ForegroundLayer = 0x4,
        AllLayers = 0xffff
    };
```

​		ItemLayer 项目层。QGraphicsScene通过调用虚函数drawItems()来渲染这一层中的所有项目。项目层绘制在背景层之后，但在前景层之前。BackgroundLayer 背景层。QGraphicsScene通过调用虚函数drawBackground()在这个层中渲染场景的背景。背景层首先绘制所有层。ForegroundLayer 前景层。QGraphicsScene通过调用虚函数drawForeground()在这一层中渲染场景的前景。前景层是所有层中最后绘制的。AllLayers 所有层;该值表示所有三层的组合。

### 属性

**backgroundBrush**：这个属性保存场景的背景笔刷。

**bspTreeDepth**：这个属性保存QGraphicsScene的BSP索引树的深度，当使用NoIndex时，此属性无效。

**focusOnTouch**：这个属性保存当接收到一个触摸开始事件时物品是否获得焦点。

```c++
bool focusOnTouch() const
void setFocusOnTouch(bool enabled)
```

**font**：这个属性保存场景的默认字体

```c++
QFont font() const
void setFont(const QFont &font)
```

**foregroundBrush**：该属性保存场景的前景画笔。

```c++
QBrush foregroundBrush() const
void setForegroundBrush(const QBrush &brush)
```

**itemIndexMethod**：此属性保存项索引方法。

```c++
QGraphicsScene::ItemIndexMethod itemIndexMethod() const
void setItemIndexMethod(QGraphicsScene::ItemIndexMethod method)
```

**minimumRenderSize**：此属性保存一个项目必须绘制的最小视图转换大小

```c++
qreal minimumRenderSize() const
void setMinimumRenderSize(qreal minSize)
```

**palette**：这个属性保存场景的默认调色板

```c++
QPalette palette() const
void setPalette(const QPalette &palette)
```

**sceneRect**：这个属性保存场景矩形

```c++
QRectF sceneRect() const
void setSceneRect(const QRectF &rect)
void setSceneRect(qreal x, qreal y, qreal w, qreal h)
```

**stickyFocus**：这个属性保存单击进入场景背景是否会清除焦点

```c++
bool stickyFocus() const
void setStickyFocus(bool enabled)
```

## QGraphicsItem

​		它为编写您自己的定制项提供了一个轻量级的基础。这包括通过事件处理程序定义物品的几何形状、碰撞检测、绘画实现和物品交互。QGraphicsItem是图形视图框架的一部分

​		为了方便起见，Qt为最常见的形状提供了一组标准图形项。如下:

- QGraphicsEllipseItem 提供了一个椭圆
- QGraphicsLineItem 提供了一个行项目
- QGraphicsPathItem 提供了一个任意路径项
- QGraphicsPixmapItem 提供了一个pixmap项
- QGraphicsPolygonItem 提供了一个多边形项目
- QGraphicsRecItem 提供了一个矩形项
- QGraphicsSimpleTextItem 提供了一个简单的文本标签项
- QGraphicsTextItem 提供了一个高级文本浏览器项目



​		一个物品的所有几何信息都是基于它的局部坐标系统。项目的位置pos()是唯一不在局部坐标中操作的函数，因为它返回父坐标中的位置。图形视图坐标系统详细描述了坐标系统。
你可以通过调用setVisible()来设置一个项目是否可见(例如，绘制，接受事件)。隐藏一个项目也会隐藏它的子项目。类似地，您可以通过调用setEnabled()来启用或禁用一个项。如果禁用一个项目，它的所有子项目也将禁用。默认情况下，项目既可见又启用。要切换一个项目是否被选中，首先通过设置ItemIsSelectable标志来启用选择，然后调用setSelected()。通常情况下，作为用户交互的结果，选择由场景进行切换。
要编写自己的图形项，首先要创建QGraphicsItem的一个子类，然后首先实现它的两个纯虚拟公共函数:boundingRect()，它返回项目绘制区域的估计，以及paint()，它实现实际绘制。