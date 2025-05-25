#include "view/component/JsonEditorWidget.h"

#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QInputDialog>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QStack>

#include "./ui_JsonEditorWidget.h"

JsonEditorWidget::JsonEditorWidget(QWidget *parent)
    : QWidget(parent)
      , ui(new Ui::JsonEditorWidget) {
    ui->setupUi(this);
    ui->treeWidget->expandAll();
}

JsonEditorWidget::~JsonEditorWidget() {
    delete ui;
}

void JsonEditorWidget::loadJaon(const QString &json) {
    ui->treeWidget->clear();

    QString text_data = json;
    _current_json_doc = QJsonDocument::fromJson(QByteArray(text_data.toStdString().c_str()));

    update_tree_widget_by_json();
}

QString JsonEditorWidget::saveJson() {
    QTextStream text_stream;
    text_stream << _current_json_doc.toJson();
    QString text_data = text_stream.readAll();
    return text_data;
}


QJsonValue JsonEditorWidget::string_to_jsonvalue(const QString &text) {
    if (text == tr("true")) {
        return QJsonValue(true);
    } else if (text == tr("false")) {
        return QJsonValue(false);
    } else if (text == tr("null")) {
        return QJsonValue();
    } else {
        if (text.size() == QVariant(text.toDouble()).toString().size()) {
            return QJsonValue(text.toDouble());
        } else {
            return QJsonValue(text);
        }
    }
    return QJsonValue(text);
}

void JsonEditorWidget::parse_json_value(const QJsonValue &json_value, QTreeWidgetItem *parent) {
    if (json_value.isArray()) {
        QTreeWidgetItem *child = new QTreeWidgetItem(QStringList(tr("[Array]")));
        parent->addChild(child);
        auto json_array = json_value.toArray();
        for (auto idx = 0; idx < json_array.size(); ++idx) {
            parse_json_value(json_array[idx], child);
        }
    } else if (json_value.isObject()) {
        QTreeWidgetItem *child = new QTreeWidgetItem(QStringList(tr("{Object}")));
        parent->addChild(child);
        auto json_obj = json_value.toObject();
        QStringList keys = json_obj.keys();
        for (auto idx = 0; idx < keys.size(); ++idx) {
            QTreeWidgetItem *next_child = new QTreeWidgetItem(QStringList(keys[idx]));
            child->addChild(next_child);
            parse_json_value(json_obj.take(keys[idx]), next_child);
        }
    } else if (json_value.isBool()) {
        QTreeWidgetItem *child = new QTreeWidgetItem(QStringList(QString(json_value.toBool() ? "true" : "false")));
        parent->addChild(child);
    } else if (json_value.isDouble()) {
        QTreeWidgetItem *child = new QTreeWidgetItem(QStringList(QVariant(json_value.toDouble()).toString()));
        parent->addChild(child);
    } else if (json_value.isString()) {
        QTreeWidgetItem *child = new QTreeWidgetItem(QStringList(json_value.toString()));
        parent->addChild(child);
    } else if (json_value.isNull()) {
        QTreeWidgetItem *child = new QTreeWidgetItem(QStringList(tr("null")));
        parent->addChild(child);
    }
    return;
}

void JsonEditorWidget::update_tree_widget_by_json() {
    QJsonDocument cur_json_doc = _current_json_doc;
    if (cur_json_doc.isArray()) {
        QTreeWidgetItem *item = new QTreeWidgetItem(QStringList(tr("#[Array]")));
        ui->treeWidget->addTopLevelItem(item);
        auto json_array = cur_json_doc.array();
        for (auto idx = 0; idx < json_array.size(); ++idx) {
            parse_json_value(json_array[idx], item);
        }
    } else if (cur_json_doc.isObject()) {
        QTreeWidgetItem *item = new QTreeWidgetItem(QStringList(tr("#{Object}")));
        ui->treeWidget->addTopLevelItem(item);
        auto json_obj = cur_json_doc.object();
        QStringList keys = json_obj.keys();
        for (auto idx = 0; idx < keys.size(); ++idx) {
            QTreeWidgetItem *child = new QTreeWidgetItem(QStringList(keys[idx]));
            item->addChild(child);
            parse_json_value(json_obj.take(keys[idx]), child);
        }
    } else if (cur_json_doc.isEmpty()) {
        QMessageBox::warning(this, tr("Json file empty"), tr("Json file is empty"));
    } else if (cur_json_doc.isNull()) {
        QMessageBox::warning(this, tr("Json file null"), tr("Json file is null"));
    }
    return;
}

void JsonEditorWidget::parse_tree_widget_value(const QTreeWidgetItem *item, QJsonArray &json_array) {
    int child_count = item->childCount();
    for (int i = 0; i < child_count; ++i) {
        QTreeWidgetItem *child_item = item->child(i);
        QString text = child_item->text(0);
        if (child_item->childCount() == 0) {
            json_array.append(string_to_jsonvalue(text));
        } else {
            if (text == tr("[Array]")) {
                QJsonArray ja;
                parse_tree_widget_value(child_item, ja);
                json_array.append(ja);
            } else if (text == tr("{Object}")) {
                QJsonObject jo;
                parse_tree_widget_value(child_item, jo);
                json_array.append(jo);
            }
        }
    }
    return;
}

void JsonEditorWidget::parse_tree_widget_value(const QTreeWidgetItem *item, QJsonObject &json_obj) {
    int child_count = item->childCount();
    QString key = item->text(0);
    for (int i = 0; i < child_count; ++i) {
        QTreeWidgetItem *child_item = item->child(i);
        QString text = child_item->text(0);
        if (child_item->childCount() == 0) {
            json_obj[key] = string_to_jsonvalue(text);
        } else {
            key = text;
            int next_child_count = child_item->childCount();
            for (int j = 0; j < next_child_count; ++j) {
                QTreeWidgetItem *next_child_item = child_item->child(j);
                QString next_child_text = next_child_item->text(0);
                if (next_child_text == tr("[Array]")) {
                    QJsonArray ja;
                    parse_tree_widget_value(next_child_item, ja);
                    json_obj.insert(key, ja);
                } else if (next_child_text == tr("{Object}")) {
                    QJsonObject jo;
                    parse_tree_widget_value(next_child_item, jo);
                    json_obj.insert(key, jo);
                } else {
                    json_obj[key] = string_to_jsonvalue(next_child_text);
                }
            }
        }
    }
    return;
}

void JsonEditorWidget::tree_widget_to_json() {
    QJsonDocument json_doc;
    QTreeWidgetItem *item = ui->treeWidget->takeTopLevelItem(0);
    if (item != nullptr) {
        QString text = item->text(0);
        if (text == tr("#[Array]")) {
            QJsonArray json_array;
            parse_tree_widget_value(item, json_array);
            json_doc.setArray(json_array);
        } else if (text == tr("#{Object}")) {
            QJsonObject json_obj;
            parse_tree_widget_value(item, json_obj);
            json_doc.setObject(json_obj);
        }
    }
    _current_json_doc.swap(json_doc);

    return;
}

void JsonEditorWidget::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column) {
    QString item_text = item->text(column);
    QString text = QInputDialog::getText(this, tr("change value"), item_text, QLineEdit::Normal, item_text);
    if (!text.isEmpty() && item_text != tr("#{Object}") && item_text != tr("#[Array]") &&
        item_text != tr("{Object}") && item_text != tr("[Array]")) {
        item->setText(column, text);
    }
}
