#ifndef SDDS_NUMBERS_H_
#define SDDS_NUMBERS_H_
#include <iostream>
#include <fstream>
namespace sdds {
    class Numbers {
        double* m_numbers{};
        char* m_filename{};
        bool m_isOriginal;
        int m_numCount;
        bool isEmpty()const;
        void setEmpty();
        void deallocate();
        void setFilename(const char* filename);
        Numbers& sort(bool ascending);
        bool load();
        void save();
    public:
        Numbers();
        Numbers(const char* filename);
        Numbers(const Numbers& num);

        Numbers& operator=(const Numbers& num);
       
        Numbers operator+()const;
        Numbers operator-()const;
        Numbers& operator+=(const double num);

        std::ostream& display(std::ostream& ostr) const;
        double average()const;
        double max()const;
        double min()const;
        int numberCount()const;
        ~Numbers();
    };
    std::ostream& operator<<(std::ostream& os, const Numbers& N);
    std::istream& operator>>(std::istream& istr, Numbers& N);
}
#endif // !SDDS_NUMBERS_H_

