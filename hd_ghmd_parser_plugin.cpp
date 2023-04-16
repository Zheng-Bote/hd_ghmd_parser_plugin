/**
 * @file hd_ghmd_parser_plugin.cpp
 * @author ZHENG Robert (www.robert.hase-zheng.net)
 * @brief Github Markdonw parser plugin for header_docu
 * @details parse Github Markdown header
 * @version 0.2.0
 * @date 2023-04-16
 *
 * @copyright Copyright (c) ZHENG Robert 2023
 *
 */

#include "hd_ghmd_parser_plugin.h"

Hd_ghmd_parser_plugin::Hd_ghmd_parser_plugin(QObject *parent)
{
    Q_UNUSED(parent);
    qInfo() << "Plugin Constructor";
}

Hd_ghmd_parser_plugin::~Hd_ghmd_parser_plugin()
{
    qInfo() << "Plugin Deconstructed";
}

void Hd_ghmd_parser_plugin::test(QString name)
{
    qInfo() << "Test from Plugin: " << name;
}

QString Hd_ghmd_parser_plugin::getName()
{
    return PLUGIN_SHORTNAME;
}

QString Hd_ghmd_parser_plugin::getVersion()
{
    return PLUGIN_NAME + "-v" + PLUGIN_VERSION;
}

// #####

QString Hd_ghmd_parser_plugin::parseLine(QString text)
{
    QRegularExpression searchTitle("TITLE:");
    QRegularExpression searchBrief("BRIEF:");
    QRegularExpression searchDesc("DESC:");
    QRegularExpression searchSource("SOURCE:");
    QRegularExpression searchSyntax("SYNTAX:");
    QRegularExpression searchReturn("RETURN:");
    QRegularExpression searchHistory("HISTORY:");

    QRegularExpressionMatch matchSearchStr = searchTitle.match(text);
    if(matchSearchStr.hasMatch()) {
        text = "\n- - -\n## " + text;
        return text;
    }

    matchSearchStr = searchBrief.match(text);
    if(matchSearchStr.hasMatch()) {
        text = "### " + text;
        return text;
    }

    matchSearchStr = searchDesc.match(text);
    if(matchSearchStr.hasMatch()) {
        text = "### " + text;
        return text;
    }

    matchSearchStr = searchSource.match(text);
    if(matchSearchStr.hasMatch()) {
        text = "### " + text;
        return text;
    }

    matchSearchStr = searchSyntax.match(text);
    if(matchSearchStr.hasMatch()) {
        text = "### " + text;
        return text;
    }

    matchSearchStr = searchReturn.match(text);
    if(matchSearchStr.hasMatch()) {
        text = "### " + text;
        return text;
    }

    matchSearchStr = searchHistory.match(text);
    if(matchSearchStr.hasMatch()) {
        text = "### " + text;
        return text;
    }

    return("> " + text);
}

void Hd_ghmd_parser_plugin::parseFile(QMap<QString, QString> &mapParseKeys, QString pathToFile)
{
     qInfo() << "GH_markdown ParserPlugin::parseFile: " << pathToFile;

    QFile file(pathToFile);
    QString searchBegin = QRegularExpression::escape("/*");
    QRegularExpression reBegin(searchBegin);
    QString searchEnd = QRegularExpression::escape("*/");
    QRegularExpression reEnd(searchEnd);

    QString outText;
    //    QTextStream out(stdout);

    // QFile file2("/home/zb_bamboo/TEMP/ESP32_BME680_Webserver_MQTT-Client/rz_version.h");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream in(&file);
    QString line;
    bool isComment = false;

    while (in.readLineInto(&line)) {
        //out << line << "\n";
        QRegularExpressionMatch matchStart = reBegin.match(line);
        QRegularExpressionMatch matchEnd = reEnd.match(line);
        if(matchStart.hasMatch()) {
            isComment = true;
            continue;
        }
        if(matchEnd.hasMatch()) {
            isComment = false;
            break;
        }
        if(isComment) {
            if(line.isEmpty()) {
                // todo
            }
            else {
                //                out << line << "\n";
                outText.append(Hd_ghmd_parser_plugin::parseLine(line));
            }
            outText.append("\n");
        }
        else {
            break;
        }
    }

    file.close();

    // outText
    qInfo() << "##### outText #####\n";
    qInfo() << outText;
}

