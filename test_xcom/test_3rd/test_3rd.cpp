#include "xc_var.h"
#include "xc_string.h"
#include <string>

int main()
{
    int size = sizeof(std::string);
    size = sizeof(xcom::xc_string);
    return 0;
}
