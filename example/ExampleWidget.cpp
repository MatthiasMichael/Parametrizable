#include "ExampleWidget.h"

#include <iostream>

#include <QPushButton>
#include <QVBoxLayout>

#include "GenericParameterWidget.h"


ExampleWidget::ExampleWidget(QWidget * parent)
{
	// Define which parameters our object has
	addStringParameter("Text", "Test");
	addIntParameter("Number of repeats", 1, 10, 3);

	// Initialize a GenericParameterWidget with the Parametrizable widget
	auto * layout = new QVBoxLayout(this);
	layout->addWidget(new GenericParameterWidget(this, *this));

	auto * button = new QPushButton("Print");
	layout->addWidget(button);

	setLayout(layout);

	connect(button, &QPushButton::clicked, [this]
	{
		// Fetch the parameters
		const auto text = getStringParameter("Text");
		const auto repeats = getIntParameter("Number of repeats");

		for (int i = 0; i < repeats; ++i)
		{
			std::cout << text.toStdString() << std::endl;
		}
	});
}