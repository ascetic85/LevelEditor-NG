#include "leveleditor.h"

#include <QtOpenGL/QGLWidget>
#include <QFileDialog>
#include <QTreeWidget>

#include <QFileSystemModel>
#include <QFileSystemWatcher>
#include <QFileInfo>
#include <QSettings>
#include <QSortFilterProxyModel>

#include "resource.h"
#include "config.h"
#include "Debug.h"
#include "model.h"
#include "advanceclone.h"


LevelEditor::LevelEditor(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LevelEditor() )
    , m_fileModel(0)
    , m_watcher(0)
    , m_resource(0)
    , m_proxyMode(0)
{
    ui->setupUi(this);

    // load settings
    QSettings settings(Config::config(), Config::format());
    if (settings.value("editor/opengl", false).toBool()) {
        ui->graphicsView->setViewport(new QGLWidget());
    }

    ui->resourceTree->setDragEnabled(true);

    ui->stackedWidget->hide();
}

LevelEditor::~LevelEditor()
{
    SAFE_DELETE(m_fileModel);
    SAFE_DELETE(m_watcher);
    SAFE_DELETE(m_resource);
    SAFE_DELETE(m_proxyMode);
    SAFE_DELETE(ui);
}

void LevelEditor::scale(qreal )
{
}

void LevelEditor::showGrid(int n)
{
    if (n > 1 && n < 50) {

    }
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

    if (!m_resource)
        m_resource = new Resource();

    if (!m_fileModel) {
        m_fileModel = new Model();
        m_fileModel->setNameFilters(
                    QStringList() << "*.png" << "*.jpg" << "*.jpeg" << "*.pshs,*.plist"
                                    );
        m_fileModel->setNameFilterDisables(false);

        // filter
        m_proxyMode = new QSortFilterProxyModel(this);
        m_proxyMode->setSourceModel(m_fileModel);
        m_proxyMode->setFilterKeyColumn(0);

        // set model
        ui->resourceTree->setModel(m_fileModel);
    }

    m_fileModel->setRootPath(dir);
    m_resource->setResource(dir);
    ui->resourceTree->setRootIndex(m_fileModel->index(dir));
}

void LevelEditor::onFilechanged(QString file)
{
    Debug() << Q_FUNC_INFO << file;
}

void LevelEditor::onDirectoryChaned(QString dir)
{
    Debug() << Q_FUNC_INFO << dir << m_watcher->files() << m_watcher->directories();
}

void LevelEditor::on_filter_textChanged(const QString &arg1)
{
    if (m_proxyMode) {
        m_proxyMode->setFilterRegExp(arg1);
    }
}

void LevelEditor::on_toolClone_clicked()
{
    ui->graphicsView->copyAndPasteSelectedItem();
}

void LevelEditor::on_toolDelete_clicked()
{
    ui->graphicsView->deleteSelectedItem();
}

void LevelEditor::on_cloneToolButton_clicked(bool checked)
{
    if (checked) {
        ui->stackedWidget->show();
        ui->stackedWidget->setMaximumHeight(ui->advanceclone->maximumHeight());
        ui->advanceclone->show();
        ui->advanceclone->raise();
    } else {
        ui->stackedWidget->hide();
    }
}

void LevelEditor::on_physicBoundToolButton_clicked(bool checked)
{
    if (checked) {
        ui->stackedWidget->show();
        ui->phsyicbound->show();
        ui->phsyicbound->raise();
    } else {
        ui->stackedWidget->hide();
    }
}
