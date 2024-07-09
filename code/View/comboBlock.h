#ifndef COMBOBLOCK_H
#define COMBOBLOCK_H

#include <QWidget>
#include <QPainter>

class ComboBlock : public QWidget {
Q_OBJECT

public:
    explicit ComboBlock(QWidget *parent = nullptr);
    void setCombo(int combo) { this->combo = combo; }

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int combo=0;
};

#endif // ComboBlock_H
