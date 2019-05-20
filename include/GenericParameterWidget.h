#pragma once

#include <QWidget>
#include <QGroupBox>

#include "Parametrizable.h"


class GenericParameterWidget : public QWidget
{
	Q_OBJECT

public:
	GenericParameterWidget(QWidget * parent, const Parametrizable & p);

	void addParameter(GenericParameter & parameter, bool showGui);
	void startGroup(const QString & name);
	void endGroup();

	bool shouldBeDisplayed() const { return m_anythingToShow; }

private:
	bool m_anythingToShow;
	int m_boxDepthLevel;

	QVector<QString> m_currentGroupNames;
	QVector<QGroupBox*> m_currentGroupBoxes;

	QLayout * m_layout;
};
