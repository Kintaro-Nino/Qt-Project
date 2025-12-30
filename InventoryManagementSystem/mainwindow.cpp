#include "mainwindow.h"
using namespace QXlsx;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(900,500);
    this->setWindowIcon(QIcon(":/Image/icon.png"));
    this->setWindowTitle("QtODBC 库存管理系统");
    QWidget *centralWidget=new QWidget(this);
    this->setCentralWidget(centralWidget);

    connectDatabase();
    InventoryManagementSystemInit();

    vLayout=new QVBoxLayout(centralWidget);
    vLayout->addLayout(gLayout);
    vLayout->addWidget(productsTable);

    product=new AddProducts(this);
    product->setWindowFlags(Qt::Dialog);
    connect(addDataButton,&QPushButton::clicked,product,[=](){
        product->productIdEdit->clear();
        product->productNameEdit->clear();
        product->productCategoryEdit->clear();
        product->productQuantityEdit->clear();
        product->productPriceEdit->clear();
        product->supplierIdEdit->clear();
        product->show();
    });
    connect(product->addProductsButton,&QPushButton::clicked,this,[=](){
        onAddProductsClicked();
        product->close();
    });
    connect(product->cancelButton,&QPushButton::clicked,this,[=](){
        product->close();
    });

    warehouseProduct=new WarehouseProduct(this);
    warehouseProduct->setWindowFlags(Qt::Dialog);
    connect(warehouseButton,&QPushButton::clicked,warehouseProduct,[=](){
        warehouseProduct->productIdBox->clear();
        warehouseProduct->warehouseQuantityEdit->clear();
        for(int i=0;i<productsTable->rowCount();i++){
            warehouseProduct->productIdBox->addItem(productsTable->item(i,0)->text());
        }
        warehouseProduct->show();
    });
    connect(warehouseProduct->warehouseButton,&QPushButton::clicked,this,[=](){
        onWarehouseClicked();
        warehouseProduct->close();
    });
    connect(warehouseProduct->cancelButton,&QPushButton::clicked,this,[=](){
        warehouseProduct->close();
    });

    deliverProduct=new DeliverProduct(this);
    deliverProduct->setWindowFlags(Qt::Dialog);
    connect(deliverButton,&QPushButton::clicked,deliverProduct,[=](){
        deliverProduct->productIdBox->clear();
        deliverProduct->deliverQuantityEdit->clear();
        for(int i=0;i<productsTable->rowCount();i++){
            deliverProduct->productIdBox->addItem(productsTable->item(i,0)->text());
        }
        deliverProduct->show();
    });
    connect(deliverProduct->deliverButton,&QPushButton::clicked,this,[=](){
        onDeliverClicked();
        deliverProduct->close();
    });
    connect(deliverProduct->cancelButton,&QPushButton::clicked,this,[=](){
        deliverProduct->close();
    });

    summaryProduct=new SummaryProducts(this);
    summaryProduct->setWindowFlags(Qt::Dialog);
    connect(summaryButton,&QPushButton::clicked,this,[=](){
        summaryProduct->show();
    });
    connect(summaryProduct->categorySummaryButton,&QPushButton::clicked,this,&MainWindow::onCategorySummaryClicked);
    connect(summaryProduct->totalPriceSummaryButton,&QPushButton::clicked,this,&MainWindow::onTotalPriceSummaryClicked);
    connect(summaryProduct->warehouseSummaryButton,&QPushButton::clicked,this,[=](){
        warehouseDeliverSummary(summaryProduct->warehouseSummaryTable);
    });
    connect(summaryProduct->deliverSummaryButton,&QPushButton::clicked,this,[=](){
        warehouseDeliverSummary(summaryProduct->deliverSummaryTable);
    });
    connect(summaryProduct->exportSummaryButton,&QPushButton::clicked,this,[=](){
        exportData(summaryProduct->summaryTable);
    });

}

MainWindow::~MainWindow() {}

void MainWindow::connectDatabase(){
    QSqlDatabase database=QSqlDatabase::addDatabase("QODBC");
    database.setHostName("127.0.0.1");
    database.setPort(3306);
    database.setDatabaseName("InventoryDatabase");  //数据库名和密码错误会导致无法打开数据库
    database.setPassword("123456");

    if(!database.open()){
        QMessageBox::critical(this,"错误","数据库打开失败！");
        return;
    }
}

