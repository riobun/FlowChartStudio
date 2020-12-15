#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QSplashScreen>

class SplashScreen : public QSplashScreen
{
    Q_OBJECT
public:
    explicit SplashScreen();
    void showScreen(QApplication& app);

private:
    void mousePressEvent(QMouseEvent* event) override;

    bool hasClicked = false;
};

#endif // SPLASHSCREEN_H
