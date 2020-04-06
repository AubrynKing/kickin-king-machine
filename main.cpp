#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include "AVLTemplate.h"
#include "Cancer.h"


int main(void)
{
    std::string line;
   AVL<cancerData> t;
    //women only
    std::ifstream infwomen ("womencancerdata2018.csv");
    if(infwomen.is_open())
    {

        while(getline(infwomen, line))
        {
            std::vector <std::string> tokens;
            std::stringstream strings(line);
            std::string temp;
            while(getline(strings, temp,','))
            {
                tokens.push_back(temp);
                //std::cout<<"-"<<temp<<std::endl;
            }
            
            std::string country = tokens[0];
            float rate = stof(tokens[1]);
            //std::cout<<country<<std::endl;
            //std::cout<<"-"<<rate<<std::endl;

            //make cancerData objects
            cancerData c= cancerData(country, rate); 
            t.insert(c);
            AVLNode<cancerData> n = AVLNode(c);
            
        }
        infwomen.close();
    }
    else
        std::cout<<"women not open"<<std::endl;

    //men only
    std::ifstream infmen ("mencancerdata2018.csv");
    if(infmen.is_open())
    {
        std::cout<<"men open"<<std::endl;
        while(getline(infmen, line))
        {
            //std::cout<<line<<std::endl;
        }
        infmen.close();
    }
    else
        std::cout<<"men not open"<<std::endl;

    //both
    std::ifstream infboth ("bothcancerdata2018.csv");
    if(infboth.is_open())
    {
        std::cout<<"both open"<<std::endl;
        while(getline(infboth, line))
        {
            //std::cout<<line<<std::endl;
        }
        infboth.close();
    }
    else
        std::cout<<"both not open"<<std::endl;

    //string parsing to make trees
   return 0;
}