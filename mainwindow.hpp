#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  bool isOperation(QString str);
private slots:
  void get_numbers();
  void on_pushButton_dot_clicked();
  void get_operations();
  void get_x();
  void get_result();
  void on_pushButton_clear_clicked();
  void send_expression();
  void on_eraseLast_clicked();
};

#endif // MAINWINDOW_HPP
