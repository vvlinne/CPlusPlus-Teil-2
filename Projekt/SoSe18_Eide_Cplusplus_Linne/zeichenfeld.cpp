#include <QtGui>
#include <QMessageBox>
#include "zeichenfeld.h"
#include "spieler.h"
#include "gegner.h"
#include "stats.h"
#include <string.h>
#include "vector"

QPainter painter;
spieler avatar;
bool avatarOnly = false;
stats *statAnzeige = new stats;
vector<gegner> gegnerVector;
int counter = 0;

zeichenFeld::zeichenFeld(QWidget *parent)
    : QWidget(parent)
{
    setPalette(QPalette(QColor(250, 250, 200)));
    setAutoFillBackground(true);
    setMouseTracking(false);

    timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
}

zeichenFeld::~zeichenFeld()
{
    setPalette(QPalette(QColor(250, 250, 200)));
    setAutoFillBackground(true);
}

void zeichenFeld::paintEvent(QPaintEvent *event)
{

    // Zeichnen der Gegner-Objekte basierend auf Typ und Koordinaten
    painter.begin(this);
    painter.setPen(QPen(Qt::black));

    for (vector<gegner>::iterator it = gegnerVector.begin() ; it != gegnerVector.end(); it++) {
        if(it->typ == 1) {
            painter.drawRect(it->x, it->y, 25, 25);
        } else {
            painter.drawEllipse(it->x, it->y, 20, 20);
        }
    }

    painter.end();

    // Wenn der Spieler gerade den Avatar bewegt, wird dieser Schritt übersprungen, da es sonst
    // zu doppeltem Springen der Gegner-Objekte kommt
    if(!avatarOnly && increment != 0) {
        for (vector<gegner>::iterator it = gegnerVector.begin() ; it != gegnerVector.end(); it++) {
            int stepRange = rand() % 100 + 40;

           it->calculatePosition(stepRange);
        }

        if(counter == 0) {
            qDebug() << counter;
        }
        if(counter == 0 || counter % 3 == 0) {
            gegner neuerGegner;
            gegnerVector.push_back(neuerGegner);
        }

        statAnzeige->updatePoints();
    }

    // Aktualisiert den Punktestand
    painter.begin(this);
    painter.setPen(QPen(Qt::black));
    painter.drawText(QRect(25, 25, 100, 25), Qt::AlignLeft, QString::number(statAnzeige->punkte) + " Punkte");
    painter.end();

    // Zeichnet die Lebensanzeige mit X-Abständen von 25
    int xPositionLeben = 500;
    for(int i = 0; i < statAnzeige->leben; i++) {
        painter.begin(this);
        painter.setBrush(QBrush(Qt::red));
        painter.drawEllipse(xPositionLeben, 20, 20, 20);
        painter.end();
        xPositionLeben = xPositionLeben + 25;
    }

    // Zeichnet den Avatar mit schraffierter Oberfläche
    painter.begin(this);
    painter.setBackgroundMode(Qt::OpaqueMode);
    painter.setBackground(QColor(Qt::white));
    painter.setPen(QPen(Qt::black));
    painter.setBrush(QBrush(Qt::black, Qt::BDiagPattern));
    painter.drawRect(avatar.x, 425, 50, 50);
    painter.end();
    avatarOnly = false;
    counter++;
}

void zeichenFeld::keyPressEvent( QKeyEvent *k )
{
    // Bewegung des Avatars durch Tasteneingabe des Spielers
    switch ( k->key()) {
        case Qt::Key_Left:
            if(avatar.x - 25 >= 0) {
                avatar.x = avatar.x - 25;
                avatarOnly = true;
                update();
            }
            break;
        case Qt::Key_Right:
            if(avatar.x + 25 <= 540) {
                avatar.x = avatar.x + 25;
                avatarOnly = true;
                update();
            }
            break;
    }
}

void zeichenFeld::serialize(QFile &file)
{
    QTextStream out(&file);

        out << avatar.x << "\n";
        out << statAnzeige->punkte << "\n";

        for (vector<gegner>::iterator it = gegnerVector.begin() ; it != gegnerVector.end(); it++) {
            out << it->x << "," << it->y << "," << it->typ << "\n";
        }
}

void zeichenFeld::deserialize(QFile &file)
{
    QTextStream in(&file);
    int lineNumber = 0;
    while(!in.atEnd())
    {
       QString line = in.readLine();
       QStringList parameters = line.split(",");

       if(lineNumber == 0) {
         avatar.x = line.toInt();
       } else if(lineNumber == 1) {
         statAnzeige->punkte = line.toInt();
       } else {
         gegner neuerGegner;
         neuerGegner.x = parameters[0].toInt();
         neuerGegner.y = parameters[1].toInt();
         neuerGegner.typ = parameters[2].toInt();
         gegnerVector.clear();
         gegnerVector.push_back(neuerGegner);
       }
       lineNumber++;
    }
    update();
}
