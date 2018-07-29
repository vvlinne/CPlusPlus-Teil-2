#include <QWidget>
#include "zeichenfeld.h"
#include "string.h"
#include <QPushButton>

class meinWidget : public QWidget
{
    Q_OBJECT  // notwendig, da Slots enthalten sind

public:
    meinWidget(QWidget *parent = 0);
    QString buttonText = "Start";
    QPushButton start;

private:
    zeichenFeld *meinZeichenFeld;

public slots:
    void toggleTimer();
    void saveFile(void);
    void loadFile(void);
};
