#include "mywidget.h"
#include "ui_mywidget.h"
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QPainter>
#include <math.h>
#include <QVector>
#include "function.h"
#define SPAN 18
#define EPS 0.001


extern GETVALUE BASEFUNC[2][3];

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    ui->radioButton->setChecked(1);
    this->setWindowTitle(tr("数据拟合"));
    ui->radioButton->setText(QCoreApplication::translate("MyWidget", "span{1, x}", nullptr));
    ui->radioButton_2->setText(QCoreApplication::translate("MyWidget", "span{1/x, 1, x}", nullptr));
    loadStatus = false;
    datafit = false;
    memset(C, 0, sizeof(C)); //清空参数
}

MyWidget::~MyWidget()
{
    delete ui;
}


void MyWidget::on_importdata_clicked()
{
    //clear table
    datafit = false;
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(tr("Select Dataset"));
    fileDialog->setDirectory("../");
    fileDialog->setNameFilter("Dataset(*.dataset);;All files(*.*)");
    QString path;
    if(fileDialog->exec() == QDialog::Accepted)
    {
        path = fileDialog->selectedFiles()[0];
        delete fileDialog;
    }
    else
    {
        delete  fileDialog;
        QMessageBox::information(this, tr("Information"), tr("please input data set"));
        return;
    }
    ui->tableWidget->clearContents();

    points.clear();

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    minx = miny = INT_MAX;
    maxx = maxy = -INT_MAX;


    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QTextStream stream (file.readAll());

    int row;
    stream >> row;
    ui->tableWidget->setRowCount(row);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "X" << "Y");

    for (int i = 0; i < row; i++) {
        double x, y;
        stream >> x >> y;
        points.push_back(QPointF(x, y));
        if(x > maxx)
        {
            maxx = x;
        }
        if(x < minx)
        {
            minx = x;
        }

        if(y > maxy)
        {
            maxy = y;
        }
        if(y < miny)
        {
            miny = y;
        }

        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(x)));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString("%1").arg(y)));
    }
    loadStatus = true;

}

void MyWidget::on_pushButton_clicked()
{
    if(!loadStatus)
    {
        QMessageBox::warning(this, tr("Warning"), tr("please input data set"));
        return;
    }
    if(ui->radioButton->isChecked())
    {
        //第一个拟合函数
        calculate(1);
    }
    else if(ui->radioButton_2->isChecked())
    {
        //第二个拟合函数
        calculate(2);
    }
}

void MyWidget::calculate(int no)
{
    datafit = false;


    Matrix A;

    if(no == 1)
    {
        A = Matrix(points.size(), 2);
    }
    else if(no == 2)
    {
        A = Matrix(points.size(), 3);
    }
    for(int j = 0; j < points.size(); j++)
    {
        if(no == 1)
        {
            A.at(j, 0) = BASEFUNC[no-1][0](points[j].x());
            A.at(j, 1) = BASEFUNC[no-1][1](points[j].x());
        }
        else if(no == 2)
        {
            A.at(j, 0) = BASEFUNC[no-1][0](points[j].x());
            A.at(j, 1) = BASEFUNC[no-1][1](points[j].x());
            A.at(j, 2) = BASEFUNC[no-1][2](points[j].x());
        }
    }

//    for (int i = 0; i < A.mm(); i++)
//    {
//        for(int j = 0; j < A.nn(); j++)
//        {
//            qDebug() << A.at(i, j);
//        }
//        qDebug() << "---------------";
//    }
//    return ;
    //---------
    Matrix detA = A.reverse();

    Matrix W = detA * A;

    Matrix y(points.size(), 1);
    for(int i = 0; i < points.size(); i++)
    {
        y.at(i, 0) = points[i].y();
    }
    Matrix Y = detA * y;

    Matrix maze = W.append(Y);

    for (int i = 0; i < maze.mm(); i++)
    {
        for(int j = 0; j < maze.nn(); j++)
        {
            qDebug() << maze.at(i, j);
        }
    }
    //        return;
    //开始计算参数
    solveC(maze);

    if(no == 1)
    {
        ui->label_2->setText(QString("y = %1 + %2 * x").arg(C[0]).arg(C[1]));
    }
    else
    {
        ui->label_2->setText(QString("y = %1 / x + %2  + %3 * x").arg(C[0]).arg(C[1]).arg(C[2]));
    }
    repaint();
}


void MyWidget::solveC(Matrix maze)
{
    bool flag = 1;
    for(int i = 0; i < maze.mm() - 1; i++)
    {
        //找出主元最大的
        int k = i;
        for(int j = i+1; j < maze.mm(); j++)
        {
            if(maze.at(j ,i ) > maze.at(i, i)) k = j;
        }

        if(maze.at(k, i) < EPS - 1e-9)
        {
            flag = 0;
            break;
        }

        //跟第i行交换
        if(k != i)
        {
            for(int e = i; e < maze.nn(); e++)
            {
                qreal x = maze.at(i, e);
                maze.at(i, e) = maze.at(k, e);
                maze.at(k, e) = x;
            }
        }

        //计算 化简
        for(int j = i+1; j < maze.mm(); j++)
        {
            double ratio = 	maze.at(j, i) / maze.at(i, i);

            for(int z = i; z < maze.nn(); z++)
            {
                maze.at(j, z) += (-1) * ratio * maze.at(i, z);
            }
        }
    }
    if(!flag)
    {
        QMessageBox::warning(this, tr("Warning"), tr("主元素太小，无法计算"));
        return;
    }
    else
    {
        int n = maze.mm() - 1;
        //回代
        C[n] = maze.at(n, n+1 ) / maze.at(n, n);
        for(int i = n-1; i>=0; i--)
        {
            qreal sum = 0.0;
            for(int j = i+1; j <=n; j++)
            {
                sum += C[j] * maze.at(i, j);
            }
            C[i] = (maze.at(i, n+1) - sum) / maze.at(i, i);
        }

        for(int i = 0; i <=n; i++)
        {
            qDebug() << i << " " << C[i];
        }
        datafit = 1;

    }
}


void MyWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPoint p = ui->widget->mapTo(this, ui->label->pos());
    QPainter paint(this);
    paint.setRenderHint(QPainter::Antialiasing);
    if(loadStatus) //如果已经导入数据
    {
        QPoint lefttop(QPoint( p.x() + SPAN, p.y() + SPAN )), rightbottom(QPoint(p.x() + ui->label->width() - SPAN, p.y() + ui->label->height()- SPAN));
        QPoint leftbottom(QPoint(p.x() + SPAN, p.y() + ui->label->height() - SPAN));


        int width = ui->label->width() - SPAN * 2, height = ui->label->height() - SPAN * 2;


        //绘制X轴
        paint.drawLine(leftbottom, rightbottom);


        int min_x = (int)floor(minx), max_x = (int) ceil(maxx);
        paint.drawText(QPointF(leftbottom.x(), leftbottom.y() + SPAN), QString("%1").arg(min_x));
        double deltaX = (width) / (25.0);
        double stepX = (max_x - min_x)/ (25 * 1.0);

//        double step = (maxx - minx) / (25);
        for(int i = 1; i <= 25; i++)
        {
            if(i % 5 == 0)
            {
                paint.drawLine(QPointF( leftbottom.x() +  i * deltaX, leftbottom.y()), QPointF(leftbottom.x() +  i * deltaX, leftbottom.y() - 10));
                paint.drawText(QPointF(leftbottom.x() +  i * deltaX - 7, leftbottom.y() + SPAN), QString("%1").arg(i * stepX + min_x));
            }
            else
            {
                paint.drawLine(QPointF( leftbottom.x() +  i * deltaX, leftbottom.y()), QPointF(leftbottom.x() +  i * deltaX, leftbottom.y() - 5));
            }
        }


        int min_y = (int) floor(miny), max_y = (int) ceil(maxy);
        double deltaY = (height) / 25.0;
        double stepY = (max_y - min_y)/ (25 * 1.0);

        //绘制y轴
        paint.drawLine(leftbottom, lefttop);
//        paint.rotate(-90);
        paint.drawText(QPointF(leftbottom.x() - SPAN, leftbottom.y()), QString("%1").arg(min_y));
//        paint.resetTransform();


        //paint.rotate(-90);
        for (int i = 1;i <= 25; i++)
        {
            if(i % 5 == 0)
            {
                paint.drawLine(QPointF( leftbottom.x(), leftbottom.y() - i * deltaY), QPointF(leftbottom.x() + 10, leftbottom.y() -   i * deltaY));
                //绘制文字
//                paint.rotate(90);
                paint.drawText(QPointF(leftbottom.x() - SPAN-2,  leftbottom.y() - i * deltaY + 3), QString("%1").arg(i * stepY + min_y));
//                paint.resetTransform();
            }
            else
            {
                paint.drawLine(QPointF( leftbottom.x(), leftbottom.y() - i * deltaY), QPointF(leftbottom.x() + 5, leftbottom.y() -   i * deltaY));
            }
        }

        //绘制点
        paint.save();
        QPen pen;
        pen.setColor(Qt::red);
        pen.setWidth(4);
        paint.setPen(pen);

        //绘制点
        for (int i = 0; i < points.size(); i++)
        {
            qreal x = points[i].x(), y = points[i].y();

            qreal nx = leftbottom.x() + (x - min_x) * width / (max_x - min_x),
                  ny = leftbottom.y() - (y - min_y) * height / (max_y - min_y);
            paint.drawPoint(QPointF(nx, ny));
        }
        paint.restore();

        if(datafit)
        {
            paint.save();
            QPen pen;
            pen.setColor(Qt::blue);
            pen.setWidth(1);
            paint.setPen(pen);

            qreal x = minx;
            qreal y;
            if(ui->radioButton->isChecked())
            {
                y = C[0] + C[1] * x;
            }
            else//(ui->radioButton_2->isChecked())
            {
                y = C[0] / x + C[1] + C[2] * x;
            }

            for (qreal i = x+0.01; i <= maxx; i += 0.01)
            {
                qreal nx = i;
                qreal ny;
                if(ui->radioButton->isChecked())
                {
                    ny = C[0] + C[1] * x;
                }
                else //(ui->radioButton_2->isChecked())
                {
                    ny = C[0] / x + C[1] + C[2] * x;
                }

                paint.drawLine(QPointF(leftbottom.x() + (x - min_x) * width / (max_x - min_x),leftbottom.y() - (y - min_y) * height / (max_y - min_y) ),
                               QPointF(leftbottom.x() + (nx - min_x) * width / (max_x - min_x), leftbottom.y() - (ny - min_y) * height / (max_y - min_y)));
                x = nx;
                y = ny;
            }

            paint.restore();
        }
    }
}

