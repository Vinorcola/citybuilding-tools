#include "InfoDialog.hpp"

#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSizePolicy>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

const QString VERSION("2.0.0 (2020-12-29)");
const QStringList COPYRIGHTS({
    "Copyright (C) 2007-2020 Bianca van Schaik &lt;pecuniam@gmail.com&gt;",
    "Copyright (C) 2020 Vinorcola &lt;vinorcola@gmail.com&gt;"
});
const QString INTRO(QObject::tr(
    "Read graphics files (*.sg2 and *.sg3) from Impressions citybuilding games.<br/><br/>"
    "This program is distributed in the hope that it will be useful,<br/>"
    "but WITHOUT ANY WARRANTY; without even the implied warranty of<br/>"
    "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.<br/>"
    "See the GNU General Public License in <strong>License</strong> tab for more details."
));
const QString HELP(QObject::tr(
   "<p>This program can open the .sg2 and .sg3 files that were used in "
   "the citybuilding games from Impressions Games.</p>"
   "<p><strong>Loading a single SG file:</strong><br/>"
   "Open a .sg2/.sg3 file and a tree of images will appear to the left. "
   "Click any image to show it on the right. Use the File menu to save the "
   "image as PNG.</p>"
   "<p><strong>Batch-extraction:</strong><br/>"
   "To extract all images in one go, use File -> Batch Extract. "
   "Select a directory where SG files are stored, select a destination, "
   "and all images will be extracted.</p>"
   "<p>SG files contain multiple images, usually thousands. The SG file itself acts as a "
   "dictionary for all the images, the actual pixels are stored in "
   "the .555 files that are also present in the games.</p>"
));
const QString LICENSES_INTRO(QObject::tr(
    "<p>SG Reader is released under the <strong>GNU General Public Licence</strong>, see below "
    "for the licence text.</p>"
    "<a>The icons are issued from <a href=\"https://fontawesome.com\">FontAwesome</a> "
    "and are released under the <strong>CC-BY-4.0</strong> License, see below for the licence text.</p>"
    "<p>The source code of this program can be downloaded at:<br/>"
    "<a href=\"https://github.com/Vinorcola/citybuilding-tools\">https://github.com/Vinorcola/citybuilding-tools</a><br/>"
    "(Forked from original project: <a href=\"https://github.com/bvschaik/citybuilding-tools\">https://github.com/bvschaik/citybuilding-tools</a>)</p>"
));



InfoDialog::InfoDialog(QWidget* parent) :
    QDialog(parent)
{
    auto tabs(new QTabWidget(this));
    tabs->addTab(generateAboutTabContent(tabs), tr("About"));
    tabs->addTab(generateHelpTabContent(tabs), tr("Help"));
    tabs->addTab(generateLicenseTabContent(tabs), tr("Licenses"));

    auto layout(new QVBoxLayout());
    layout->addWidget(tabs);
    setLayout(layout);
}



QWidget* InfoDialog::generateAboutTabContent(QWidget* parent)
{
    QString copyrights("");
    for (auto copyright: COPYRIGHTS) {
        copyrights += "<li>" + copyright + "</li>";
    }
    auto content(
        QString(
            "<p style=\"text-align: center\"><strong>%0:</strong> %1</p>"
            "<ul>%2</ul>"
            "<p style=\"text-align: center\">%3</p>"
        )
        .arg(tr("Version"))
        .arg(VERSION)
        .arg(copyrights)
        .arg(INTRO)
    );

    auto label(new QLabel(content, parent));
    label->setWordWrap(true);
    label->setMinimumWidth(600);
    label->setMaximumWidth(600);

    auto layout(new QVBoxLayout());
    layout->addWidget(label);

    auto widget(new QWidget(parent));
    widget->setLayout(layout);

    return widget;
}



QWidget* InfoDialog::generateHelpTabContent(QWidget* parent)
{
    auto label(new QLabel(HELP, parent));
    label->setWordWrap(true);
    label->setMinimumWidth(600);
    label->setMaximumWidth(600);

    auto layout(new QVBoxLayout());
    layout->addWidget(label);

    auto widget(new QWidget(parent));
    widget->setLayout(layout);

    return widget;
}



QWidget* InfoDialog::generateLicenseTabContent(QWidget* parent)
{
    auto label(new QLabel(LICENSES_INTRO, parent));
    label->setWordWrap(true);
    label->setMinimumWidth(600);
    label->setMaximumWidth(600);

    auto licenseTabs(new QTabWidget(parent));
    licenseTabs->addTab(generateGplLicenseTabContent(licenseTabs), tr("GPL v2"));
    licenseTabs->addTab(generateCcByLicenseTabContent(licenseTabs), tr("CC-BY-4.0"));

    auto layout(new QVBoxLayout());
    layout->addWidget(label);
    layout->addWidget(licenseTabs);

    auto widget(new QWidget(parent));
    widget->setLayout(layout);

    return widget;
}



QWidget* InfoDialog::generateGplLicenseTabContent(QWidget* parent)
{
    QFile licenseFile(":/license/software");
    licenseFile.open(QIODevice::ReadOnly);
    QTextStream stream(&licenseFile);

    auto label(new QTextEdit(QString("<pre>%0</pre>").arg(stream.readAll()), parent));
    label->setReadOnly(true);

    auto layout(new QVBoxLayout());
    layout->addWidget(label);

    auto widget(new QWidget(parent));
    widget->setLayout(layout);

    return widget;
}



QWidget* InfoDialog::generateCcByLicenseTabContent(QWidget* parent)
{
    QFile licenseFile(":/license/icons");
    licenseFile.open(QIODevice::ReadOnly);
    QTextStream stream(&licenseFile);

    auto label(new QTextEdit(QString("<pre>%0</pre>").arg(stream.readAll()), parent));
    label->setReadOnly(true);

    auto layout(new QVBoxLayout());
    layout->addWidget(label);

    auto widget(new QWidget(parent));
    widget->setLayout(layout);

    return widget;
}
