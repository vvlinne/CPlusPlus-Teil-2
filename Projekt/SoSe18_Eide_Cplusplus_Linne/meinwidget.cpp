#include <QtGui>
// nur notwendig, wenn Qt 5:
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QFileDialog>

//Ende Qt 5
#include "meinwidget.h"

meinWidget::meinWidget(QWidget *parent)
    : QWidget(parent)
{
    // Fügt Buttons hinzu, welche Starten,
    // Stoppen, Speichern und Laden des Spiels zulassen.
    meinZeichenFeld = new zeichenFeld;

    // Button wird einzeln behandelt: Wechsel von Start auf Stop und andersrum möglich (siehe toggleTimer)
    start.setText("Start");
    start.setFocusPolicy(Qt::FocusPolicy::NoFocus);
    start.setFont(QFont("Times", 18, QFont::Bold));
    connect(&start, SIGNAL(clicked()), this, SLOT(toggleTimer()));

    QPushButton *save = new QPushButton(tr("Speichern"));
    save->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    save->setFont(QFont("Times", 18, QFont::Bold));
    connect(save, SIGNAL(clicked()), this, SLOT(saveFile()));

    QPushButton *load = new QPushButton(tr("Laden"));
    load->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    load->setFont(QFont("Times", 18, QFont::Bold));
    connect(load, SIGNAL(clicked()), this, SLOT(loadFile()));

    QPushButton *quit = new QPushButton(tr("Ende"));
    quit->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    quit->setFont(QFont("Times", 18, QFont::Bold));
    connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));

    // Fügt Buttons dem Grid hinzu
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(&start, 0, 0);
    gridLayout->addWidget(save, 1, 0);
    gridLayout->addWidget(load, 2, 0);
    gridLayout->addWidget(quit, 3, 0);
    gridLayout->addWidget(meinZeichenFeld, 0, 1, 0, 2);
    gridLayout->setColumnStretch(1, 10);
    setLayout(gridLayout);
}

void meinWidget::toggleTimer() {
    // Behandelt Start/Stop-Button basierend auf momentanem Timerstatus
    if(meinZeichenFeld->increment == 0) {
        meinZeichenFeld->start();
        meinZeichenFeld->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
        start.setText("Stop");
    } else {
        meinZeichenFeld->stop();
        meinZeichenFeld->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        start.setText("Start");
    }
}

void meinWidget::saveFile(void)
{
    QFileDialog dialog(this);
    QString fileName;
    QFile file;

    dialog.setFileMode(QFileDialog::AnyFile);
    fileName = dialog.getSaveFileName(this,
                                      tr("Speichern als"), ".", tr("Zeichnungen (*.myz)"));

    if (fileName.isNull()==false)
    {
        file.setFileName(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox::warning(this, tr("Dateifehler"),
                                 tr("Folgende Datei kann nicht verwendet werden: ") + fileName,QMessageBox::Ok);
        }

        meinZeichenFeld->serialize(file);
        file.close();
        return;
    }
}

void meinWidget::loadFile(void)
{
    QFileDialog dialog(this);
    QString fileName;
    QFile file;

    dialog.setFileMode(QFileDialog::AnyFile);
    fileName = dialog.getOpenFileName(this,
                                      tr("Speichern als"), ".", tr("Zeichnungen (*.myz)"));

    if (fileName.isNull()==false)
    {
        file.setFileName(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this, tr("Dateifehler"),
                                 tr("Folgende Datei kann nicht geöffnet werden: ") + fileName,QMessageBox::Ok);
        }

        meinZeichenFeld->deserialize(file);
        file.close();
        return;
    }
}

