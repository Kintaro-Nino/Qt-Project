#ifndef TEXTEDITAREA_H
#define TEXTEDITAREA_H

#include <QScrollArea>
#include <QTextEdit>
#include <QBoxLayout>
#include <QEvent>
class TextEditArea : public QScrollArea
{
    Q_OBJECT
public:
    TextEditArea();
    QWidget *widget;
    QTextEdit *textEditArea;
    QHBoxLayout *hLayout;
    QVBoxLayout *vLayout;
    QList<QTextEdit*> textEditList;
protected:
    bool eventFilter(QObject *obj,QEvent *event);
};

#endif
