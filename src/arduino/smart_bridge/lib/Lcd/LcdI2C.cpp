#include <Arduino.h>
#include "LcdI2C.h"

#define DEFAULT_ROWS 16
#define DEFAULT_COLUMNS 2

LcdI2C::LcdI2C(const int address)
{
    rows = DEFAULT_ROWS;
    columns = DEFAULT_COLUMNS;
    pLcd = new LiquidCrystal_I2C(address, rows, columns);
}

LcdI2C::LcdI2C(const int address, const int rows, const int columns)
{
    this->rows = rows;
    this->columns = columns;
    pLcd = new LiquidCrystal_I2C(address, this->rows, this->columns);
}

void LcdI2C::init(void)
{
    pLcd->init();
}

char LcdI2C::getRows(void)
{
    return rows;
}

char LcdI2C::getColumns(void)
{
    return columns;
}

void LcdI2C::on(void)
{
    pLcd->backlight();
    pLcd->setCursor(0, 0);
}

void LcdI2C::off(void)
{
    pLcd->clear();
    pLcd->noBacklight();
}

void LcdI2C::write(const char *string)
{
    pLcd->print(string);
}

LcdI2C::~LcdI2C(void)
{
    delete pLcd;
}
