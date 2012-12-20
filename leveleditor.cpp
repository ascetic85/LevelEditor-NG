#include "leveleditor.h"

#include <QtOpenGL/QGLWidget>
#include <QFileDialog>
#include <QFileSystemModel>
#include <QTreeWidget>
#include <QFileInfo>

#include "Debug.h"


LevelEditor::LevelEditor(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LevelEditor() )
    , m_fileModel(0)
{
    ui->setupUi(this);
}

LevelEditor::~LevelEditor()
{
    delete ui;
}

void LevelEditor::setUseOpenGL()
{
    ui->graphicsView->setViewport(new QGLWidget());
    //    Q_ASSERT(!"LevelEditor::setUseOpenGL is not complete");
}

void LevelEditor::scale(qreal )
{
}

/**
 * @brief LevelEditor::on_resToolButton_clicked
 * get the resource's directory (include subdirector),
 * show all the resource into @ui->resourceTree
 *
 * 获取资源目录, 把资源目录下的符合要求的资源都加载到resourceTree显示.
 * png, jpg, plist(TP 压缩出来的图片) ?
 *
 */
void LevelEditor::on_resToolButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this
                                                    , tr("Open Directory")
                                                    , "."
                                                    , QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    Debug() << dir;
    if (dir.isEmpty() | dir.isNull()) return;
}



