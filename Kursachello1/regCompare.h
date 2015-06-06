#pragma once
#include<QVector>
#include<QTextStream>
#include<QFile>
#include"regElement.h"

class RegCompare{
	private:
		bool read(QTextStream& stream, RegElement& buf);

	public:
		QVector< RegElement > newHives;
		QVector< RegElement > deletedHives;
		QVector< RegElement > changedDefaultValues;
		QVector< RegElement > changedKeys;
		QVector< RegElement > renamedKeys;

		void compareFiles(const QString& name1, const QString& name2);
		void clear();
		bool checkChanges(){
			if(newHives.size() || deletedHives.size() || renamedKeys.size() ||
					changedDefaultValues.size() || changedKeys.size())
				return true;
			else
				return false;
		}
		RegCompare(void);
		~RegCompare(void);
};
