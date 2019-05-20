#include "Parametrizable.h"

#include <iostream>

#include "GenericParameterWidget.h"


Parametrizable::Parametrizable():
	m_parameterToName(),
	m_parameters()                    
{
	// empty
}


Parametrizable::~Parametrizable()
{
	for(auto p : m_parameters)
	{
		delete p;
	}
}


Parametrizable::Parametrizable(const Parametrizable& other) : m_parameterToName(), m_parameters(), m_guiBuilder(other.m_guiBuilder)
{
	for(auto it = other.m_parameterToName.constBegin(); it != other.m_parameterToName.constEnd(); ++it)
	{
		GenericParameter * p = it.value()->copy();
		m_parameterToName.insert(it.key(), p);
		m_parameters.push_back(p);
	}
}


Parametrizable& Parametrizable::operator=(const Parametrizable & other)
{
	if (this == &other)
		return *this;

	m_guiBuilder = other.m_guiBuilder;

	for(auto p : m_parameters)
	{
		delete p;
	}

	m_parameterToName.clear();
	m_parameters.clear();

	for (auto it = other.m_parameterToName.constBegin(); it != other.m_parameterToName.constEnd(); ++it)
	{
		GenericParameter * p = it.value()->copy();
		m_parameterToName.insert(it.key(), p);
		m_parameters.push_back(p);
	}

	return *this;
}


void Parametrizable::addDoubleParameter(const QString& name, double min, double max, double value, double singleStep, bool showGUI)
{
	addGenericParameter(new DoubleParameter(name, min, max, value, singleStep), showGUI);
}


void Parametrizable::addIntParameter(const QString & name, int min, int max, int value, int singleStep, bool showGUI)
{
	addGenericParameter(new IntParameter(name, min, max, value, singleStep), showGUI);
}


void Parametrizable::addEnumParameter(const QString & name, const QVector<QString> & allValues, int value, bool showGUI)
{
	addGenericParameter(new EnumParameter(name, allValues, value), showGUI);
}


void Parametrizable::addBoolParameter(const QString & name, bool value, bool showGUI)
{
	addGenericParameter(new BoolParameter(name, value), showGUI);
}


void Parametrizable::addStringParameter(const QString & name, QString value, bool showGUI)
{
	addGenericParameter(new StringParameter(name, value), showGUI);
}


void Parametrizable::addFolderParameter(const QString & name, QString value, bool showGUI)
{
	addGenericParameter(new FolderParameter(name, value), showGUI);
}


void Parametrizable::addFileParameter(const QString & name, QString value, FileDirection direction, QString typeSelector, bool showGUI)
{
	addGenericParameter(new FileParameter(name, value, typeSelector, direction), showGUI);
}


void Parametrizable::addTriggerParameter(const QString& name, QObject* receiver, const char* slot, bool showGUI)
{
	addGenericParameter(new TriggerParameter(name, receiver, slot), showGUI);
}


int Parametrizable::getEnumParameter(const QString & name) const
{
	return getParameterToName(name)->getValueAsEnum();
}


int Parametrizable::getIntParameter(const QString & name) const
{
	return getParameterToName(name)->getValueAsInt();
}


double Parametrizable::getDoubleParameter(const QString & name) const
{
	return getParameterToName(name)->getValueAsDouble();
}


bool Parametrizable::getBoolParameter(const QString & name) const
{
	return getParameterToName(name)->getValueAsBool();
}


QString Parametrizable::getStringParameter(const QString & name) const
{
	return getParameterToName(name)->getValueAsString();
}


QString Parametrizable::getFileParameter(const QString & name) const
{
	return getParameterToName(name)->getValueAsString();
}


QString Parametrizable::getFolderParameter(const QString & name) const
{
	return getParameterToName(name)->getValueAsString();
}


void Parametrizable::setEnumParameter(const QString & name, int value)
{
	getParameterToName(name)->setValue(value);
}


void Parametrizable::setIntParameter(const QString & name, int value)
{
	getParameterToName(name)->setValue(value);
}


void Parametrizable::setDoubleParameter(const QString & name, double value)
{
	getParameterToName(name)->setValue(value);
}


void Parametrizable::setBoolParameter(const QString & name, bool value)
{
	getParameterToName(name)->setValue(value);
}


void Parametrizable::setStringParameter(const QString & name, const QString & value)
{
	getParameterToName(name)->setValue(value);
}


void Parametrizable::setFileParameter(const QString & name, const QString & value)
{
	getParameterToName(name)->setValue(value);
}


void Parametrizable::setFolderParameter(const QString & name, const QString & value)
{
	getParameterToName(name)->setValue(value);
}


void Parametrizable::setParameterLocked(const QString& name, bool locked)
{
	getParameterToName(name)->setLocked(locked);
}


