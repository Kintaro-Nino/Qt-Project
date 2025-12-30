#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QBoxLayout>
#include <QGridLayout>
#include <QDateTime>
#include <QFileDialog>
#include "xlsxdocument.h"
#include "xlsxformat.h"
#include "addproducts.h"
#include "warehouseproduct.h"
#include "deliverproduct.h"
#include "summaryproducts.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void connectDatabase();
    void InventoryManagementSystemInit();

private:
    AddProducts *product;
    WarehouseProduct *warehouseProduct;
    DeliverProduct *deliverProduct;
    SummaryProducts *summaryProduct;

    QTableWidget *productsTable;
    QVBoxLayout *vLayout;

    QLabel *queryLabel;
    QLineEdit *queryEdit;
    QPushButton *queryDataButton;
    QList<QString> queryList;

    QPushButton *addDataButton;
    QPushButton *deleteDataButton;
    QPushButton *warehouseButton;
    QPushButton *deliverButton;
    QPushButton *exportButton;
    QPushButton *summaryButton;
    QPushButton *updateButton;
    QHBoxLayout *hLayout;
    QGridLayout *gLayout;

private slots:
    void onQueryDataClicked();
    void onAddProductsClicked();
    void onDeleteDataClicked();
    void onWarehouseClicked();
    void onDeliverClicked();
    void exportData(QTableWidget *table);
    void updateTable();
    void onCategorySummaryClicked();
    void onTotalPriceSummaryClicked();
    void warehouseDeliverSummary(QTableWidget *table);
};
#endif // MAINWINDOW_H
