#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>
#include <QtMath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    totaldist = 0;
    setGeometry(1000, 500, 1000, 500);

    // Change slider handle
    //setStyleSheet("QSlider{ background-color: yellow }");
    setStyleSheet("QSlider::handle:horizontal {background-color: white;}");
    setStyleSheet("QSlider::handle:horizontal {shape: circle;}");
    //setStyleSheet("QSlider::slider:horizontal {background-color: white;}");
    //setStyleSheet("QSlider::groove:horizonatal {background-color: white;}");
    //setStyleSheet("QSlider::handle {image: url(:/new/images/Football.png);}");
    //setStyleSheet("QComboBox { background-color: black; }");

    ui->customPlot->rescaleAxes();
    ui->customPlot->axisRect()->setAutoMargins(QCP::msNone);
    ui->customPlot->axisRect()->setMargins(QMargins(0,0,0,0));
    //QPixmap pixmap = QPixmap (":/new/images/soccerfield.png").scaled(size(),Qt::KeepAspectRatioByExpanding);
    //ui->customPlot->setBackground(pixmap);
    ui->customPlot->setBackground(Qt::lightGray);


}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    qInfo() << "test" ;

    // declare a variable called player of type string
    QString Player;

    // Get selected text from combo box and save it in variable Player
    Player = ui->comboBox->currentText();

    // Set the text in the label using the variable Player
    // ui->label_2->setText(Player);

    // Set the image depending on player selected
    if (Player == "Player 1"){
        QPixmap picture(":/new/images/Jersey-1.jpg");
        ui->label->setPixmap(picture);
    }
    else if (Player == "Player 2"){
         QPixmap picture(":/new/images/Jersey-2.jpg");
         ui->label->setPixmap(picture);
    }

    else if (Player == "Player 3"){
         QPixmap picture(":/new/images/Jersey-3.jpg");
         ui->label->setPixmap(picture);
    }

    else if (Player == "Player 4"){
         QPixmap picture(":/new/images/Jersey-4.jpg");
         ui->label->setPixmap(picture);
    }

    else if (Player == "Player 5"){
         QPixmap picture(":/new/images/Jersey-5.jpg");
         ui->label->setPixmap(picture);
    }

    else if (Player == "Player 6"){
         QPixmap picture(":/new/images/Jersey-6.jpg");
         ui->label->setPixmap(picture);
    }

    else if (Player == "Player 7"){
         QPixmap picture(":/new/images/Jersey-7.jpg");
         ui->label->setPixmap(picture);
    }

    else if (Player == "Player 8"){
         QPixmap picture(":/new/images/Jersey-8.jpg");
         ui->label->setPixmap(picture);
    }

    else if (Player == "Player 9"){
         QPixmap picture(":/new/images/Jersey-9.jpg");
         ui->label->setPixmap(picture);
    }

    else if (Player == "Player 10"){
         QPixmap picture(":/new/images/Jersey-10.jpg");
         ui->label->setPixmap(picture);
    }

    else if (Player == "Player 11"){
         QPixmap picture(":/new/images/Jersey-11.jpg");
         ui->label->setPixmap(picture);
    }

    //set up plot
    setupDemo(2);
    //setupPlayground(ui->customPlot);
    // 1: setupQuadraticDemo(ui->customPlot);
    // 2: setupItemDemo(ui->customPlot);

}

void MainWindow::setupDemo(int demoIndex)
{
  switch (demoIndex)
  {
    case 1: setupQuadraticDemo(ui->customPlot); break;
    case 2: setupItemDemo(ui->customPlot); break;
  }
  setWindowTitle("QCustomPlot: "+demoName);
  statusBar()->clearMessage();
  currentDemoIndex = demoIndex;
  ui->customPlot->replot();
}