void MainWindow::InventoryManagementSystemInit(){
    //初始化控件
    queryLabel=new QLabel("数据查询:");
    queryEdit=new QLineEdit;

    queryDataButton=new QPushButton("查询");
    connect(queryDataButton,&QPushButton::clicked,this,&MainWindow::onQueryDataClicked);

    addDataButton=new QPushButton("添加数据");

    deleteDataButton=new QPushButton("删除数据");
    connect(deleteDataButton,&QPushButton::clicked,this,&MainWindow::onDeleteDataClicked);

    warehouseButton=new QPushButton("入库");

    deliverButton=new QPushButton("出库");

    exportButton=new QPushButton("导出数据");
    connect(exportButton,&QPushButton::clicked,this,[=](){
        exportData(productsTable);
    });

    summaryButton=new QPushButton("数据汇总");

    updateButton=new QPushButton("刷新数据");
    connect(updateButton,&QPushButton::clicked,this,&MainWindow::updateTable);

    hLayout=new QHBoxLayout;
    hLayout->addWidget(queryLabel);
    hLayout->addWidget(queryEdit);
    hLayout->addWidget(queryDataButton);

    gLayout=new QGridLayout;
    gLayout->addLayout(hLayout,0,7,1,3);
    gLayout->addWidget(addDataButton);
    gLayout->addWidget(deleteDataButton);
    gLayout->addWidget(warehouseButton);
    gLayout->addWidget(deliverButton);
    gLayout->addWidget(exportButton);
    gLayout->addWidget(summaryButton);
    gLayout->addWidget(updateButton);

    productsTable=new QTableWidget;
    //设置控件样式
    queryLabel->setStyleSheet("QLabel{font-size:13px;width:50px;height:30px}");
    queryEdit->setStyleSheet("QLineEdit{padding-left:5px;border-radius:5px;font-size:13px;width:200px;height:30px;}");
    queryDataButton->setStyleSheet("QPushButton{background-color:#2196F3;"
                                   "color:white;"
                                   "border:none;"
                                   "border-radius:5px;"
                                   "font-size:13px;"
                                   "font-weight:bold;"
                                   "min-width:70px;"
                                   "min-height:30px}"
                                   "QPushButton:pressed{background-color:#1565C0}");
    addDataButton->setStyleSheet("QPushButton{background-color:#2196F3;"
                                 "color:white;"
                                 "border:none;"
                                 "border-radius:5px;"
                                 "font-size:13px;"
                                 "font-weight:bold;"
                                 "min-width:70px;"
                                 "min-height:30px}"
                                 "QPushButton:pressed{background-color:#1565C0}");
    deleteDataButton->setStyleSheet("QPushButton{background-color:#2196F3;"
                                    "color:white;"
                                    "border:none;"
                                    "border-radius:5px;"
                                    "font-size:13px;"
                                    "font-weight:bold;"
                                    "min-width:70px;"
                                    "min-height:30px}"
                                    "QPushButton:pressed{background-color:#1565C0}");
    warehouseButton->setStyleSheet("QPushButton{background-color:#2196F3;"
                                   "color:white;"
                                   "border:none;"
                                   "border-radius:5px;"
                                   "font-size:13px;"
                                   "font-weight:bold;"
                                   "min-width:70px;"
                                   "min-height:30px}"
                                   "QPushButton:pressed{background-color:#1565C0}");
    deliverButton->setStyleSheet("QPushButton{background-color:#2196F3;"
                                 "color:white;"
                                 "border:none;"
                                 "border-radius:5px;"
                                 "font-size:13px;"
                                 "font-weight:bold;"
                                 "min-width:70px;"
                                 "min-height:30px}"
                                 "QPushButton:pressed{background-color:#1565C0}");
    exportButton->setStyleSheet("QPushButton{background-color:#2196F3;"
                                "color:white;"
                                "border:none;"
                                "border-radius:5px;"
                                "font-size:13px;"
                                "font-weight:bold;"
                                "min-width:70px;"
                                "min-height:30px}"
                                "QPushButton:pressed{background-color:#1565C0}");
    summaryButton->setStyleSheet("QPushButton{background-color:#2196F3;"
                                 "color:white;"
                                 "border:none;"
                                 "border-radius:5px;"
                                 "font-size:13px;"
                                 "font-weight:bold;"
                                 "min-width:70px;"
                                 "min-height:30px}"
                                 "QPushButton:pressed{background-color:#1565C0}");
    updateButton->setStyleSheet("QPushButton{background-color:#2196F3;"
                                "color:white;"
                                "border:none;"
                                "border-radius:5px;"
                                "font-size:13px;"
                                "font-weight:bold;"
                                "min-width:70px;"
                                "min-height:30px}"
                                "QPushButton:pressed{background-color:#1565C0}");

    //初始化产品表
    QStringList productList;
    productList << "产品编号" << "产品名称" << "产品种类" << "库存数量" << "单价" << "供应商编号" << "入库时间" << "出库时间";
    productsTable->setColumnCount(8);
    productsTable->setColumnWidth(1,130);
    productsTable->setColumnWidth(6,160);
    productsTable->setColumnWidth(7,160);
    productsTable->setHorizontalHeaderLabels(productList);

    QSqlQuery sqlQuery;
    sqlQuery.exec("CREATE TABLE products ("
                  "product_id INTEGER PRIMARY KEY AUTO_INCREMENT,"
                  "product_name TEXT NOT NULL,"
                  "category TEXT,"
                  "quantity INTEGER DEFAULT 0,"
                  "price REAL DEFAULT 0.0,"
                  "supplier_id TEXT,"
                  "warehouse_time DATETIME DEFAULT CURRENT_TIMESTAMP,"
                  "delivery_time DATETIME)");

    updateTable();
}

