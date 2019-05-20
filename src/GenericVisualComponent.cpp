#include "GenericVisualComponent.h"


#include <QCheckBox>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "GenericParameter.h"


GenericVisualComponent::GenericVisualComponent(const GenericParameter& param, QWidget* pParent /*= nullptr*/) :
	QWidget(pParent), m_locked(false)
{
}


void GenericVisualComponent::onLocked(bool locked)
{
	setEnabled(locked);
	m_locked = locked;
}



DoubleGenericVisualComponent::DoubleGenericVisualComponent(const DoubleParameter & param, QWidget * pParent /*= nullptr*/) : 
	GenericVisualComponent(param)
{
	QHBoxLayout * pLayout = new QHBoxLayout(this);
	
	QLabel * pLabel = new QLabel(this);
	pLabel->setText(param.m_name);

	QDoubleSpinBox * pSpinBox = new QDoubleSpinBox(this);
	pSpinBox->setMinimum(param.m_min);
	pSpinBox->setMaximum(param.m_max);
	pSpinBox->setValue(param.m_value);
	pSpinBox->setDecimals(4);

	if(param.m_singleStep != 0)
	{
		pSpinBox->setSingleStep(param.m_singleStep);
	}
	else
	{
		double range = param.m_max - param.m_min;
		double stepWidth = 1.0;
		
		if (range <= 0.1)
		{
			stepWidth = 0.001;
		}
		else if(range <= 1)
		{
			stepWidth = 0.01;
		}
		else if(range <= 10)
		{
			stepWidth = 0.1;
		}
		else if (range <= 100)
		{
			stepWidth = 1.0;
		}
		pSpinBox->setSingleStep(stepWidth);
	}

	connect(pSpinBox, &QDoubleSpinBox::editingFinished, [=] { onValueChangedByGui(pSpinBox->value()); });
	connect(this, &DoubleGenericVisualComponent::valueChangedByProgram, pSpinBox, &QDoubleSpinBox::setValue);

	connect(&param, &DoubleParameter::valueChangedByProgram, this, &DoubleGenericVisualComponent::onValueChangedByProgram);
	connect(this, &DoubleGenericVisualComponent::valueChangedByGui, &param, &DoubleParameter::onValueChangedByGui);

	pLayout->addWidget(pLabel);
	pLayout->addWidget(pSpinBox);

	pLayout->setContentsMargins(9, 3, 9, 0);

	setLayout(pLayout);
}


void DoubleGenericVisualComponent::onValueChangedByGui(double value)
{
	if (!m_locked)
	{
		emit valueChangedByGui(value);
	}
}


void DoubleGenericVisualComponent::onValueChangedByProgram(double value)
{
	if(!m_locked)
	{
		emit valueChangedByProgram(value);
	}
}


IntGenericVisualComponent::IntGenericVisualComponent(const IntParameter & param, QWidget * pParent /*= nullptr*/) : 
	GenericVisualComponent(param, pParent)
{
	QHBoxLayout * pLayout = new QHBoxLayout(this);

	QLabel * pLabel = new QLabel(this);
	pLabel->setText(param.m_name);
	
	QSpinBox * pSpinBox = new QSpinBox(this);
	pSpinBox->setMinimum(param.m_min);
	pSpinBox->setMaximum(param.m_max);
	pSpinBox->setValue(param.m_value);

	if (param.m_singleStep != 0)
	{
		pSpinBox->setSingleStep(param.m_singleStep);
	}
	else
	{
		int range = param.m_max - param.m_min;
		int stepWidth = 1;

		if (range <= 100)
		{
			stepWidth = 1;
		}
		else if (range <= 1000)
		{
			stepWidth = 10;
		}
		else if (range <= 10000)
		{
			stepWidth = 100;
		}

		pSpinBox->setSingleStep(stepWidth);
	}

	connect(pSpinBox, &QSpinBox::editingFinished, [=] { onValueChangedByGui(pSpinBox->value()); });
	connect(this, &IntGenericVisualComponent::valueChangedByProgram, pSpinBox, &QSpinBox::setValue);

	connect(&param, &IntParameter::valueChangedByProgram, this, &IntGenericVisualComponent::onValueChangedByProgram);
	connect(this, &IntGenericVisualComponent::valueChangedByGui, &param, &IntParameter::onValueChangedByGui);

	pLayout->addWidget(pLabel);
	pLayout->addWidget(pSpinBox);

	pLayout->setContentsMargins(9, 3, 9, 0);

	setLayout(pLayout);
}


