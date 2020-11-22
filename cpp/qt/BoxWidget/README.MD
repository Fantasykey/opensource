# 接口介绍

## cboxwidget.h
> CHBoxWidget

| 接口             | 作用                    |
| ---------------- | ----------------------- |
| CHBoxWidget      | 建立子父窗口关系        |
| addSpacing       | 添加空白间隙            |
| addStretch       | 添加弹簧                |
| addSpacerItem    | 添加QSpacerItem         |
| addWidget        | 添加窗口部件            |
| addLayout        | 添加QLayout             |
| addStrut         | 添加垂直尺寸限制        |
| addItem          | 添加QLayoutItem         |
| insertSpacing    | 插入空白间隙            |
| insertStretch    | 插入弹簧                |
| insertSpacerItem | 插入QSpacerItem         |
| insertWidget     | 插入窗口部件            |
| insertLayout     | 插入QLayout             |
| insertItem       | 插入QLayoutItem         |
| spacing          | 返回固定空白间隙        |
| setSpacing       | 设置固定空白间隙        |
| setStretchFactor | 设置控件的伸缩权重      |
| setStretch       | 设置伸展权重            |
| stretch          | 返回部件的伸展权重      |
| itemAt           | 返回索引处的QLayoutItem |
| takeAt           | 移除并返回QLayoutItem   |
| count            | 返回部件个数            |

> CVBoxWidget

| 接口             | 作用                    |
| ---------------- | ----------------------- |
| CVBoxWidget      | 建立子父窗口关系        |
| addSpacing       | 添加空白间隙            |
| addStretch       | 添加弹簧                |
| addSpacerItem    | 添加QSpacerItem         |
| addWidget        | 添加窗口部件            |
| addLayout        | 添加QLayout             |
| addStrut         | 添加垂直尺寸限制        |
| addItem          | 添加QLayoutItem         |
| insertSpacing    | 插入空白间隙            |
| insertStretch    | 插入弹簧                |
| insertSpacerItem | 插入QSpacerItem         |
| insertWidget     | 插入窗口部件            |
| insertLayout     | 插入QLayout             |
| insertItem       | 插入QLayoutItem         |
| spacing          | 返回固定空白间隙        |
| setSpacing       | 设置固定空白间隙        |
| setStretchFactor | 设置控件的伸缩权重      |
| setStretch       | 设置伸展权重            |
| stretch          | 返回部件的伸展权重      |
| itemAt           | 返回索引处的QLayoutItem |
| takeAt           | 移除并返回QLayoutItem   |
| count            | 返回部件个数            |

> CGridBoxWidget

| 接口                  | 作用                          |
| --------------------- | ----------------------------- |
| CGridBoxWidget        | 建立子父窗口关系              |
| setHorizontalSpacing  | 设置水平方向的固定空白间隙    |
| horizontalSpacing     | 返回水平方向的固定空白间隙    |
| setVerticalSpacing    | 设置垂直方向的固定空白间隙    |
| verticalSpacing       | 返回垂直方向的固定空白间隙    |
| setSpacing            | 设置固定空白间隙              |
| spacing               | 返回固定空白间隙              |
| setRowStretch         | 设置某行伸展权重              |
| setColumnStretch      | 设置某列伸展权重              |
| rowStretch            | 返回某行伸展权重              |
| columnStretch         | 返回某列伸展权重              |
| setRowMinimumHeight   | 设置某行最小高度              |
| setColumnMinimumWidth | 设置某列最小宽度              |
| rowMinimumHeight      | 返回某行最小高度              |
| columnMinimumWidth    | 返回某列最小宽度              |
| columnCount           | 返回列数                      |
| rowCount              | 返回行数                      |
| cellRect              | 返回窗口尺寸                  |
| addWidget             | 添加窗口部件                  |
| addLayout             | 添加QLayout                   |
| setOriginCorner       | 设置原始方向                  |
| originCorner          | 返回方向                      |
| itemAt                | 返回索引处的QLayoutItem       |
| itemAtPosition        | 返回索引处的QLayoutItem的位置 |
| takeAt                | 移除并返回QLayoutItem         |
| count                 | 返回部件个数                  |
| addItem               | 添加QLayoutItem               |
