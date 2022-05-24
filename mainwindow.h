#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void input_symbols();
    void input_numbers();
    void mathematics();
    void on_pushButton_dot_clicked();
    void on_pushButton_round_clicked();
    void on_pushButton_sign_clicked();
    void on_pushButton_sign_2_clicked();
    void on_pushButton_c_clicked();
    void on_pushButton_backspace_clicked();
    void sign_on(int);
    void sign_off();
    void on_pushButton_clicked();
    void on_pushButton_ac_clicked();
};
#endif // MAINWINDOW_H
