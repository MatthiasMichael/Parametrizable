#pragma once

#include <functional>

#include <QString>
#include <QMap>
#include <QGroupBox>

#include "GenericParameter.h"



class Parametrizable
{
	friend class GenericParameterWidget;

public:
	Parametrizable();
	virtual ~Parametrizable();

	Parametrizable(const Parametrizable & other);
	Parametrizable & operator=(const Parametrizable & other);

	GenericParameter *getParameterToName(const QString& name) const;

	void setParameterLocked(const QString& name, bool locked);

	void notifyOnParameterChanged(const QString& name, QObject* receiver, const char *slot) const;

	size_t getNumParameters() const;
	bool hasParameters() const;

	void startGroup(const QString& name);
	void endGroup();

	void addIntParameter(const QString& name, int min, int max, int value, int singleStep = 1, bool showGUI = true);
	void addDoubleParameter(const QString& name, double min, double max, double value, double singleStep = 0.1, bool showGUI = true);
	void addBoolParameter(const QString& name, bool value, bool showGUI = true);
	void addStringParameter(const QString& name, QString value, bool showGUI = true);
	void addEnumParameter(const QString& name, const QVector<QString>& allValues, int value, bool showGUI = true);
	void addFileParameter(const QString& name, QString value, FileDirection direction = OPEN, QString typeSelector = "", bool showGUI = true);
	void addFolderParameter(const QString& name, QString value, bool showGUI = true);
	void addTriggerParameter(const QString& name, QObject* receiver, const char* slot, bool showGUI = true);

	int getIntParameter(const QString & name) const;
	double getDoubleParameter(const QString & name) const;
	bool getBoolParameter(const QString & name) const;
	QString getStringParameter(const QString & name) const;
	int getEnumParameter(const QString & name) const;
	QString getFileParameter(const QString & name) const;
	QString getFolderParameter(const QString & name) const;

	void setEnumParameter(const QString & name, int value);
	void setIntParameter(const QString & name, int value);
	void setDoubleParameter(const QString & name, double value);
	void setBoolParameter(const QString & name, bool value);
	void setStringParameter(const QString & name, const QString & value);
	void setFileParameter(const QString & name, const QString & value);
	void setFolderParameter(const QString & name, const QString & value);

protected:
	void addGenericParameter(GenericParameter *pParameter, bool showGUI);

protected:
	QMap<QString, GenericParameter*> m_parameterToName;
	QVector<GenericParameter*> m_parameters;

	std::vector<std::function<void(GenericParameterWidget*, const Parametrizable *)>> m_guiBuilder;
};
