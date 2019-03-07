#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H

#pragma once

#define MAXLEN 875
        ///Console support Maximum 300 line for show
#define MAXKEYWORDS 295
#define MAXKEYLENGTH 100

//Struct of BloomFilter
typedef struct BloomFilter{
    char bitFilter[MAXLEN];                                     //safe Filter
    char keyWords[MAXKEYWORDS][MAXKEYLENGTH] = { 0 };           //safe Key Words
}BloomFilter;

//Hash function
int HashFunc(unsigned char *str, int bit);                                     //Hash function
int BKDRHash(unsigned char *str);                                     //BKDRHash function
int APHash(unsigned char *str);                                       //APHash function
int DJBHash(unsigned char *str);                                      //DJBHash function
int JSHash(unsigned char *str);                                       //JSHash function
int RSHash(unsigned char *str);                                       //RSHash function
int SDBMHash(unsigned char *str);                                     //SDBMHash function
int PJWHash(unsigned char *str);                                      //PJWHash function
int ELFHash(unsigned char *str);                                      //ELFHash function
int BKDRHashM1(unsigned char *str);                                   //BKDRHashM1 function
int BKDRHashM2(unsigned char *str);                                   //BKDRHashM2 function

void initialBitFilter(BloomFilter &BF);                               //initial bitFilter
void import_C_KeyWords(BloomFilter &BF, char *str);                   //import C's key words
void importKeyWords(BloomFilter &BF);                                 //import key words to bitFilter
bool keyExistInBitFilter(BloomFilter &BF, char *str);                 //judge a word if it's already in Filter
void importKeyToBloomFilter(BloomFilter &BF, char *str);              //import a key to BloomFilter
void initialBloomFilter(BloomFilter &BF);                             //initial the BloomFilter
void creatBloomFilter(BloomFilter &BF);                               //creat the BloomFilter

///[test]
void prtFilter(BloomFilter &BF);                                      //print Filter for testing
void prtKeyWords(BloomFilter &BF);                                    //print Key Words[][]for testing

#endif // BLOOMFILTER_H