//具体功能实现
void MainWindow::onQueryDataClicked(){
    QString keyword=queryEdit->text();
    if(keyword.isEmpty()) return;

    QSqlQuery sqlQuery;
    sqlQuery.prepare(
        "SELECT product_id FROM products WHERE "
        "product_id LIKE :keyword OR "
        "product_name LIKE :keyword OR "
        "category LIKE :keyword OR "
        "quantity LIKE :keyword OR "
        "price LIKE :keyword OR "
        "supplier_id LIKE :keyword OR "
        "warehouse_time LIKE :keyword OR "
        "delivery_time LIKE :keyword"
        );
    sqlQuery.bindValue(":keyword","%" + keyword + "%");

    if(!sqlQuery.exec()){
        QMessageBox::critical(this,"数据库查询错误",sqlQuery.lastError().text());
        return;
    }

    //重置选中状态
    for(int i=0;i<productsTable->rowCount();i++){
        QTableWidgetItem *allItem=productsTable->item(i,0);
        allItem->setSelected(false);
    }

    if(!sqlQuery.next()){
        QMessageBox::warning(this,"提示","未查询到符合要求的数据!");
        return;
    }
    else{
        //将查询到的符合要求的数据行第一列选中
        int queryIndex=queryList.indexOf(sqlQuery.value(0).toString());
        productsTable->item(queryIndex,0)->setSelected(true);
        while(sqlQuery.next()){
            queryIndex=queryList.indexOf(sqlQuery.value(0).toString());
            productsTable->item(queryIndex,0)->setSelected(true);
        }
    }
}

void MainWindow::onAddProductsClicked(){
    QSqlQuery sqlQuery;
    sqlQuery.prepare("INSERT INTO products (product_id, product_name, category, quantity, price, supplier_id)"
                  "VALUES(:product_id, :product_name, :category, :quantity, :price, :supplier_id)");

    sqlQuery.bindValue(":product_id",product->productIdEdit->text().toInt());
    sqlQuery.bindValue(":product_name",product->productNameEdit->text());
    sqlQuery.bindValue(":category",product->productCategoryEdit->text());
    sqlQuery.bindValue(":quantity",product->productQuantityEdit->text().toInt());
    sqlQuery.bindValue(":price",product->productPriceEdit->text().toDouble());
    sqlQuery.bindValue(":supplier_id",product->supplierIdEdit->text());

    if(!sqlQuery.exec()){
        QMessageBox::critical(this,"数据库插入数据失败",sqlQuery.lastError().text());
        return;
    }

    sqlQuery.prepare("SELECT * FROM products WHERE product_id=:product_id");
    sqlQuery.bindValue(":product_id",product->productIdEdit->text().toInt());

    if(!sqlQuery.exec()){
        QMessageBox::critical(this,"数据库查询失败",sqlQuery.lastError().text());
        return;
    }

    sqlQuery.next();
    productsTable->insertRow(productsTable->rowCount());
    queryList<<sqlQuery.value(0).toString();

    productsTable->setItem(productsTable->rowCount()-1,0,new QTableWidgetItem(sqlQuery.value(0).toString()));
    Qt::ItemFlags flags = productsTable->item(productsTable->rowCount()-1,0)->flags();
    flags &= ~Qt::ItemIsEditable;
    productsTable->item(productsTable->rowCount()-1,0)->setFlags(flags);

    productsTable->setItem(productsTable->rowCount()-1,1,new QTableWidgetItem(sqlQuery.value(1).toString()));
    productsTable->setItem(productsTable->rowCount()-1,2,new QTableWidgetItem(sqlQuery.value(2).toString()));
    productsTable->setItem(productsTable->rowCount()-1,3,new QTableWidgetItem(sqlQuery.value(3).toString()));
    productsTable->setItem(productsTable->rowCount()-1,4,new QTableWidgetItem(sqlQuery.value(4).toString()));
    productsTable->setItem(productsTable->rowCount()-1,5,new QTableWidgetItem(sqlQuery.value(5).toString()));
    productsTable->setItem(productsTable->rowCount()-1,6,new QTableWidgetItem(sqlQuery.value(6).toString().replace(QRegularExpression(R"(T|\.\d+$)"), " ")));
    productsTable->setItem(productsTable->rowCount()-1,7,new QTableWidgetItem(sqlQuery.value(7).toString().replace(QRegularExpression(R"(T|\.\d+$)"), " ")));
}

