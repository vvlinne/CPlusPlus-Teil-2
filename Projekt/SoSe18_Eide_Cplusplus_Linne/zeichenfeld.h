#include <vector>
using namespace std;
#include <QWidget>
#include <QTimer>
#include <QFile>

class zeichenFeld : public QWidget
{
public:
    zeichenFeld(QWidget *parent = 0);
    ~zeichenFeld();
    void start(void) { timer->start(1000); increment=1;};
    void stop(void) { timer->stop(); increment=0;};
    void serialize(QFile &file);
    void deserialize(QFile &file);
    int increment=0;

private:
    QTimer *timer = new QTimer;
    QColor color;
    int width;

protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent* event);
};
