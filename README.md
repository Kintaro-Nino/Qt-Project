# 主要功能
用户主要包括库存管理员和仓库操作员，可进行以下操作：

## 1.浏览产品列表
启动系统后，主界面显示当前所有产品列表，包括产品编号、名称、类别、库存数量、单价、供应商、入库时间、出库时间等信息。

![image](https://github.com/Kintaro-Nino/Qt-Project/blob/InventoryManagementSystem/images/image%20(1).png)

## 2.查询产品数据
在查询框中输入关键词（如产品名称、编号、类别等），点击“查询”按钮，系统将选中并高亮显示匹配的产品编号项。

![image](https://github.com/Kintaro-Nino/Qt-Project/blob/InventoryManagementSystem/images/image%20(2).png)

![image](https://github.com/Kintaro-Nino/Qt-Project/blob/InventoryManagementSystem/images/image%20(3).png)

## 3.添加产品数据
点击“添加数据”按钮，弹出产品信息录入窗口。填写产品编号、名称、类别、数量、单价、供应商编号后，点击“确定”即可保存至数据库并添加到产品列表。

![image](https://github.com/Kintaro-Nino/Qt-Project/blob/InventoryManagementSystem/images/image%20(4).png)

![image](https://github.com/Kintaro-Nino/Qt-Project/blob/InventoryManagementSystem/images/image%20(5).png)

![image](https://github.com/Kintaro-Nino/Qt-Project/blob/InventoryManagementSystem/images/image%20(6).png)

![image](https://github.com/Kintaro-Nino/Qt-Project/blob/InventoryManagementSystem/images/image%20(7).png)

## 4.删除产品数据
在列表中选择一行或多行产品数据的“产品编号”列，点击“删除数据”按钮，系统将提示是否确认删除所选记录，点击“确认”按钮后数据行将从数据库和列表中删除。

![image](https://github.com/Kintaro-Nino/Qt-Project/blob/InventoryManagementSystem/images/image%20(8).png)

![image](https://github.com/Kintaro-Nino/Qt-Project/blob/InventoryManagementSystem/images/image%20(9).png)

![image](https://github.com/Kintaro-Nino/Qt-Project/blob/InventoryManagementSystem/images/image%20(10).png)

## 5.产品入库
点击“入库”按钮，选择产品编号并输入入库数量，系统将更新库存数量并记录入库时间，同时更新到数据库和产品列表。

![image](https://github.com/Kintaro-Nino/Qt-Project/blob/InventoryManagementSystem/images/image%20(11).png)

![image](https://github.com/Kintaro-Nino/Qt-Project/blob/InventoryManagementSystem/images/image%20(12).png)

![image](https://github.com/Kintaro-Nino/Qt-Project/blob/InventoryManagementSystem/images/image%20(13).png)

![image](https://github.com/Kintaro-Nino/Qt-Project/blob/InventoryManagementSystem/images/image%20(14).png)

## 6.产品出库
点击“出库”按钮，选择产品编号并输入出库数量。若库存充足，则更新库存并记录出库时间，同时更新信息到数据库和产品列表，否则提示库存不足。

![image](https://github.com/Kintaro-Nino/Qt-Project/blob/InventoryManagementSystem/images/image%20(15).png)

![image](https://github.com/Kintaro-Nino/Qt-Project/blob/InventoryManagementSystem/images/image%20(16).png)

![image](https://github.com/Kintaro-Nino/Qt-Project/blob/InventoryManagementSystem/images/image%20(17).png)

![image](https://github.com/Kintaro-Nino/Qt-Project/blob/InventoryManagementSystem/images/image%20(18).png)

## 7.数据汇总与导出
点击“数据汇总”按钮，可查看按类别、总价、入库/出库记录的汇总表格。点击“导出数据”可将当前表格导出为 Excel 文件。

![image](https://github.com/Kintaro-Nino/Qt-Project/blob/InventoryManagementSystem/images/image%20(19).png)

![image](https://github.com/Kintaro-Nino/Qt-Project/blob/InventoryManagementSystem/images/image%20(20).png)

![image](https://github.com/Kintaro-Nino/Qt-Project/blob/InventoryManagementSystem/images/image%20(21).png)

![image](https://github.com/Kintaro-Nino/Qt-Project/blob/InventoryManagementSystem/images/image%20(22).png)

![image](https://github.com/Kintaro-Nino/Qt-Project/blob/InventoryManagementSystem/images/image%20(23).png)

数据备份：将总价汇总表导出为Excel文件

![image](https://github.com/Kintaro-Nino/Qt-Project/blob/InventoryManagementSystem/images/image%20(24).png)

![image](https://github.com/Kintaro-Nino/Qt-Project/blob/InventoryManagementSystem/images/image%20(25).png)

![image](https://github.com/Kintaro-Nino/Qt-Project/blob/InventoryManagementSystem/images/image%20(26).png)

桌面得到对应的导出产品数据，打开产品数据Excel文件得到的结果如下：

![image](https://github.com/Kintaro-Nino/Qt-Project/blob/InventoryManagementSystem/images/image%20(27).png)

![image](https://github.com/Kintaro-Nino/Qt-Project/blob/InventoryManagementSystem/images/image%20(28).png)

