#include "Cancer.h"

cancerData::cancerData(std::string country, float rate)
{
    this->mCancerRate = rate;
   this-> mCountry = country;

    std::cout<<"country: "<< mCountry<<std::endl;
    std::cout<<"cancerRate: "<< mCancerRate<<std::endl;
    
}
cancerData::cancerData()
{

}

void cancerData::setCountry(std::string newCountry)
{
    this-> mCountry = newCountry;
}
void cancerData::setCancerRate(float newRate)
{
    this-> mCancerRate = newRate;
}

std::string cancerData::getCountry(void)
{
    return this->mCountry;
}
float cancerData::getCancerRate(void)
{
    return this->mCancerRate;
}

bool & operator >(cancerData & c1, cancerData &c2)
{
    bool result;
    if(c1.getCountry() > c2.getCountry())
    {
        result = true;
    }
    else
        result = false;
    return result;
}

bool & operator <(cancerData & c1, cancerData &c2)
{
    bool result;
    if(c1.getCountry() < c2.getCountry())
    {
        result = true;
    }
    else
        result = false;
    return result;
}

bool & operator ==(cancerData & c1, cancerData &c2)
{
    bool result;
    if(c1.getCountry() == c2.getCountry())
    {
        result = true;
    }
    else
        result = false;
    return result;
}