#include<simplecpp>
#include<fstream>

void update_log (char argName[], double argTime) {
    fstream f("log.txt" , ios::app);
    f << argName << '\t' << argTime << '\n';
}

