#ifndef MAXCOMBOBLOCK_H
#define MAXCOMBOBLOCK_H

#include <QWidget>
#include <QPainter>

class maxComboBlock : public QWidget {
Q_OBJECT

public:
    explicit maxComboBlock(QWidget *parent = nullptr);
    void setmaxCombo(int maxCombo) { this->maxCombo = maxCombo; }

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int maxCombo = 0;
};

#endif // maxComboBlock_H