void MainWindow::onDeleteDataClicked(){
    QSqlQuery sqlQuery;
    QTableWidgetItem *item;

    for(int i=productsTable->rowCount()-1;i>=0;i--){
        item=productsTable->item(i,0);
        if(item->isSelected()) {
            QMessageBox::StandardButton btn=QMessageBox::information(this,"删除数据","是否删除数据行?",QMessageBox::Ok|QMessageBox::Cancel);
            if(btn==QMessageBox::Cancel) return;
            sqlQuery.prepare("DELETE FROM products WHERE product_id=:product_id");
            sqlQuery.bindValue(":product_id",item->text().toInt());
            if(!sqlQuery.exec()){
                QMessageBox::critical(this,"数据库数据删除错误",sqlQuery.lastError().text());
                return;
            }
            queryList.removeAll(item->text());
            productsTable->removeRow(i);
        }
    }
}

void MainWindow::onWarehouseClicked(){
    if(warehouseProduct->warehouseQuantityEdit->text().isEmpty()) return;
    int productId,productQuantity;
    productId=warehouseProduct->productIdBox->currentText().toInt();
    productQuantity=warehouseProduct->warehouseQuantityEdit->text().toInt();

    QSqlQuery sqlQuery;
    sqlQuery.prepare("UPDATE products SET quantity=quantity+:quantity, warehouse_time=CURRENT_TIMESTAMP WHERE product_id=:product_id");
    sqlQuery.bindValue(":quantity",productQuantity);
    sqlQuery.bindValue(":product_id",productId);

    if(!sqlQuery.exec()){
        QMessageBox::critical(this,"数据库数据更新错误",sqlQuery.lastError().text());
        return;
    }

    sqlQuery.prepare("SELECT product_id, product_name, category, quantity, price, supplier_id, warehouse_time FROM products WHERE product_id=:product_id");
    sqlQuery.bindValue(":product_id",productId);

    if(!sqlQuery.exec()){
        QMessageBox::critical(this,"数据库查询错误",sqlQuery.lastError().text());
        return;
    }

    sqlQuery.next();
    productsTable->item(queryList.indexOf(warehouseProduct->productIdBox->currentText()),3)->setText(sqlQuery.value(3).toString());
    productsTable->item(queryList.indexOf(warehouseProduct->productIdBox->currentText()),6)->setText(sqlQuery.value(6).toString().replace(QRegularExpression(R"(T|\.\d+$)"), " "));

    static int warehouseTableRow=0;
    summaryProduct->warehouseSummaryTable->setRowCount(warehouseTableRow+1);
    summaryProduct->warehouseSummaryTable->setItem(warehouseTableRow,0,new QTableWidgetItem(sqlQuery.value(0).toString()));
    summaryProduct->warehouseSummaryTable->setItem(warehouseTableRow,1,new QTableWidgetItem(sqlQuery.value(1).toString()));
    summaryProduct->warehouseSummaryTable->setItem(warehouseTableRow,2,new QTableWidgetItem(sqlQuery.value(2).toString()));
    summaryProduct->warehouseSummaryTable->setItem(warehouseTableRow,3,new QTableWidgetItem(sqlQuery.value(3).toString()));
    summaryProduct->warehouseSummaryTable->setItem(warehouseTableRow,4,new QTableWidgetItem(sqlQuery.value(4).toString()));
    summaryProduct->warehouseSummaryTable->setItem(warehouseTableRow,5,new QTableWidgetItem(sqlQuery.value(5).toString()));
    summaryProduct->warehouseSummaryTable->setItem(warehouseTableRow,6,new QTableWidgetItem(warehouseProduct->warehouseQuantityEdit->text()));
    summaryProduct->warehouseSummaryTable->setItem(warehouseTableRow,7,new QTableWidgetItem(sqlQuery.value(6).toString().replace(QRegularExpression(R"(T|\.\d+$)"), " ")));
    warehouseTableRow++;
}

