#include "deliverproduct.h"

DeliverProduct::DeliverProduct(QWidget *parent)
    : QWidget{parent}
{
    this->setFixedSize(400,200);
    this->setWindowTitle("产品出库");
    productId=new QLabel("产品编号:");
    productIdBox=new QComboBox;

    deliverQuantity=new QLabel("出库数量:");
    deliverQuantityEdit=new QLineEdit;

    deliverButton=new QPushButton("出库");
    cancelButton=new QPushButton("取消");

    gLayout=new QGridLayout(this);
    hLayout=new QHBoxLayout;

    gLayout->addWidget(productId,0,0);
    gLayout->addWidget(productIdBox,0,1);
    gLayout->addWidget(deliverQuantity,1,0);
    gLayout->addWidget(deliverQuantityEdit,1,1);

    hLayout->addWidget(deliverButton);
    hLayout->addWidget(cancelButton);

    gLayout->addLayout(hLayout,2,0,1,2);

    productId->setStyleSheet("QLabel{font-size:13px;height:30px}");
    productIdBox->setStyleSheet("QComboBox{padding-left:5px;border-radius:5px;font-size:13px;height:30px;}");

    deliverQuantity->setStyleSheet("QLabel{font-size:13px;height:30px}");
    deliverQuantityEdit->setStyleSheet("QLineEdit{padding-left:5px;border-radius:5px;font-size:13px;height:30px;}");

    deliverButton->setStyleSheet("QPushButton{background-color:#2196F3;"
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

DeliverProduct::~DeliverProduct(){}
