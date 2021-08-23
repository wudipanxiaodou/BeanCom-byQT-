#ifndef RSA_H
#define RSA_H

#include <QString>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

#define BEGIN_RSA_PUBLIC_KEY  "BEGIN RSA PUBLIC KEY"
#define BEGIN_PUBLIC_KEY      "BEGIN PUBLIC KEY"
#define KEY_LENGTH            1024

class BeanComRSA
{
public:
    BeanComRSA();
    ~BeanComRSA();

    bool createRSAKey(QString& strPubKey, QString& strPriKey);

    QString BeanComRSAPriEncrypt(const QString& strPlainData, const QString& strPriKey);

    QString BeanComRSAPubDecrypt(const QString& strDecryptData, const QString& strPubKey);

    QString BeanComRSAPubEncrypt(const QString& strPlainData, const QString& strPubKey);

    QString BeanComRSAPriDecrypt(const QString& strDecryptData, const QString& strPriKey);

};

BeanComRSA::BeanComRSA()
{

}

BeanComRSA::~BeanComRSA()
{

}

bool BeanComRSA::createRSAKey(QString& strPubKey, QString& strPriKey)
{
    RSA* pRsa = RSA_generate_key(KEY_LENGTH, RSA_3, NULL, NULL);
    if (!pRsa) {
        return false;
    }

    BIO* pPriBio = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPrivateKey(pPriBio, pRsa, NULL, NULL, 0, NULL, NULL);
    BIO* pPubBio = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPublicKey(pPubBio, pRsa);

    //获取长度
    size_t nPriKeyLen = BIO_pending(pPriBio);
    size_t nPubKeyLen = BIO_pending(pPubBio);

    //密钥对读取到字符串
    char* pPriKey = new char[nPriKeyLen];
    char* pPubKey = new char[nPubKeyLen];
    BIO_read(pPriBio, pPriKey, nPriKeyLen);
    BIO_read(pPubBio, pPubKey, nPubKeyLen);

    //存储密钥对
    strPubKey = QByteArray(pPubKey, nPubKeyLen);
    strPriKey = QByteArray(pPriKey, nPriKeyLen);

    //内存释放
    RSA_free(pRsa);
    BIO_free_all(pPriBio);
    BIO_free_all(pPubBio);
    delete pPriKey;
    delete pPubKey;

    return true;
}

QString BeanComRSA::BeanComRSAPriEncrypt(const QString& strPlainData, const QString& strPriKey)
{
    QByteArray priKeyArry = strPriKey.toUtf8();
    uchar* pPriKey = (uchar*)priKeyArry.data();
    BIO* pKeyBio = BIO_new_mem_buf(pPriKey, strPriKey.length());
    if (pKeyBio == NULL) {
        return "";
    }

    RSA* pRsa = RSA_new();
    pRsa = PEM_read_bio_RSAPrivateKey(pKeyBio, &pRsa, NULL, NULL);
    if (pRsa == NULL) {
        BIO_free_all(pKeyBio);
        return "";
    }

    int nLen = RSA_size(pRsa);
    char* pEncryptBuf = new char[nLen];
    memset(pEncryptBuf, 0, nLen);

    //加密
    QByteArray plainDataArry = strPlainData.toUtf8();
    int nPlainDataLen = plainDataArry.length();
    uchar* pPlainData = (uchar*)plainDataArry.data();
    int nSize = RSA_private_encrypt(nPlainDataLen,
        pPlainData,
        (uchar*)pEncryptBuf,
        pRsa,
        RSA_PKCS1_PADDING);

    QString strEncryptData = "";
    if (nSize >= 0) {
        QByteArray arry(pEncryptBuf, nSize);
        strEncryptData = arry.toBase64();
    }

    //释放内存
    delete pEncryptBuf;
    BIO_free_all(pKeyBio);
    RSA_free(pRsa);

    return strEncryptData;
}

