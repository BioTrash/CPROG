#include <string>
#include <map>

struct PictureData{
    int width, height;
    unsigned int* pixels;
};

class Picture{
    public:
        Picture(std::string filename){
            data = new PictureData();
            data->width = 100;
            data->height = 200;
            data->pixels = new unsigned int[data->width*data->height];
            counts[data] = 1;
        }

        Picture(const Picture& other){
            data = new PictureData();
            data = other.data;
            counts[data] = 1;
        }

        const Picture& operator=(const Picture& other){
            if(this->data != other.data){
                delete [] data->pixels;
                delete data;
                data = new PictureData();
                data->width = other.data->width;
                data->height = other.data->height;
                data->pixels = new unsigned int[other.data->width*other.data->height];
                counts[data] = 1;
            }

            return *this;
        }

        ~Picture(){ delete [] data->pixels; delete data; }
    private:
        PictureData* data;
        static std::map<PictureData*, int> counts;
};

int main(){

}