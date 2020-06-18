#include "Date.h"

int get_number_from_stringdate(string& str)
{
    int position_point = str.find('.');
    if (position_point != -1)
    {
        string tmp_substr = str.substr(0, position_point);
        str.erase(0, position_point + 1);
        return atoi(tmp_substr.c_str());
    }
    return 0;
}
