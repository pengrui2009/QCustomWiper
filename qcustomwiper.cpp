#include "qcustomwiper.h"

QCustomWiper::QCustomWiper(QWidget *parent) : QWidget(parent)
{
    m_wiper_state_ = WIPERMODE_DEFAULT;

    m_background_color_ = QColor(55,107,154, 30);

    m_active_color_ = Qt::yellow;
    m_unactive_color_ = Qt::gray;
}

QCustomWiper::~QCustomWiper()
{

}

void QCustomWiper::resizeEvent(QResizeEvent *)
{
    this->repaint();
}

QSize QCustomWiper::sizeHint() const
{
    return QSize(150, 150);
}

QSize QCustomWiper::minimumSizeHint() const
{
    return QSize(30, 30);
}

void QCustomWiper::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    drawBackground(&painter);

    drawWiper(&painter);


//    drawTitle(&painter);

//    drawTimeCost(&painter);

//    drawSystemTime(&painter);
}

void QCustomWiper::drawBackground(QPainter *painter)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    painter->save();

    painter->setBrush(m_background_color_);
    painter->drawRect(-width, -height, width * 2, height * 2);

    painter->restore();
}

void QCustomWiper::drawWiper(QPainter *painter)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    QLine lines[] = {
        {-76, -37, -35, 31},
        { 76, -37,  35, 31},
        { -40,-30,   0, 40}
    };

    painter->save();


    if (m_wiper_state_ != WIPERMODE_DEFAULT)
    {
        painter->setPen(QPen(m_active_color_, 4));
    } else {
        painter->setPen(QPen(m_unactive_color_, 4));
    }

    QRectF outer_rectangle(-150.0, -60.0, 300.0, 300.0);
    int outer_startAngle = 60 * 16;
    int outer_spanAngle = 60 * 16;
    painter->drawArc(outer_rectangle, outer_startAngle, outer_spanAngle);

    QRectF inner_rectangle(-50.0, 20.0, 100.0, 100.0);
    int inner_startAngle = 50 * 16;
    int inner_spanAngle = 80 * 16;
    painter->drawArc(inner_rectangle, inner_startAngle, inner_spanAngle);

    painter->drawLines(lines,  (sizeof(lines)/sizeof (lines[0])));

    QFont font;
    font.setPixelSize(28);
    painter->setFont(font);
    switch (m_wiper_state_)
    {
    case WIPERMODE_A:
        painter->drawText(QRect(-10, -30, 30, 30), "A");
        break;
    case WIPERMODE_B:
        painter->drawText(QRect(-10, -30, 30, 30), "B");
        break;
    case WIPERMODE_C:
        painter->drawText(QRect(-10, -30, 30, 30), "C");
        break;
    default:
        painter->drawText(QRect(-10, -30, 30, 30), "");
        break;
    }

    if (m_wiper_state_ != WIPERMODE_DEFAULT)
    {
        painter->setPen(Qt::NoPen);
        painter->setBrush(m_active_color_);
    } else {
        painter->setPen(Qt::NoPen);
        painter->setBrush(m_unactive_color_);
    }

    painter->drawEllipse(-8, 32, 15, 15);

    painter->restore();
}

void QCustomWiper::setWiperMode(WiperMode mode)
{
    if (this->m_wiper_state_ != mode)
    {
        this->m_wiper_state_ = mode;
        this->update();
    }
}