void MainWindow::setupQuadraticDemo(QCustomPlot *customPlot)
{
  demoName = "Quadratic Demo";

  // Works
  // File to read from
  QVector<double> x, y, v, v2;
  QVector<double> soccer_v, soccer_v2;
  int currentslidervalue;
  float sliderpercentage;
  //QFile textFile (":/new/files/02262017newdata.txt");
  //QFile textFile (":/new/files/decimaldatanew.txt");
  QFile textFile (":/new/files/17081103.txt");
  QFile textFile2 (":/new/files/soccerballcoordinates.txt");
  if(textFile.open(QIODevice::ReadOnly) && textFile2.open(QIODevice::ReadOnly))
    {
      qInfo() << "opened file successfully";
      double a, b;
      double soccer_a, soccer_b;
      QTextStream textStream (&textFile);
      QTextStream textStream2 (&textFile2);
      while (!textStream.atEnd() && !textStream2.atEnd()) {
        textStream >> a >> b;
        textStream2 >> soccer_a >> soccer_b;
        qInfo() << qSetRealNumberPrecision(8) << a <<" "<< qSetRealNumberPrecision(8) << b;
        qInfo() << qSetRealNumberPrecision(8) << soccer_a <<" "<< qSetRealNumberPrecision(8) << soccer_b;
        if(textStream.status() == QTextStream::Ok && textStream2.status() == QTextStream::Ok){
            v.append(a);
            v2.append(b);
            soccer_v.append(soccer_a);
            soccer_v2.append(soccer_b);

        }
        else
            break;
    }

      // Print num of lines in data file
      qInfo() << "number of data entries is" << v.size();

      // Get value of horizontal slider
      //double slidermax = *std::max_element(v.begin(), v.end());
      int slidermax = v.size();
      int slidermin = 0;
      ui->horizontalSlider->setMinimum(slidermin);
      qInfo() << "slider minimum is" << slidermin << endl;
      ui->horizontalSlider->setMaximum(slidermax);
      qInfo() << "slider maximum is" << slidermax << endl;
      currentslidervalue = ui->horizontalSlider->value();
      qInfo() << "value of slider is" << currentslidervalue;
      sliderpercentage = ((float)currentslidervalue/(float)slidermax) * 100;
      qInfo() << "slider percentage is" << sliderpercentage;

      qInfo() << "value is" << (sliderpercentage*v.size())/100;
      for(int i=0; i<(sliderpercentage*v.size())/100; ++i)
      {
          x.append(v[i]);
          y.append(v2[i]);
          qInfo() << "x" << qSetRealNumberPrecision(8) << i << "=" << qSetRealNumberPrecision(9) << x[i];
      }

  }

  ////////////////////////////////////////////////////////////////////////

  customPlot->clearPlottables();

  QCPCurve *closedcurve = new QCPCurve(customPlot->xAxis, customPlot->yAxis);


  ////////////////////////////////////////////
  // read complete data at once so that axes are set properly according to full data
  // generate the curve using all the data points:
  const int pointCount0 = v.size();
  QVector<QCPCurveData> dataSpiral(pointCount0) ;
  for (int i=0; i<pointCount0; ++i)
  {

    dataSpiral[i] = QCPCurveData(i, v[i], v2[i]);

  }
  // pass the data to the curves; we know t (i in loop above) is ascending, so set alreadySorted=true (saves an extra internal sort):
  closedcurve->data()->set(dataSpiral, true);
  closedcurve->setScatterStyle(QCPScatterStyle::ssDisc);

  // color the curves:
  closedcurve->setPen(QPen(Qt::blue));
  //test->setBrush(QBrush(QColor(0, 0, 255, 20)));

  // set some basic customPlot config:
  customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
  customPlot->axisRect()->setupFullAxesBox();
  customPlot->rescaleAxes();
 /////////////////////////////////////////////

  // generate the curve data points: read partial data according to slider position
  const int pointCount = (sliderpercentage*v.size())/100;
  QVector<QCPCurveData> dataSpiral1(pointCount) ;
  for (int i=0; i<pointCount; ++i)
  {

    dataSpiral1[i] = QCPCurveData(i, x[i], y[i]);

  }
  // pass the data to the curves; we know t (i in loop above) is ascending, so set alreadySorted=true (saves an extra internal sort):
  closedcurve->data()->set(dataSpiral1, true);
  closedcurve->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, Qt::blue, Qt::blue, 2));
  // color the curves:
  //closedcurve->setPen(QPen(Qt::blue));
  //closedcurve->setBrush(QBrush(QColor(0, 0, 255, 20)));

  //set some basic customPlot config:
  customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
  customPlot->axisRect()->setupFullAxesBox();
  customPlot->rescaleAxes();

  // give the axes some labels:
  customPlot->xAxis->setLabel("x");
  customPlot->yAxis->setLabel("y");

  QPixmap pixmap = QPixmap (":/new/images/soccerfield.png").scaled(size()); //best one so far
  customPlot->setBackground(pixmap);

  textFile.close();

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MainWindow::setupItemDemo(QCustomPlot *customPlot)
{
  demoName = "Soccer Ball Tracking Option 3";

  customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
  customPlot->axisRect()->setAutoMargins(QCP::msNone);
  customPlot->axisRect()->setMargins(QMargins(0,0,0,0));
  QCPGraph *graph = customPlot->addGraph();

 /////////////////////////////////////////////////////////
  // read x and y coordinate values from file
  QVector<double> x, y, v, v2;
  QVector<double> soccer_x, soccer_y, soccer_v, soccer_v2;
  int currentslidervalue;
  float sliderpercentage;
  //QFile textFile (":/new/files/02262017newdata.txt");
  //QFile textFile (":/new/files/decimaldatanew.txt");
  QFile textFile (":/new/files/17081103.txt");
  QFile textFile2 (":/new/files/soccerballcoordinates.txt");
  if(textFile.open(QIODevice::ReadOnly) && textFile2.open(QIODevice::ReadOnly))
    {
      qInfo() << "opened file successfully";
      double a, b;
      double soccer_a, soccer_b;
      QTextStream textStream (&textFile);
      QTextStream textStream2 (&textFile2);
      while (!textStream.atEnd() && !textStream2.atEnd()) {
        textStream >> a >> b;
        textStream2 >> soccer_a >> soccer_b;

        qInfo() << qSetRealNumberPrecision(8) << a <<" "<< qSetRealNumberPrecision(9) << b;
        qInfo() << qSetRealNumberPrecision(8) << soccer_a <<" "<< qSetRealNumberPrecision(9) <<soccer_b;
        if(textStream.status() == QTextStream::Ok && textStream2.status() == QTextStream::Ok){
            v.append(a);
            v2.append(b);
            x.append(a);
            y.append(b);
            soccer_v.append(soccer_a);
            soccer_v2.append(soccer_b);
            soccer_x.append(soccer_a);
            soccer_y.append(soccer_b);

        }
        else
            break;
    }
  }
///////////////////////////////////////////////////////////////////

  // Get value of horizontal slider
  int slidermax = 2500;
  int slidermin = 100;
  int slidersum = slidermin + slidermax;
  ui->horizontalSlider->setMinimum(slidermin);
  ui->horizontalSlider->setMaximum(slidermax);
  currentslidervalue = ui->horizontalSlider->value();
  qInfo() << "value of slider is" << currentslidervalue;
  sliderpercentage = ((float)currentslidervalue/(float)slidermax) * 100;
  qInfo() << "slider percentage is" << sliderpercentage;

  qInfo() << "element number of vector is" << (sliderpercentage*v.size())/100;
  qInfo() << "value of " << (sliderpercentage*v.size())/100 << "is" << v[((sliderpercentage*v.size())/100)-1];

  /*
  for(int i=0; i<(sliderpercentage*v.size())/100; ++i)
  {
      x.append(v[i]);
      y.append(v2[i]);
      qInfo() << "x" << i << "=" << x[i];
  }
  */

  ////////////////////////////////////////////////////////////////

  graph->setData(x, y);
  graph->setData(soccer_x,soccer_y);
  //color of line
  graph->setPen(QPen(Qt::red));
  graph->setLineStyle((QCPGraph::LineStyle)QCPGraph::lsNone);
  graph->rescaleKeyAxis();
  //customPlot->yAxis->setRange(-5, 5);
  //customPlot->yAxis->setRange(-1.45, 1.65);
  customPlot->xAxis->grid()->setZeroLinePen(Qt::NoPen);
  customPlot->rescaleAxes();
  x.clear();
  y.clear();
  soccer_x.clear();
  soccer_y.clear();
  graph->setData(x,y);
  graph->setData(soccer_x, soccer_y);

  // add the phase tracer (red circle) which sticks to the graph data (and gets updated in bracketDataSlot by timer event):
  QCPItemTracer *phaseTracer = new QCPItemTracer(customPlot);
  itemDemoPhaseTracer = phaseTracer; // so we can access it later in the bracketDataSlot for animation
  phaseTracer->setGraph(graph); // makes it stick to the graph data
  //phaseTracer->setGraphKey(v[((sliderpercentage*v.size())/100)-1]);
  phaseTracer->setInterpolating(false);
  phaseTracer->setStyle(QCPItemTracer::tsCircle);
  phaseTracer->setPen(QPen(Qt::red));
  phaseTracer->setBrush(Qt::red);
  phaseTracer->setSize(7);

  // add the phase tracer (red circle) which sticks to the graph data (and gets updated in bracketDataSlot by timer event):
  phaseTracer1 = new QCPItemTracer(customPlot);
  itemDemoPhaseTracer1 = phaseTracer1; // so we can access it later in the bracketDataSlot for animation
  phaseTracer1->setGraph(graph); // makes it stick to the graph data
  //phaseTracer->setGraphKey(v[((sliderpercentage*v.size())/100)-1]);
  phaseTracer1->setInterpolating(false);
  phaseTracer1->setStyle(QCPItemTracer::tsCircle);
  phaseTracer1->setPen(QPen(Qt::red));
  phaseTracer1->setBrush(QColor(255, 0, 0, 150));
  phaseTracer1->setSize(6);
  phaseTracer1->setVisible(false);

  // add the phase tracer (green circle) which sticks to the soccer ball graph data (and gets updated in bracketDataSlot by timer event):
  QCPItemTracer *phaseTracer2 = new QCPItemTracer(customPlot);
  itemDemoPhaseTracer2 = phaseTracer2; // so we can access it later in the bracketDataSlot for animation
  phaseTracer2->setGraph(graph); // makes it stick to the graph data
  //phaseTracer->setGraphKey(v[((sliderpercentage*v.size())/100)-1]);
  phaseTracer2->setInterpolating(false);
  phaseTracer2->setStyle(QCPItemTracer::tsCircle);
  phaseTracer2->setPen(QPen(Qt::green));
  phaseTracer2->setBrush(Qt::green);
  phaseTracer2->setSize(7);



  // setup a timer that repeatedly calls MainWindow::bracketDataSlot:
  connect(&dataTimer, SIGNAL(timeout()), this, SLOT(bracketDataSlot()));
  dataTimer.start(slidersum - currentslidervalue); // Interval 0 means to refresh as fast as possible
  qInfo() << "slider value is" << slidersum - currentslidervalue << endl;

  //try to change background color
  //QPixmap pixmap = QPixmap (":/new/images/soccerfield.png").scaled(size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
  QImage img(":/new/images/soccerfield.png");
  QPixmap pixmap;
  pixmap = pixmap.fromImage(img.scaled(1000, 500, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
  customPlot->setBackground(pixmap);

}

void MainWindow::realtimeDataSlot()
{
  static QTime time(QTime::currentTime());
  // calculate two new data points:
  double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
  static double lastPointKey = 0;
  if (key-lastPointKey > 0.002) // at most add point every 2 ms
  {
    // add data to lines:
    ui->customPlot->graph(0)->addData(key, qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843));
    ui->customPlot->graph(1)->addData(key, qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364));
    // rescale value (vertical) axis to fit the current data:
    //ui->customPlot->graph(0)->rescaleValueAxis();
    //ui->customPlot->graph(1)->rescaleValueAxis(true);
    lastPointKey = key;
  }
  // make key axis range scroll with the data (at a constant range size of 8):
  ui->customPlot->xAxis->setRange(key, 8, Qt::AlignRight);
  ui->customPlot->replot();

  // calculate frames per second:
  static double lastFpsKey;
  static int frameCount;
  ++frameCount;
  if (key-lastFpsKey > 2) // average fps over 2 seconds
  {
    ui->statusBar->showMessage(
          QString("%1 FPS, Total Data points: %2")
          .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
          .arg(ui->customPlot->graph(0)->data()->size()+ui->customPlot->graph(1)->data()->size())
          , 0);
    lastFpsKey = key;
    frameCount = 0;
  }
}


