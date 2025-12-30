#include "mainwindow.h"
#include <QApplication>
#include <QFileDialog>
#include <QColorDialog>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("QtWriter 文字处理软件");
    setWindowIcon(QIcon(":/wordpicture/pictures/icon.png"));
    resize(900,600);

    createAction();
    createMenuBar();
    createToolBar();

    textEdit=new TextEditArea();
    this->setCentralWidget(textEdit);
    textEdit->textEditArea->setFocus();

    wordCountLabel->setText("页面总字符数:0");
    pageLabel->setText("共1页");
    statusBar()->addPermanentWidget(pageLabel);
    statusBar()->addPermanentWidget(wordCountLabel);
    connectToStatusBar(textEdit->textEditArea);
}

MainWindow::~MainWindow() {}

void MainWindow::createAction(){
    //创建文件项菜单动作
    newFileAction=new QAction(QIcon(":/wordpicture/pictures/new.png"),tr("新建(&N)"),this);
    connect(newFileAction,&QAction::triggered,[=](){
        statusBar()->showMessage("新建文档成功！",2000);
    });
    connect(newFileAction,&QAction::triggered,this,&MainWindow::newFile);

    openFileAction=new QAction(QIcon(":/wordpicture/pictures/open.png"),tr("打开(&O)"),this);
    connect(openFileAction,&QAction::triggered,this,&MainWindow::openFile);

    saveFileAction=new QAction(QIcon(":/wordpicture/pictures/save.png"),tr("保存(&S)"),this);
    connect(saveFileAction,&QAction::triggered,[=](){
        if(saveSignal==true){
            statusBar()->showMessage("保存文档成功！",2000);
        }
    });
    connect(saveFileAction,&QAction::triggered,this,&MainWindow::saveFile);

    saveAsAction=new QAction(tr("另存为(&A)"),this);
    connect(saveAsAction,&QAction::triggered,this,&MainWindow::saveAs);

    printAction=new QAction(QIcon(":/wordpicture/pictures/printer.png"),tr("打印(&P)"),this);
    connect(printAction,&QAction::triggered,this,&MainWindow::print);

    printPreviewAction=new QAction(tr("打印预览"),this);
    connect(printPreviewAction,&QAction::triggered,this,&MainWindow::printPreview);

    exitAction=new QAction(tr("退出(&X)"),this);
    connect(exitAction,&QAction::triggered,this,&MainWindow::close);

    //创建编辑项菜单动作
    undoAction=new QAction(QIcon(":/wordpicture/pictures/undo.png"),tr("撤销(&U)"),this);
    connect(undoAction,&QAction::triggered,this,&MainWindow::undo);

    redoAction=new QAction(QIcon(":/wordpicture/pictures/redo.png"),tr("重做(&R)"),this);
    connect(redoAction,&QAction::triggered,this,&MainWindow::redo);

    cutAction=new QAction(QIcon(":/wordpicture/pictures/cut.png"),tr("裁剪(&T)"),this);
    connect(cutAction,&QAction::triggered,this,&MainWindow::cut);

    copyAction=new QAction(QIcon(":/wordpicture/pictures/copy.png"),tr("复制(&C)"),this);
    connect(copyAction,&QAction::triggered,this,&MainWindow::copy);

    pasteAction=new QAction(QIcon(":/wordpicture/pictures/paste.png"),tr("粘贴(&P)"),this);
    connect(pasteAction,&QAction::triggered,this,&MainWindow::paste);

    //创建格式项菜单动作
    boldAction=new QAction(QIcon(":/wordpicture/pictures/bold.png"),tr("加粗(&B)"),this);
    //将一个动作（QAction）设置为可勾选/可切换的状态
    boldAction->setCheckable(true);
    connect(boldAction,&QAction::triggered,this,&MainWindow::bold);

    italicAction=new QAction(QIcon(":/wordpicture/pictures/italic.png"),tr("倾斜(&I)"),this);
    italicAction->setCheckable(true);
    connect(italicAction,&QAction::triggered,this,&MainWindow::italic);

    underlineAction=new QAction(QIcon(":/wordpicture/pictures/underline.png"),tr("下划线(&U)"),this);
    underlineAction->setCheckable(true);
    connect(underlineAction,&QAction::triggered,this,&MainWindow::underline);

    centerAlignmentAction=new QAction(QIcon(":/wordpicture/pictures/centeralign.png"),tr("居中(&E)"),this);
    centerAlignmentAction->setCheckable(true);
    connect(centerAlignmentAction,&QAction::triggered,this,&MainWindow::centerAlignment);

    leftAlignmentAction=new QAction(QIcon(":/wordpicture/pictures/leftalign.png"),tr("左对齐(&L)"),this);
    leftAlignmentAction->setCheckable(true);
    connect(leftAlignmentAction,&QAction::triggered,this,&MainWindow::leftAlignment);

    rightAlignmentAction=new QAction(QIcon(":/wordpicture/pictures/rightalign.png"),tr("右对齐(&R)"),this);
    rightAlignmentAction->setCheckable(true);
    connect(rightAlignmentAction,&QAction::triggered,this,&MainWindow::rightAlignment);

    twoSectionAlignmentAction=new QAction(QIcon(":/wordpicture/pictures/twosectionalign.png"),tr("两端对齐(&J)"),this);
    twoSectionAlignmentAction->setCheckable(true);
    connect(twoSectionAlignmentAction,&QAction::triggered,this,&MainWindow::twoSectionAlignment);

    setColorAction=new QAction(QIcon(":/wordpicture/pictures/color.png"),tr("颜色(&C)"),this);
    connect(setColorAction,&QAction::triggered,this,&MainWindow::setColor);

    //创建窗口项菜单动作
    addBlankDraftPageAction=new QAction(tr("添加空白草稿页(&A)"),this);
    connect(addBlankDraftPageAction,&QAction::triggered,[=](){
        statusBar()->showMessage("添加空白页成功！",2000);
    });
    connect(addBlankDraftPageAction,&QAction::triggered,this,&MainWindow::addBlankDraftPage);

    deleteBlankDraftPageAction=new QAction(tr("删除空白草稿页(&D)"),this);
    connect(deleteBlankDraftPageAction,&QAction::triggered,[=](){
        statusBar()->showMessage("删除空白页成功！",2000);
    });
    connect(deleteBlankDraftPageAction,&QAction::triggered,this,&MainWindow::deleteBlankDraftPage);

    //创建帮助项菜单动作
    aboutAction=new QAction(tr("关于(&A)"),this);
    connect(aboutAction,&QAction::triggered,this,&MainWindow::about);

    aboutQtAction=new QAction(tr("关于Qt(&Q)"),this);
    connect(aboutQtAction,&QAction::triggered,this,&MainWindow::aboutQt);
}

