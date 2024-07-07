#ifndef COMBOBLOCK_H
#define COMBOBLOCK_H

#include <QWidget>
#include <QPainter>

class ComboBlock : public QWidget {
Q_OBJECT

public:
    explicit ComboBlock(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // ComboBlock_H
