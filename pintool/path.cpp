#include "path.h"

namespace pintool
{
namespace path
{

std::string filename(const std::string& path)
{
    const std::string::size_type path_delimiter_pos = path.find_last_of("/\\");
    const std::string::size_type file_name_pos = (path_delimiter_pos == path.npos) ? 0 : path_delimiter_pos + 1;

    return path.substr(file_name_pos);
}

std::string filename(const IMG& img)
{
    if (!IMG_Valid(img)) {
        return std::string();
    }

    const std::string& image_name = IMG_Name(img);

    return filename(image_name);
}

} // namespace path
} // namespace pintool