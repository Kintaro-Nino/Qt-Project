#ifndef WAREHOUSEPRODUCT_H
#define WAREHOUSEPRODUCT_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QBoxLayout>

class WarehouseProduct : public QWidget
{
    Q_OBJECT
public:
    explicit WarehouseProduct(QWidget *parent = nullptr);
    ~WarehouseProduct();

    QComboBox *productIdBox;
    QLineEdit *warehouseQuantityEdit;

    QPushButton *warehouseButton;
    QPushButton *cancelButton;

private:
    QLabel *productId;
    QLabel *warehouseQuantity;

    QGridLayout *gLayout;
    QHBoxLayout *hLayout;
};

#endif // WAREHOUSEPRODUCT_H
