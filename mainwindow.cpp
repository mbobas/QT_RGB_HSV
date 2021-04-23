#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>

// Konstruktor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Pobieramy współrzędne (względem głównego okna) lewego, górnego naroznika ramki
    startX = ui->frame->x();
    startY = ui->frame->y();

    // Pobieramy wymiary ramki
    width = ui->frame->width();
    height = ui->frame->height();

    // Tworzymy obiekt klasy QImage o wymiarach równych wymiarom ramki
    // Format_RGB32 to 32 bitowe RGB (z kanałem alfa ustawionym na wartość 255)
    img = new QImage(width, height, QImage::Format_RGB32);
}
//*****************************************************************************************************


// Destruktor
MainWindow::~MainWindow()
{
    delete ui;
}
//*****************************************************************************************************


// Funkcja ,,odrysowująca'' okno aplikacji. Wywoływana automatycznie podczas uruchamiania aplikacji
// i w innych sytuacjach, w których zachodzi konieczność ponownego narysowania okna.
// Można też wymusić jej wywołanie za pomocą funkcji update()
void MainWindow::paintEvent(QPaintEvent*)
{
    // Obiekt przy pomocy, którego możemy rysować po elementach interfejsu graficznego aplikacji
    QPainter p(this);

    // Metoda drawImage wyświetla zawartość obiektu *img klasy QImage w głównym oknie aplikacji
    // startX i startY to współrzędne (względem głównego okna) lewego górnego narożnika
    // wyświetlanego obiektu
    p.drawImage(startX, startY, *img);
}
//*****************************************************************************************************


// Funkcja zamalowująca na czarno wszystkie piksele obrazu *img
void MainWindow::clean()
{
    // deklaracja wskaźnika do poruszania się po pikselach obrazu
    unsigned char *wsk;

    // przechodzimy po wszystkich wierszach obrazu
    for(int i=0; i<height; i++)
    {
        // ustawiamy wskaźnik na początku i-tego wiersza
        wsk = img->scanLine(i);

        // przechodzimy po wszystkich piselach i-tego wiersza
        // i nadajemy im wartość (0,0,0) odpowiadającą kolorowi czarnemu
        for(int j=0; j<width; j++)
        {
            wsk[4*j] = 0;   // ustawiamy składową ,,niebieską'' na 0
            wsk[4*j+1] = 0; // ustawiamy składową ,,zielonąą'' na 0
            wsk[4*j+2] = 0; // ustawiamy składową ,,czerwoną'' na 0
        }
    }
}
//*****************************************************************************************************

// zamalowuje piksel (x,y) na kolor (red,green,blue), domyślnie na biało
void MainWindow::drawPixel(int x, int y, unsigned char red, unsigned char green, unsigned char blue)
{
    unsigned char *wsk;

    // sprawdzamy czy (x,y) leży w granicach rysunku
    if(x>=0 && y>=0 && x<width && y<height)
    {
        wsk = img->scanLine(y);
        wsk[4*x] = blue;
        wsk[4*x+1] = green;
        wsk[4*x+2] = red;
    }

}
//*****************************************************************************************************

// Metoda wywoływana po wciśnięciu przycisku myszy
// Inne metody związane z obsługą myszy to
// void MainWindow::mouseReleaseEvent(QMouseEvent *event)
// wywoływana po puszczeniu przycisku myszy i
// void MainWindow::mouseMoveEvent(QMouseEvent *event)
// wywoływana po każdym ruchu myszy
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int x,y;

    // Pobieramy współrzędne punktu kliknięcia
    x = event->x();
    y = event->y();
    // Współrzędne obliczane są względem głównego okna programu
    // aby uzyskać współrzędne względem obszaru rysowania (ramki) musimy je przesunąć
    // tak aby punkt (0,0) pokrywał się z lewym górnym naroznikiem obszaru rysowania
    x = x - startX;
    y = y - startY;

    // Jeżeli wciśnięto lewy przycisk to zamolowujemy piksel na biało
    if(event->button() == Qt::LeftButton)
    {
        drawPixel(x,y);
    }
    // a w przeciwnym wypadku na czerwono
    else
    {
        drawPixel(x,y,255,0,0);
    }

    update();
}
//*****************************************************************************************************


// Metoda wywoływana po nacisnięciu przycisku exitButton (,,Wyjście'')
void MainWindow::on_exitButton_clicked()
{
    // qApp to globalny wskaźnik na obiekt aplikacji
    // metoda quit() powoduje zakończenie działania aplikacji z kodem wyjścia 0 (sukces)
    qApp->quit();
}
//*****************************************************************************************************

