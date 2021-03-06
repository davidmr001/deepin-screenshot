#include "fontsizewidget.h"

#include <QHBoxLayout>
#include <QDebug>

#include "utils/baseutils.h"
#include "utils/configsettings.h"

const QSize BUTTON_SIZE = QSize(20, 16);
const QSize LINE_EDIT_SIZE = QSize(43, 16);

Seperator::Seperator(QWidget *parent)
    : QLabel(parent) {
    setFixedSize(1, 16);
}

Seperator::~Seperator(){}

FontSizeWidget::FontSizeWidget(QWidget *parent)
    : QLabel(parent) {
    initWidget();
}

void FontSizeWidget::initWidget() {
    setObjectName("FontSizeWidget");
    setStyleSheet(getFileContent(":/resources/qss/fontsizewidget.qss"));
    setFixedSize(86, 18);
    m_fontSizeEdit = new QLineEdit(this);
    m_fontSizeEdit->setObjectName("FontSizeEdit");
    m_fontSizeEdit->setFixedSize(LINE_EDIT_SIZE);

    m_fontSize = ConfigSettings::instance()->value("text", "fontsize").toInt();
    m_fontSizeEdit->setText(QString("%1").arg(m_fontSize));
    m_addSizeBtn = new QPushButton(this);
    m_addSizeBtn->setObjectName("AddSizeBtn");
    m_addSizeBtn->setFixedSize(BUTTON_SIZE);
    m_reduceSizeBtn = new QPushButton(this);
    m_reduceSizeBtn->setObjectName("ReduceSizeBtn");
    m_reduceSizeBtn->setFixedSize(BUTTON_SIZE);

    QHBoxLayout* layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addSpacing(4);
    layout->addWidget(m_fontSizeEdit);
    layout->addSpacing(0);
    layout->addWidget( new Seperator(this));
    layout->addWidget(m_addSizeBtn);
    layout->addWidget( new Seperator(this));
    layout->addSpacing(0);
    layout->addWidget(m_reduceSizeBtn);
    layout->addStretch();
    setLayout(layout);

    connect(m_addSizeBtn, &QPushButton::clicked, [=]{
        adjustFontSize(true);
    });
    connect(m_reduceSizeBtn, &QPushButton::clicked, [=]{
        adjustFontSize(false);
    });
}

void FontSizeWidget::setFontSize(int fontSize) {
    m_fontSize = fontSize;
}

void FontSizeWidget::adjustFontSize(bool add) {
    if (add) {
        m_fontSize = m_fontSize + 1;
        m_fontSize = std::min(m_fontSize, 72);
    } else {
        m_fontSize = m_fontSize - 1;
        m_fontSize = std::max(9, m_fontSize);
    }

    m_fontSizeEdit->setText(QString("%1").arg(m_fontSize));
    emit fontSizeChanged(m_fontSize);

    connect(this, &FontSizeWidget::fontSizeChanged, this, [=](int fontSize){
        ConfigSettings::instance()->setValue("text", "fontsize", fontSize);
    });
}

FontSizeWidget::~FontSizeWidget() {

}
