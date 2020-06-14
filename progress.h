/* Заголовочный файл окна прогресса*/
#ifndef PROGRESS_H
#define PROGRESS_H

#include <QDialog>
#include <QLineSeries>
#include <QChart>
#include <QChartView>
#include <QFile>
#include <QDataStream>
#include <QTime>

using namespace QtCharts;

namespace Ui {
  class Progress;
}

class Progress : public QDialog
{
  Q_OBJECT

public:
  explicit Progress(QWidget *parent = nullptr);
  ~Progress();

  // Объявление объектов, необходимых для создания графика прогресса
  QLineSeries *progressSeries = new QLineSeries();
  QChart *progressChart = new QChart();
  QChartView *progressChartView = new QChartView();


private:
  Ui::Progress *ui;

  void getData(); // Функция загружает данные из файла сохранений в progressSeries
};

#endif // PROGRESS_H