void MainWindow::createMenuBar(){
    //创建文件项菜单
    fileMenu=menuBar()->addMenu(tr("文件(&F)"));
    fileMenu->addAction(newFileAction);
    fileMenu->addAction(openFileAction);
    fileMenu->addSeparator();
    fileMenu->addAction(saveFileAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(printAction);
    fileMenu->addAction(printPreviewAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    //创建编辑项菜单
    editMenu=menuBar()->addMenu(tr("编辑(&E)"));
    editMenu->addAction(undoAction);
    editMenu->addAction(redoAction);
    editMenu->addSeparator();
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);

    //创建格式项菜单
    formatMenu=menuBar()->addMenu(tr("格式(&O)"));
    fontMenu=formatMenu->addMenu(tr("字体(&D)"));
    fontMenu->addAction(boldAction);
    fontMenu->addAction(italicAction);
    fontMenu->addAction(underlineAction);
    alignmentMenu=formatMenu->addMenu(tr("段落"));
        alignmentMenu->addAction(centerAlignmentAction);
    alignmentMenu->addAction(leftAlignmentAction);
    alignmentMenu->addAction(rightAlignmentAction);
    alignmentMenu->addAction(twoSectionAlignmentAction);
    formatMenu->addAction(setColorAction);

    //创建窗口项菜单
    windowMenu=menuBar()->addMenu(tr("窗口(&W)"));
    windowMenu->addAction(addBlankDraftPageAction);
    windowMenu->addAction(deleteBlankDraftPageAction);

    //创建帮助项菜单
    helpMenu=menuBar()->addMenu(tr("帮助(&H)"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);

    //创建文件名项菜单
    fileNameMenu=menuBar()->addMenu(tr(currentFileName.toUtf8()));
    connect(fileNameMenu, &QMenu::aboutToShow, [=]() {
        statusBar()->showMessage(currentFileName);
    });
}

void MainWindow::createToolBar(){
    //创建文件项工具栏
    fileToolBar=addToolBar(tr("文件"));
    fileToolBar->setMovable(false);
    fileToolBar->addAction(newFileAction);
    fileToolBar->addAction(openFileAction);
    fileToolBar->addAction(saveFileAction);
    fileToolBar->addAction(printAction);

    //创建编辑项工具栏
    editToolBar=addToolBar(tr("编辑"));
    editToolBar->setMovable(false);
    editToolBar->addAction(undoAction);
    editToolBar->addAction(redoAction);
    editToolBar->addSeparator();
    editToolBar->addAction(cutAction);
    editToolBar->addAction(copyAction);
    editToolBar->addAction(pasteAction);

    //创建格式项工具栏
    formatToolBar=addToolBar(tr("格式"));
    formatToolBar->setMovable(false);
    formatToolBar->addAction(boldAction);
    formatToolBar->addAction(italicAction);
    formatToolBar->addAction(underlineAction);
    formatToolBar->addSeparator();
    formatToolBar->addAction(centerAlignmentAction);
    formatToolBar->addAction(leftAlignmentAction);
    formatToolBar->addAction(rightAlignmentAction);
    formatToolBar->addAction(twoSectionAlignmentAction);
    formatToolBar->addSeparator();
    formatToolBar->addAction(setColorAction);

    //创建组合工具栏
    addToolBarBreak(Qt::TopToolBarArea);    //addToolBarBreak() 是 QMainWindow 类中的一个函数，用于在指定的工具栏区域中添加一个"断点"
    comboToolBar=addToolBar(tr("组合栏"));
    comboToolBar->setMovable(false);

    //编号工具栏
    numberComboBox=new QComboBox();
    comboToolBar->addWidget(numberComboBox);
    numberComboBox->addItem("无编号");
    numberComboBox->addItem("编号 ●");
    numberComboBox->addItem("编号 ○");
    numberComboBox->addItem("编号 ■");
    numberComboBox->addItem("编号 (1.2.3.)");
    numberComboBox->addItem("编号 ( a.b.c.)");
    numberComboBox->addItem("编号 ( A.B.C.)");
    numberComboBox->addItem("编号 (ⅰ.ⅱ.ⅲ.)");
    numberComboBox->addItem("编号 (Ⅰ.Ⅱ.Ⅲ.)");
    connect(numberComboBox,&QComboBox::currentIndexChanged,this,&MainWindow::setNumber);

    //字体工具栏
    //QFontComboBox 字体选择组合框，专门用于让用户从系统可用字体列表中选择字体
    fontFamilyComboBox=new QFontComboBox();
    fontFamilyComboBox->setEditable(false);
    comboToolBar->addWidget(fontFamilyComboBox);
    connect(fontFamilyComboBox,&QFontComboBox::currentFontChanged,this,&MainWindow::setFontFamily);

    //字号工具栏
    fontSizeComboBox=new QComboBox();
    comboToolBar->addWidget(fontSizeComboBox);
    QFontDatabase database; //QFontDatabase 提供了访问系统字体数据库的功能，可以枚举系统中可用的字体家族、字体样式，以及查询字体的详细信息
    foreach(int pixelSize,database.standardSizes()){    //standardSizes() 是 Qt 中 QFontDatabase 类的一个函数，用于获取字体的标准尺寸列表
        fontSizeComboBox->addItem(QString::number(pixelSize));
    }
    fontSizeComboBox->setCurrentIndex(fontSizeComboBox->findText(QString::number(QApplication::font().pointSize())));
    connect(fontSizeComboBox,&QComboBox::currentTextChanged,this,&MainWindow::setFontSize);
}

QString MainWindow::handleFileName(QString fileName){
    QFileInfo fileInfo(fileName);
    QString fileBaseName=fileInfo.completeBaseName();
    QString fileSuffix=fileInfo.completeSuffix();
    if(fileBaseName.size()>20){
        fileBaseName=fileBaseName.left(20)+"...";
        return fileBaseName+fileSuffix;
    }
    return fileName;
}

void MainWindow::newFile(){
    if(saveSignal==false&&!textEdit->textEditArea->toPlainText().isEmpty()){
        QMessageBox::StandardButton button=QMessageBox::warning(this,"警告","当前文档未保存是否继续？",QMessageBox::Ok|QMessageBox::Cancel);
        if(button==QMessageBox::Cancel) return;
    }
    if(textEdit) delete textEdit;
    textEdit=new TextEditArea();
    this->setCentralWidget(textEdit);
    textEdit->textEditArea->setFocus();
    connectToStatusBar(textEdit->textEditArea);
    static int currentFileIndex=2;
    currentFileName=QString("文档%1").arg(currentFileIndex++);
    fileNameMenu->setTitle(tr(currentFileName.toUtf8()));
    saveSignal=false;
}

void MainWindow::openFile(){
    currentFilePath=QFileDialog::getOpenFileName(this,"打开文件","/","HTML文档(*.html *.htm);;所有文件(*.*)");
    if(currentFilePath.isEmpty()){
        QMessageBox::warning(this,"警告","未选取文件！");
        return;
    }
    else{
        QFile file(currentFilePath);
        if(!file.open(QIODevice::ReadWrite|QIODevice::Text)){
            QMessageBox::critical(this,"错误","打开文件失败，请检查是否出错！");
            return;
        }
        QTextStream fileIn(&file);
        QString fileContent=fileIn.readAll();
        currentFileName=QFileInfo(file).fileName();
        file.close();
        if(Qt::mightBeRichText(fileContent)){
            textEdit->textEditArea->setHtml(fileContent);
        }
        else{
            textEdit->textEditArea->setPlainText(fileContent);
        }
        saveSignal=true;
        fileNameMenu->setTitle(tr(handleFileName(currentFileName).toUtf8()));
    }
}

void MainWindow::saveFile(){
    if(saveSignal==false){
        saveAs();
    }
    else{
        QFile file(currentFilePath);
        if(!file.open(QIODevice::ReadWrite|QIODevice::Text)){
            QMessageBox::critical(this,"错误","保存文件失败，请检查是否出错！");
        }
        QTextStream fileOut(&file);
        QString fileContent=textEdit->textEditArea->toHtml();
        fileOut<<fileContent;
        file.close();
    }
}

void MainWindow::saveAs(){
    currentFilePath=QFileDialog::getSaveFileName(this,"另存为",currentFileName,"HTML文档(*.html *.htm);;所有文件(*.*)");
    if(currentFilePath.isEmpty()) return;
    else{
        QFile file(currentFilePath);
        if(!file.open(QIODevice::ReadWrite|QIODevice::Text)){
            QMessageBox::critical(this,"错误","保存文件失败，请检查是否出错！");
            return;
        }
        QTextStream fileOut(&file);
        QString fileContent=textEdit->textEditArea->toHtml();
        fileOut<<fileContent;
        file.close();
        saveSignal=true;
        statusBar()->showMessage("保存文档成功！",2000);
    }
}

void MainWindow::print(){
    if(textEdit->textEditArea->toPlainText().isEmpty()){
        QMessageBox::StandardButton button=QMessageBox::warning(this,"警告","文档内容为空！是否继续？",QMessageBox::Yes|QMessageBox::Cancel);
        if(button==QMessageBox::Cancel) return;
    }
    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog  printDialog(&printer,textEdit->textEditArea);
    if(printDialog.exec()==QDialog::Accepted){
        QTextDocument *textDocument=textEdit->textEditArea->document();
        textDocument->print(&printer);
    }
}

void MainWindow::printPreview(){
    QPrinter printer(QPrinter::HighResolution);
    QPrintPreviewDialog printPreviewDialog(&printer,textEdit->textEditArea);
    connect(&printPreviewDialog,&QPrintPreviewDialog::paintRequested,[&](){
        textEdit->textEditArea->print(&printer);
    });
    printPreviewDialog.exec();
}

void MainWindow::undo(){
    textEdit->textEditArea->undo();
}

void MainWindow::redo(){
    textEdit->textEditArea->redo();
}

void MainWindow::cut(){
    textEdit->textEditArea->cut();
}

void MainWindow::copy(){
    textEdit->textEditArea->copy();
}

void MainWindow::paste(){
    textEdit->textEditArea->paste();
}

void MainWindow::bold(){
    QTextCharFormat textFormat;
    textFormat.setFontWeight(boldAction->isChecked()?QFont::Bold:QFont::Normal);
    textEdit->textEditArea->mergeCurrentCharFormat(textFormat);
}

void MainWindow::italic(){
    QTextCharFormat textFormat;
    textFormat.setFontItalic(italicAction->isChecked());
    textEdit->textEditArea->mergeCurrentCharFormat(textFormat);
}

void MainWindow::underline(){
    QTextCharFormat textFormat;
    textFormat.setFontUnderline(underlineAction->isChecked());
    textEdit->textEditArea->mergeCurrentCharFormat(textFormat);
}

void MainWindow::centerAlignment(bool checked){
    if(checked==true){
        textEdit->textEditArea->setAlignment(Qt::AlignCenter);
        leftAlignmentAction->setChecked(false);
        rightAlignmentAction->setChecked(false);
        twoSectionAlignmentAction->setChecked(false);
    }
    else {
        textEdit->textEditArea->setAlignment(Qt::AlignJustify);
        twoSectionAlignmentAction->setChecked(true);
    }
}

void MainWindow::leftAlignment(bool checked){
    if(checked==true){
        textEdit->textEditArea->setAlignment(Qt::AlignLeft);
        centerAlignmentAction->setChecked(false);
        rightAlignmentAction->setChecked(false);
        twoSectionAlignmentAction->setChecked(false);
    }
    else {
        textEdit->textEditArea->setAlignment(Qt::AlignJustify);
        twoSectionAlignmentAction->setChecked(true);
    }
}

void MainWindow::rightAlignment(bool checked){
    if(checked==true){
        textEdit->textEditArea->setAlignment(Qt::AlignRight);
        centerAlignmentAction->setChecked(false);
        leftAlignmentAction->setChecked(false);
        twoSectionAlignmentAction->setChecked(false);
    }
    else {
        textEdit->textEditArea->setAlignment(Qt::AlignJustify);
        twoSectionAlignmentAction->setChecked(true);
    }
}

void MainWindow::twoSectionAlignment(bool checked){
    if(checked==true){
        textEdit->textEditArea->setAlignment(Qt::AlignJustify);
        centerAlignmentAction->setChecked(false);
        leftAlignmentAction->setChecked(false);
        rightAlignmentAction->setChecked(false);
    }
    else {
        textEdit->textEditArea->setAlignment(Qt::AlignLeft);
        leftAlignmentAction->setChecked(true);
    }
}

void MainWindow::setColor(){
    QColor textColor=QColorDialog::getColor();
    if(!textColor.isValid()) return;
    QTextCharFormat textFormat;
    textFormat.setForeground(textColor);
    textEdit->textEditArea->mergeCurrentCharFormat(textFormat);
}

void MainWindow::addBlankDraftPage(){
    QTextEdit *newBlankPage=new QTextEdit;
    newBlankPage->setFixedSize(595,842);
    newBlankPage->installEventFilter(textEdit);
    textEdit->vLayout->addWidget(newBlankPage);
    textEdit->textEditList<<newBlankPage;
    connectToStatusBar(newBlankPage);
}

void MainWindow::deleteBlankDraftPage(){
    if(textEdit->textEditList.isEmpty()){
        QMessageBox::warning(this,"警告","无可删除空白页!");
        return;
    }
    for(int i=textEdit->textEditList.count()-1;i>=0;i--){
        if(textEdit->textEditList[i]->toPlainText().isEmpty()&&textEdit->textEditList.count()>1){
            QTextEdit *blankPage=textEdit->textEditList.takeLast();
            textEdit->vLayout->removeWidget(blankPage);
            delete blankPage;
        }
    }
}

void MainWindow::about(){
    QMessageBox::about(this,"关于","QtWriter-此软件是基于Qt6实现的文字处理软件");
}

void MainWindow::aboutQt(){
    QMessageBox::aboutQt(this,"关于Qt");
}

void MainWindow::setNumber(int index){
    QTextCursor textCursor=textEdit->textEditArea->textCursor();
    QTextListFormat listFormat;
    switch(index){
    case 1: listFormat.setStyle(QTextListFormat::ListDisc); break;        // ● 实心圆点
    case 2: listFormat.setStyle(QTextListFormat::ListCircle); break;      // ○ 空心圆圈
    case 3: listFormat.setStyle(QTextListFormat::ListSquare); break;      // ■ 实心方块
    case 4: listFormat.setStyle(QTextListFormat::ListDecimal); break;     // 1, 2, 3... 十进制数字
    case 5: listFormat.setStyle(QTextListFormat::ListLowerAlpha); break;  // a, b, c... 小写字母
    case 6: listFormat.setStyle(QTextListFormat::ListUpperAlpha); break;  // A, B, C... 大写字母
    case 7: listFormat.setStyle(QTextListFormat::ListLowerRoman); break;  // i, ii, iii... 小写罗马数字
    case 8: listFormat.setStyle(QTextListFormat::ListUpperRoman); break;  // I, II, III... 大写罗马数字
    default:break;
    }
    textCursor.createList(listFormat);
}

void MainWindow::setFontFamily(const QFont &font){
    QTextCharFormat textFormat;
    textFormat.setFontFamilies(font.families());
    textEdit->textEditArea->mergeCurrentCharFormat(textFormat);
}

void MainWindow::setFontSize(const QString &size){
    QTextCharFormat textFormat;
    textFormat.setFontPointSize(size.toFloat());
    textEdit->textEditArea->mergeCurrentCharFormat(textFormat);
}

void MainWindow::connectToStatusBar(QTextEdit *textEdit){
    //切换textEdit时更新状态栏
    connect(textEdit,&QTextEdit::selectionChanged,[=](){
        int totalPage=1;
        if(textEdit->document()->size().height()>=1016){
            totalPage=(textEdit->document()->size().height()-1016)/992+2;
        }
        pageLabel->setText(QString("共%1页").arg(totalPage));
        wordCountLabel->setText("页面总字符数:"+QString::number(textEdit->toPlainText().length()));
    });

    //实时统计当前textEdit页面总数和总字符数并更新状态栏
    connect(textEdit,&QTextEdit::cursorPositionChanged,[=](){
        int totalPage=1;
        if(textEdit->document()->size().height()>=1016){
            totalPage=(textEdit->document()->size().height()-1016)/992+2;
        }
        pageLabel->setText(QString("共%1页").arg(totalPage));
        wordCountLabel->setText("页面总字符数:"+QString::number(textEdit->toPlainText().length()));
    });
}
