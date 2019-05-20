#include "GenericParameterWidget.h"

#include <QVBoxLayout>
#include <QLabel>

#include "GenericVisualComponent.h"
#include <iostream>


GenericParameterWidget::GenericParameterWidget(QWidget * parent, const Parametrizable& p) : 
QWidget(parent), m_anythingToShow(false), m_boxDepthLevel(0)
{
	m_layout = new QVBoxLayout(this);

	for (auto f : p.m_guiBuilder)
	{
		f(this, &p);
	}

	setLayout(m_layout);
}


void GenericParameterWidget::addParameter(GenericParameter& parameter, bool showGui)
{
	if (showGui)
	{
		m_anythingToShow = true;

		GenericVisualComponent* t_component = parameter.createVisualComponent();
		if (m_boxDepthLevel > 0)
		{
			m_currentGroupBoxes.back()->layout()->addWidget(t_component);
		}
		else
		{
			m_layout->addWidget(t_component);
		}
	}
}


void GenericParameterWidget::startGroup(const QString& name)
{
	QVBoxLayout *t_GroupBoxLayout = new QVBoxLayout();
	t_GroupBoxLayout->addSpacerItem(new QSpacerItem(0, 10, QSizePolicy::Minimum, QSizePolicy::Fixed));

	QGroupBox *t_GroupBox = new QGroupBox(name);
	t_GroupBox->setContentsMargins(0, 0, 0, 3);
	t_GroupBox->setLayout(t_GroupBoxLayout);

	if(m_boxDepthLevel == 0)
	{
		m_layout->addWidget(t_GroupBox);
	}
	else
	{
		m_currentGroupBoxes.back()->layout()->addWidget(t_GroupBox);
	}
	
	m_currentGroupBoxes.push_back(t_GroupBox);
	m_currentGroupNames.push_back(name);

	m_boxDepthLevel++;
}


void GenericParameterWidget::endGroup()
{
	if (m_boxDepthLevel == 1)
	{
		static_cast<QVBoxLayout*>(m_layout)->addSpacerItem(
			new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));		
	}
	else if (m_boxDepthLevel > 1)
	{
		static_cast<QVBoxLayout*>(m_currentGroupBoxes.back()->layout())->addSpacerItem(
			new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));
	}

	m_currentGroupBoxes.pop_back();
	m_currentGroupNames.pop_back();

	m_boxDepthLevel--;
}