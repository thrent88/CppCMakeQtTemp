#ifndef JSONEDITORWIDGET_H
#define JSONEDITORWIDGET_H

#include <QWidget>
#include <QTreeWidgetItem>
#include <QJsonDocument>


namespace Ui {
class JsonEditorWidget;
}

class JsonEditorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit JsonEditorWidget(QWidget *parent = nullptr);
    ~JsonEditorWidget();

    void loadJaon(const QString& json);

    QString saveJson();

private:
    QJsonValue string_to_jsonvalue(const QString& text);
    void parse_json_value(const QJsonValue& json_value, QTreeWidgetItem* parent);
    void update_tree_widget_by_json();
    void parse_tree_widget_value(const QTreeWidgetItem* item, QJsonArray& json_array);
    void parse_tree_widget_value(const QTreeWidgetItem* item, QJsonObject& json_obj);
    void tree_widget_to_json();

private slots:
    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

private:
    Ui::JsonEditorWidget *ui;

    QString _current_json_filename;
    QJsonDocument _current_json_doc;
};

#endif // JSONEDITORWIDGET_H