// Metoda wywoływana po nacisnięciu przycisku exitButton (,,Wyjście'')
void MainWindow::on_cleanButton_clicked()
{
    clean();

    // Po zmodyfikowaniu obiektu QImage odświeżamy okno aplikacji, aby zobaczyc zmiany
    update();
}

void MainWindow::on_pushButton_clicked()
{
    for(int i=0; i<height/2; i++)
    {
        for(int j=0; j<width; j++)
        drawPixel(j,i,255,255,255);
    }

    for(int i=height/2; i<height; i++)
    {
        for(int j=0; j<width; j++)
            drawPixel(j,i,255,0,0);
    }
    update();
}


void MainWindow::on_pushButton_2_clicked()
{
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width/3; j++)
        drawPixel(j,i,0,0,0);
    }

    for(int i=0; i<height; i++)
    {
        for(int j=width/3; j<(width/3)*2; j++)
            drawPixel(j,i,255,224,56);
    }
     for(int i=0; i<height; i++)
    {
    {
        for(int j=(width/3)*2; j<width; j++)
            drawPixel(j,i,249,24,32);
    }
    }
    update();
}

void MainWindow::on_pushButton_3_clicked()
{
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        drawPixel(j,i,255,0,0);
    }

    for(int i=height/2-30; i<height/2+30; i++)
    {
        for(int j=0; j<width; j++)
        drawPixel(j,i,255,255,255);
    }

    for(int i=0; i<height; i++)
    {
        for(int j=width/2-30; j<width/2+30; j++)
        drawPixel(j,i,255,255,255);
    }
    update();
}

void MainWindow::on_pushButton_4_clicked()
{

}

void MainWindow::on_verticalSlider_valueChanged(int value)
{
        for(int x=1; x<=255; x++)
        {
            for(int y=1; y<=255; y++){
                drawPixel(x*2,y*2,value,x,y);
                drawPixel(x*2,y*2-1,value,x,y);
            drawPixel(x*2-1,y*2,value,x,y);
            drawPixel(x*2-1,y*2-1,value,x,y);
            drawPixel(x*2+1,y*2,value,x,y);
            drawPixel(x*2+1,y*2-1,value,x,y);
            update();
            }
        }

}




void MainWindow::on_verticalSlider_2_valueChanged(int value)
{
    for(int x=1; x<=255; x++)
    {
        for(int y=1; y<=255; y++){
        drawPixel(x*2,y*2,x,value,y);
        drawPixel(x*2,y*2-1,x,value,y);
        drawPixel(x*2-1,y*2,x,value,y);
        drawPixel(x*2-1,y*2-1,x,value,y);
        drawPixel(x*2+1,y*2,x,value,y);
        drawPixel(x*2+1,y*2-1,x,value,y);
        update();
        }
    }
}

void MainWindow::on_verticalSlider_3_valueChanged(int value)
{
    for(int x=1; x<=255; x++)
    {
        for(int y=1; y<=255; y++){
        drawPixel(x*2,y*2,x,y,value);
        drawPixel(x*2,y*2-1,x,y,value);
        drawPixel(x*2-1,y*2,x,y,value);
        drawPixel(x*2-1,y*2-1,x,y,value);
        drawPixel(x*2+1,y*2,x,y,value);
        drawPixel(x*2+1,y*2-1,x,y,value);
        update();
        }
    }
}

void MainWindow::HSVtoRGB(float H, float S,float V){
    if(H>360 || H<0 || S>100 || S<0 || V>100 || V<0){
        qDebug()<<"The givem HSV values are not in valid range";
        return;
    }
    float s = S/100;
    float v = V/100;
    float C = s*v;
    float X = C*(1-fabs(fmod(H/60.0, 2)-1));
    float m = v-C;
    float r,g,b;
    if(H >= 0 && H < 60){
        r = C,g = X,b = 0;
    }
    else if(H >= 60 && H < 120){
        r = X,g = C,b = 0;
    }
    else if(H >= 120 && H < 180){
        r = 0,g = C,b = X;
    }
    else if(H >= 180 && H < 240){
        r = 0,g = X,b = C;
    }
    else if(H >= 240 && H < 300){
        r = X,g = 0,b = C;
    }
    else{
        r = C,g = 0,b = X;
    }

    int R = (r+m)*255;
    int G = (g+m)*255;
    int B = (b+m)*255;

    drawPixel(V,S,R,G,B);
    update();
}

void MainWindow::on_verticalSlider_4_valueChanged(int hue)
{
    for(int x=0; x<=100; x++){
        for (int y=0; y<=100; y++ ){
            HSVtoRGB(hue, y, x);

        }
    }
}

void MainWindow::on_verticalSlider_5_valueChanged(int sat)
{
    for(int x=0; x<=360; x++){
        for (int y=0; y<=100; y++ ){
            HSVtoRGB(x, sat, y);

        }
    }
}
