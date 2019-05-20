#pragma once

#include <QObject>
#include <QMap>
#include <QVector>


enum FileDirection { OPEN, SAVE };

class GenericParameter : public QObject
{
	Q_OBJECT

	friend class GenericVisualComponent;

public:
	GenericParameter(QString name) : m_name(name), m_locked(false) { }

	virtual GenericParameter * copy() const = 0;
	virtual GenericVisualComponent * createVisualComponent(QWidget * pParent = nullptr) const = 0;

	virtual double getValueAsDouble () const { invalidTypeRequest(); return 0; }
	virtual int getValueAsInt       () const { invalidTypeRequest(); return 0; }
	virtual int getValueAsEnum      () const { invalidTypeRequest(); return 0; }
	virtual bool getValueAsBool     () const { invalidTypeRequest(); return false; }
	virtual QString getValueAsString() const { invalidTypeRequest(); return ""; }

	virtual void setValue(double value) { invalidTypeRequest();	}
	virtual void setValue(int value) { invalidTypeRequest(); }
	virtual void setValue(bool value) { invalidTypeRequest(); }
	virtual void setValue(const QString & value) { invalidTypeRequest(); }

	virtual bool isDouble () const { return false; }
	virtual bool isInt    () const { return false; }
	virtual bool isEnum   () const { return false; }
	virtual bool isBool   () const { return false; }
	virtual bool isString () const { return false; }
	virtual bool isFile   () const { return false; }
	virtual bool isFolder () const { return false; }
	virtual bool isTrigger() const { return false; }

	virtual void setName(const QString & name) { m_name = name; }
	virtual void setLocked(bool locked);

	virtual QString getName() const { return m_name; }
	virtual bool isLocked() const { return m_locked; }

signals:
	void locked(bool);

private:
	void invalidTypeRequest() const;

protected:
	QString m_name;
	bool m_locked;
};


class DoubleParameter : public GenericParameter
{
	Q_OBJECT

	friend class DoubleGenericVisualComponent;

public:
	DoubleParameter(QString name, double min, double max, double value, double singleStep) : 
		GenericParameter(name), m_min(min), m_max(max), m_value(value), m_singleStep(singleStep)
	{
		// empty
	}

	GenericParameter * copy() const override
	{ 
		return new DoubleParameter(m_name, m_min, m_max, m_value, m_singleStep); 
	}

	GenericVisualComponent* createVisualComponent(QWidget* pParent) const override;
	
	void setValue(double value) override { onValueChangedByProgram(value); }

	double getValueAsDouble() const override { return m_value; }
	bool isDouble() const override { return true; }

private:
	void setValueInternal(double value);

private:
	double m_min;
	double m_max;
	double m_value;
	double m_singleStep;

public slots:
	void onValueChangedByGui(double value);
	void onValueChangedByProgram(double value);

signals:
	void valueChangedByGui(double value);
	void valueChangedByProgram(double value);
};


class IntParameter : public GenericParameter
{
	Q_OBJECT

	friend class IntGenericVisualComponent;

public:
	IntParameter(QString name, int min, int max, int value, int singleStep) : 
		GenericParameter(name), m_min(min), m_max(max), m_value(value), m_singleStep(singleStep)
	{
		// empty
	}

	GenericParameter * copy() const override
	{ 
		return new IntParameter(m_name, m_min, m_max, m_value, m_singleStep); 
	}

	GenericVisualComponent* createVisualComponent(QWidget* pParent) const override;

	void setValue(int value) override { onValueChangedByProgram(value); }
	
	int getValueAsInt() const override { return m_value; }
	bool isInt() const override { return true; }

private:
	void setValueInternal(int value);

private:
	int m_min;
	int m_max;
	int m_value;
	int m_singleStep;

public slots:
	void onValueChangedByGui(int value);
	void onValueChangedByProgram(int value);

signals:
	void valueChangedByGui(int value);
	void valueChangedByProgram(int value);
};


class EnumParameter : public GenericParameter
{
	Q_OBJECT

	friend class EnumGenericVisualComponent;

public:
	EnumParameter(const QString& name, const QVector<QString>& allValues, int value) :
		GenericParameter(name), m_value(value), m_allValues(allValues)
	{
		for (int i = 0; i < m_allValues.size(); i++)
		{
			m_indicesToValue.insert(m_allValues[i], i);
		}
	}

	GenericParameter* copy() const override
	{ 
		return new EnumParameter(m_name, m_allValues, m_value); 
	}

	GenericVisualComponent* createVisualComponent(QWidget* pParent) const override;
	
	void setValue(int value) override { onValueChangedByProgram(value); }
	
	int getValueAsEnum() const override { return m_value; }
	bool isEnum() const override { return true; }

	QString getValueToInt(int idx) const;
	int getIntToValue(const QString& name) const;

private:
	void setValueInternal(int value);

private:
	int m_value;
	QMap<QString, int> m_indicesToValue;
	QVector<QString> m_allValues;

