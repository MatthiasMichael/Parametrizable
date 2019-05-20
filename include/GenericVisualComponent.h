#pragma once

#include <QWidget>

#include "GenericParameter.h"


class GenericVisualComponent : public QWidget
{
	Q_OBJECT

public:
	explicit GenericVisualComponent(const GenericParameter & param, QWidget * pParent = nullptr);
	virtual ~GenericVisualComponent() { }

	GenericVisualComponent(const GenericVisualComponent &) = delete;
	GenericVisualComponent & operator=(const GenericVisualComponent &) = delete;

public slots:
	virtual void onLocked(bool locked);

protected:
	bool m_locked;
};


class DoubleGenericVisualComponent : public GenericVisualComponent
{
	Q_OBJECT

public:
	DoubleGenericVisualComponent(const DoubleParameter & param, QWidget * pParent = nullptr);

public slots:
	void onValueChangedByGui(double value);
	void onValueChangedByProgram(double value);

signals:
	void valueChangedByGui(double value);
	void valueChangedByProgram(double value);
};


class IntGenericVisualComponent : public GenericVisualComponent
{
	Q_OBJECT

public:
	IntGenericVisualComponent(const IntParameter & param, QWidget * pParent = nullptr);

public slots:
	void onValueChangedByGui(int value);
	void onValueChangedByProgram(int value);

signals:
	void valueChangedByGui(int value);
	void valueChangedByProgram(int value);
};


class EnumGenericVisualComponent : public GenericVisualComponent
{
	Q_OBJECT

public:
	EnumGenericVisualComponent(const EnumParameter & param, QWidget * pParent = nullptr);

public slots:
	void onValueChangedByGui(int value);
	void onValueChangedByProgram(int value);

signals:
	void valueChangedByGui(int value);
	void valueChangedByProgram(int value);
};


class BoolGenericVisualComponent : public GenericVisualComponent
{
	Q_OBJECT

public:
	BoolGenericVisualComponent(const BoolParameter & param, QWidget * pParent = nullptr);
	
public slots:
	void onValueChangedByGui(bool value);
	void onValueChangedByProgram(bool value);

signals:
	void valueChangedByGui(bool value);
	void valueChangedByProgram(bool value);
};


class StringGenericVisualComponent : public GenericVisualComponent
{
	Q_OBJECT

public:
	StringGenericVisualComponent(const StringParameter & param, QWidget * pParent = nullptr);
	
public slots:
	void onValueChangedByGui(QString value);
	void onValueChangedByProgram(QString value);

signals:
	void valueChangedByGui(QString value);
	void valueChangedByProgram(QString value);
};


class FileGenericVisualComponent : public GenericVisualComponent
{
	Q_OBJECT

public:
	FileGenericVisualComponent(const FileParameter & param, QWidget * pParent = nullptr);

public slots:
	void onButtonClicked(bool checked);
	
	void onValueChangedByGui(QString value);
	void onValueChangedByProgram(QString value);

signals:
	void valueChangedByGui(QString value);
	void valueChangedByProgram(QString value);

private:
	FileDirection m_direction;
	QString m_typeSelector;
};


class FolderGenericVisualComponent : public GenericVisualComponent
{
	Q_OBJECT

public:
	FolderGenericVisualComponent(const FolderParameter & param, QWidget * pParent = nullptr);

public slots:
	void onValueChangedByGui(QString value);
	void onValueChangedByProgram(QString value);
	void onButtonClicked(bool checked);

signals:
	void valueChangedByGui(QString value);
	void valueChangedByProgram(QString value);
};


class TriggerGenericVisualComponent : public GenericVisualComponent
{
	Q_OBJECT
public:
	TriggerGenericVisualComponent(const TriggerParameter & param, QWidget * pParent = nullptr);

public slots:
	void onTriggeredByGui();
	void onTriggeredByProgram();

signals:
	void triggeredByGui();
	void triggeredByProgram();
};