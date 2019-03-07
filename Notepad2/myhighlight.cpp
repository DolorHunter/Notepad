#include "myhighlight.h"
#include "bloomfilter.h"
#include <QDebug>
#include <iostream>

using namespace std;

myHighLight::myHighLight(QTextDocument *parent)
    :QSyntaxHighlighter (parent)
{
    //find each word
    rule = new QRegExp("(\\b)(\\w+)(\\b)");

    format.setForeground(Qt::blue);
    format.setFontWeight(QFont::Bold);

    initialBitFilter(BF);                               //initial bitFilter
    importKeyWords(BF);                                 //import key words to bitFilter
    initialBloomFilter(BF);                             //initial the BloomFilter
    creatBloomFilter(BF);                               //creat the BloomFilter;

    ///[test] All Pass!!
    //prtFilter(BF);//[test]
    //prtKeyWords(BF);///[test]
    //cout<<keyExistInBitFilter(BF, "asm");//[test]keyword
    //cout<<keyExistInBitFilter(BF, "aaa");//[test]not a keyword
    //cout << isKeyExisted("asm") << endl;
    //cout << isKeyExisted("aaa") << endl;
}

bool myHighLight::isKeyExisted(QString key) {
    return keyExistInBitFilter(BF, (char*)key.toStdString().data());
}


void myHighLight::highlightBlock(const QString &text) {
    int index = rule->indexIn(text);
    while(index >= 0)
    {
        int length = rule->matchedLength();
        if(isKeyExisted(text.mid(index, length)))
        {
            setFormat(index, length, format);
        }
        index = rule->indexIn(text, index + length);
    }
}
