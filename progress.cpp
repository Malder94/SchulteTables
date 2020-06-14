#include "progress.h"
#include "ui_progress.h"

Progress::Progress(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Progress)
{
  ui->setupUi(this);

  progressSeries = new QLineSeries();

  getData();


  progressChart = new QChart();
  progressChart->legend()->hide();
  progressChart->addSeries(progressSeries);
  progressChart->createDefaultAxes();
  progressChart->setTitle("Прогресс");

  progressChartView = new QChartView(progressChart);
  progressChartView->setRenderHint(QPainter::Antialiasing);

  ui->progressLayout->addWidget(progressChartView);

}

Progress::~Progress()
{
  delete ui;
}

// Загрузка данных из файла сохранений
void Progress::getData()
{
  QFile file ("save.bin");

  QDataStream stream (&file);

  file.open(QIODevice::ReadOnly);

  QTime result;
  int round = 1;

  while (!file.atEnd()) {
      stream >> result;
      progressSeries->append(round++, result.second());
    }
  file.close();

}
