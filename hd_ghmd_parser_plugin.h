#ifndef HD_GHMD_PARSER_PLUGIN_H
#define HD_GHMD_PARSER_PLUGIN_H

#include <QObject>
#include <QtPlugin>
#include <QDebug>
#include <QString>

#include <QDir>
#include <QTextStream>
#include <QRegularExpression>

#include "rz_header_docu_plugins.h"

const QString PLUGIN_SHORTNAME = "gh_markdown";
const QString PLUGIN_NAME ="Github Markdown parser";
const QString PLUGIN_VERSION = "1.0.0";

class Hd_ghmd_parser_plugin: public QObject, public Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "net.hase-zheng.header_docu_plugin");
    Q_INTERFACES(Plugin);

public:
    explicit Hd_ghmd_parser_plugin(QObject *parent = nullptr);
    ~Hd_ghmd_parser_plugin();

private:
    QString parseLine(QString text);

signals:
public slots:

    // Plugin interface
public:
    void test(QString name) Q_DECL_OVERRIDE;
    QString getName() Q_DECL_OVERRIDE;
    QString getVersion() Q_DECL_OVERRIDE;

    void parseFile(QMap<QString, QString> &mapParseKeys, QString pathToFile) Q_DECL_OVERRIDE;
    void writeFile(QMap<QString, QString> mapParseKeys, QMap<QString, QString> mapFileAttribs, QString pathToFile) Q_DECL_OVERRIDE;
};

#endif // HD_GHMD_PARSER_PLUGIN_H