void MainWindow::onDeliverClicked(){
    if(deliverProduct->deliverQuantityEdit->text().isEmpty()) return;
    int productId,productQuantity;
    productId=deliverProduct->productIdBox->currentText().toInt();
    productQuantity=deliverProduct->deliverQuantityEdit->text().toInt();

    if(productQuantity>productsTable->item(queryList.indexOf(deliverProduct->productIdBox->currentText()),3)->text().toInt()){
        QMessageBox::warning(this,"警告","库存数量不足！");
        return;
    }

    QSqlQuery sqlQuery;
    sqlQuery.prepare("UPDATE products SET quantity=quantity-:quantity, delivery_time=CURRENT_TIMESTAMP WHERE product_id=:product_id");
    sqlQuery.bindValue(":quantity",productQuantity);
    sqlQuery.bindValue(":product_id",productId);

    if(!sqlQuery.exec()){
        QMessageBox::critical(this,"数据库数据更新错误",sqlQuery.lastError().text());
        return;
    }

    sqlQuery.prepare("SELECT product_id, product_name, category, quantity, price, supplier_id, delivery_time FROM products WHERE product_id=:product_id");
    sqlQuery.bindValue(":product_id",productId);

    if(!sqlQuery.exec()){
        QMessageBox::critical(this,"数据库查询错误",sqlQuery.lastError().text());
        return;
    }

    sqlQuery.next();
    productsTable->item(queryList.indexOf(deliverProduct->productIdBox->currentText()),3)->setText(sqlQuery.value(3).toString());
    productsTable->item(queryList.indexOf(deliverProduct->productIdBox->currentText()),7)->setText(sqlQuery.value(6).toString().replace(QRegularExpression(R"(T|\.\d+$)"), " "));

    static int deliverTableRow=0;
    summaryProduct->deliverSummaryTable->setRowCount(deliverTableRow+1);
    summaryProduct->deliverSummaryTable->setItem(deliverTableRow,0,new QTableWidgetItem(sqlQuery.value(0).toString()));
    summaryProduct->deliverSummaryTable->setItem(deliverTableRow,1,new QTableWidgetItem(sqlQuery.value(1).toString()));
    summaryProduct->deliverSummaryTable->setItem(deliverTableRow,2,new QTableWidgetItem(sqlQuery.value(2).toString()));
    summaryProduct->deliverSummaryTable->setItem(deliverTableRow,3,new QTableWidgetItem(sqlQuery.value(3).toString()));
    summaryProduct->deliverSummaryTable->setItem(deliverTableRow,4,new QTableWidgetItem(sqlQuery.value(4).toString()));
    summaryProduct->deliverSummaryTable->setItem(deliverTableRow,5,new QTableWidgetItem(sqlQuery.value(5).toString()));
    summaryProduct->deliverSummaryTable->setItem(deliverTableRow,6,new QTableWidgetItem(deliverProduct->deliverQuantityEdit->text()));
    summaryProduct->deliverSummaryTable->setItem(deliverTableRow,7,new QTableWidgetItem(sqlQuery.value(6).toString().replace(QRegularExpression(R"(T|\.\d+$)"), " ")));
    deliverTableRow++;
}

