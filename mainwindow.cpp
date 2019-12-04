#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <derivation.hpp>
#include <string>
#include <sstream>
#include <polynomialchecker.hpp>
#include <parsepolynomial.hpp>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  /*Simple X;

  auto f = 3 * Pow(X, 5) - 2 * Pow(X,4) + Pow(X,3) - 10 * Pow(X, 2) + X + 2;
  auto df = derivative(f);
  QString str = QString::number(df(2));
  std::string exp = "3*x^5-2*x^4+x^3-10*x^2+5*x+2";
  std::string exp1 = "2*x^2+2*x";
  PolynomialChecker pc(exp);
  pc.isCorrect();
  std::stringstream stream(exp);
  ParsePolynomial pp(stream);
  double d = pp.getResult();
  std::cout << d << "\n";
  QString str2 = QString::number(d);*/
  connect(ui->button_0, SIGNAL(clicked(bool)), this, SLOT(get_numbers()));
  connect(ui->button_1, SIGNAL(clicked(bool)), this, SLOT(get_numbers()));
  connect(ui->button_2, SIGNAL(clicked(bool)), this, SLOT(get_numbers()));
  connect(ui->button_3, SIGNAL(clicked(bool)), this, SLOT(get_numbers()));
  connect(ui->button_4, SIGNAL(clicked(bool)), this, SLOT(get_numbers()));
  connect(ui->button_5, SIGNAL(clicked(bool)), this, SLOT(get_numbers()));
  connect(ui->button_6, SIGNAL(clicked(bool)), this, SLOT(get_numbers()));
  connect(ui->button_7, SIGNAL(clicked(bool)), this, SLOT(get_numbers()));
  connect(ui->button_8, SIGNAL(clicked(bool)), this, SLOT(get_numbers()));
  connect(ui->button_9, SIGNAL(clicked(bool)), this, SLOT(get_numbers()));
  connect(ui->button_x, SIGNAL(clicked(bool)), this, SLOT(get_x()));
  connect(ui->pushButton_send, SIGNAL(clicked(bool)), this, SLOT(send_expression()));
  connect(ui->pushButton_minus, SIGNAL(clicked(bool)), this, SLOT(get_operations()));
  connect(ui->pushButton_plus, SIGNAL(clicked(bool)), this, SLOT(get_operations()));
  connect(ui->pushButton_mult, SIGNAL(clicked(bool)), this, SLOT(get_operations()));
  connect(ui->pushButton_degree, SIGNAL(clicked(bool)), this, SLOT(get_operations()));
  connect(ui->pushButton_getResult, SIGNAL(clicked(bool)), this, SLOT(get_result()));
  ui->pushButton_degree->setCheckable(true);
  ui->pushButton_plus->setCheckable(true);
  ui->pushButton_minus->setCheckable(true);
  ui->pushButton_mult->setCheckable(true);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::get_result()
{
  std::string expression = ui->resultShow->text().toStdString();
  PolynomialChecker polynomialChecker(expression);
  if (polynomialChecker.isCorrect())
  {
    std::stringstream stream(expression);
    ParsePolynomial parseString(stream);
    ui->derivationResult->setText(QString::number(parseString.getResult(ui->x_value->text().toDouble())));
  }
}

bool MainWindow::isOperation(QString str)
{
  return ((str == "*") || (str == "+") || (str == "-") || (str == "^"));
}

void MainWindow::get_numbers()
{
  QPushButton *button = (QPushButton *) sender();
  QString new_label = ui->resultShow->text() + button->text();
  ui->resultShow->setText(new_label);
}

void MainWindow::send_expression()
{
  ui->resultShow->setText(ui->resultKeyBoardShow->text());
}

void MainWindow::on_pushButton_dot_clicked()
{
  if (!(ui->resultShow->text().contains('.')))
    ui->resultShow->setText(ui->resultShow->text() + ".");
}

void MainWindow::get_operations()
{
  QPushButton *button = (QPushButton *) sender();
  QString new_label;
  if (button->isChecked())
  {
    if (!isOperation( ui->resultShow->text().at(ui->resultShow->text().length() - 1)))
    {
      ui->resultShow->setText(ui->resultShow->text() + button->text());
    }
  }
  button->setChecked(false);
}

void MainWindow::on_pushButton_clear_clicked()
{
    ui->resultShow->setText("");
}

void MainWindow::get_x()
{
  QPushButton *button = (QPushButton *) sender();
  QString new_label;
  if ((ui->resultShow->text().length() == 0) || (isOperation(ui->resultShow->text().at(ui->resultShow->text().length() - 1))
      && (!isdigit(button->text().toInt()))))
  {
    ui->resultShow->setText(ui->resultShow->text() + button->text());
  }
}

