#ifndef DELIVERPRODUCT_H
#define DELIVERPRODUCT_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QBoxLayout>

class DeliverProduct : public QWidget
{
    Q_OBJECT
public:
    explicit DeliverProduct(QWidget *parent = nullptr);
    ~DeliverProduct();

    QComboBox *productIdBox;
    QLineEdit *deliverQuantityEdit;

    QPushButton *deliverButton;
    QPushButton *cancelButton;

private:
    QLabel *productId;
    QLabel *deliverQuantity;

    QGridLayout *gLayout;
    QHBoxLayout *hLayout;
};

#endif // DELIVERPRODUCT_H
