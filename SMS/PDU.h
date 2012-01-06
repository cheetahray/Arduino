#ifndef PDU_H
#define PDU_H

#define max_number  64
#define max_number_type  1024
#define max_smsc  64
#define max_date 32
#define max_time  32
#define max_udh_data  512
#define max_udh_type  512
#define max_err  1024
#define maxsms_binary  140
#define max_message  maxsms_binary<<2
#define validity_period  255
#define max_pdu  160

class PDU {
public:
    enum NumerFormat {
        NF_UNKNOWN = 129,
        NF_INTERNATIONAL = 145,
        NF_INATIONAL = 161
    };

    enum Alphabet {
        GSM = -1,
        ISO = 0,
        BINARY = 1,
        UCS2 = 2
    };

    // Constructors/Destructors
    PDU();
    PDU(const char *pdu);
    ~PDU();

    // Getters
    inline const char* getPDU() const { return m_pdu; }
    inline const char* getSMSC() const { return m_smsc; }
    inline const char* getNumber() const { return m_number; }
    inline const char* getNumberType() const { return m_number_type; }
    inline const char* getDate() const { return m_date; }
    inline const char* getTime() const { return m_time; }
    inline const char* getUDHType() const { return m_udh_type; }
    inline const char* getUDHData() const { return m_udh_data; }
    inline const char* getMessage() const { return m_message; }
    inline const char* getError() const { return m_err; }
    inline const int getMessageLen() const { return m_message_len; }
    /*
    // Setters
    void setMessage(const char* message, const int message_len = -1);
    void setSMSC(const char* smsc);
    void setNumber(const char* number);
    void setAlphabet(const Alphabet alphabet);
    */
    //
    bool parse();
    void generateII();

    // iconv
    //int convert(const char *tocode, const char *fromcode);
private:
    char m_pdu[max_pdu];
    char* m_pdu_ptr;
    char m_message[max_message];
    int m_message_len;
    char m_smsc[max_smsc];
    char m_number[max_number];
    char m_number_type[max_number_type];
    NumerFormat m_number_fmt;
    char m_date[max_date];
    char m_time[max_time];
    char m_udh_type[max_udh_type];
    char m_udh_data[max_udh_data];
    char m_err[max_err];
    bool m_with_udh;
    bool m_report;
    bool m_is_statusreport;
    int m_replace;
    int m_alphabet;
    bool m_flash;
    const char* m_mode;
    int m_validity;
    int m_system_msg;
    int m_replace_msg;

    void reset();
    bool parseSMSC();
    bool parseDeliver();
    bool parseStatusReport();
    int explainAddressType(const char *octet_char, int octet_int);
};

#endif