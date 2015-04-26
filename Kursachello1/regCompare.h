#pragma once
#include<QVector>
#include<QTextStream>
#include <QFile>
#include"regElement.h"

class RegCompare
{
private:
    bool read(QTextStream& stream, RegElement& buf);
    int compareElements(RegElement& element1, RegElement& element2);

public:
    QVector< RegElement > newHives;
    QVector< RegElement > deletedHives;
    QVector< RegElement > changedDefaultValues;
    QVector< RegElement > changedKeys;

	void compareShots(char *name1, char *name2);	
	RegCompare(void);
	~RegCompare(void);
};
