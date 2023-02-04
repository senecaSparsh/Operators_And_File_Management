#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>
#include <string>
#include <fstream>
#include "Numbers.h"
using namespace std;
namespace sdds {


    Numbers::Numbers() {
        setEmpty();
        m_isOriginal = false;
    }

    Numbers::Numbers(const char* filename) {
        setEmpty();
        m_isOriginal = true;
        setFilename(filename);
        m_numCount = numberCount();
        if (m_numCount == 0 || !load()) {
            deallocate();
            setEmpty();
            m_isOriginal = false;
        }
    }

    Numbers::Numbers(const Numbers& num)
    {
        setEmpty();
        this->m_isOriginal = false;

        *this = num;
      
    }

    Numbers& Numbers::operator=(const Numbers& num)
    {
        if (this != &num) {
            delete[] m_numbers;
            m_numbers = nullptr;

            setEmpty();

            m_isOriginal = false;
            m_numbers = new double[num.m_numCount];

            for (int i = 0; i < num.m_numCount; i++) {
                m_numbers[i] = num.m_numbers[i];
            }
        }
        else {
            std::cout << "It's a self copy" << std::endl;
        }
        
        return *this;
    }

   

    Numbers Numbers::operator+() const
    {
        Numbers temp(*this);
        temp.sort(true);
        return temp;
    }

    Numbers Numbers::operator-() const
    {
        
        Numbers temp(*this);
        temp.sort(false);
        return temp;
    }

    Numbers& Numbers::operator+=(const double num)
    {
        if (!isEmpty()) {
            double* temp{};

            temp = new double[m_numCount + 1];
            for (int i = 0; i < m_numCount; i++) {
                temp[i] = m_numbers[i];
            }
            m_numCount++;
            temp[m_numCount] = num;
            delete[] m_numbers;
            m_numbers = temp;
        }
        return *this;
    }

    Numbers::~Numbers() {
        save();
        deallocate();
    }

    bool Numbers::isEmpty() const {
        return m_numbers == nullptr;
    }

    void Numbers::setEmpty() {
        m_numbers = nullptr;
        m_filename = nullptr;
        m_numCount = 0;
    }

    void Numbers::deallocate() {
        delete[] m_filename;
        delete[] m_numbers;
    }

    void Numbers::setFilename(const char* filename) {
        delete[] m_filename;
        m_filename = new char[strlen(filename) + 1];
        strcpy(m_filename, filename);
    }

    

    Numbers& Numbers::sort(bool ascending)
    {
        double temp{};
        if (ascending) {
            for (int i = m_numCount - 1; i > 0; i--) {
                for (int j = 0; j < i; j++) {
                    if (m_numbers[j] > m_numbers[j + 1]) {
                        temp = m_numbers[j];
                        m_numbers[j] = m_numbers[j + 1];
                        m_numbers[j + 1] = temp;
                    }
                }

            }
        }
        else {
            for (int i = m_numCount - 1; i > 0; i--) {
                for (int j = 0; j < i; j++) {
                    if (m_numbers[j] < m_numbers[j + 1]) {
                        temp = m_numbers[j];
                        m_numbers[j] = m_numbers[j + 1];
                        m_numbers[j + 1] = temp;
                    }
                }

            }
        }
        return *this;
    }



  

    

    std::ostream& Numbers::display(std::ostream& ostr) const
    {
        if (isEmpty()) {
            ostr << "Empty list" << endl;

        }
        else {
            ostr << "=========================" << endl;
            if (m_isOriginal) {
                ostr << "=========================" << endl;
            }
            else {
                ostr << "*** COPY ***" << endl;
            }

            for (int i = 0; i < m_numCount; i++) {
                ostr << m_numbers[i] << ", ";
            }
            ostr << endl;
            ostr << "-------------------------" << endl;
            ostr << "-------------------------" << endl;
            ostr << "Total of " << m_numCount << " number(s)" << endl;
            ostr << "Largest number:  " << max() << endl;
            ostr << "Smallest number:  " << min() << endl;
            ostr << "Average:  " << average() << endl;
            ostr << "=========================";

        }
        return ostr;
    }

    double Numbers::average() const {
        double aver = 0.0;
        if (!isEmpty()) {
            for (int i = 0; i < m_numCount; i++)
                aver += m_numbers[i];
            aver = aver / m_numCount;
        }
        return aver;
    }

    double Numbers::min() const {
        double minVal = 0.0;
        if (!isEmpty()) {
            minVal = m_numbers[0];
            for (int i = 1; i < m_numCount; i++)
                if (minVal > m_numbers[i]) minVal = m_numbers[i];
        }
        return minVal;
    }
    int Numbers::numberCount() const
    {
        ifstream fptr(m_filename);
        char x{};
        int noOfLine{};

        if (fptr.is_open()) {

            while (!fptr.fail()) {

                x = fptr.get();

                if (x == '\n') {
                    noOfLine++;
                }
            }
        }
        return noOfLine;
    }
    bool Numbers::load()
    {
        int i = 0;
        bool flag = false;

        if (m_numCount > 0) {
            delete[] m_numbers;
            m_numbers = nullptr;
            m_numbers = new double[m_numCount];


            ifstream fptr(m_filename);
            if (fptr.is_open()) {
                while (fptr >> m_numbers[i]) {

                    i++;
                }
                if (i == m_numCount) {
                    flag = true;
                }
            }
        }


        return flag;
    }
    void Numbers::save()
    {
       
        if (m_isOriginal && !isEmpty()) {
            ofstream file(m_filename);

            if (file.is_open()) {
                for (int i = 0; i < m_numCount; i++) {
                    file << m_numbers[i] << "\n";
                }
            }
            file.close();

        }
    }
    double Numbers::max() const {
        double maxVal = 0.0;
        if (!isEmpty()) {
            maxVal = m_numbers[0];
            for (int i = 1; i < m_numCount; i++)
                if (maxVal < m_numbers[i]) maxVal = m_numbers[i];
        }
        return maxVal;
    }


    std::ostream& operator<<(std::ostream& os, const Numbers& N)
    {
        return N.display(os);
    }

    std::istream& operator>>(std::istream& istr, Numbers& N)
    {
        double num{};
        istr >> num;
        if (num) {
            N += num;
        }
        return istr;
    }

}
