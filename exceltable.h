#include <qqml.h>
#include <QAbstractTableModel>


class ExcelTable : public QAbstractTableModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_ADDED_IN_MINOR_VERSION(1)

private:

    Q_PROPERTY(QString textEdit READ getCurrentEditText WRITE setCurrentEditText NOTIFY textEditChanged)

    struct Cell
    {
        bool isSelected;
        QString text;
    };

    Cell* lastSelectedCell;

    QString currentEditText;

    int columns = 5;
    int rows = 5;

    QHash <QModelIndex, Cell> cells;


signals:
    void cellEdited(QString);
    void textEditChanged(QString);
public:

    QString getCurrentEditText();
    void setCurrentEditText(QString line);

    ExcelTable(QObject* = nullptr);

    QVariant data(const QModelIndex &index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;

    QStringList prepareForSave();

    QString calculate(QString str) const;

    Q_INVOKABLE void saveFile();

    Q_INVOKABLE void openFile();

    Q_INVOKABLE int rowCount(const QModelIndex& = QModelIndex()) const override;

    Q_INVOKABLE int columnCount(const QModelIndex& = QModelIndex()) const override;

    Q_INVOKABLE QStringList getHeader() const;

    Q_INVOKABLE void saveToCell(int row, int column, const QString string);

    Q_INVOKABLE QString getCellText(int row, int column) const;

    Q_INVOKABLE void addColumn();

    Q_INVOKABLE void addRow();

    Q_INVOKABLE void removeColumn();

    Q_INVOKABLE void removeRow();

    Q_INVOKABLE void selectCell(int row, int column);

    Q_INVOKABLE QString getLastCellText();

    Q_INVOKABLE void saveLastCellText();

};
