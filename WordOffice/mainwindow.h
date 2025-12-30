#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <texteditarea.h>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QComboBox>
#include <QFontComboBox>
#include <QLabel>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    TextEditArea *textEdit;
    //菜单项
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *formatMenu;
    QMenu *fontMenu;
    QMenu *alignmentMenu;
    QMenu *windowMenu;
    QMenu *helpMenu;
    QMenu *fileNameMenu;

    //工具栏项
    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    QToolBar *formatToolBar;
    QToolBar *comboToolBar;
    QComboBox *numberComboBox;
    QFontComboBox *fontFamilyComboBox;
    QComboBox *fontSizeComboBox;

    //文件项动作
    QAction *newFileAction;
    QAction *openFileAction;
    QAction *saveFileAction;
    QAction *saveAsAction;
    QAction *printAction;
    QAction *printPreviewAction;
    QAction *exitAction;

    //编辑项动作
    QAction *undoAction;
    QAction *redoAction;
    QAction *cutAction;
    QAction *copyAction;
    QAction *pasteAction;

    //格式项动作
    QAction *boldAction;
    QAction *italicAction;
    QAction *underlineAction;
    QAction *centerAlignmentAction;
    QAction *leftAlignmentAction;
    QAction *rightAlignmentAction;
    QAction *twoSectionAlignmentAction;
    QAction *setColorAction;

    //窗口项动作
    QAction *addBlankDraftPageAction;
    QAction *deleteBlankDraftPageAction;

    //帮助项动作
    QAction *aboutAction;
    QAction *aboutQtAction;

    bool saveSignal=false;
    QString currentFileName="文档1";
    QString currentFilePath;
    QLabel *wordCountLabel=new QLabel;
    QLabel *pageLabel=new QLabel;

    //初始化主窗口
    void createAction();
    void createMenuBar();
    void createToolBar();

    //文件项功能
    void newFile();
    void openFile();
    void saveFile();
    void saveAs();
    void print();
    void printPreview();
    QString handleFileName(QString fileName);

    //编辑项功能
    void undo();
    void redo();
    void cut();
    void copy();
    void paste();

    //格式项功能
    void bold();
    void italic();
    void underline();
    void centerAlignment(bool checked);
    void leftAlignment(bool checked);
    void rightAlignment(bool checked);
    void twoSectionAlignment(bool checked);
    void setColor();

    //窗口项功能
    void addBlankDraftPage();
    void deleteBlankDraftPage();

    //帮助项动作
    void about();
    void aboutQt();

    //组合工具栏项功能
    void setNumber(int index);
    void setFontFamily(const QFont &font);
    void setFontSize(const QString &size);

    //连接到状态栏
    void connectToStatusBar(QTextEdit *textEdit);
};
#endif // MAINWINDOW_H