void MainWindow::exportData(QTableWidget *table){
    if(table->rowCount()==0||table==nullptr){
        QMessageBox::warning(this,"警告","无可导出的数据！");
        return;
    }

    QString fileName=QFileDialog::getSaveFileName(table,"导出数据","产品数据","Excel文件(*.xlsx)");

    Format headerFormat;
    headerFormat.setFontSize(13);
    headerFormat.setHorizontalAlignment(QXlsx::Format::AlignHCenter);

    Format dataFormat;
    dataFormat.setFontSize(13);
    dataFormat.setHorizontalAlignment(QXlsx::Format::AlignHCenter);

    Document xlsx;
    for(int i=0;i<table->columnCount();i++){
        xlsx.write(1,i+1,table->horizontalHeaderItem(i)->text(),headerFormat);
    }

    for(int i=0;i<table->rowCount();i++){
        for(int j=0;j<table->columnCount();j++){
            QVariant data = table->item(i,j)->data(Qt::DisplayRole);
            if(data.typeId()==QMetaType::Int){
                xlsx.write(i+2,j+1,data.toInt(),dataFormat);
            }
            else if(data.typeId()==QMetaType::Double){
                xlsx.write(i+2,j+1,data.toDouble(),dataFormat);
            }
            else{
                xlsx.write(i+2,j+1,table->item(i,j)->text(),dataFormat);
            }
        }
    }

    xlsx.currentWorksheet()->setColumnWidth(1,table->columnCount(),25.0);

    if(xlsx.saveAs(fileName)){
        QMessageBox::information(this,"成功","导出数据保存成功！");
        return;
    }
}

void MainWindow::updateTable(){
    QSqlQuery sqlQuery;
    sqlQuery.exec("SELECT *FROM products ORDER BY product_id");

    for(int i=0;sqlQuery.next();i++){
        productsTable->setRowCount(i+1);
        queryList<<sqlQuery.value(0).toString();

        productsTable->setItem(i,0,new QTableWidgetItem(sqlQuery.value(0).toString()));
        Qt::ItemFlags flags = productsTable->item(i,0)->flags();
        flags &= ~Qt::ItemIsEditable;  // 清除编辑标志
        productsTable->item(i,0)->setFlags(flags);

        productsTable->setItem(i,1,new QTableWidgetItem(sqlQuery.value(1).toString()));
        productsTable->setItem(i,2,new QTableWidgetItem(sqlQuery.value(2).toString()));
        productsTable->setItem(i,3,new QTableWidgetItem(sqlQuery.value(3).toString()));
        productsTable->setItem(i,4,new QTableWidgetItem(sqlQuery.value(4).toString()));
        productsTable->setItem(i,5,new QTableWidgetItem(sqlQuery.value(5).toString()));
        //使用正则表达式处理数据库与Qt时间精度问题
        productsTable->setItem(i,6,new QTableWidgetItem(sqlQuery.value(6).toString().replace(QRegularExpression(R"(T|\.\d+$)"), " ")));
        productsTable->setItem(i,7,new QTableWidgetItem(sqlQuery.value(7).toString().replace(QRegularExpression(R"(T|\.\d+$)"), " ")));
    }
}

void MainWindow::onCategorySummaryClicked(){
    QSqlQuery sqlQuery;
    if(!sqlQuery.exec("SELECT category,COUNT(*) AS total_count FROM products GROUP BY category")){
        QMessageBox::critical(this,"数据库查询错误",sqlQuery.lastError().text());
        return;
    }

    summaryProduct->summaryTable->clear();
    summaryProduct->summaryTable->setRowCount(0);
    summaryProduct->summaryTable->setColumnCount(0);
    QStringList headerList;
    headerList<<"产品种类"<<"库存数量";
    summaryProduct->summaryTable->setColumnCount(2);
    summaryProduct->summaryTable->setHorizontalHeaderLabels(headerList);

    for(int i=0;sqlQuery.next();i++){
        summaryProduct->summaryTable->setRowCount(i+1);
        summaryProduct->summaryTable->setItem(i,0,new QTableWidgetItem(sqlQuery.value(0).toString()));
        summaryProduct->summaryTable->setItem(i,1,new QTableWidgetItem(sqlQuery.value(1).toString()));
    }


}

