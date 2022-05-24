#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string.h>
#include <math.h>

wchar_t word = L'°';
int put_1,put_2,put_3;
QString b;
double k;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_sign->setVisible(0);
    ui->pushButton_sign_2->setVisible(0);
    ui->pushButton_ac->setVisible(0);
    sign_off();
    setFixedWidth(270);
    connect(ui->pushButton_0,SIGNAL(clicked()),this,SLOT(input_numbers()));
    connect(ui->pushButton_1,SIGNAL(clicked()),this,SLOT(input_numbers()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(input_numbers()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(input_numbers()));
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(input_numbers()));
    connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(input_numbers()));
    connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(input_numbers()));
    connect(ui->pushButton_7,SIGNAL(clicked()),this,SLOT(input_numbers()));
    connect(ui->pushButton_8,SIGNAL(clicked()),this,SLOT(input_numbers()));
    connect(ui->pushButton_9,SIGNAL(clicked()),this,SLOT(input_numbers()));
    connect(ui->pushButton_plus,SIGNAL(clicked()),this,SLOT(mathematics()));
    connect(ui->pushButton_minus,SIGNAL(clicked()),this,SLOT(mathematics()));
    connect(ui->pushButton_multiply,SIGNAL(clicked()),this,SLOT(mathematics()));
    connect(ui->pushButton_divide,SIGNAL(clicked()),this,SLOT(mathematics()));
    connect(ui->pushButton_equally,SIGNAL(clicked()),this,SLOT(mathematics()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::input_numbers(){

    QPushButton *button = (QPushButton *)sender();

    QString all_symbols=ui->label->text();

    if (ui->label->text().length()<16&&!ui->label->text().endsWith('"')) {
    all_symbols+=button->text();                                //добавляет цифру если есть свободное место в строке
    }

    if ((all_symbols[0]=='0')&&((all_symbols[1]=='0')||(all_symbols[1]=='1')||(all_symbols[1]=='2')||(all_symbols[1]=='3')||(all_symbols[1]=='4')||(all_symbols[1]=='5')||(all_symbols[1]=='6')||(all_symbols[1]=='7')||(all_symbols[1]=='8')||(all_symbols[1]=='9'))){
        all_symbols=all_symbols.right(1);                       //убирает 0 если ввели другую цифру, чтобы не было вот так: 0654+075=0729
    }
    ui->pushButton_c->setVisible(1);
    ui->pushButton_ac->setVisible(0);
    ui->label->setText(all_symbols);

}


void MainWindow::on_pushButton_backspace_clicked()
{
    if (!(ui->label->text()=="0")){                         //если строка не нулевая то
        if(ui->label->text().endsWith('"')){                //если хотим удалить " то показываем кнопку ", а остальные скрываем

            ui->pushButton_round->setVisible(0);
            ui->pushButton_sign->setVisible(0);
            ui->pushButton_sign_2->setVisible(1);

        } else if(ui->label->text().endsWith("'")){         //если хотим удалить ' то показываем кнопку ', а остальные скрываем

            ui->pushButton_round->setVisible(0);
            ui->pushButton_sign->setVisible(1);
            ui->pushButton_sign_2->setVisible(0);

        } else if(ui->label->text().endsWith(word)){        //если хотим удалить ° то показываем кнопку °, а остальные скрываем

            ui->pushButton_round->setVisible(1);
            ui->pushButton_sign->setVisible(0);
            ui->pushButton_sign_2->setVisible(0);
        }
        ui->label->setText(ui->label->text().left(ui->label->text().length()-1));                   //удаляем последний символ

    }
    if (ui->label->text().isEmpty()){                                                               //если основная строка пустая то пишем ноль
        ui->label->setText("0");
    }
}


void MainWindow::input_symbols(){
    /*QPushButton *button = (QPushButton *)sender();

    QString all_symbols=ui->label->text();
    wchar_t word = L'°';
    if (!(all_symbols.endsWith(word)||all_symbols.endsWith('"')||all_symbols.endsWith("'"))){
        all_symbols+=button->text();                            //добавляет символ градусной меры усли это возможно
    }
    if (!(all_symbols.contains(word))){
        all_symbols+=button->text();
    }
    ui->label->setText(all_symbols);*/
}


void MainWindow::on_pushButton_dot_clicked()                //ставим запятую так чтобы не было лишних
{
    if(((1+ui->label->text().contains(word)+ui->label->text().contains("'")+ui->label->text().contains('"'))>ui->label->text().count(','))&&!(ui->label->text().endsWith(word)||ui->label->text().endsWith('"')||ui->label->text().endsWith("'"))){
    ui->label->setText(ui->label->text()+",");
    }
}


void MainWindow::on_pushButton_round_clicked()              //ставим символ градусов ° и прятаем кнопку, а кнопку минут ' показываем
{
    if(!(ui->label->text().contains(word))){
    ui->label->setText(ui->label->text()+word);
    ui->pushButton_round->hide();
    ui->pushButton_sign->setVisible(1);
    }
}


void MainWindow::on_pushButton_sign_clicked()               //аналогично, но минуты меняем на секунды
{
    if(!(ui->label->text().contains("'")||ui->label->text().endsWith(word))){
    ui->label->setText(ui->label->text()+"'");
    ui->pushButton_sign->hide();
    ui->pushButton_sign_2->setVisible(1);
    }
}


void MainWindow::on_pushButton_sign_2_clicked()             //аналогично, но секунды меняем на градусы
{
    if(!(ui->label->text().contains('"')||ui->label->text().endsWith("'"))){
    ui->label->setText(ui->label->text()+'"');
    ui->pushButton_sign_2->hide();
    ui->pushButton_round->setVisible(1);
    }
}


void MainWindow::on_pushButton_c_clicked()                  //очищаем строку
{
    ui->label->setText("0");
    ui->pushButton_sign->setVisible(0);                 //и возвращаем символы мер в исходное состояние
    ui->pushButton_sign_2->setVisible(0);
    ui->pushButton_round->setVisible(1);
    if (!ui->label_2->text().isEmpty()){                    //если нижняя строка знака не пуста то заменяем кнопку на AC
        ui->pushButton_c->hide();
        ui->pushButton_ac->setVisible(1);
    }
}



void MainWindow::mathematics()
{

    b=ui->label->text();

    k=b.split(word)[0].toDouble()+b.remove(0,b.indexOf(word)+1).split("'")[0].toDouble()+b.remove(0,b.indexOf("'")+1).split('"')[0].toDouble();
//      ui->label_4->setText(QString::number(k,'g',15));
    QPushButton *button = (QPushButton *)sender();

    if(!(ui->label->text()=='0')){
        if((put_1==5)||ui->label_2->text()==""){
            put_1 = button->toolTipDuration();
            sign_on(put_1);
            if(put_1==5){
                b=ui->label->text();
                ui->label_2->setText(b);
                k=b.split(word)[0].toDouble()*3600+b.remove(0,b.indexOf(word)+1).split("'")[0].toDouble()*60+b.remove(0,b.indexOf("'")+1).split('"')[0].toDouble();
                ui->label->setText(QString::number(floor(k/3600),'g',8)+word+QString::number((fmod(k,3600)-fmod(k,60))/60,'g',8)+"'"+QString::number(fmod(k,60),'g',8)+'"');
            }else {
                ui->label_2->setText(ui->label->text());
                ui->label->setText("0");
                ui->pushButton_sign->setVisible(0);                 //и возвращаем символы мер в исходное состояние
                ui->pushButton_sign_2->setVisible(0);
                ui->pushButton_round->setVisible(1);
            }
        } else {

            if(button->toolTipDuration()==5){
                b=ui->label_2->text();
                k=b.split(word)[0].toDouble()*3600+b.remove(0,b.indexOf(word)+1).split("'")[0].toDouble()*60+b.remove(0,b.indexOf("'")+1).split('"')[0].toDouble();
                b=ui->label->text();
                switch (put_1){
                case 1:{
                    k=k-(b.split(word)[0].toDouble()*3600+b.remove(0,b.indexOf(word)+1).split("'")[0].toDouble()*60+b.remove(0,b.indexOf("'")+1).split('"')[0].toDouble());
                    ui->label->setText(QString::number(floor(k/3600),'g',8)+word+QString::number((fmod(k,3600)-fmod(k,60))/60,'g',8)+"'"+QString::number(fmod(k,60),'g',8)+'"');
                }
                  break;
                case 2:{
                    k=k+b.split(word)[0].toDouble()*3600+b.remove(0,b.indexOf(word)+1).split("'")[0].toDouble()*60+b.remove(0,b.indexOf("'")+1).split('"')[0].toDouble();
                    ui->label->setText(QString::number(floor(k/3600),'g',8)+word+QString::number((fmod(k,3600)-fmod(k,60))/60,'g',8)+"'"+QString::number(fmod(k,60),'g',8)+'"');
                }
                  break;
                case 3:{
                    k=k*b.toDouble();
                    ui->label->setText(QString::number(floor(k/3600),'g',8)+word+QString::number((fmod(k,3600)-fmod(k,60))/60,'g',8)+"'"+QString::number(fmod(k,60),'g',8)+'"');
                }
                  break;
                case 4:
                    if (b.contains(word)){
                        k=k/(b.split(word)[0].toDouble()*3600+b.remove(0,b.indexOf(word)+1).split("'")[0].toDouble()*60+b.remove(0,b.indexOf("'")+1).split('"')[0].toDouble());
                        ui->label->setText(QString::number(k,'g',8));
                    }else{
                        k=k/b.toDouble();
                        ui->label->setText(QString::number(floor(k/3600),'g',8)+word+QString::number((fmod(k,3600)-fmod(k,60))/60,'g',8)+"'"+QString::number(fmod(k,60),'g',8)+'"');
                    }
                  break;
                }
                ui->label_2->setText("");
                sign_off();
                ui->pushButton_sign->setVisible(0);                 //и возвращаем символы мер в исходное состояние
                ui->pushButton_sign_2->setVisible(0);
                ui->pushButton_round->setVisible(1);
            }
        }
    }
















    /*if(!(ui->label->text()=='0')){
        if(put_1==5){
            put_1 = button->toolTipDuration();
            ui->label_2->setText(ui->label->text());
            if(put_1==5){
                k=b.split(word)[0].toDouble()+b.remove(0,b.indexOf(word)+1).split("'")[0].toDouble()+b.remove(0,b.indexOf("'")+1).split('"')[0].toDouble();
                ui->label->setText(QString::number(k,'g',15));
            }
            ui->label->setText("0");
            sign_on(put_1);
        }
        if(!(ui->label_2->text()=='0')){

        }
        put_1 = button->toolTipDuration();
        ui->label_2->setText(ui->label->text());
        ui->label->setText("0");
        sign_on(put_1);
    }*/


}



void MainWindow::sign_on(int number){
    ui->label_minus_1->setVisible(0);
    ui->label_plus_1->setVisible(0);
    ui->label_multiply_1->setVisible(0);
    ui->label_divide_1->setVisible(0);
    switch ( number ) {
    case 1:
        ui->label_minus_1->setVisible(1);
      break;
    case 2:
        ui->label_plus_1->setVisible(1);
      break;
    case 3:
        ui->label_multiply_1->setVisible(1);
      break;
    case 4:
        ui->label_divide_1->setVisible(1);
      break;
    }
}



void MainWindow::sign_off(){
    ui->label_minus_1->setVisible(0);
    ui->label_plus_1->setVisible(0);
    ui->label_multiply_1->setVisible(0);
    ui->label_divide_1->setVisible(0);
};



void MainWindow::on_pushButton_clicked()
{
    if(width()==460){
        setFixedWidth(270);
    } else {
        setFixedWidth(460);
    }
}

void MainWindow::on_pushButton_ac_clicked()
{
    ui->label_2->setText("");
    ui->label->setText("0");
    sign_off();
    ui->pushButton_sign->setVisible(0);                 //и возвращаем символы мер в исходное состояние
    ui->pushButton_sign_2->setVisible(0);
    ui->pushButton_round->setVisible(1);
    put_1=0;
    ui->pushButton_c->setVisible(1);
    ui->pushButton_ac->setVisible(0);
}

