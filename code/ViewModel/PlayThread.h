//
// Created by Frankoxer on 24-7-6.
//

#ifndef PLAYTHREAD_H
#define PLAYTHREAD_H

#include <QThread>

// 前向声明
class ViewModel;

class PlayThread : public QThread {
    Q_OBJECT
public:
    explicit PlayThread(ViewModel* viewModel);

protected:
    void run() override;

private:
    ViewModel* viewModel;
};

#endif //PLAYTHREAD_H
