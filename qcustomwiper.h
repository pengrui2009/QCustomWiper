#ifndef QCUSTOMWIPER_H
#define QCUSTOMWIPER_H

#include <QWidget>
#include <QPainter>

/**
 * @brief Feature:
 * Support
 * Support
 * Support
 * Support
 */

#ifdef quc
#if (QT_VERSION < QT_VERSION_CHECK(5,0,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT QCustomMobileSignal : public QWidget
#else
class QCustomWiper : public QWidget
#endif
{
    Q_OBJECT
    //    Q_PROPERTY()
public:
    enum WiperMode {
        WIPERMODE_DEFAULT = 0,
        WIPERMODE_A = 1,
        WIPERMODE_B = 2,
        WIPERMODE_C = 3,
    };

    explicit QCustomWiper(QWidget *parent = nullptr);
    ~QCustomWiper();

protected:
    QSize sizeHint()                const;
    QSize minimumSizeHint()         const;

    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);

    void drawBackground(QPainter *painter);
    void drawWiper(QPainter *painter);
private:
    QColor m_active_color_;
    QColor m_unactive_color_;

    WiperMode m_wiper_state_;
    QColor m_background_color_;

signals:

public slots:
    void setWiperMode(WiperMode mode);
};

#endif // QCUSTOMWIPER_H