void Parametrizable::notifyOnParameterChanged(const QString& name, QObject* receiver, const char * slot) const
{
	GenericParameter* genericParameter = getParameterToName(name);
	if (genericParameter->isInt())
	{
		IntParameter* parameter = dynamic_cast<IntParameter*>(genericParameter);
		if (parameter)
		{
			QObject::connect(parameter, SIGNAL(valueChangedByGui(int)), receiver, slot);
			QObject::connect(parameter, SIGNAL(valueChangedByProgram(int)), receiver, slot);
		}
	}
	else if (genericParameter->isDouble())
	{
		DoubleParameter* parameter = dynamic_cast<DoubleParameter*>(genericParameter);
		if (parameter)
		{
			QObject::connect(parameter, SIGNAL(valueChangedByGui(double)), receiver, slot);
			QObject::connect(parameter, SIGNAL(valueChangedByProgram(double)), receiver, slot);
		}
	}
	else if (genericParameter->isEnum())
	{
		EnumParameter* parameter = dynamic_cast<EnumParameter*>(genericParameter);
		if (parameter)
		{
			QObject::connect(parameter, SIGNAL(valueChangedByGui(int)), receiver, slot);
			QObject::connect(parameter, SIGNAL(valueChangedByProgram(int)), receiver, slot);
		}
	}
	else if (genericParameter->isBool())
	{
		BoolParameter* parameter = dynamic_cast<BoolParameter*>(genericParameter);
		if (parameter)
		{
			QObject::connect(parameter, SIGNAL(valueChangedByGui(bool)), receiver, slot);
			QObject::connect(parameter, SIGNAL(valueChangedByProgram(bool)), receiver, slot);
		}
	}
	else if (genericParameter->isString())
	{
		StringParameter* parameter = dynamic_cast<StringParameter*>(genericParameter);
		if (parameter)
		{
			QObject::connect(parameter, SIGNAL(valueChangedByGui(QString)), receiver, slot);
			QObject::connect(parameter, SIGNAL(valueChangedByProgram(QString)), receiver, slot);
		}
	}
	else if (genericParameter->isFile())
	{
		FileParameter* parameter = dynamic_cast<FileParameter*>(genericParameter);
		if (parameter)
		{
			QObject::connect(parameter, SIGNAL(valueChangedByGui(QString)), receiver, slot);
			QObject::connect(parameter, SIGNAL(valueChangedByProgram(QString)), receiver, slot);
		}
	}
	else if (genericParameter->isFolder())
	{
		FolderParameter* parameter = dynamic_cast<FolderParameter*>(genericParameter);
		if (parameter)
		{
			QObject::connect(parameter, SIGNAL(valueChangedByGui(QString)), receiver, slot);
			QObject::connect(parameter, SIGNAL(valueChangedByProgram(QString)), receiver, slot);
		}
	}
	else if(genericParameter->isTrigger())
	{
		TriggerParameter* parameter = dynamic_cast<TriggerParameter*>(genericParameter);
		if(parameter)
		{
			QObject::connect(parameter, SIGNAL(triggered()), receiver, slot);
		}
	}
}


size_t Parametrizable::getNumParameters() const
{
	return m_parameters.size();
}


bool Parametrizable::hasParameters() const
{
	return getNumParameters() > 0;
}


void Parametrizable::addGenericParameter(GenericParameter* pParameter, bool showGUI)
{
	QString parameterName = pParameter->getName();
	m_guiBuilder.push_back(
		[parameterName, showGUI](GenericParameterWidget * w, const Parametrizable * p)
	{
		GenericParameter * pParameter = p->getParameterToName(parameterName);
		w->addParameter(*pParameter, showGUI);
	});

	bool conflict = m_parameterToName.contains(pParameter->getName());

	if (!conflict)
	{
		m_parameters.append(pParameter);
		m_parameterToName.insert(pParameter->getName(), pParameter);
	}
	else // No insertion took place
	{
		QMap<QString, GenericParameter*>::iterator it = m_parameterToName.find(pParameter->getName());
		if (typeid(*pParameter) == typeid(*(it.value()))) // If it is the same parameter it gets overwritten.
		{
			m_parameterToName[pParameter->getName()] = pParameter;
		}
		else
		{
			std::cout << "[Exception] Parameter Name Conflict (" << pParameter->getName().toStdString() << ")" << std::endl;
			throw std::runtime_error("[Exception] Parameter Name Conflict (" + pParameter->getName().toStdString() + ")");
		}
	}
}


void Parametrizable::startGroup(const QString &name)
{
	m_guiBuilder.push_back(
		[name](GenericParameterWidget * w, const Parametrizable * p)
	{
		w->startGroup(name);
	});
}


void Parametrizable::endGroup()
{
	m_guiBuilder.push_back(
		[](GenericParameterWidget * w, const Parametrizable * p)
	{
		w->endGroup();
	});
}


GenericParameter* Parametrizable::getParameterToName(const QString & name) const
{
	QMap<QString, GenericParameter*>::const_iterator it = m_parameterToName.find(name);
	if (it == m_parameterToName.end())
	{
		std::cout << "[Exception] Parameter Not found (" << name.toStdString() << ")" << std::endl;
		throw std::runtime_error("[Exception] Parameter Not found (" + name.toStdString() + ")");
	}

	return it.value();
}