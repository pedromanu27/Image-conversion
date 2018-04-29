#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnAbrir_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Abrir Image", "", "Arquivos de Imagem (*.pgn *.jpg *.bmp)");
    ui->lineEdit->setText(fileName);
}

void MainWindow::on_btnConverter_clicked()
{
    QString fileName = ui->lineEdit->text();

    if (fileName != "")
    {
        QFileInfo fileInfo = QFile(fileName);
        QString newFileName = fileInfo.path() + "/" + fileInfo.completeBaseName();

        QImage image = QImage(ui->lineEdit->text());

        if (!image.isNull())
        {
            // 0 - PNG
            // 1 - JPG
            // 2 - BMP
            int format = ui->comboBox->currentIndex();
            if (format == 0)
            {
                newFileName +=".png";
            }
            else if (format == 1)
            {
                newFileName += ".jpg";
            }
            else if (format == 2)
            {
                newFileName += ".bmp";
            }

            qDebug() << newFileName << format;

            if (image.save(newFileName, 0, -1))
            {
                QMessageBox::information(this, "Sucesso", "Imagem convertida com sucesso.");
            }
            else
            {
                QMessageBox::warning(this, "Falhou", "Falhou ao converter a imagem.");
            }
        }
        else
        {
            QMessageBox::warning(this, "Falhou", "Falhou ao abrir arquivo de imagem.");
        }
    }
    else
    {
        QMessageBox::warning(this, "Falhou", "Nenhum arquivo selecionado.");
    }
}