void IntGenericVisualComponent::onValueChangedByGui(int value)
{
	if(!m_locked)
	{
		emit valueChangedByGui(value);
	}
}


void IntGenericVisualComponent::onValueChangedByProgram(int value)
{
	if (!m_locked)
	{
		emit valueChangedByProgram(value);
	}
}


EnumGenericVisualComponent::EnumGenericVisualComponent(const EnumParameter & param, QWidget * pParent /*= nullptr*/) : 
	GenericVisualComponent(param, pParent)
{
	QHBoxLayout * pLayout = new QHBoxLayout(this);

	QLabel * pLabel = new QLabel(this);
	pLabel->setText(param.m_name);

	QComboBox * pComboBox = new QComboBox(this);
	
	for (int i = param.m_allValues.size() - 1 ; i >= 0; i--)
	{
		pComboBox->insertItem(0, param.m_allValues[i]);
	}

	if(param.m_value < pComboBox->count())
		pComboBox->setCurrentIndex(param.m_value);

	connect(pComboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), 
		this, &EnumGenericVisualComponent::onValueChangedByGui);
	connect(this, &EnumGenericVisualComponent::valueChangedByProgram, pComboBox, &QComboBox::setCurrentIndex);

	connect(&param, &EnumParameter::valueChangedByProgram, this, &EnumGenericVisualComponent::onValueChangedByProgram);
	connect(this, &EnumGenericVisualComponent::valueChangedByGui, &param, &EnumParameter::onValueChangedByGui);

	pLayout->addWidget(pLabel);
	pLayout->addWidget(pComboBox);

	pLayout->setContentsMargins(9, 3, 9, 0);

	setLayout(pLayout);
}


void EnumGenericVisualComponent::onValueChangedByGui(int value)
{
	if (!m_locked)
	{
		emit valueChangedByGui(value);
	}
}


void EnumGenericVisualComponent::onValueChangedByProgram(int value)
{
	if (!m_locked)
	{
		emit valueChangedByProgram(value);
	}
}


BoolGenericVisualComponent::BoolGenericVisualComponent(const BoolParameter & param, QWidget * pParent /*= nullptr*/) : 
	GenericVisualComponent(param, pParent)
{
	QHBoxLayout * pLayout = new QHBoxLayout(this);

	QCheckBox * pCheckBox = new QCheckBox(this);
	pCheckBox->setText(param.m_name);
	pCheckBox->setChecked(param.m_value);

	connect(pCheckBox, &QCheckBox::stateChanged, [=] {onValueChangedByGui(pCheckBox->checkState() == Qt::Checked); });
	connect(this, &BoolGenericVisualComponent::valueChangedByProgram, 
		[=](bool value) {pCheckBox->setCheckState(value ? Qt::Checked : Qt::Unchecked); });

	connect(&param, &BoolParameter::valueChangedByProgram, this, &BoolGenericVisualComponent::onValueChangedByProgram);
	connect(this, &BoolGenericVisualComponent::valueChangedByGui, &param, &BoolParameter::onValueChangedByGui);

	pLayout->addWidget(pCheckBox);

	pLayout->setContentsMargins(9, 3, 9, 0);

	setLayout(pLayout);
}


