#ifndef CBOXWIDGET_H
#define CBOXWIDGET_H

#include <QWidget>
#include <QHBoxLayout>

class CHBoxWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CHBoxWidget(QWidget *parent = nullptr)
        : QWidget(parent)
        , m_mainLayout(new QHBoxLayout(this))
    { this->setLayout(m_mainLayout); }

    void addSpacing(int size)
    { m_mainLayout->addSpacing(size); }
    void addStretch(int stretch = 0)
    { m_mainLayout->addStretch(stretch); }
    void addSpacerItem(QSpacerItem *spacerItem)
    { m_mainLayout->addSpacerItem(spacerItem); }
    void addWidget(QWidget *widget, int stretch = 0, Qt::Alignment alignment = Qt::Alignment())
    { m_mainLayout->addWidget(widget, stretch, alignment); }
    void addLayout(QLayout *layout, int stretch = 0)
    { m_mainLayout->addLayout(layout, stretch); }
    void addStrut(int strut)
    { m_mainLayout->addStrut(strut); }
    void addItem(QLayoutItem *item)
    { m_mainLayout->addItem(item); }

    void insertSpacing(int index, int size)
    { m_mainLayout->insertSpacing(index, size); }
    void insertStretch(int index, int stretch = 0)
    { m_mainLayout->insertStretch(index, stretch); }
    void insertSpacerItem(int index, QSpacerItem *spacerItem)
    { m_mainLayout->insertSpacerItem(index, spacerItem); }
    void insertWidget(int index, QWidget *widget, int stretch = 0, Qt::Alignment alignment = Qt::Alignment())
    { m_mainLayout->insertWidget(index, widget, stretch, alignment); }
    void insertLayout(int index, QLayout *layout, int stretch = 0)
    { m_mainLayout->insertLayout(index, layout, stretch); }
    void insertItem(int index, QLayoutItem *item)
    { m_mainLayout->insertItem(index, item); }

    int spacing() const
    { return m_mainLayout->spacing(); }
    void setSpacing(int spacing)
    { m_mainLayout->setSpacing(spacing); }

    bool setStretchFactor(QWidget *w, int stretch)
    { m_mainLayout->setStretchFactor(w, stretch); }
    bool setStretchFactor(QLayout *l, int stretch)
    { m_mainLayout->setStretchFactor(l, stretch); }
    void setStretch(int index, int stretch)
    { m_mainLayout->setStretch(index, stretch); }
    int stretch(int index) const
    { return m_mainLayout->stretch(index); }

    QLayoutItem *itemAt(int index) const
    { return m_mainLayout->itemAt(index); }
    QLayoutItem *takeAt(int index)
    { return m_mainLayout->takeAt(index); }
    int count() const
    { return m_mainLayout->count(); }

private:
    QHBoxLayout *m_mainLayout; // root
};

class CVBoxWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CVBoxWidget(QWidget *parent = nullptr)
        : QWidget(parent)
        , m_mainLayout(new QVBoxLayout(this))
    { this->setLayout(m_mainLayout); }

    void addSpacing(int size)
    { m_mainLayout->addSpacing(size); }
    void addStretch(int stretch = 0)
    { m_mainLayout->addStretch(stretch); }
    void addSpacerItem(QSpacerItem *spacerItem)
    { m_mainLayout->addSpacerItem(spacerItem); }
    void addWidget(QWidget *widget, int stretch = 0, Qt::Alignment alignment = Qt::Alignment())
    { m_mainLayout->addWidget(widget, stretch, alignment); }
    void addLayout(QLayout *layout, int stretch = 0)
    { m_mainLayout->addLayout(layout, stretch); }
    void addStrut(int strut)
    { m_mainLayout->addStrut(strut); }
    void addItem(QLayoutItem *item)
    { m_mainLayout->addItem(item); }

    void insertSpacing(int index, int size)
    { m_mainLayout->insertSpacing(index, size); }
    void insertStretch(int index, int stretch = 0)
    { m_mainLayout->insertStretch(index, stretch); }
    void insertSpacerItem(int index, QSpacerItem *spacerItem)
    { m_mainLayout->insertSpacerItem(index, spacerItem); }
    void insertWidget(int index, QWidget *widget, int stretch = 0, Qt::Alignment alignment = Qt::Alignment())
    { m_mainLayout->insertWidget(index, widget, stretch, alignment); }
    void insertLayout(int index, QLayout *layout, int stretch = 0)
    { m_mainLayout->insertLayout(index, layout, stretch); }
    void insertItem(int index, QLayoutItem *item)
    { m_mainLayout->insertItem(index, item); }

    int spacing() const
    { return m_mainLayout->spacing(); }
    void setSpacing(int spacing)
    { m_mainLayout->setSpacing(spacing); }

    bool setStretchFactor(QWidget *w, int stretch)
    { m_mainLayout->setStretchFactor(w, stretch); }
    bool setStretchFactor(QLayout *l, int stretch)
    { m_mainLayout->setStretchFactor(l, stretch); }
    void setStretch(int index, int stretch)
    { m_mainLayout->setStretch(index, stretch); }
    int stretch(int index) const
    { return m_mainLayout->stretch(index); }

    QLayoutItem *itemAt(int index) const
    { return m_mainLayout->itemAt(index); }
    QLayoutItem *takeAt(int index)
    { return m_mainLayout->takeAt(index); }
    int count() const
    { return m_mainLayout->count(); }

