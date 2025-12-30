#include "warehouseproduct.h"

WarehouseProduct::WarehouseProduct(QWidget *parent)
    : QWidget{parent}
{
    this->setFixedSize(400,200);
    this->setWindowTitle("产品入库");
    productId=new QLabel("产品编号:");
    productIdBox=new QComboBox;

    warehouseQuantity=new QLabel("入库数量:");
    warehouseQuantityEdit=new QLineEdit;

    warehouseButton=new QPushButton("入库");
    cancelButton=new QPushButton("取消");

    gLayout=new QGridLayout(this);
    hLayout=new QHBoxLayout;

    gLayout->addWidget(productId,0,0);
    gLayout->addWidget(productIdBox,0,1);
    gLayout->addWidget(warehouseQuantity,1,0);
    gLayout->addWidget(warehouseQuantityEdit,1,1);

    hLayout->addWidget(warehouseButton);
    hLayout->addWidget(cancelButton);

    gLayout->addLayout(hLayout,2,0,1,2);

    productId->setStyleSheet("QLabel{font-size:13px;height:30px}");
    productIdBox->setStyleSheet("QComboBox{padding-left:5px;border-radius:5px;font-size:13px;height:30px;}");

    warehouseQuantity->setStyleSheet("QLabel{font-size:13px;height:30px}");
    warehouseQuantityEdit->setStyleSheet("QLineEdit{padding-left:5px;border-radius:5px;font-size:13px;height:30px;}");

    warehouseButton->setStyleSheet("QPushButton{background-color:#2196F3;"
                                   "color:white;"
                                   "border:none;"
                                   "border-radius:5px;"
                                   "font-size:13px;"
                                   "font-weight:bold;"
                                   "min-height:30px}"
                                   "QPushButton:pressed{background-color:#1565C0}");
    cancelButton->setStyleSheet("QPushButton{background-color:#2196F3;"
                                "color:white;"
                                "border:none;"
                                "border-radius:5px;"
                                "font-size:13px;"
                                "font-weight:bold;"
                                "min-height:30px}"
                                "QPushButton:pressed{background-color:#1565C0}");
}

WarehouseProduct::~WarehouseProduct(){}
