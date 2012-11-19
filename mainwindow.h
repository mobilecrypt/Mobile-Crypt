#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <cmath>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    enum
    {
        state_inverse = 0,
        state_rsa_crypt = 1,
        state_rsa_sign = 2,
        state_rsa_decrypt = 3,
        state_euler = 4,
        state_pocklington = 5,
        state_gcd = 6,
        state_power = 7,
        state_order = 8,
        state_primitiv = 9,
        state_rabin_crypt = 10,
        state_rabin_decrypt = 11
    } states;

    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    void changeState(const QString& state);
    void changeCalcButton(const QString& state);
    void changeLabels();
    ~MainWindow();
    bool calculatePocklington(int _prime, int _factor);
    bool PocklingtonFirstTest(int _prime, int _factor);
    bool PocklingtonSecondTest(int _prime, int _factor);
    bool PocklingtonThirdTest(int _prime, int _factor);
    int gcd(int a,int b);
    void print(const QString& string);
    int calculateInverse(int _number, int _euler);
    long long calculatePower(int _factor, int _number, int _power, int _modulo);


    long long calculateRSACrypt(int _message, int _pk, int _modulus);

    long long calculateRSASign(int _message, int _p, int _q, int _pk);
    long long calculateRSADecrypt(int _message, int _p, int _q, int _pk);
    int calculatePrimitivElement(int _euler, int _modulu);
    int calculateOrder(int _element, int _modulu, int _euler);
    int calculateRabinCrypt(int message, int modulus);
    int calculateRabinDeCrypt(int message, int p, int q);
    bool isMirrored(const int number);
    int halfNumber(const int number);
public slots:
    void addNumber();
    void stateRotator();
    void TextfieldRotator();
    void clearTextField();
    void compute();
    void quit();
    
private:
    Ui::MainWindow *ui;
    QLineEdit* currentLineEdit;
    int state;
};

#endif // MAINWINDOW_H