	public slots:
	void onValueChangedByGui(int value);
	void onValueChangedByProgram(int value);

signals:
	void valueChangedByGui(int value);
	void valueChangedByProgram(int value);
};


class BoolParameter : public GenericParameter
{
	Q_OBJECT

	friend class BoolGenericVisualComponent;

public:
	BoolParameter(const QString& name, bool value) : GenericParameter(name), m_value(value) { }

	GenericParameter * copy() const override
	{ 
		return new BoolParameter(m_name, m_value); 
	}

	GenericVisualComponent* createVisualComponent(QWidget* pParent) const override;

	void setValue(bool value) override { onValueChangedByProgram(value); }
	bool getValueAsBool() const override { return m_value; }
	bool isBool() const override { return true; }

private:
	void setValueInternal(bool value);

private:
	bool m_value;

	public slots:
	void onValueChangedByGui(bool value);
	void onValueChangedByProgram(bool value);

signals:
	void valueChangedByGui(bool value);
	void valueChangedByProgram(bool value);
};


class StringParameter : public GenericParameter
{
	Q_OBJECT

	friend class StringGenericVisualComponent;

public:
	StringParameter(const QString& name, QString value) : GenericParameter(name), m_value(value) { }

	GenericParameter * copy() const override
	{ 
		return new StringParameter(m_name, m_value); 
	}

	GenericVisualComponent* createVisualComponent(QWidget* pParent) const override;
	
	void setValue(const QString& value) override { onValueChangedByProgram(value); }
	QString getValueAsString() const override { return m_value; }
	bool isString() const override { return true; }

private:
	void setValueInternal(const QString & value);

private:
	QString m_value;

public slots:
	void onValueChangedByGui(QString value);
	void onValueChangedByProgram(QString value);

signals:
	void valueChangedByGui(QString value);
	void valueChangedByProgram(QString value);
};


class FileParameter : public GenericParameter
{
	Q_OBJECT

	friend class FileGenericVisualComponent;

public:
	FileParameter(const QString& name, QString value, QString typeSelector, FileDirection direction = OPEN) : 
		GenericParameter(name), m_value(value), m_typeSelector(typeSelector), m_direction(direction)
	{
		// empty
	}

	GenericParameter * copy() const override
	{ 
		return new FileParameter(m_name, m_value, m_typeSelector, m_direction); 
	}

	GenericVisualComponent* createVisualComponent(QWidget* pParent) const override;

	void setValue(const QString& value) override { onValueChangedByProgram(value); }
	QString getValueAsString() const override { return m_value; }
	bool isFile() const override { return true; }

	QString getTypeSelector() const { return m_typeSelector; }

private:
	void setValueInternal(const QString & value);

private:
	QString m_value;
	QString m_typeSelector;
	FileDirection m_direction;

public slots:
	void onValueChangedByGui(QString value);
	void onValueChangedByProgram(QString value);

signals:
	void valueChangedByGui(QString value);
	void valueChangedByProgram(QString value);
};


class FolderParameter : public GenericParameter
{
	Q_OBJECT

	friend class FolderGenericVisualComponent;

public:
	FolderParameter(const QString&name, QString value) : GenericParameter(name), m_value(value) { }

	GenericParameter * copy() const override
	{ 
		return new FolderParameter(m_name, m_value); 
	}
	
	GenericVisualComponent* createVisualComponent(QWidget* pParent) const override;

	void setValue(const QString& value) override { onValueChangedByProgram(value); }
	QString getValueAsString() const override { return m_value; }
	bool isFolder() const override { return true; }

private:
	void setValueInternal(const QString & value);

private:
	QString m_value;

public slots:
	void onValueChangedByGui(QString value);
	void onValueChangedByProgram(QString value);

signals:
	void valueChangedByGui(QString value);
	void valueChangedByProgram(QString value);
};


class TriggerParameter : public GenericParameter
{
	Q_OBJECT

	friend class TriggerGenericVisualComponent;

public:
	TriggerParameter(const QString & name, QObject* receiver = nullptr, const char* slot = nullptr) : 
		GenericParameter(name), m_receiver(receiver), m_slot(slot)
	{
		if (receiver && slot)
		{
			connect(this, SIGNAL(triggered), receiver, SLOT(slot));
		}
	}

	GenericParameter* copy() const override
	{
		return new TriggerParameter(m_name, m_receiver, m_slot.c_str());
	}

	GenericVisualComponent* createVisualComponent(QWidget* pParent) const override;

	void trigger() { onTriggeredByProgram(); }
	bool isTrigger() const override { return true; }	

private:
	QObject * m_receiver;
	std::string m_slot;

public slots:
	void onTriggeredByGui() { emit triggered(); }
	void onTriggeredByProgram() { emit triggered(); }

signals:
	void triggered();
};