#ifndef ADDPRODUCTS_H
#define ADDPRODUCTS_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QBoxLayout>
class AddProducts : public QWidget
{
    Q_OBJECT
public:
    explicit AddProducts(QWidget *parent = nullptr);
    ~AddProducts();

    QLineEdit *productIdEdit;
    QLineEdit *productNameEdit;
    QLineEdit *productCategoryEdit;
    QLineEdit *productQuantityEdit;
    QLineEdit *productPriceEdit;
    QLineEdit *supplierIdEdit;

    QPushButton *addProductsButton;
    QPushButton *cancelButton;

private:
    QLabel *productId;
    QLabel *productName;
    QLabel *productCategory;
    QLabel *productQuantity;
    QLabel *productPrice;
    QLabel *supplierId;

    QHBoxLayout *hLayout;
    QGridLayout *gLayout;
};

#endif // ADDPRODUCTS_H
