#include "file.h"
#include "bloomfilter.h"

#define MAXLEN 875
        ///Console support Maximum 300 line for show
#define MAXKEYWORDS 295
#define MAXKEYLENGTH 100

using namespace std;

///[test]print filter for testing
void prtFilter(BloomFilter &BF){
    for(int i=0; i<MAXLEN; i++){
        if(BF.bitFilter[i]==0){
            cout << "0" << "\t";
        }
        else{
            cout << "1" <<"\t";
        }
    }
}

///[test]print Key Words for testing
void prtKeyWords(BloomFilter &BF){
    for(int i=0; i<200; i++){
        cout << BF.keyWords[i] << endl;
    }
}

//refresh keyWords[][] for other key words to import
void refresh_keyWords(BloomFilter &BF){
    for(int i=0; i<MAXKEYWORDS; i++){
        for(int j=0; j<MAXKEYLENGTH; j++){
            BF.keyWords[i][j]=0;
        }
    }
}

//import all key words of C/C++
void import_C_KeyWords(BloomFilter &BF){
    ReadFileToArray("C.txt", BF.keyWords);
}

//initial bitFilter
void initialBitFilter(BloomFilter &BF){
    for(int i=0; i<MAXLEN; i++){
        BF.bitFilter[i]=0;
    }
}

//import all key words of Languages
void importKeyWords(BloomFilter &BF){
    refresh_keyWords(BF);
    import_C_KeyWords(BF);//import C's key words
    /**!!if you gonna import more key words insert the func here!!**/
    ///prtKeyWords(BF);///[test]
    ///refresh_keyWords(BF);
}


// 1. BKDR Hash Function
int BKDRHash(char *str){
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;

    while (*str){
        hash = hash * seed + (*str++);
    }

    return (hash & 0x7FFFFFFF)%7000;
}

// 2. AP Hash Function
int APHash(char *str){
    unsigned int hash = 0;
    int i;

    for (i=0; *str; i++){
        if ((i & 1) == 0){
            hash ^= ((hash << 7) ^ (*str++) ^ (hash >> 3));
        }
        else{
            hash ^= (~((hash << 11) ^ (*str++) ^ (hash >> 5)));
        }
    }

    return (hash & 0x7FFFFFFF)%7000;
}

// 3. DJB Hash Function
int DJBHash(char *str){
    unsigned int hash = 5381;

    while (*str){
        hash += (hash << 5) + (*str++);
    }

    return (hash & 0x7FFFFFFF)%7000;
}

// 4. JS Hash Function
int JSHash(char *str){
    unsigned int hash = 1315423911;

    while (*str){
        hash ^= ((hash << 5) + (*str++) + (hash >> 2));
    }

    return (hash & 0x7FFFFFFF)%7000;
}

// 5. RS Hash Function
int RSHash(char *str){
    unsigned int b = 378551;
    unsigned int a = 63689;
    unsigned int hash = 0;

    while (*str){
        hash = hash * a + (*str++);
        a *= b;
    }

    return (hash & 0x7FFFFFFF)%7000;
}

// 6. SDBM Hash function
int SDBMHash(char *str){
    unsigned int hash = 0;

    while (*str){
        // equivalent to: hash = 65599*hash + (*str++);
        hash = (*str++) + (hash << 6) + (hash << 16) - hash;
    }

    return (hash & 0x7FFFFFFF)%7000;
}

// 7. PJW Hash function
int PJWHash(char *str){
    unsigned int BitsInUnignedInt = (unsigned int)(sizeof(unsigned int) * 8);
    unsigned int ThreeQuarters    = (unsigned int)((BitsInUnignedInt  * 3) / 4);
    unsigned int OneEighth        = (unsigned int)(BitsInUnignedInt / 8);
    unsigned int HighBits         = (unsigned int)(0xFFFFFFFF) << (BitsInUnignedInt - OneEighth);
    unsigned int hash             = 0;
    unsigned int test             = 0;

    while (*str)
    {
        hash = (hash << OneEighth) + (*str++);
        if ((test = hash & HighBits) != 0)
        {
            hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
        }
    }

    return (hash & 0x7FFFFFFF)%7000;
}

// 8. ELF Hash Function
int ELFHash(char *str){
    unsigned int hash = 0;
    unsigned int x    = 0;

    while (*str){
        hash = (hash << 4) + (*str++);
        if ((x = hash & 0xF0000000L) != 0){
            hash ^= (x >> 24);
            hash &= ~x;
        }
    }

    return (hash & 0x7FFFFFFF)%7000;
}

// 9. BKDR Hash Function(Modified v1)
int BKDRHashM1(char *str){
    unsigned int seed = 31; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;

    while (*str){
        hash = hash * seed + (*str++);
    }

    return (hash & 0x7FFFFFFF)%7000;
}

// 10. BKDR Hash Function(Modified v2)
int BKDRHashM2(char *str){
    unsigned int seed = 13131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;

    while (*str){
        hash = hash * seed + (*str++);
    }

    return (hash & 0x7FFFFFFF)%7000;
}

//return from 0 to 7000
int HashFunc(char *str, int h){
    switch(h){
    case 0:
        BKDRHash(str);
        break;
    case 1:
        APHash(str);
        break;
    case 2:
        DJBHash(str);
        break;
    case 3:
        JSHash(str);
        break;
    case 4:
        RSHash(str);
        break;
    case 5:
        SDBMHash(str);
        break;
    case 6:
        PJWHash(str);
        break;
    case 7:
        ELFHash(str);
        break;
    case 8:
        BKDRHashM1(str);
        break;
    case 9:
        BKDRHashM2(str);
        break;

    default:
        break;
    }
}

//judge a word if it's already in Filter
bool keyExistInBitFilter(BloomFilter &BF, char *str){
    for(int i=0; i<10; i++){
        int bit=HashFunc(str, i);
        ///cout << i<<"bit:"<<bit << endl;///[test]
        //judge (BF.bitFilter[hash/8] >> hash%8) %2 == 1
        if(!((BF.bitFilter[bit/8] >> bit%8) % 2)){
            return false;
        }
    }
    return true;
}

//import a key to BloomFilter
void importKeyToBloomFilter(BloomFilter &BF, char *str){
    if(keyExistInBitFilter(BF, str)){
        return;
    }
    for(int i=0; i<10; i++){
        int bit=HashFunc(str, i);
        if(!((BF.bitFilter[bit/8] >> bit%8)%2)){
            //switch No.Hash 0->1
            BF.bitFilter[bit/8]+=1 << bit%8;
        }
    }
}

//initial BloomFilter
void initialBloomFilter(BloomFilter &BF){
    for(int i=0; i<MAXLEN; i++){
        BF.bitFilter[i]=0;
    }
}

//using All Key Words to create a BloomFilter
void creatBloomFilter(BloomFilter &BF){
    char str[MAXKEYLENGTH]={0};
    for(int i=0; i<MAXKEYWORDS; i++){
        for(int j=0; j<MAXKEYLENGTH; j++){
            if(BF.keyWords[i][j]!=0){
                str[j] = BF.keyWords[i][j];
            }
        }
        ///cout << BF.keyWords[i]<<endl;///[test]
        ///cout <<i<< "str:"<<str<<endl;///[test]
        importKeyToBloomFilter(BF, str);
        for(int j=0; j<MAXKEYLENGTH; j++){
            str[j]=0;
        }
    }
}

