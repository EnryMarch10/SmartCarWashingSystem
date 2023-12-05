#include "Tasks/BlinkTask.h"

BlinkTask::BlinkTask(Light *pLight)
{
    this->pLight = pLight;    
}

void BlinkTask::laterInit(void) { }

void BlinkTask::tick(void)
{
    pLight->toggle();
}

BlinkTask::~BlinkTask(void)
{
    pLight->switchOff();
}
