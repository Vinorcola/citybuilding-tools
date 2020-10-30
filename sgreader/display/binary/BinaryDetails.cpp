#include "BinaryDetails.hpp"

#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>



BinaryDetails::BinaryDetails(QWidget* parent) :
    QWidget(parent),
    errorMessage(new QLabel(this)),
    details(new QLabel(this))
{
    details->setFont(QFont("Courier New"));

    auto layout(new QVBoxLayout(this));
    layout->addWidget(errorMessage);
    layout->addWidget(details);
    layout->addStretch(1);

    setMinimumWidth(340);
    setMaximumWidth(340);
    setLayout(layout);
}



void BinaryDetails::changeBinaryDetails(const QString& details)
{
    errorMessage->setVisible(false);
    this->details->setText(details);
    this->details->setVisible(true);
}



void BinaryDetails::setError(const QString& errorMessage)
{
    details->setVisible(false);
    this->errorMessage->setText(errorMessage);
    this->errorMessage->setVisible(true);
}



void BinaryDetails::clear()
{
    errorMessage->setVisible(false);
    details->setText("");
}
