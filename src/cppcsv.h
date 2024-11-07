#include <iostream>
#include <vector>
#include <fstream>
#include <initializer_list>

class CSVFile {
    private:
        std::ofstream file;
        std::string sep;

    public:
        CSVFile(std::string path, std::string sep = ",") {
            this->sep = sep;
            this->open(path);
        }

        bool open(std::string filename){
            file.open(filename);
            return true;
        }

        template <typename T>
        void write_line(T elem) {
            write_elem(elem);
            write_endl();
            file.flush();
        }

        template <typename T, typename... Args>
        void write_line(T first, Args... args) {
            write_elem(first);
            write_sep();
            write_line(args...);
        }

        template<typename T> void write_vector(std::vector<T> vec) {
            typename std::vector<T>::iterator it = vec.begin();
            write_elem(*it);
            it++;
            for(; it != vec.end(); it++) {
                write_sep();
                write_elem(*it);
            }
            write_endl();
            file.flush();
        }

        template<typename T> void write_elem(T elem) {
            file << elem;
        }

        void write_sep() {
            file << sep;
        }
        void write_endl() {
            file << std::endl;
            file.flush();
        }

        bool close(){
            file.close();
            return true;
        }
};