void MainWindow::bracketDataSlot()
{
  double secs = QCPAxisTickerDateTime::dateTimeToKey(QDateTime::currentDateTime());

  QVector<double> x, y, v, v2;
  QVector<double> soccer_x, soccer_y, soccer_v, soccer_v2;
  int currentslidervalue;
  float sliderpercentage;
   QFile textFile (":/new/files/17081103.txt");
   QFile textFile2 (":/new/files/soccerballcoordinates.txt");
  if(textFile.open(QIODevice::ReadOnly) && textFile2.open(QIODevice::ReadOnly))
    {
      qInfo() << "opened file successfully";
      double a, b;
      double soccer_a, soccer_b;
      QTextStream textStream (&textFile);
      QTextStream textStream2 (&textFile2);
      while (!textStream.atEnd() && !textStream2.atEnd()) {
          textStream >> a >> b;
          textStream2 >> soccer_a >> soccer_b;
          qInfo() << "a and b" << qSetRealNumberPrecision(8) << a <<" "<< qSetRealNumberPrecision(9) << b;
          qInfo() << "soccer a and soccer b" <<qSetRealNumberPrecision(8) << soccer_a <<" "<< qSetRealNumberPrecision(9) << soccer_b;
        if(textStream.status() == QTextStream::Ok && textStream2.status() == QTextStream::Ok){
            v.append(a);
            v2.append(b);
            x.append(a);
            y.append(b);
            soccer_v.append(soccer_a);
            soccer_v2.append(soccer_b);
            soccer_x.append(soccer_a);
            soccer_y.append(soccer_b);

       }
        else
            break;
    }
  }

  //add distance up to current point for all player positions
  if ( i >=1 ) {

      float p1_lat = x[i];
      qInfo() << "value compared to ideone for x is" << qSetRealNumberPrecision(8) << x[i] << endl;
      float p1_long = y[i];
      qInfo() << "value compared to ideone for y is" << qSetRealNumberPrecision(9) << y[i]<< endl;
      float p2_lat = x[i-1];
      qInfo() << "value compared to ideone for x-1 is" << qSetRealNumberPrecision(8) << x[i-1]<< endl;
      float p2_long = y[i-1];
      qInfo() << "value compared to ideone for y-1 is" << qSetRealNumberPrecision(9) << y[i-1]<< endl;

      // radius of the earth in km
      float earthradius = 6371.0;
      float deglat = deg2rad(p1_lat - p2_lat);
      //float deglat = qDegreesToRadians(p1_lat - p2_lat);
      float deglong = deg2rad(p1_long - p2_long);
      //float deglong = qDegreesToRadians(p1_long - p2_long);
      qInfo() << "value of degrees latitude in radians is " << deglat << endl;
      qInfo() << "value of degrees longitude in radians is " << deglong << endl;

      float a = (qSin(deglat/2))*(qSin(deglat/2)) + qCos(deg2rad(p1_lat)) * qCos(deg2rad(p2_lat)) * (qSin(deglong/2))*(qSin(deglong/2));
      qInfo() << "the value of a is " << a << endl;
      float c = 2.0 * qAtan2(sqrt(a), sqrt(1-a));
      qInfo() << "the value of c is " << c << " in radians" << endl;
      float d = earthradius * c;
      qInfo() << "the distance is " << d << " km" << endl;

      qInfo() << "total distance is" << totaldist << "km" <<endl;

      totaldist = totaldist + d ;
      qInfo() << "total distance is" << totaldist << "km" <<endl;

      double ts = 1;
      double instantaneousvelocity = (d*1000)/ts;

      ui->label_8->setText(QString::number(instantaneousvelocity, 'f', 2));

  }

  //calculate distance from player to soccer ball for each set of positions
  if ( i >=1 ) {

      float soccer_lat = soccer_x[i];
      qInfo() << "value compared to ideone for soccer ball x is" << qSetRealNumberPrecision(8) << soccer_x[i] << endl;
      float soccer_long = soccer_y[i];
      qInfo() << "value compared to ideone for socccer ball y is" << qSetRealNumberPrecision(9) << soccer_y[i]<< endl;
      float player_lat = x[i];
      qInfo() << "value compared to ideone for soccer ball x-1 is" << qSetRealNumberPrecision(8) << soccer_x[i-1]<< endl;
      float player_long = y[i];
      qInfo() << "value compared to ideone for soccer ball y-1 is" << qSetRealNumberPrecision(9) << soccer_y[i-1]<< endl;

      // radius of the earth in km
      float earthradius = 6371.0;
      float soccer_deglat = deg2rad(soccer_lat - player_lat);
      //float deglat = qDegreesToRadians(p1_lat - p2_lat);
      float soccer_deglong = deg2rad(soccer_long - player_long);
      //float deglong = qDegreesToRadians(p1_long - p2_long);
      qInfo() << "value of degrees latitude in radians is " << soccer_deglat << endl;
      qInfo() << "value of degrees longitude in radians is " << soccer_deglong << endl;

      float soc_a = (qSin(soccer_deglat/2))*(qSin(soccer_deglat/2)) + qCos(deg2rad(soccer_lat)) * qCos(deg2rad(player_lat)) * (qSin(soccer_deglong/2))*(qSin(soccer_deglong/2));
      qInfo() << "the value of soc_a is " << soc_a << endl;
      float soc_c = 2.0 * qAtan2(sqrt(soc_a), sqrt(1-soc_a));
      qInfo() << "the value of soc_c is " << soc_c << " in radians" << endl;
      float soc_d = earthradius * soc_c;
      qInfo() << "the distance is " << soc_d << " km" << endl;

      qInfo() << "total touch is" << totaltouch << endl;
      if(soc_d <= 0.0005){

          totaltouch = totaltouch +1;
      }

      qInfo() << "total touch is" << totaltouch << endl;

      ui->label_10->setText(QString::number(totaltouch, 'f', 0));

  }

  // display the calculted data
  ui->label_7->setText(QString::number(totaldist*1000, 'f', 2));
  double avgvel = totaldist / 1;

  ui->customPlot->graph()->setData(x, y);
  ui->customPlot->graph()->setData(soccer_x, soccer_y);


  int slidermax = 2500;
  ui->horizontalSlider->setMinimum(100);
  ui->horizontalSlider->setMaximum(slidermax);
  currentslidervalue = ui->horizontalSlider->value();
  qInfo() << "value of slider is" << currentslidervalue;


  static QTime time(QTime::currentTime());
  //calculate two new data points:
  double key1 = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
  static double lastPointKey = 0;

  qInfo() << "key value is " << key1;

  qInfo() << (key1 - lastPointKey) / 100;
  qInfo() << "x[i] is" << qSetRealNumberPrecision(8) << x[i];
  qInfo() << "y[i] is" << qSetRealNumberPrecision(9) << y[i];

  //itemDemoPhaseTracer->setGraphKey((8*M_PI+fmod(M_PI*1.5-phase, 6*M_PI))/k);
  itemDemoPhaseTracer->setGraphKey(x[i]);
  itemDemoPhaseTracer2->setGraphKey(soccer_x[i]);
  if (i>0){
      phaseTracer1->setVisible(true);
      itemDemoPhaseTracer1->setGraphKey(x[i-1]);
  }

  // ui->label_2->setText(QString::number(x[i], 'f', 6) + " " + QString::number(y[i], 'f', 6));
  i++;

  //reset when end of vector is reached
  if (i==x.size()) {
      totaldist = 0;
      totaltouch = 0;
      i=0;
  }

  ui->customPlot->replot();

  // calculate frames per second:
  double key = secs;
  static double lastFpsKey;
  static int frameCount;
  ++frameCount;
  if (key-lastFpsKey > 2) // average fps over 2 seconds
  {
    ui->statusBar->showMessage(
          QString("%1 FPS, Total Data points: %2")
          .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
          .arg(ui->customPlot->graph(0)->data()->size())
          , 0);
    lastFpsKey = key;
    frameCount = 0;
  }
  lastPointKey = key ;



  // Disable button
  ui->pushButton->setEnabled(false);

}