void MainWindow::onTotalPriceSummaryClicked(){
    QSqlQuery sqlQuery;
    if(!sqlQuery.exec("SELECT product_id, product_name, category, quantity, price, quantity*price AS total_price, supplier_id, warehouse_time, delivery_time FROM products")){
        QMessageBox::critical(this,"数据库查询错误",sqlQuery.lastError().text());
        return;
    }

    summaryProduct->summaryTable->clear();
    summaryProduct->summaryTable->setRowCount(0);
    summaryProduct->summaryTable->setColumnCount(0);
    QStringList headerList;
    headerList<<"产品编号" << "产品名称" << "产品种类" << "库存数量" << "单价" <<"产品总价"<< "供应商编号" << "入库时间" << "出库时间";
    summaryProduct->summaryTable->setColumnCount(9);
    summaryProduct->summaryTable->setColumnWidth(1,130);
    summaryProduct->summaryTable->setColumnWidth(7,160);
    summaryProduct->summaryTable->setColumnWidth(8,160);
    summaryProduct->summaryTable->setHorizontalHeaderLabels(headerList);

    for(int i=0;sqlQuery.next();i++){
        summaryProduct->summaryTable->setRowCount(i+1);

        summaryProduct->summaryTable->setItem(i,0,new QTableWidgetItem(sqlQuery.value(0).toString()));
        Qt::ItemFlags flags = summaryProduct->summaryTable->item(i,0)->flags();
        flags &= ~Qt::ItemIsEditable;
        summaryProduct->summaryTable->item(i,0)->setFlags(flags);

        summaryProduct->summaryTable->setItem(i,1,new QTableWidgetItem(sqlQuery.value(1).toString()));
        summaryProduct->summaryTable->setItem(i,2,new QTableWidgetItem(sqlQuery.value(2).toString()));
        summaryProduct->summaryTable->setItem(i,3,new QTableWidgetItem(sqlQuery.value(3).toString()));
        summaryProduct->summaryTable->setItem(i,4,new QTableWidgetItem(sqlQuery.value(4).toString()));
        summaryProduct->summaryTable->setItem(i,5,new QTableWidgetItem(sqlQuery.value(5).toString()));
        summaryProduct->summaryTable->setItem(i,6,new QTableWidgetItem(sqlQuery.value(6).toString()));
        summaryProduct->summaryTable->setItem(i,7,new QTableWidgetItem(sqlQuery.value(7).toString().replace(QRegularExpression(R"(T|\.\d+$)"), " ")));
        summaryProduct->summaryTable->setItem(i,8,new QTableWidgetItem(sqlQuery.value(8).toString().replace(QRegularExpression(R"(T|\.\d+$)"), " ")));
    }
}

void MainWindow::warehouseDeliverSummary(QTableWidget *table){
    summaryProduct->summaryTable->clear();
    summaryProduct->summaryTable->setRowCount(0);
    summaryProduct->summaryTable->setColumnCount(0);
    QStringList headerList;
    if(table==summaryProduct->warehouseSummaryTable){
        headerList<<"产品编号" << "产品名称" << "产品种类" << "库存数量" << "单价" << "供应商编号" << "入库数量" << "入库时间";
    }
    else{
        headerList<<"产品编号" << "产品名称" << "产品种类" << "库存数量" << "单价" << "供应商编号" << "出库数量" << "出库时间";
    }
    summaryProduct->summaryTable->setColumnCount(8);
    summaryProduct->summaryTable->setColumnWidth(1,130);
    summaryProduct->summaryTable->setColumnWidth(7,160);
    summaryProduct->summaryTable->setHorizontalHeaderLabels(headerList);

    for(int i=0;i<table->rowCount();i++){
        summaryProduct->summaryTable->setRowCount(i+1);

        summaryProduct->summaryTable->setItem(i,0,new QTableWidgetItem(table->item(i,0)->text()));
        Qt::ItemFlags flags = summaryProduct->summaryTable->item(i,0)->flags();
        flags &= ~Qt::ItemIsEditable;
        summaryProduct->summaryTable->item(i,0)->setFlags(flags);

        summaryProduct->summaryTable->setItem(i,1,new QTableWidgetItem(table->item(i,1)->text()));
        summaryProduct->summaryTable->setItem(i,2,new QTableWidgetItem(table->item(i,2)->text()));
        summaryProduct->summaryTable->setItem(i,3,new QTableWidgetItem(table->item(i,3)->text()));
        summaryProduct->summaryTable->setItem(i,4,new QTableWidgetItem(table->item(i,4)->text()));
        summaryProduct->summaryTable->setItem(i,5,new QTableWidgetItem(table->item(i,5)->text()));
        summaryProduct->summaryTable->setItem(i,6,new QTableWidgetItem(table->item(i,6)->text()));
        summaryProduct->summaryTable->setItem(i,7,new QTableWidgetItem(table->item(i,7)->text()));
    }
}
