#include "GenericParameter.h"

#include <iostream>

#include "GenericVisualComponent.h"


void GenericParameter::setLocked(bool locked)
{
	m_locked = locked;
	emit this->locked(m_locked);
}


void GenericParameter::invalidTypeRequest() const
{
	std::cout << "[Exception] Invalid Generic Parameter Type (" << getName().toStdString() << ")" << std::endl;
	throw std::runtime_error("[Exception] Invalid Generic Parameter Type (" + getName().toStdString() + ")");
}


GenericVisualComponent* DoubleParameter::createVisualComponent(QWidget* pParent) const
{
	return new DoubleGenericVisualComponent(*this, pParent);
}


void DoubleParameter::setValueInternal(double value)
{
	if (value < m_min)
		value = m_min;
	if (value > m_max)
		value = m_max;

	m_value = value;
}


void DoubleParameter::onValueChangedByGui(double value)
{
	setValueInternal(value);
	emit valueChangedByGui(value);
}


void DoubleParameter::onValueChangedByProgram(double value)
{
	setValueInternal(value);
	emit valueChangedByProgram(value);
}


GenericVisualComponent* IntParameter::createVisualComponent(QWidget* pParent) const
{
	return new IntGenericVisualComponent(*this, pParent);
}


void IntParameter::setValueInternal(int value)
{
	if (value < m_min)
		value = m_min;
	if (value > m_max)
		value = m_max;

	m_value = value;
}


void IntParameter::onValueChangedByGui(int value)
{
	setValueInternal(value);
	emit valueChangedByGui(value);
}


void IntParameter::onValueChangedByProgram(int value)
{
	setValueInternal(value);
	emit valueChangedByProgram(value);
}


void EnumParameter::setValueInternal(int value)
{ 
	if (value < 0 || value >= m_allValues.size())
		return;

	m_value = value; 
}


GenericVisualComponent* EnumParameter::createVisualComponent(QWidget* pParent) const
{
	return new EnumGenericVisualComponent(*this, pParent);
}


QString EnumParameter::getValueToInt(int idx) const
{
	if (idx << m_allValues.size())
	{
		return m_allValues[idx];
	}
	
	std::cout << "[Exception] Enum Entry Not Found (" << idx << "in " << getName().toStdString() << ")" << std::endl;
	throw std::runtime_error("[Exception] Enum Entry Not Found(" + std::to_string(idx) + "in " + getName().toStdString() + ")");
}


int EnumParameter::getIntToValue(const QString& name) const
{
	QMap<QString, int>::const_iterator it = m_indicesToValue.find(name);
	if (it == m_indicesToValue.end())
	{
		std::cout << "[Exception] Enum Entry Not Found (" << name.toStdString() << "in " << getName().toStdString() << ")" << std::endl;
		throw std::runtime_error("[Exception] Enum Entry Not Found(" + name.toStdString() + "in " + getName().toStdString() + ")");
	}
	return it.value();
}


void EnumParameter::onValueChangedByGui(int value)
{
	setValueInternal(value);
	emit valueChangedByGui(value);
}


void EnumParameter::onValueChangedByProgram(int value)
{
	setValueInternal(value);
	emit valueChangedByProgram(value);
}


GenericVisualComponent* BoolParameter::createVisualComponent(QWidget* pParent) const
{
	return new BoolGenericVisualComponent(*this, pParent);
}


void BoolParameter::setValueInternal(bool value)
{
	m_value = value;
}


void BoolParameter::onValueChangedByGui(bool value)
{
	setValueInternal(value);
	emit valueChangedByGui(value);
}


void BoolParameter::onValueChangedByProgram(bool value)
{
	setValueInternal(value);
	emit valueChangedByProgram(value);
}


GenericVisualComponent* StringParameter::createVisualComponent(QWidget* pParent) const
{
	return new StringGenericVisualComponent(*this, pParent);
}


void StringParameter::setValueInternal(const QString& value)
{ 
	m_value = value;
}


void StringParameter::onValueChangedByGui(QString value)
{
	setValueInternal(value);
	emit valueChangedByGui(value);
}


void StringParameter::onValueChangedByProgram(QString value)
{
	setValueInternal(value);
	emit valueChangedByProgram(value);
}


GenericVisualComponent* FileParameter::createVisualComponent(QWidget* pParent) const
{
	return new FileGenericVisualComponent(*this, pParent);
}


void FileParameter::setValueInternal(const QString& value)
{ 
	m_value = value; 
}


void FileParameter::onValueChangedByGui(QString value)
{
	setValueInternal(value);
	emit valueChangedByGui(value);
}


void FileParameter::onValueChangedByProgram(QString value)
{
	setValueInternal(value);
	emit valueChangedByProgram(value);
}


GenericVisualComponent* FolderParameter::createVisualComponent(QWidget* pParent) const
{
	return new FolderGenericVisualComponent(*this, pParent);
}


void FolderParameter::setValueInternal(const QString& value)
{ 
	m_value = value; 
}


void FolderParameter::onValueChangedByGui(QString value)
{
	setValueInternal(value);
	emit valueChangedByGui(value);
}


void FolderParameter::onValueChangedByProgram(QString value)
{
	setValueInternal(value);
	emit valueChangedByProgram(value);
}


GenericVisualComponent* TriggerParameter::createVisualComponent(QWidget* pParent) const
{
	return new TriggerGenericVisualComponent(*this, pParent);
}