private:
    QVBoxLayout *m_mainLayout; // root
};

class CGridBoxWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CGridBoxWidget(QWidget *parent = nullptr)
        : QWidget(parent)
        , m_mainLayout(new QGridLayout(this))
    { this->setLayout(m_mainLayout); }

    void setHorizontalSpacing(int spacing)
    { m_mainLayout->setHorizontalSpacing(spacing); }
    int horizontalSpacing() const
    { return m_mainLayout->horizontalSpacing(); }
    void setVerticalSpacing(int spacing)
    { m_mainLayout->setHorizontalSpacing(spacing); }
    int verticalSpacing() const
    { return m_mainLayout->verticalSpacing(); }
    void setSpacing(int spacing)
    { m_mainLayout->setSpacing(spacing); }
    int spacing() const
    { return m_mainLayout->spacing(); }

    void setRowStretch(int row, int stretch)
    { m_mainLayout->setRowStretch(row, stretch); }
    void setColumnStretch(int column, int stretch)
    { m_mainLayout->setColumnStretch(column, stretch); }
    int rowStretch(int row) const
    { return m_mainLayout->rowStretch(row); }
    int columnStretch(int column) const
    { return m_mainLayout->columnStretch(column); }

    void setRowMinimumHeight(int row, int minSize)
    { m_mainLayout->setRowMinimumHeight(row, minSize); }
    void setColumnMinimumWidth(int column, int minSize)
    { m_mainLayout->setColumnMinimumWidth(column, minSize); }
    int rowMinimumHeight(int row) const
    { return m_mainLayout->rowMinimumHeight(row); }
    int columnMinimumWidth(int column) const
    { return m_mainLayout->columnMinimumWidth(column); }

    int columnCount() const
    { return m_mainLayout->columnCount(); }
    int rowCount() const
    { return m_mainLayout->rowCount(); }

    QRect cellRect(int row, int column) const
    { return m_mainLayout->cellRect(row, column); }

    inline void addWidget(QWidget *w)
    { m_mainLayout->addWidget(w); }
    void addWidget(QWidget *w, int row, int column, Qt::Alignment alignment = Qt::Alignment())
    { m_mainLayout->addWidget(w, row, column, alignment); }
    void addWidget(QWidget *w, int row, int column, int rowSpan, int columnSpan, Qt::Alignment alignment = Qt::Alignment())
    { m_mainLayout->addWidget(w, row, column, rowSpan, columnSpan, alignment); }
    void addLayout(QLayout *l, int row, int column, Qt::Alignment alignment = Qt::Alignment())
    { m_mainLayout->addLayout(l, row, column, alignment); }
    void addLayout(QLayout *l, int row, int column, int rowSpan, int columnSpan, Qt::Alignment alignment = Qt::Alignment())
    { m_mainLayout->addLayout(l, row, column, rowSpan, columnSpan, alignment); }

    void setOriginCorner(Qt::Corner corner)
    { m_mainLayout->setOriginCorner(corner); }
    Qt::Corner originCorner() const
    { return m_mainLayout->originCorner(); }

    QLayoutItem *itemAt(int index) const
    { return m_mainLayout->itemAt(index); }
    QLayoutItem *itemAtPosition(int row, int column) const
    { return m_mainLayout->itemAtPosition(row, column); }
    QLayoutItem *takeAt(int index)
    { return m_mainLayout->takeAt(index); }
    int count() const
    { return m_mainLayout->count(); }

    void addItem(QLayoutItem *item, int row, int column, int rowSpan = 1, int columnSpan = 1, Qt::Alignment alignment = Qt::Alignment())
    { return m_mainLayout->addItem(item, row, column, rowSpan, columnSpan, alignment); }

private:
    QGridLayout *m_mainLayout; // root
};


#endif // CBOXWIDGET_H
