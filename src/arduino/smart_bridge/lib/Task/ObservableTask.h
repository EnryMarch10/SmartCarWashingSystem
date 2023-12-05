#ifndef __OBSERVABLE_TASK__
#define __OBSERVABLE_TASK__

#include "utils.h"
#include "Task.h"
#include "TaskObserver.h"

#include "ArrayList.h"

class ObservableTask: public Task {

public:
    ObservableTask(void)
    {
        listeners = new ArrayList<TaskObserver *>();
    }
    void addListener(TaskObserver *listener)
    {
        listeners->add(listener);
    }
    void removeListener(TaskObserver *listener)
    {
        listeners->remove(listener);
    }
    void notifyListeners(void)
    {
        for (int i = 0; i < listeners->length(); i++) {
            (*listeners)[i]->update(this);
        }
    }
    virtual ~ObservableTask(void)
    {
        delete listeners;
    }

private:
    ArrayList<TaskObserver *> *listeners;

};

#endif
