#include "texteditarea.h"

TextEditArea::TextEditArea() {
    this->setWidgetResizable(true);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    textEditArea=new QTextEdit();
    textEditArea->setFixedSize(595,842);
    textEditList<<textEditArea;
    textEditArea->installEventFilter(this);

    widget=new QWidget;

    hLayout=new QHBoxLayout(widget);
    hLayout->setAlignment(Qt::AlignCenter);
    vLayout = new QVBoxLayout;
    vLayout->setAlignment(Qt::AlignTop);
    vLayout->setSpacing(10);
    vLayout->addWidget(textEditArea);
    hLayout->addLayout(vLayout);

    this->setWidget(widget);
}

bool TextEditArea::eventFilter(QObject *obj,QEvent *event){
    QTextEdit *textEdit=qobject_cast<QTextEdit*>(obj);
    if(textEditArea==textEdit||!textEditList.contains(textEdit)) return QScrollArea::eventFilter(obj,event);
    if(event->type()==QEvent::FocusIn){
        textEditArea=textEdit;
    }
    return QScrollArea::eventFilter(obj,event);
}