void MainWindow::setupPlayground(QCustomPlot *customPlot)
{
  Q_UNUSED(customPlot)
}

/*
MainWindow::~MainWindow()
{
  delete ui;
}
*/

void MainWindow::screenShot()
{
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
  QPixmap pm = QPixmap::grabWindow(qApp->desktop()->winId(), this->x()+2, this->y()+2, this->frameGeometry().width()-4, this->frameGeometry().height()-4);
#elif QT_VERSION < QT_VERSION_CHECK(5, 5, 0)
  QPixmap pm = qApp->primaryScreen()->grabWindow(qApp->desktop()->winId(), this->x()+2, this->y()+2, this->frameGeometry().width()-4, this->frameGeometry().height()-4);
#else
  QPixmap pm = qApp->primaryScreen()->grabWindow(qApp->desktop()->winId(), this->x()-7, this->y()-7, this->frameGeometry().width()+14, this->frameGeometry().height()+14);
#endif
  QString fileName = demoName.toLower()+".png";
  fileName.replace(" ", "");
  pm.save("./screenshots/"+fileName);
  qApp->quit();
}

void MainWindow::allScreenShots()
{
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
  QPixmap pm = QPixmap::grabWindow(qApp->desktop()->winId(), this->x()+2, this->y()+2, this->frameGeometry().width()-4, this->frameGeometry().height()-4);
#else
  QPixmap pm = qApp->primaryScreen()->grabWindow(qApp->desktop()->winId(), this->x()+2, this->y()+2, this->frameGeometry().width()-4, this->frameGeometry().height()-4);
#endif
  QString fileName = demoName.toLower()+".png";
  fileName.replace(" ", "");
  pm.save("./screenshots/"+fileName);

  if (currentDemoIndex < 19)
  {
    if (dataTimer.isActive())
      dataTimer.stop();
    dataTimer.disconnect();
    delete ui->customPlot;
    ui->customPlot = new QCustomPlot(ui->centralWidget);
    ui->verticalLayout->addWidget(ui->customPlot);
    setupDemo(currentDemoIndex+1);
    // setup delay for demos that need time to develop proper look:
    int delay = 250;
    if (currentDemoIndex == 10) // Next is Realtime data demo
      delay = 12000;
    else if (currentDemoIndex == 15) // Next is Item demo
      delay = 5000;
    QTimer::singleShot(delay, this, SLOT(allScreenShots()));
  } else
  {
    qApp->quit();
  }
}


void MainWindow::on_horizontalSlider_sliderMoved(int position)
{

    int slidermax = 2500;
    int slidermin = 100;
    int slidersum = slidermin + slidermax;
    ui->horizontalSlider->setMinimum(slidermin);
    ui->horizontalSlider->setMaximum(slidermax);
    int currentslidervalue = ui->horizontalSlider->value();
    //connect(&dataTimer, SIGNAL(timeout()), this, SLOT(bracketDataSlot()));
    dataTimer.start(slidersum - currentslidervalue); // Interval 0 means to refresh as fast as possible

    int a = ui->horizontalSlider->value();
    QString s = QString::number(a);
    // ui->label_2->setText(s);

}

/*
void MainWindow::on_pushButton_2_clicked()
{
    ui->pushButton->setEnabled(true);
}
*/

float MainWindow::deg2rad(float x){

    float xinrad = (x * M_PI)/180;

    return xinrad;
}
