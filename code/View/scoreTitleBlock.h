#ifndef SCORETITLEBLOCK_H
#define SCORETITLEBLOCK_H

#include <QWidget>
#include <QPainter>

class ScoreTitleBlock : public QWidget {
Q_OBJECT

public:
    explicit ScoreTitleBlock(QWidget *parent = nullptr);
    void setTitle(const QString &title);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QString title;
};

#endif // SCORETITLEBLOCK_H
