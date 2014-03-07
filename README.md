qmlwebmodelserver
=================

A server-side model server for QMLWeb.

QMLWeb (https://projects.kde.org/projects/playground/www/qmlweb) is a client-side only scripting approach that uses QML to create web pages. This is a simple REST-based model server (sends JSON with Qt-style model indexes) and supports various Qt models:

QSqlTableModel
QSqlQueryModel
QStringListModel

and a custom 
CsvModel

Status
======
The Q*models are complete for read access. Write is not yet implemented but it is easy to add.
THe CsvModel is still bing developed.

Usage
=====
The model server looks for .json files that defines the model source including database connection info. One model per json file. The provided sample.json gives a sample of all the models so far.


