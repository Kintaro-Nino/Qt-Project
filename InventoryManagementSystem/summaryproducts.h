#ifndef SUMMARYPRODUCTS_H
#define SUMMARYPRODUCTS_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QTableWidget>
#include <QLabel>
#include <QPushButton>
#include <QBoxLayout>
#include <QGridLayout>
class SummaryProducts : public QWidget
{
    Q_OBJECT
public:
    explicit SummaryProducts(QWidget *parent = nullptr);
    ~SummaryProducts();

    QTableWidget *summaryTable;
    QLabel *summaryLabel;
    QTableWidget *warehouseSummaryTable;
    QTableWidget *deliverSummaryTable;
    QPushButton *categorySummaryButton;
    QPushButton *totalPriceSummaryButton;
    QPushButton *warehouseSummaryButton;
    QPushButton *deliverSummaryButton;
    QPushButton *exportSummaryButton;

private:
    QGridLayout *gLayout;
    QVBoxLayout *vLayout;
};

#endif // SUMMARYPRODUCTS_H