void BoolGenericVisualComponent::onValueChangedByGui(bool value)
{
	if (!m_locked)
	{
		emit valueChangedByGui(value);
	}
}


void BoolGenericVisualComponent::onValueChangedByProgram(bool value)
{
	if (!m_locked)
	{
		emit valueChangedByProgram(value);
	}
}


StringGenericVisualComponent::StringGenericVisualComponent(const StringParameter & param, QWidget * pParent /*= nullptr*/) : 
	GenericVisualComponent(param, pParent)
{
	QHBoxLayout * pLayout = new QHBoxLayout(this);
	
	QLabel * pLabel = new QLabel(this);
	pLabel->setText(param.m_name);

	QLineEdit * pLineEdit = new QLineEdit(this);
	pLineEdit->setText(param.m_value);

	connect(pLineEdit, &QLineEdit::editingFinished, [=] {onValueChangedByGui(pLineEdit->text()); });
	connect(this, &StringGenericVisualComponent::onValueChangedByProgram, pLineEdit, &QLineEdit::setText);

	connect(&param, &StringParameter::valueChangedByProgram, this, &StringGenericVisualComponent::onValueChangedByProgram);
	connect(this, &StringGenericVisualComponent::valueChangedByGui, &param, &StringParameter::onValueChangedByGui);

	pLayout->addWidget(pLabel);
	pLayout->addWidget(pLineEdit);

	pLayout->setContentsMargins(9, 3, 9, 0);

	this->setLayout(pLayout);
}


void StringGenericVisualComponent::onValueChangedByGui(QString value)
{
	if (!m_locked)
	{
		emit valueChangedByGui(value);
	}
}


void StringGenericVisualComponent::onValueChangedByProgram(QString value)
{
	if (!m_locked)
	{
		emit valueChangedByProgram(value);
	}
}


FileGenericVisualComponent::FileGenericVisualComponent(const FileParameter & param, QWidget * pParent /*= nullptr*/) : 
	GenericVisualComponent(param, pParent), m_direction(param.m_direction), m_typeSelector(param.m_typeSelector)
{
	QHBoxLayout * pLayout = new QHBoxLayout(this);
	
	QLabel * pLabel = new QLabel(this);
	pLabel->setText(param.m_name);
	
	QLineEdit * pLineEdit = new QLineEdit(this);
	pLineEdit->setText(param.m_value);
	pLineEdit->setReadOnly(true);
	
	QPushButton * pButton = new QPushButton(this);
	pButton->setText("Search...");
	
	connect(pButton, &QPushButton::clicked, this, &FileGenericVisualComponent::onButtonClicked);

	connect(pLineEdit, &QLineEdit::editingFinished, [=] {onValueChangedByGui(pLineEdit->text()); });
	connect(this, &FileGenericVisualComponent::onValueChangedByProgram, pLineEdit, &QLineEdit::setText);

	connect(&param, &FileParameter::valueChangedByProgram, this, &FileGenericVisualComponent::onValueChangedByProgram);
	connect(this, &FileGenericVisualComponent::valueChangedByGui, [=](QString value) {pLineEdit->setText(value); });
	connect(this, &FileGenericVisualComponent::valueChangedByGui, &param, &FileParameter::onValueChangedByGui);

	pLayout->addWidget(pLabel);
	pLayout->addWidget(pLineEdit);
	pLayout->addWidget(pButton);

	pLayout->setContentsMargins(9, 3, 9, 0);

	setLayout(pLayout);
}

void FileGenericVisualComponent::onButtonClicked(bool checked)
{
	QString mode = m_direction == OPEN ? "Open " : "Save ";
	QString t_dialogName = mode + "File";
	QString t_fileName = "";
	if(m_direction == OPEN)
	{
		t_fileName = QFileDialog::getOpenFileName(this, t_dialogName, QString(),  "File (" + m_typeSelector + ")");
	}
	else if(m_direction == SAVE)
	{
		t_fileName = QFileDialog::getSaveFileName(this, t_dialogName, QString(),  m_typeSelector);
	}

	if(!t_fileName.isEmpty())
	{
		onValueChangedByGui(t_fileName);
	}
}


