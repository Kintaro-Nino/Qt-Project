#include "summaryproducts.h"

SummaryProducts::SummaryProducts(QWidget *parent)
    : QWidget{parent}
{
    this->resize(800,450);
    this->setWindowTitle("产品汇总");

    summaryTable=new QTableWidget;
    summaryLabel=new QLabel;
    warehouseSummaryTable=new QTableWidget;
    deliverSummaryTable=new QTableWidget;
    categorySummaryButton=new QPushButton("种类汇总");
    totalPriceSummaryButton=new QPushButton("总价汇总");
    warehouseSummaryButton=new QPushButton("入库汇总");
    deliverSummaryButton=new QPushButton("出库汇总");
    exportSummaryButton=new QPushButton("数据备份");

    gLayout=new QGridLayout;
    gLayout->addWidget(summaryLabel,0,0,1,4);
    gLayout->addWidget(categorySummaryButton,1,4);
    gLayout->addWidget(totalPriceSummaryButton,1,5);
    gLayout->addWidget(warehouseSummaryButton,1,6);
    gLayout->addWidget(deliverSummaryButton,1,7);
    gLayout->addWidget(exportSummaryButton,1,8);

    vLayout=new QVBoxLayout(this);
    vLayout->addLayout(gLayout);
    vLayout->addWidget(summaryTable);

    QStringList warehouseHeaderList;
    warehouseHeaderList<<"产品编号" << "产品名称" << "产品种类" << "库存数量" << "单价" << "供应商编号" << "入库数量" << "入库时间";
    warehouseSummaryTable->setColumnCount(8);
    warehouseSummaryTable->setHorizontalHeaderLabels(warehouseHeaderList);

    QStringList deliverHeaderList;
    deliverHeaderList<<"产品编号" << "产品名称" << "产品种类" << "库存数量" << "单价" << "供应商编号" << "出库数量" << "出库时间";
    deliverSummaryTable->setColumnCount(8);
    deliverSummaryTable->setHorizontalHeaderLabels(deliverHeaderList);

    summaryLabel->setFixedSize(150,35);
    summaryLabel->setPixmap(QPixmap(":/Image/summary.png").scaled(summaryLabel->size()));
    categorySummaryButton->setStyleSheet("QPushButton{background-color:#2196F3;"
                                   "color:white;"
                                   "border:none;"
                                   "border-radius:5px;"
                                   "font-size:13px;"
                                   "font-weight:bold;"
                                   "min-height:30px}"
                                   "QPushButton:pressed{background-color:#1565C0}");
    totalPriceSummaryButton->setStyleSheet("QPushButton{background-color:#2196F3;"
                                  "color:white;"
                                  "border:none;"
                                  "border-radius:5px;"
                                  "font-size:13px;"
                                  "font-weight:bold;"
                                  "min-height:30px}"
                                  "QPushButton:pressed{background-color:#1565C0}");
    warehouseSummaryButton->setStyleSheet("QPushButton{background-color:#2196F3;"
                                    "color:white;"
                                    "border:none;"
                                    "border-radius:5px;"
                                    "font-size:13px;"
                                    "font-weight:bold;"
                                    "min-height:30px}"
                                    "QPushButton:pressed{background-color:#1565C0}");
    deliverSummaryButton->setStyleSheet("QPushButton{background-color:#2196F3;"
                                  "color:white;"
                                  "border:none;"
                                  "border-radius:5px;"
                                  "font-size:13px;"
                                  "font-weight:bold;"
                                  "min-height:30px}"
                                  "QPushButton:pressed{background-color:#1565C0}");
    exportSummaryButton->setStyleSheet("QPushButton{background-color:#2196F3;"
                                       "color:white;"
                                       "border:none;"
                                       "border-radius:5px;"
                                       "font-size:13px;"
                                       "font-weight:bold;"
                                       "min-height:30px}"
                                       "QPushButton:pressed{background-color:#1565C0}");
}

SummaryProducts::~SummaryProducts(){}
