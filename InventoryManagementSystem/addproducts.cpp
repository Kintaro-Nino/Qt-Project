#include "addproducts.h"

AddProducts::AddProducts(QWidget *parent)
    : QWidget{parent}
{
    this->setWindowTitle("添加产品");
    this->setFixedSize(400,500);

    productId=new QLabel("产品编号:");
    productIdEdit=new QLineEdit;

    productName=new QLabel("产品名称:");
    productNameEdit =new QLineEdit;

    productCategory=new QLabel("产品种类:");
    productCategoryEdit=new QLineEdit;

    productQuantity=new QLabel("库存数量:");
    productQuantityEdit=new QLineEdit;

    productPrice=new QLabel("单价:");
    productPriceEdit=new QLineEdit;

    supplierId=new QLabel("供应商编号:");
    supplierIdEdit=new QLineEdit;

    addProductsButton=new QPushButton("确定");
    cancelButton=new QPushButton("取消");

    hLayout=new QHBoxLayout;
    hLayout->addWidget(addProductsButton);
    hLayout->addWidget(cancelButton);

    gLayout=new QGridLayout(this);
    gLayout->addWidget(productId,0,0);
    gLayout->addWidget(productIdEdit,0,1);
    gLayout->addWidget(productName,1,0);
    gLayout->addWidget(productNameEdit,1,1);
    gLayout->addWidget(productCategory,2,0);
    gLayout->addWidget(productCategoryEdit,2,1);
    gLayout->addWidget(productQuantity,3,0);
    gLayout->addWidget(productQuantityEdit,3,1);
    gLayout->addWidget(productPrice,4,0);
    gLayout->addWidget(productPriceEdit,4,1);
    gLayout->addWidget(supplierId,5,0);
    gLayout->addWidget(supplierIdEdit,5,1);
    gLayout->addLayout(hLayout,6,0,1,2);

    productId->setStyleSheet("QLabel{font-size:13px;height:30px}");
    productIdEdit->setStyleSheet("QLineEdit{padding-left:5px;border-radius:5px;font-size:13px;height:30px;}");

    productName->setStyleSheet("QLabel{font-size:13px;height:30px}");
    productNameEdit->setStyleSheet("QLineEdit{padding-left:5px;border-radius:5px;font-size:13px;height:30px;}");

    productCategory->setStyleSheet("QLabel{font-size:13px;height:30px}");
    productCategoryEdit->setStyleSheet("QLineEdit{padding-left:5px;border-radius:5px;font-size:13px;height:30px;}");

    productQuantity->setStyleSheet("QLabel{font-size:13px;height:30px}");
    productQuantityEdit->setStyleSheet("QLineEdit{padding-left:5px;border-radius:5px;font-size:13px;height:30px;}");

    productPrice->setStyleSheet("QLabel{font-size:13px;height:30px}");
    productPriceEdit->setStyleSheet("QLineEdit{padding-left:5px;border-radius:5px;font-size:13px;height:30px;}");

    supplierId->setStyleSheet("QLabel{font-size:13px;height:30px}");
    supplierIdEdit->setStyleSheet("QLineEdit{padding-left:5px;border-radius:5px;font-size:13px;height:30px;}");

    addProductsButton->setStyleSheet("QPushButton{background-color:#2196F3;"
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

AddProducts::~AddProducts(){}