void FileGenericVisualComponent::onValueChangedByGui(QString value)
{
	if (!m_locked)
	{
		emit valueChangedByGui(value);
	}
}


void FileGenericVisualComponent::onValueChangedByProgram(QString value)
{
	if (!m_locked)
	{
		emit valueChangedByProgram(value);
	}
}


FolderGenericVisualComponent::FolderGenericVisualComponent(const FolderParameter & param, QWidget * pParent /*= nullptr */) : 
	GenericVisualComponent(param, pParent)
{
	QHBoxLayout * pLayout = new QHBoxLayout(this);
	
	QLabel * pLabel = new QLabel(this);
	pLabel->setText(param.m_name);
	
	QLineEdit * pLineEdit = new QLineEdit(this);
	pLineEdit->setText(param.m_value);
	pLineEdit->setReadOnly(true);
	
	QPushButton * pButton = new QPushButton(this);
	pButton->setText("Search...");
	
	connect(pButton, &QPushButton::clicked, this, &FolderGenericVisualComponent::onButtonClicked);

	connect(pLineEdit, &QLineEdit::editingFinished, [=] {onValueChangedByGui(pLineEdit->text()); });
	connect(this, &FolderGenericVisualComponent::onValueChangedByProgram, pLineEdit, &QLineEdit::setText);

	connect(&param, &FolderParameter::valueChangedByProgram, this, &FolderGenericVisualComponent::onValueChangedByProgram);
	connect(this, &FolderGenericVisualComponent::valueChangedByGui, [=](QString value) {pLineEdit->setText(value); });
	connect(this, &FolderGenericVisualComponent::valueChangedByGui, &param, &FolderParameter::onValueChangedByGui);

	pLayout->addWidget(pLabel);
	pLayout->addWidget(pLineEdit);
	pLayout->addWidget(pButton);

	pLayout->setContentsMargins(9, 3, 9, 0);

	this->setLayout(pLayout);
}


void FolderGenericVisualComponent::onButtonClicked(bool checked)
{
	QString t_dialogName = "Select Folder";

	QString t_folderName = QFileDialog::getExistingDirectory(this, t_dialogName);// , m_lineEdit->text());
	if(!t_folderName.isEmpty())
	{
		onValueChangedByGui(t_folderName);
	}
}


void FolderGenericVisualComponent::onValueChangedByGui(QString value)
{
	if (!m_locked)
	{
		emit valueChangedByGui(value);
	}
}


void FolderGenericVisualComponent::onValueChangedByProgram(QString value)
{
	if (!m_locked)
	{
		emit valueChangedByProgram(value);
	}
}


TriggerGenericVisualComponent::TriggerGenericVisualComponent(const TriggerParameter & param, QWidget * pParent /*= nullptr*/) :
	GenericVisualComponent(param, pParent)
{
	QHBoxLayout * pLayout = new QHBoxLayout(this);

	QPushButton * pButton = new QPushButton(this);
	pButton->setText(param.m_name);

	connect(pButton, &QPushButton::clicked, this, &TriggerGenericVisualComponent::onTriggeredByGui);

	connect(&param, &TriggerParameter::triggered, this, &TriggerGenericVisualComponent::onTriggeredByProgram);
	connect(this, &TriggerGenericVisualComponent::triggeredByGui, &param, &TriggerParameter::onTriggeredByGui);

	pLayout->addWidget(pButton);

	setLayout(pLayout);
}


void TriggerGenericVisualComponent::onTriggeredByGui()
{
	if(!m_locked)
	{
		emit triggeredByGui();
	}
}


void TriggerGenericVisualComponent::onTriggeredByProgram()
{
	if (!m_locked)
	{
		emit triggeredByProgram();
	}
}