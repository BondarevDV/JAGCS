#ifndef BASE_PRESENTER_H
#define BASE_PRESENTER_H

#define PROPERTY(x) # x
#define NAME(x) QString(PROPERTY(x))

#include <QPointer>

namespace presentation
{
    class BasePresenter: public QObject
    {
        Q_OBJECT

        Q_PROPERTY(QObject* view READ view WRITE setView NOTIFY viewChanged)

    public:
        explicit BasePresenter(QObject* parent = nullptr);

        QObject* view() const;

    public slots:
        void setView(QObject* view);

        void setViewProperty(const char* name, const QVariant& value);
        void setViewProperty(const QString& child, const char* name, const QVariant& value);

        void invokeViewMethod(const char* name);
        void invokeViewMethod(const char* name, const QVariant& arg);
        void invokeViewMethod(const char* name, const QVariant& arg1, const QVariant& arg2);

    signals:
        void viewChanged(QObject* view);

    protected:
        QVariant viewProperty(const char* name) const;

        virtual void connectView(QObject* view);
        virtual void disconnectView(QObject* view);

    private:
        QPointer<QObject> m_view;

        Q_DISABLE_COPY(BasePresenter)
    };
}

#endif // BASE_PRESENTER_H
