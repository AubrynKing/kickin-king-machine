#include <iostream>
#include <cstring>
class cancerData
{
    public:
    cancerData(std::string country, float rate);
    cancerData();

    std::string getCountry(void);
    float getCancerRate(void);
    
    void setCountry(std::string newCountry);
    void setCancerRate(float newRate);

    friend bool & operator >(cancerData & c1, cancerData &c2);
    friend bool & operator <(cancerData & c1, cancerData &c2);
    friend bool & operator ==(cancerData & c1, cancerData &c2);
    
    private:
    std::string mCountry;
    float mCancerRate;
};