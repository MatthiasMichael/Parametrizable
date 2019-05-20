#pragma once

#include "Parametrizable.h"


class ExampleWidget : public QWidget, public Parametrizable
{
	Q_OBJECT
public:
	ExampleWidget(QWidget * parent = nullptr);
};