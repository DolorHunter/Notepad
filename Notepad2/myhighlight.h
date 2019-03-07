#ifndef MYHIGHLIGHT_H
#define MYHIGHLIGHT_H

#pragma once

#include <QSyntaxHighlighter>
#include <QTextFormat>
#include <QRegularExpression>
#include <QTextCharFormat>
#include <QTextDocument>
#include <qtextcursor.h>
#include <qhash.h>
#include <qvector.h>
#include <qregexp.h>
#include <qcolor.h>
#include <qstring.h>
#include "bloomfilter.h"

class QTextDocument;

class myHighLight : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    myHighLight(QTextDocument *parent = nullptr);

    // judge if the word is existing in the bloom filter
    bool isKeyExisted(QString key);

protected:
   // highlight the keyword block on TextEditor
   void highlightBlock(const QString &text) override;

private:
    QRegExp *rule;
    QTextCharFormat format;

    BloomFilter BF;
};

#endif // MYHIGHLIGHT_H
