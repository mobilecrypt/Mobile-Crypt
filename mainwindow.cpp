#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_0,SIGNAL(clicked()),this, SLOT(addNumber()));
    connect(ui->pushButton_1,SIGNAL(clicked()),this, SLOT(addNumber()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this, SLOT(addNumber()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this, SLOT(addNumber()));
    connect(ui->pushButton_4,SIGNAL(clicked()),this, SLOT(addNumber()));
    connect(ui->pushButton_5,SIGNAL(clicked()),this, SLOT(addNumber()));
    connect(ui->pushButton_6,SIGNAL(clicked()),this, SLOT(addNumber()));
    connect(ui->pushButton_7,SIGNAL(clicked()),this, SLOT(addNumber()));
    connect(ui->pushButton_8,SIGNAL(clicked()),this, SLOT(addNumber()));
    connect(ui->pushButton_9,SIGNAL(clicked()),this, SLOT(addNumber()));
    connect(ui->nextAlgoButton,SIGNAL(clicked()),this, SLOT(stateRotator()));
    connect(ui->forwardButton,SIGNAL(clicked()),this, SLOT(TextfieldRotator()));
    connect(ui->clearButton,SIGNAL(clicked()),this, SLOT(clearTextField()));
    connect(ui->calcButton, SIGNAL(clicked()),this,SLOT(compute()));
    connect(ui->button_quit, SIGNAL(clicked()),this,SLOT(quit()));

    currentLineEdit = ui->lineEdit_1;

    currentLineEdit->setEnabled(true);
    state = this->state_inverse;
    changeCalcButton("inverse");
    changeLabels();
}

void MainWindow::changeState(const QString &_state)
{
    if(_state == "inverse")
    {
        state = state_inverse;
    }

    if(_state == "euler")
    {
        state = state_euler;
    }

    else if(_state == "rsa_crypt")
    {
        state = state_rsa_crypt;
    }

    else if(_state == "rsa_sign")
    {
        state = state_rsa_sign;
    }

    else if(_state == "rsa_decrypt")
    {
        state = state_rsa_decrypt;
    }

    else if(_state == "pocklington")
    {
        state = state_pocklington;
    }

    else if(_state == "gcd")
    {
        state = state_gcd;
    }

    else if(_state == "power")
    {
        state = state_power;
    }

    else if(_state == "order")
    {
        state = state_order;
    }

    else if(_state == "primitiv")
    {
        state = state_primitiv;
    }

    else if(_state == "RabinCrypt")
    {
        state = state_rabin_crypt;
    }

    else if(_state == "RabinDecrypt")
    {
        state = state_rabin_decrypt;
    }

    else
    {
        state = state_inverse;
    }
    changeCalcButton(_state);
    changeLabels();
}

void MainWindow::changeCalcButton(const QString &state)
{
    ui->calcButton->setText(state);
}

void MainWindow::changeLabels()
{
    if(state == state_inverse)
    {
        ui->label_1->setText("Number");
        ui->label_2->setText("Euler");
        ui->label_3->setText("x");
        ui->label_4->setText("x");
    }

    else if(state == state_rsa_crypt)
    {
        ui->label_1->setText("M");
        ui->label_2->setText("PK");
        ui->label_3->setText("modolus");
        ui->label_4->setText("x");
    }

    else if(state == state_rsa_sign)
    {
        ui->label_1->setText("M");
        ui->label_2->setText("p");
        ui->label_3->setText("q");
        ui->label_4->setText("PK");
    }

    else if(state == state_rsa_decrypt)
    {
        ui->label_1->setText("M");
        ui->label_2->setText("p");
        ui->label_3->setText("q");
        ui->label_4->setText("PK");
    }

    else if(state == state_euler)
    {
        ui->label_1->setText("Number");
        ui->label_2->setText("x");
        ui->label_3->setText("x");
        ui->label_4->setText("x");
    }

    else if(state == state_pocklington)
    {
        ui->label_1->setText("Prime");
        ui->label_2->setText("Factor");
        ui->label_3->setText("x");
        ui->label_4->setText("x");
    }

    else if(state == state_gcd)
    {
        ui->label_1->setText("a");
        ui->label_2->setText("b");
        ui->label_3->setText("x");
        ui->label_4->setText("x");
    }

    else if(state == state_power)
    {
        ui->label_1->setText("Factor");
        ui->label_2->setText("Number");
        ui->label_3->setText("Power");
        ui->label_4->setText("Modulu");
        ui->lineEdit_1->setText("1");
    }

    else if(state == state_order)
    {
        ui->label_1->setText("Element");
        ui->label_2->setText("Modulu");
        ui->label_3->setText("Euler");
        ui->label_4->setText("x");
    }

    else if(state == state_primitiv)
    {
        ui->label_1->setText("Euler");
        ui->label_2->setText("Modulu");
        ui->label_3->setText("x");
        ui->label_4->setText("x");
    }

    else if(state == state_rabin_crypt)
    {
        ui->label_1->setText("Message");
        ui->label_2->setText("Modulu");
        ui->label_3->setText("x");
        ui->label_4->setText("x");
    }

    else if(state == state_rabin_decrypt)
    {
        ui->label_1->setText("Message");
        ui->label_2->setText("p");
        ui->label_3->setText("q");
        ui->label_4->setText("x");
    }


    else
    {
        ui->label_1->setText("Number");
        ui->label_2->setText("Euler");
        ui->label_3->setText("x");
        ui->label_4->setText("x");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

long long MainWindow::calculateRSACrypt(int _message, int _pk, int _modulus)
{
    long long powerNumber = _message;

    //counter = 1 because 2 ^ 1 = 2
    for(int counter = 1; counter < _pk; counter++)
    {
        powerNumber = (powerNumber * _message) % _modulus;
    }

    print("Message " + QString::number(_message) + " ^ " + QString::number(_pk) + " % " + QString::number(_modulus) + " = " + QString::number(powerNumber) + "\n");
    return(powerNumber);
}

long long MainWindow::calculateRSADecrypt(int _message, int _p, int _q, int _pk)
{
    int euler = (_p-1)*(_q-1);
    int modulus = _p * _q;
    long long inverse = calculateInverse(_pk,euler);
    long long powerNumber = _message;

    for(long long counter = 1; counter < inverse; counter++)
    {
        powerNumber = (powerNumber * _message) % modulus;
    }

    print("Cryptogram " + QString::number(_message) + " is decrypted with " + QString::number(_message) + "^" + QString::number(inverse) + " % " + QString::number(modulus) + " = " + QString::number(powerNumber)+"\n");
    return(powerNumber);
}


long long MainWindow::calculateRSASign(int _message, int _p, int _q, int _pk)
{
    int euler = (_p-1)*(_q-1);
    int modulus = _p * _q;
    long long inverse = calculateInverse(_pk,euler);
    long long powerNumber = _message;

    for(long long counter = 1; counter < inverse; counter++)
    {
        powerNumber = (powerNumber * _message) % modulus;
    }

    print("Message " + QString::number(_message) + " is signed with " + QString::number(_message) + "^" + QString::number(inverse) + " % " + QString::number(modulus) + " = " + QString::number(powerNumber)+"\n");

    return(powerNumber);
}

bool MainWindow::calculatePocklington(int _prime, int _factor)
{
    if(!PocklingtonFirstTest(_prime,_factor))
    {
        return(false);
    }
    if(!PocklingtonSecondTest(_prime,_factor))
    {
        return(false);
    }

    return PocklingtonThirdTest(_prime,_factor);
}

bool MainWindow::PocklingtonFirstTest(int _prime, int _factor)
{
    long long powerNumber = (long long) pow(_factor, ((_factor*_prime)/_prime));
    long long gcd_number = gcd(powerNumber,(_prime*_factor+1));

    print("gcd of " + QString::number(powerNumber) + " " + QString::number(_prime*_factor+1) + " is " + QString::number(gcd_number) + "\n");

    if(gcd_number == 1)
    {
        return(true);
    }
    return(false);
}

bool MainWindow::PocklingtonSecondTest(int _prime, int _factor)
{
    long long newPrime = _factor * _prime + 1;
    long long powerNumber = _factor;

    //counter = 1 because 2 ^ 1 = 2
    for(int counter = 1; counter < newPrime-1; counter++)
    {
        powerNumber = (powerNumber * _factor) % newPrime;

    }

    print(QString::number(_factor) + " ^ " + QString::number(newPrime-1) + " % " + QString::number(newPrime) + " = " + QString::number(powerNumber)+"\n");


    return(powerNumber == 1);
}

bool MainWindow::PocklingtonThirdTest(int _prime, int _factor)
{
    print(QString::number(_prime) + " > " + QString::number(sqrt(_prime*_factor+1)) + "\n");
    return(_prime > sqrt(_prime*_factor+1));
}

int MainWindow::gcd(int a, int b)
{
    while( 1 )
    {
        a = a % b;
        if( a == 0 )
            return b;
        b = b % a;

        if( b == 0 )
            return a;
    }
}

void MainWindow::print(const QString &string)
{
    ui->output->setText(ui->output->toPlainText() + string);
}

int MainWindow::calculateInverse(int _number, int _euler)
{
    if(gcd(_number,_euler) != 1)
    {
        print("gcd(" + QString::number(_number) + "," + QString::number(_euler) + ") != 1 (" + QString::number(gcd(_number,_euler)) + ")");
        return(0);
    }

    int n1 = _euler;
    int n2 = _number;
    int a1 = 1;
    int a2 = 0;
    int b1 = 0;
    int b2 = 1;
    int q = 0;
    int r = 0;
    int temp = 0;
    int cnt = 0;

    print(QString::number(n1) + "," + QString::number(n2) + "," + QString::number(a1) + "," + QString::number(b1) + "," + QString::number(a2) + "," + QString::number(b2) + "," + QString::number(q) + "," + QString::number(r) + "\n");

    do
    {
        cnt++;

        if(n1 < n2)
        {
            temp = n2;
            n2 = n1;
            n1 = temp;
        }



        q = (int) (((float)(n1)) / n2);
        r = n1 % n2;
        temp = b1;
        b1 = b2;
        b2 = temp - q * b2;
        temp = a1;
        a1 = a2;
        a2 = temp - a2 *q;

        if(r > n2)
        {
            n1 = r;
            n2 = n2;
        }
        else
        {
            n1 = n2;
            n2 = r;
        }

        print(QString::number(n1) + "," + QString::number(n2) + "," + QString::number(a1) + "," + QString::number(b1) + "," + QString::number(a2) + "," + QString::number(b2) + "," + QString::number(q) + "," + QString::number(r) + "\n");
    }while(r != 1 && cnt < 1000);

    if(b2 < 0)
    {
        b2 = b2+_euler;
    }

    return(b2);
}

long long MainWindow::calculatePower(int _factor, int _number, int _power, int _modulo)
{
    long long powerNumber = _number;

    //counter = 1 because 2 ^ 1 = 2
    for(int counter = 1; counter < _power; counter++)
    {
        powerNumber = (powerNumber * _number) % _modulo;

    }

    powerNumber = (powerNumber * _factor) % _modulo;

    print(QString::number(_factor) + "*" + QString::number(_number) + " ^ " + QString::number(_power) + " % " + QString::number(_modulo) + " = " + QString::number(powerNumber)+"\n");
    return(powerNumber);
}

int MainWindow::calculatePrimitivElement(int _euler, int _modulu)
{
    print("Number of Primitive Elements = Euler(Euler(Prime)).\n");
    print("% of Primitives Elements = Above Number / Euler(Prim).\n");

    for (int i = 2; i <= _euler; i++)
    {
        if(calculateOrder(i,_modulu,_euler) == _euler)
        {
            return(i);
        }
    }
    return(0);
}

int MainWindow::calculateOrder(int _element, int _modulu, int _euler)
{
    int stop = (int) (_euler / 2);
    int result = 0;

    if(gcd(_element,_modulu) == 1)
    {
        for(int i = 1; i <= stop; i++)
        {
            if(_euler % i == 0)
            {
                result = calculatePower(1,_element,i,_modulu);
                if(result == 1)
                {
                    return(i);
                }
            }
        }
        return(_euler);
    }
    return(0);
}

int MainWindow::calculateRabinCrypt(int message, int modulus)
{
    int bitcounter = message;
    int counter = 0;
    long long doubledMessage;

    while(bitcounter > 0)
    {
        bitcounter = bitcounter>>1;
        counter++;
    }

    doubledMessage = message + (message<<counter);

    long long cryptedMessage = doubledMessage*doubledMessage%modulus;

    print("Number: " + QString::number(message) + " / " + QString::number(message,2)+"\n");
    print("Doubled Number: " + QString::number(doubledMessage) + " / " + QString::number(doubledMessage,2)+"\n");
    print(QString::number(doubledMessage) + "*" + QString::number(doubledMessage) + "%" + QString::number(modulus) + "=" + QString::number(cryptedMessage) + " / " + QString::number(cryptedMessage,2)+"\n");
    return(cryptedMessage);

}

int MainWindow::calculateRabinDeCrypt(int message, int p, int q)
{
    int a,b;
    int decrypted = -1;

    for(a = 1; a < 1000; a++)
    {
        for(b = 1; b < 1000; b++)
        {
            if(p*a-q*b == 1)
            {
                break;
            }
            else if(p*a-q*b < 1)
            {
                break;
            }
        }
        if(p*a-q*b == 1)
        {
            break;
        }
    }

    b = -b;

    print(QString::number(p) + " * " + QString::number(a) + " + " + QString::number(q) + " * " + QString::number(b) + " = " + QString::number(p*a+q*b) + "\n" );

    int r = calculatePower(1,message,(p+1)>>2,p);
    int s = calculatePower(1,message,(q+1)>>2,q);

    print("a " + QString::number(a) + " / " + "b " + QString::number(b) + "\n");
    print("r " + QString::number(r) + " / " + "s " + QString::number(s) + "\n");


    int x = (a*p*s + b*q*r) % (p*q);
    int y = (a*p*s - b*q*r) % (p*q);

    x = x < 0 ? x+(p*q) : x;
    y = y < 0 ? y+(p*q) : y;

    int invertedX = ((-1)*x) + (p*q);
    int invertedY = ((-1)*y) + (p*q);

    print("x: " + QString::number(x) + " / " + QString::number(x,2)+"\n");
    print("ix: " + QString::number(invertedX) + " / " + QString::number(invertedX,2)+"\n");
    print("y: " + QString::number(y) + " / " + QString::number(y,2)+"\n");
    print("iy: " + QString::number(invertedY) + " / " + QString::number(invertedY,2)+"\n");

    if(isMirrored(x))
    {
        decrypted = halfNumber(x);
    }
    else if(isMirrored(y))
    {
        decrypted = halfNumber(y);
    }

    else if(isMirrored(invertedX))
    {
        decrypted = halfNumber(invertedX);
    }

    else if(isMirrored(invertedY))
    {
        decrypted = halfNumber(invertedY);
    }

    return(decrypted);
}

bool MainWindow::isMirrored(const int number)
{
    int bitcounter = number;
    int counter = 0;
    int doubledMessage;

    while(bitcounter > 0)
    {
        bitcounter = bitcounter>>1;
        counter++;
    }

    if(counter % 2 == 1)
    {
        return(false);
    }

    //delete the last n/2 bits, then shift it back and XOR delete the first n/2 bits for mirrored check
    doubledMessage = number>>(counter>>1);
    bitcounter = number ^ (doubledMessage <<(counter>>1));

    print("number: " + QString::number(number) + " / " + QString::number(number,2)+"\n");
    print("front: " + QString::number(doubledMessage) + " / " + QString::number(doubledMessage,2)+"\n");
    print("back: " + QString::number(bitcounter) + " / " + QString::number(bitcounter,2)+"\n");

    return(doubledMessage == bitcounter);

}

int MainWindow::halfNumber(const int number)
{
    int bitcounter = number;
    int counter = 0;
    int doubledMessage;

    while(bitcounter > 0)
    {
        bitcounter = bitcounter>>1;
        counter++;
    }

    if(counter % 2 == 1)
    {
        return(false);
    }

    //delete the last n/2 bits, then shift it back and XOR delete the first n/2 bits for mirrored check
    doubledMessage = number>>(counter>>1);
    return(doubledMessage);
}


void MainWindow::addNumber()
{
    QObject* button = sender();

    if(button)
    {
        QString text = button->objectName();
        text.remove("pushButton_");

        currentLineEdit->setText(currentLineEdit->text()+text);
    }
}

void MainWindow::stateRotator()
{
    if(state == state_inverse)
    {
        changeState("rsa_crypt");
    }

    else if(state == state_rsa_crypt)
    {
        changeState("rsa_sign");
    }

    else if(state == state_rsa_sign)
    {
        changeState("rsa_decrypt");
    }

    else if(state == state_rsa_decrypt)
    {
        changeState("euler");
    }

    else if(state == state_euler)
    {
        changeState("pocklington");
    }

    else if(state == state_pocklington)
    {
        changeState("gcd");
    }

    else if(state == state_gcd)
    {
        changeState("power");
    }

    else if(state == state_power)
    {
        changeState("order");
    }

    else if(state == state_order)
    {
        changeState("primitiv");
    }

    else if(state == state_primitiv)
    {
        changeState("RabinCrypt");
    }

    else if(state == state_rabin_crypt)
    {
        changeState("RabinDecrypt");
    }

    else if(state == state_rabin_decrypt)
    {
        changeState("inverse");
    }


    else
    {
        changeState("inverse");
    }

}

void MainWindow::TextfieldRotator()
{
    currentLineEdit->setEnabled(false);

    if (currentLineEdit == ui->lineEdit_1)
    {
        currentLineEdit = ui->lineEdit_2;
    }
    else if (currentLineEdit == ui->lineEdit_2)
    {
        currentLineEdit = ui->lineEdit_3;
    }
    else if (currentLineEdit == ui->lineEdit_3)
    {
        currentLineEdit = ui->lineEdit_4;
    }
    else if (currentLineEdit == ui->lineEdit_4)
    {
        currentLineEdit = ui->lineEdit_1;
    }
    currentLineEdit->setEnabled(true);
}

void MainWindow::clearTextField()
{
    currentLineEdit->clear();
    ui->output->clear();
}

void MainWindow::compute()
{
    //ui->output->setText("My state is " + QString::number(state));
    if(state == state_gcd)
    {
        ui->output->setText(ui->output->toPlainText() + QString::number(gcd(ui->lineEdit_1->text().toInt(),ui->lineEdit_2->text().toInt())) + "\n");
    }
    else if(state == state_pocklington)
    {
        print("Pocklingtons Theorem: " + QString::number((int)calculatePocklington(ui->lineEdit_1->text().toInt(),ui->lineEdit_2->text().toInt())) + "\n");
    }
    else if(state == state_rsa_crypt)
    {
        print("RSA Crypted Message: " + QString::number(calculateRSACrypt(ui->lineEdit_1->text().toInt(),ui->lineEdit_2->text().toInt(),ui->lineEdit_3->text().toInt())) + "\n");
    }
    else if(state == state_rsa_sign)
    {
        print("RSA Signed Message: " + QString::number(calculateRSASign(ui->lineEdit_1->text().toInt(),ui->lineEdit_2->text().toInt(),ui->lineEdit_3->text().toInt(),ui->lineEdit_4->text().toInt())) + "\n");
    }
    else if(state == state_rsa_decrypt)
    {
        print("RSA Decrypted Message: " + QString::number(calculateRSADecrypt(ui->lineEdit_1->text().toInt(),ui->lineEdit_2->text().toInt(),ui->lineEdit_3->text().toInt(),ui->lineEdit_4->text().toInt())) + "\n");
    }
    else if(state == state_inverse)
    {
        print("Inverse: " + QString::number(calculateInverse(ui->lineEdit_1->text().toInt(),ui->lineEdit_2->text().toInt())) + "\n");
    }
    else if(state == state_power)
    {
        print("Power: " + QString::number(calculatePower(ui->lineEdit_1->text().toInt(),ui->lineEdit_2->text().toInt(),ui->lineEdit_3->text().toInt(),ui->lineEdit_4->text().toInt())) + "\n");
    }
    else if(state == state_order)
    {
        print("Order: " + QString::number(calculateOrder(ui->lineEdit_1->text().toInt(),ui->lineEdit_2->text().toInt(),ui->lineEdit_3->text().toInt())) + "\n");
    }
    else if(state == state_primitiv)
    {
        print("Primitve Element: " + QString::number(calculatePrimitivElement(ui->lineEdit_1->text().toInt(),ui->lineEdit_2->text().toInt())) + "\n");
    }
    else if(state == state_rabin_crypt)
    {
        print("Rabin Crypt: " + QString::number(calculateRabinCrypt(ui->lineEdit_1->text().toInt(),ui->lineEdit_2->text().toInt())) + "\n");
    }
    else if(state == state_rabin_decrypt)
    {
        print("Rabin DeCrypt: " + QString::number(calculateRabinDeCrypt(ui->lineEdit_1->text().toInt(),ui->lineEdit_2->text().toInt(),ui->lineEdit_3->text().toInt())) + "\n");
    }

}

void MainWindow::quit()
{
    exit(0);
}