QString BeanComRSA::BeanComRSAPubDecrypt(const QString& strDecryptData, const QString& strPubKey)
{
    QByteArray pubKeyArry = strPubKey.toUtf8();
    uchar* pPubKey = (uchar*)pubKeyArry.data();
    BIO* pKeyBio = BIO_new_mem_buf(pPubKey, strPubKey.length());
    if (pKeyBio == NULL) {
        return "";
    }

    RSA* pRsa = RSA_new();
    if (strPubKey.contains(BEGIN_RSA_PUBLIC_KEY)) {
        pRsa = PEM_read_bio_RSAPublicKey(pKeyBio, &pRsa, NULL, NULL);
    }
    else {
        pRsa = PEM_read_bio_RSA_PUBKEY(pKeyBio, &pRsa, NULL, NULL);
    }

    if (pRsa == NULL) {
        BIO_free_all(pKeyBio);
        return "";
    }

    int nLen = RSA_size(pRsa);
    char* pPlainBuf = new char[nLen];
    memset(pPlainBuf, 0, nLen);

    //解密
    QByteArray decryptDataArry = strDecryptData.toUtf8();
    decryptDataArry = QByteArray::fromBase64(decryptDataArry);
    int nDecryptDataLen = decryptDataArry.length();
    uchar* pDecryptData = (uchar*)decryptDataArry.data();
    int nSize = RSA_public_decrypt(nDecryptDataLen,
        pDecryptData,
        (uchar*)pPlainBuf,
        pRsa,
        RSA_PKCS1_PADDING);

    QString strPlainData = "";
    if (nSize >= 0) {
        strPlainData = QByteArray(pPlainBuf, nSize);
    }

    //释放内存
    delete pPlainBuf;
    BIO_free_all(pKeyBio);
    RSA_free(pRsa);

    return strPlainData;
}

QString BeanComRSA::BeanComRSAPubEncrypt(const QString& strPlainData, const QString& strPubKey)
{
    QByteArray pubKeyArry = strPubKey.toUtf8();
    uchar* pPubKey = (uchar*)pubKeyArry.data();
    BIO* pKeyBio = BIO_new_mem_buf(pPubKey, pubKeyArry.length());
    if (pKeyBio == NULL) {
        return "";
    }

    RSA* pRsa = RSA_new();
    if (strPubKey.contains(BEGIN_RSA_PUBLIC_KEY)) {
        pRsa = PEM_read_bio_RSAPublicKey(pKeyBio, &pRsa, NULL, NULL);
    }
    else {
        pRsa = PEM_read_bio_RSA_PUBKEY(pKeyBio, &pRsa, NULL, NULL);
    }

    if (pRsa == NULL) {
        BIO_free_all(pKeyBio);
        return "";
    }

    int nLen = RSA_size(pRsa);
    char* pEncryptBuf = new char[nLen];
    memset(pEncryptBuf, 0, nLen);

    //加密
    QByteArray plainDataArry = strPlainData.toUtf8();
    int nPlainDataLen = plainDataArry.length();
    uchar* pPlainData = (uchar*)plainDataArry.data();
    int nSize = RSA_public_encrypt(nPlainDataLen,
        pPlainData,
        (uchar*)pEncryptBuf,
        pRsa,
        RSA_PKCS1_PADDING);

    QString strEncryptData = "";
    if (nSize >= 0) {
        QByteArray arry(pEncryptBuf, nSize);
        strEncryptData = arry.toBase64();
    }

    //释放内存
    delete pEncryptBuf;
    BIO_free_all(pKeyBio);
    RSA_free(pRsa);

    return strEncryptData;
}

QString BeanComRSA::BeanComRSAPriDecrypt(const QString& strDecryptData, const QString& strPriKey)
{
    QByteArray priKeyArry = strPriKey.toUtf8();
    uchar* pPriKey = (uchar*)priKeyArry.data();
    BIO* pKeyBio = BIO_new_mem_buf(pPriKey, priKeyArry.length());
    if (pKeyBio == NULL) {
        return "";
    }

    RSA* pRsa = RSA_new();
    pRsa = PEM_read_bio_RSAPrivateKey(pKeyBio, &pRsa, NULL, NULL);
    if (pRsa == NULL) {
        BIO_free_all(pKeyBio);
        return "";
    }

    int nLen = RSA_size(pRsa);
    char* pPlainBuf = new char[nLen];
    memset(pPlainBuf, 0, nLen);

    //解密
    QByteArray decryptDataArry = strDecryptData.toUtf8();
    decryptDataArry = QByteArray::fromBase64(decryptDataArry);
    int nDecryptDataLen = decryptDataArry.length();
    uchar* pDecryptData = (uchar*)decryptDataArry.data();
    int nSize = RSA_private_decrypt(nDecryptDataLen,
        pDecryptData,
        (uchar*)pPlainBuf,
        pRsa,
        RSA_PKCS1_PADDING);

    QString strPlainData = "";
    if (nSize >= 0) {
        strPlainData = QByteArray(pPlainBuf, nSize);
    }

    //释放内存
    delete pPlainBuf;
    BIO_free_all(pKeyBio);
    RSA_free(pRsa);

    return strPlainData;
}

#endif 